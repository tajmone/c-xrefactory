#include "globals.h"            /* for s_language in addToTrail() */

#include "memory.h"
#include "log.h"


static bool memoryTrace = false;
#define mem_trace(...)  { if (memoryTrace) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__); }


CodeBlock *s_topBlock;

Memory *cxMemory=NULL;
int olcxMemoryAllocatedBytes;

jmp_buf memoryResizeJumpTarget;

/* Memory types */
static char workMemory[SIZE_workMemory];   /* Allocation using stackMemoryAlloc() et.al */

char tmpWorkMemory[SIZE_tmpWorkMemory];
int tmpWorkMemoryIndex = 0;

char ftMemory[SIZE_ftMemory];
int ftMemoryIndex = 0;

char tmpMemory[SIZE_TMP_MEM];

char ppmMemory[SIZE_ppmMemory];
int ppmMemoryIndex=0;

char mbMemory[SIZE_mbMemory];
int mbMemoryIndex=0;



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
void memoryResized(void) {
    longjmp(memoryResizeJumpTarget,1);
}

void initMemory(Memory *memory, bool (*overflowHandler)(int n), int size) {
    memory->overflowHandler = overflowHandler;
    memory->index = 0;
    memory->size = size;
    memory->block = 0;
}

/* ************************** Overflow Handlers ************************* */

bool cxMemoryOverflowHandler(int n) {
    int oldfactor, factor, oldsize, newsize;
    Memory *oldcxMemory;

    log_trace("Handling CX memory overflow with n=%d", n);
    if (cxMemory!=NULL) {
        oldsize = cxMemory->size;
    } else {
        oldsize = 0;
    }

    oldfactor = oldsize / CX_MEMORY_CHUNK_SIZE;
    factor = ((n>1)?(n-1):0)/CX_MEMORY_CHUNK_SIZE + 1; // 1 no patience to wait ;
    //& if (options.cxMemoryFactor>=1) factor *= options.cxMemoryFactor;
    factor += oldfactor;
    if (oldfactor*2 > factor)
        factor = oldfactor*2;
    newsize = factor * CX_MEMORY_CHUNK_SIZE;
    oldcxMemory = cxMemory;
    if (oldcxMemory!=NULL)
        free(oldcxMemory);
    cxMemory = malloc(newsize + sizeof(Memory));
    if (cxMemory!=NULL) {
        initMemory(cxMemory, cxMemoryOverflowHandler, newsize);
    }
    log_debug("Reallocating cxMemory: %d -> %d", oldsize, newsize);

    return cxMemory != NULL;
}

/* ***************************************************************** */

static void trailDump(void) {
    log_trace("*** begin trailDump");
    for (FreeTrail *t=s_topBlock->trail; t!=NULL; t=t->next)
        log_trace("%p ", t);
    log_trace("*** end trailDump");
}


void addToTrail(void (*action)(void*), void *pointer) {
    FreeTrail *t;
    /* no trail at level 0 in C */
    if ((nestingLevel() == 0) && (LANGUAGE(LANG_C)||LANGUAGE(LANG_YACC)))
        return;
    t = StackMemoryAlloc(FreeTrail);
    t->action = action;
    t->pointer = (void **) pointer;
    t->next = s_topBlock->trail;
    s_topBlock->trail = t;
    if (memoryTrace)
        trailDump();
}

void removeFromTrailUntil(FreeTrail *untilP) {
    FreeTrail *p;
    for (p=s_topBlock->trail; untilP<p; p=p->next) {
        assert(p!=NULL);
        (*(p->action))(p->pointer);
    }
    if (p!=untilP) {
        error(ERR_INTERNAL, "block structure mismatch?");
    }
    s_topBlock->trail = p;
    if (memoryTrace)
        trailDump();
}

static void fillTopBlock(CodeBlock *topBlock, int firstFreeIndex, int tmpMemoryBasei, FreeTrail *trail, CodeBlock *previousTopBlock) {
    topBlock->firstFreeIndex = firstFreeIndex;
    topBlock->tmpMemoryBaseIndex = tmpMemoryBasei;
    topBlock->trail = trail;
    topBlock->outerBlock = previousTopBlock;
}

