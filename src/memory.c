#include "globals.h"

#include "memory.h"
#include "log.h"
#include "misc.h"               /* for removeFromTrailUntil() */

S_memory *cxMemory=NULL;
S_topBlock *s_topBlock;

jmp_buf s_memoryResize;

/* Memory types: */
char memory[SIZE_workMemory];
char tmpWorkMemory[SIZE_tmpWorkMemory];
int tmpWorkMemoryi = 0;

char ftMemory[SIZE_ftMemory];
int ftMemoryi = 0;


/* Inject the function to call when fatalErrors occur */
static void (*fatalError)(int errCode, char *mess, int exitStatus);
void memoryUseFunctionForFatalError(void (*function)(int errCode, char *mess, int exitStatus)) {
    fatalError = function;
}

/* Inject the function to call when assert() fails, a.k.a internalCheckFail() */
static void (*internalCheckFail)(char *expr, char *file, int line);
void memoryUseFunctionForInternalCheckFail(void (*function)(char *expr, char *file, int line)) {
    internalCheckFail = function;
}

/* Inject the function to call for error() */
static void (*error)(int code, char *message);
void memoryUseFunctionForError(void (*function)(int code, char *message)) {
    error = function;
}


/* With this as a separate function it is possible to catch memory resize longjmps */
void memoryResize(void) {
    longjmp(s_memoryResize,1);
}

void initMemory(S_memory *memory, bool (*overflowHandler)(int n), int size) {
    memory->overflowHandler = overflowHandler;
    memory->i = 0;
    memory->size = size;
    memory->b = 0;
}

/* ************************** Overflow Handlers ************************* */

bool cxMemoryOverflowHandler(int n) {
    int ofactor,factor,oldsize, newsize;
    S_memory *oldcxMemory;

    if (cxMemory!=NULL) {
        oldsize = cxMemory->size;
    } else {
        oldsize = 0;
    }

    ofactor = oldsize / CX_MEMORY_CHUNK_SIZE;
    factor = ((n>1)?(n-1):0)/CX_MEMORY_CHUNK_SIZE + 1; // 1 no patience to wait ;
    //& if (s_opt.cxMemoryFactor>=1) factor *= s_opt.cxMemoryFactor;
    factor += ofactor;
    if (ofactor*2 > factor) factor = ofactor*2;
    newsize = factor * CX_MEMORY_CHUNK_SIZE;
    oldcxMemory = cxMemory;
    if (oldcxMemory!=NULL) free(oldcxMemory);
    cxMemory = malloc(newsize + sizeof(S_memory));
    if (cxMemory!=NULL) {
        initMemory(cxMemory, cxMemoryOverflowHandler, newsize);
    }
    log_debug("Reallocating cxMemory: %d -> %d", oldsize, newsize);

    return(cxMemory!=NULL);
}

/* ***************************************************************** */

#if ZERO
static void trailDump(void) {
    S_freeTrail *t;
    log_trace("*** start trailDump");
    for(t=s_topBlock->trail; t!=NULL; t=t->next)
        log_trace("%p ", t);
    log_trace("***stop trailDump");
}
#endif

void addToTrail(void (*a)(void*), void *p) {
    S_freeTrail *t;
    /* no trail at level 0 in C*/
    if (WORK_NEST_LEVEL0() && (LANGUAGE(LANG_C)||LANGUAGE(LANG_YACC))) return;
    t = StackMemAlloc(S_freeTrail);
    t->action = a;
    t->p = (void **) p;
    t->next = s_topBlock->trail;
    s_topBlock->trail = t;
    /*trailDump();*/
}

void removeFromTrailUntil(S_freeTrail *untilP) {
    S_freeTrail *p;
    for(p=s_topBlock->trail; untilP<p; p=p->next) {
        assert(p!=NULL);
        (*(p->action))(p->p);
    }
    if (p!=untilP) {
        error(ERR_INTERNAL,"block structure mismatch?");
    }
    s_topBlock->trail = p;
    /*trailDump();*/
}

static void fillTopBlock(S_topBlock *topBlock, int firstFreeIndex, int tmpMemoryBasei, S_freeTrail *trail, S_topBlock *previousTopBlock) {
    topBlock->firstFreeIndex = firstFreeIndex;
    topBlock->tmpMemoryBasei = tmpMemoryBasei;
    topBlock->trail = trail;
    topBlock->previousTopBlock = previousTopBlock;
}

void stackMemoryInit(void) {
    s_topBlock = (S_topBlock *) memory;
    fillTopBlock(s_topBlock, sizeof(S_topBlock), 0, NULL, NULL);
}

void *stackMemoryAlloc(int size) {
    register int i;
    i = s_topBlock->firstFreeIndex;
    i = ((char *)ALIGNMENT(memory+i,STANDARD_ALIGNMENT))-memory;
    if (i+size < SIZE_workMemory) {
        s_topBlock->firstFreeIndex = i+size;
        return( & memory[i] );
    } else {
        fatalError(ERR_ST,"i+size > SIZE_workMemory,\n\tworking memory overflowed,\n\tread TROUBLES section of README file\n", XREF_EXIT_ERR);
        assert(0);
        return(NULL);
    }
}

void *stackMemoryPush(void *p, int size) {
    void *m;
    m = stackMemoryAlloc(size);
    memcpy(m,p,size);
    return(m);
}

void stackMemoryPop(void *p, int size) {
    int i;
    i = s_topBlock->firstFreeIndex;
    if (i-size < 0) {
        fprintf(stderr,"i-size < 0\n"); assert(0);
    }
    memcpy(p, & memory[i-size], size);
    s_topBlock->firstFreeIndex = i-size;
}

int *stackMemoryPushInt(int x) {
    /*fprintf(dumpOut,"pushing int %d\n", x);*/
    return((int*)stackMemoryPush(&x, sizeof(int)));
}

char *stackMemoryPushString(char *s) {
    /*fprintf(dumpOut,"pushing string %s\n",s);*/
    return((char*)stackMemoryPush(s, strlen(s)+1));
}

void stackMemoryBlockStart(void) {
    S_topBlock *p,top;
    log_trace("start block");
    top = *s_topBlock;
    p = StackMemPush(&top, S_topBlock);
    // trail can't be reset to NULL, because in case of syntax errors
    // this would avoid balancing of } at the end of class
    /*& fillTopBlock(s_topBlock, s_topBlock->firstFreeIndex, tmpWorkMemoryi, NULL, p); */
    fillTopBlock(s_topBlock, s_topBlock->firstFreeIndex, tmpWorkMemoryi, s_topBlock->trail, p);
}

void stackMemoryBlockFree(void) {
    log_trace("finish block");
    //&removeFromTrailUntil(NULL);
    assert(s_topBlock && s_topBlock->previousTopBlock);
    removeFromTrailUntil(s_topBlock->previousTopBlock->trail);
    log_trace("block free %d %d",tmpWorkMemoryi,s_topBlock->tmpMemoryBasei);
    assert(tmpWorkMemoryi >= s_topBlock->tmpMemoryBasei);
    tmpWorkMemoryi = s_topBlock->tmpMemoryBasei;
    * s_topBlock =  * s_topBlock->previousTopBlock;
    /*  FILL_topBlock(s_topBlock,s_topBlock->firstFreeIndex,NULL,NULL); */
    // burk, following disables any memory freeing for Java
    //  if (LANGUAGE(LAN_JAVA)) s_topBlock->firstFreeIndex = memi;
    assert(s_topBlock != NULL);
}