void stackMemoryInit(void) {
    s_topBlock = (CodeBlock *) workMemory;
    fillTopBlock(s_topBlock, sizeof(CodeBlock), 0, NULL, NULL);
}

void *stackMemoryAlloc(int size) {
    int i;

    mem_trace("stackMemoryAlloc: allocating %d bytes", size);
    i = s_topBlock->firstFreeIndex;
    i = ((char *)ALIGNMENT(workMemory+i,STANDARD_ALIGNMENT))-workMemory;
    if (i+size < SIZE_workMemory) {
        s_topBlock->firstFreeIndex = i+size;
        return &workMemory[i];
    } else {
        fatalError(ERR_ST,"i+size > SIZE_workMemory,\n\tworking memory overflowed,\n\tread TROUBLES section of README file\n", XREF_EXIT_ERR);
        /* Should not return, but for testing and compilers sake return something */
        return NULL;
    }
}

static void *stackMemoryPush(void *p, int size) {
    void *m;
    m = stackMemoryAlloc(size);
    memcpy(m,p,size);
    return m;
}

char *stackMemoryPushString(char *s) {
    /*fprintf(dumpOut,"pushing string %s\n",s);*/
    return((char*)stackMemoryPush(s, strlen(s)+1));
}

void beginBlock(void) {
    CodeBlock *p, top;
    log_trace("Start block");
    top = *s_topBlock;
    p = stackMemoryPush(&top, sizeof(CodeBlock));
    // trail can't be reset to NULL, because in case of syntax errors
    // this would avoid balancing of } at the end of class
    fillTopBlock(s_topBlock, s_topBlock->firstFreeIndex, tmpWorkMemoryIndex, s_topBlock->trail, p);
}

void endBlock(void) {
    log_trace("finish block");
    //&removeFromTrailUntil(NULL);
    assert(s_topBlock && s_topBlock->outerBlock);
    removeFromTrailUntil(s_topBlock->outerBlock->trail);
    log_trace("block free %d %d",tmpWorkMemoryIndex,s_topBlock->tmpMemoryBaseIndex);
    assert(tmpWorkMemoryIndex >= s_topBlock->tmpMemoryBaseIndex);
    tmpWorkMemoryIndex = s_topBlock->tmpMemoryBaseIndex;
    * s_topBlock =  * s_topBlock->outerBlock;
    /*  FILL_topBlock(s_topBlock,s_topBlock->firstFreeIndex,NULL,NULL); */
    // burk, following disables any memory freeing for Java
    //  if (LANGUAGE(LAN_JAVA)) s_topBlock->firstFreeIndex = memi;
    assert(s_topBlock != NULL);
}


int nestingLevel(void) {
    int level = 0;
    CodeBlock *block = s_topBlock;
    while (block->outerBlock != NULL) {
        block = block->outerBlock;
        level++;
    }
    return level;
}


bool isMemoryFromPreviousBlock(void *address) {
    return s_topBlock->outerBlock != NULL &&
        (char*)address > workMemory &&
        (char*)address < workMemory + s_topBlock->outerBlock->firstFreeIndex;
}


bool freedPointer(void *ptr) {
    return ((char*)ptr >= workMemory + s_topBlock->firstFreeIndex &&
            (char*)ptr < workMemory + SIZE_workMemory);
}

void dm_init(Memory *memory, char *name) {
    memory->name = name;
    memory->index = 0;
}


static void align(Memory *memory) {
    memory->index = ((char*)ALIGNMENT(((char*)&memory->block)+memory->index,STANDARD_ALIGNMENT)) - ((char*)&memory->block);
}


void *dm_allocc(Memory *memory, int count, size_t size) {
    int previous_index;

    assert(count >= 0);
    align(memory);
    if (memory->index+count*size >= memory->size) {
        if (memory->overflowHandler(count))
            memoryResized();
        else
            fatalError(ERR_NO_MEMORY, memory->name, XREF_EXIT_ERR);
    }
    previous_index = memory->index;
    memory->index += (count)*size;
    return (void *) (((char*)&memory->block) + previous_index);
}
