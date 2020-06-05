#include "cxfile.h"

#include "lexer.h"
#include "yylex.h"
#include "cxref.h"
#include "html.h"
#include "options.h"
#include "editor.h"
#include "reftab.h"
#include "classhierarchy.h"
#include "fileio.h"

#include "enumTxt.h"

#include "protocol.h"
#include "globals.h"
#include "commons.h"
#include "misc.h"
#include "hash.h"
#include "log.h"
#include "utils.h"


/* *********************** INPUT/OUTPUT ************************** */

#define CXFI_FILE_FUMTIME   'm'     /* last full update mtime for file item */
#define CXFI_FILE_UMTIME    'p'     /* last update mtime for file item */
#define CXFI_FILE_INDEX     'f'
#define CXFI_SOURCE_INDEX   'o'     /* source index for java classes */
#define CXFI_SYM_INDEX      's'
#define CXFI_USAGE          'u'
#define CXFI_LINE_INDEX     'l'
#define CXFI_COLL_INDEX     'c'
#define CXFI_REFERENCE      'r'     /* using 'fsulc' */
#define CXFI_INPUT_FROM_CL  'i'     /* file was introduced from comand line */
#define CXFI_ACCESS_BITS    'a'     /* java access bit */
#define CXFI_REQ_ACCESS     'A'     /* java reference required accessibilite index */
#define CXFI_STORAGE        'g'     /* storaGe field */

#define CXFI_SUPER_CLASS    'h'     /* hore = up in slovac */
#define CXFI_INFER_CLASS    'd'     /* dole = down in slovac */
#define CXFI_CLASS_EXT      'e'     /* using 'fhd' */

#define CXFI_MACRO_BASE_FILE 'b'    /* ref to a file invoking macro */

#define CXFI_SYM_TYPE       't'

#define CXFI_SYM_NAME       '/'     /* using 'atdhg' -> 's'             */
#define CXFI_CLASS_NAME     '+'     /*               -> 'h' info    */
#define CXFI_FILE_NAME      ':'     /*               -> 'ifm' info  */

#define CXFI_CHECK_NUMBER   'k'
#define CXFI_REFNUM         'n'
#define CXFI_VERSION        'v'
#define CXFI_SINGLE_RECORDS '@'
#define CXFI_REMARK         '#'

static int s_cxGeneratedSingleRecords[] = {
    CXFI_FILE_FUMTIME,
    CXFI_FILE_UMTIME,
    CXFI_FILE_INDEX,
    CXFI_SOURCE_INDEX,
    CXFI_SYM_TYPE,
    CXFI_USAGE,
    CXFI_LINE_INDEX,
    CXFI_COLL_INDEX,
    CXFI_SYM_INDEX,
    CXFI_REFERENCE,
    CXFI_SUPER_CLASS,
    CXFI_INFER_CLASS,
    CXFI_CLASS_EXT,
    CXFI_INPUT_FROM_CL,
    CXFI_MACRO_BASE_FILE,
    CXFI_REFNUM,
    CXFI_ACCESS_BITS,
    CXFI_REQ_ACCESS,
    CXFI_STORAGE,
    CXFI_CHECK_NUMBER,
    -1
};

#define MAX_CX_SYMBOL_TAB 2

struct lastCxFileInfos {
    int                 onLineReferencedSym;
    S_olSymbolsMenu     *onLineRefMenuItem;
    int                 onLineRefIsBestMatchFlag; // vyhodit ?
    SymbolReferenceItem     *symbolTab[MAX_CX_SYMBOL_TAB];
    char                symbolIsWritten[MAX_CX_SYMBOL_TAB];
    char                *symbolBestMatchFlag[MAX_CX_SYMBOL_TAB];
    int                 macroBaseFileGeneratedForSym[MAX_CX_SYMBOL_TAB];
    char                singleRecord[MAX_CHARS];
    int                 counter[MAX_CHARS];
    void                (*fun[MAX_CHARS])(int size, int ri, CharacterBuffer *cb, int additional);
    int                 additional[MAX_CHARS];

    // dead code detection vars
    int                 symbolToCheckForDeadness;
    char                deadSymbolIsDefined;

    // following item can be used only via symbolTab,
    // it is just to smplifie memoru handling !!!!!!!!!!!!!!!!
    SymbolReferenceItem     _symbolTab[MAX_CX_SYMBOL_TAB];
    char                _symbolTabNames[MAX_CX_SYMBOL_TAB][MAX_CX_SYMBOL_SIZE];
};

static struct lastCxFileInfos s_inLastInfos;
static struct lastCxFileInfos s_outLastInfos;


static CharacterBuffer cxfCharacterBuffer;

static unsigned s_decodeFilesNum[MAX_FILES];

static char tmpFileName[MAX_FILE_NAME_SIZE];



/* *********************** INPUT/OUTPUT ************************** */

int cxFileHashNumber(char *sym) {
    unsigned   res,r;
    char       *ss,*bb;
    int        c;

    if (s_opt.referenceFileCount <= 1) return(0);
    if (s_opt.xfileHashingMethod == XFILE_HASH_DEFAULT) {
        res = 0;
        ss = sym;
        while ((c = *ss)) {
            if (c == '(') break;
            SYMTAB_HASH_FUN_INC(res, c);
            if (LINK_NAME_MAYBE_START(c)) res = 0;
            ss++;
        }
        SYMTAB_HASH_FUN_FINAL(res);
        res %= s_opt.referenceFileCount;
        return(res);
    } else if (s_opt.xfileHashingMethod == XFILE_HASH_ALPHA1) {
        assert(s_opt.referenceFileCount == XFILE_HASH_ALPHA1_REFNUM);
        for(ss = bb = sym; *ss && *ss!='('; ss++) {
            c = *ss;
            if (LINK_NAME_MAYBE_START(c)) bb = ss+1;
        }
        c = *bb;
        c = tolower(c);
        if (c>='a' && c<='z') res = c-'a';
        else res = ('z'-'a')+1;
        assert(res>=0 && res<s_opt.referenceFileCount);
        return(res);
    } else if (s_opt.xfileHashingMethod == XFILE_HASH_ALPHA2) {
        for(ss = bb = sym; *ss && *ss!='('; ss++) {
            c = *ss;
            if (LINK_NAME_MAYBE_START(c)) bb = ss+1;
        }
        c = *bb;
        c = tolower(c);
        if (c>='a' && c<='z') r = c-'a';
        else r = ('z'-'a')+1;
        if (c==0) res=0;
        else {
            c = *(bb+1);
            c = tolower(c);
            if (c>='a' && c<='z') res = c-'a';
            else res = ('z'-'a')+1;
        }
        res = r*XFILE_HASH_ALPHA1_REFNUM + res;
        assert(res>=0 && res<s_opt.referenceFileCount);
        return(res);
    } else {
        assert(0);
        return(0);
    }
}

static int searchSingleStringEqual(char *s, char *c) {
    while (*s!=0 && *s!=' ' && *s!='\t' && tolower(*s)==tolower(*c)) {
        c++; s++;
    }
    if (*s==0 || *s==' ' || *s=='\t') return(1);
    return(0);
}

static int searchSingleStringFitness(char *cxtag, char *searchedStr, int len) {
    char *cc;
    int i, pilotc;

    assert(searchedStr);
    pilotc = tolower(*searchedStr);
    if (pilotc == '^') {
        // check for exact prefix
        return(searchSingleStringEqual(searchedStr+1, cxtag));
    } else {
        cc = cxtag;
        for(cc=cxtag, i=0; *cc && i<len; cc++,i++) {
            if (searchSingleStringEqual(searchedStr, cc)) return(1);
        }
    }
    return(0);
}

int searchStringNonWildcardFitness(char *cxtag, int len) {
    char    *ss;
    int     r;
    ss = s_opt.olcxSearchString;
    while (*ss) {
        while (*ss==' ' || *ss=='\t') ss++;
        if (*ss == 0) goto fini1;
        r = searchSingleStringFitness(cxtag, ss, len);
        if (r==0) return(0);
        while (*ss!=0 && *ss!=' ' && *ss!='\t') ss++;
    }
 fini1:
    return(1);
}

int searchStringFitness(char *cxtag, int len) {
    if (s_wildcardSearch) return(shellMatch(cxtag, len, s_opt.olcxSearchString, 0));
    else return(searchStringNonWildcardFitness(cxtag, len));
}


#define SET_MAX(max,val) {                      \
        if (val > max) max = val;               \
    }

char *crTagSearchLineStatic(char *name, Position *p,
                            int *len1, int *len2, int *len3) {
    static char res[2*COMPLETION_STRING_SIZE];
    char file[TMP_STRING_SIZE];
    char dir[TMP_STRING_SIZE];
    char *ffname;
    int l1,l2,l3,fl, dl;

    l1 = l2 = l3 = 0;
    l1 = strlen(name);

    /*&
      char type[TMP_STRING_SIZE];
      type[0]=0;
      if (symType != TypeDefault) {
      l2 = strmcpy(type,typeName[symType]+4) - type;
      }
      &*/

    ffname = s_fileTab.tab[p->file]->name;
    assert(ffname);
    ffname = getRealFileNameStatic(ffname);
    fl = strlen(ffname);
    l3 = strmcpy(file,simpleFileName(ffname)) - file;

    dl = fl /*& - l3 &*/ ;
    strncpy(dir, ffname, dl);
    dir[dl]=0;

    SET_MAX(*len1, l1);
    SET_MAX(*len2, l2);
    SET_MAX(*len3, l3);

    if (s_opt.tagSearchSpecif == TSS_SEARCH_DEFS_ONLY_SHORT
        || s_opt.tagSearchSpecif==TSS_FULL_SEARCH_SHORT) {
        sprintf(res, "%s", name);
    } else {
        sprintf(res, "%-*s :%-*s :%s", *len1, name, *len3, file, dir);
    }
    return(res);
}

// Filter out symbols which pollute search reports
bool symbolNameShouldBeHiddenFromReports(char *name) {
    char *s;

    // internal xref symbol?
    if (name[0] == ' ')
        return true;

    // Only Java specific pollution
    if (! LANGUAGE(LANG_JAVA))
        return false;

    // Hide class$ fields
    if (strncmp(name, "class$", 6)==0)
        return true;

    // Hide anonymous classes
    if (isdigit(name[0]))
        return true;

    // And what is this?
    s = name;
    while ((s=strchr(s, '$'))!=NULL) {
        s++;
        while (isdigit(*s))
            s++;
        if (*s == '.' || *s=='(' || *s=='$' || *s==0)
            return true;
    }

    return false;
}

void searchSymbolCheckReference(SymbolReferenceItem  *ss, Reference *rr) {
    char ssname[MAX_CX_SYMBOL_SIZE];
    char *s, *sname;
    int slen;

    if (ss->b.symType == TypeCppInclude)
        return;   // no %%i symbols
    if (symbolNameShouldBeHiddenFromReports(ss->name))
        return;

    linkNamePrettyPrint(ssname, ss->name, MAX_CX_SYMBOL_SIZE, SHORT_NAME);
    sname = ssname;
    slen = strlen(sname);
    // if completing without profile, cut profile
    if (s_opt.tagSearchSpecif==TSS_SEARCH_DEFS_ONLY_SHORT
        || s_opt.tagSearchSpecif==TSS_FULL_SEARCH_SHORT) {
        s = strchr(sname, '(');
        if (s!=NULL) *s = 0;
    }
    // cut package name for checking
    do {
        s = strchr(sname, '.');
        if (s!=NULL) sname = s+1;
    } while (s!=NULL);
    slen = strlen(sname);
    if (searchStringFitness(sname, slen)) {
        static int count = 0;
        //& olCompletionListPrepend(sname, NULL, NULL, 0, NULL, NULL, rr, ss->vFunClass, s_olcxCurrentUser->retrieverStack.top);
        //&sprintf(tmpBuff,"adding %s of %s(%d) matched %s %d", sname, s_fileTab.tab[rr->p.file]->name, rr->p.file, s_opt.olcxSearchString, s_wildcardSearch);ppcGenTmpBuff();
        olCompletionListPrepend(sname, NULL, NULL, 0, NULL, ss, rr, ss->b.symType, ss->vFunClass, s_olcxCurrentUser->retrieverStack.top);
        // this is a hack for memory reduction
        // compact completions from time to time
        count ++;
        if (count > COMPACT_TAG_SEARCH_AFTER) {
            tagSearchCompactShortResults();
            count = 0;
        }
    }
}

/* ************************* WRITE **************************** */

static void get_version_string(char *ttt) {                             \
    sprintf(ttt," file format: C-xrefactory %s ", C_XREF_FILE_VERSION_NUMBER); \
}


#define writeCompactRecord(recNum, info, blankPrefix) {                   \
        assert(recNum >= 0 && recNum < MAX_CHARS); \
        assert(info >= 0);                                              \
        if (*blankPrefix!=0) fputs(blankPrefix, cxOut);                 \
        if (info != 0) fPutDecimal(cxOut, info);                        \
        fputc(recNum, cxOut);                                           \
        s_outLastInfos.counter[recNum] = info;                          \
    }

#define writeOptionalCompactRecord(recNum, info, blankPrefix) {    \
        assert(recNum >= 0 && recNum < MAX_CHARS);          \
        if (*blankPrefix!=0) fputs(blankPrefix, cxOut);     \
        if (s_outLastInfos.counter[recNum] != info) {       \
            if (info != 0) fPutDecimal(cxOut, info);        \
            fputc(recNum, cxOut);                           \
            s_outLastInfos.counter[recNum] = info;          \
        }                                                   \
    }

static void writeStringRecord(int recNum, char *s, char *blankPrefix) {
    int rsize;
    rsize = strlen(s)+1;
    if (*blankPrefix!=0) fputs(blankPrefix, cxOut);
    fPutDecimal(cxOut, rsize);
    fputc(recNum, cxOut);
    fputs(s, cxOut);
}


static void writeSymbolItem(int symIndex) {
    char ttt[TMP_STRING_SIZE];
    SymbolReferenceItem *d;
    writeOptionalCompactRecord(CXFI_SYM_INDEX, symIndex, "");
    d = s_outLastInfos.symbolTab[symIndex];
    writeOptionalCompactRecord(CXFI_SYM_TYPE, d->b.symType, "\n");
    writeOptionalCompactRecord(CXFI_INFER_CLASS, d->vApplClass, "");
    writeOptionalCompactRecord(CXFI_SUPER_CLASS, d->vFunClass, "");
    writeOptionalCompactRecord(CXFI_ACCESS_BITS, d->b.accessFlags, "");
    writeOptionalCompactRecord(CXFI_STORAGE, d->b.storage, "");
    s_outLastInfos.macroBaseFileGeneratedForSym[symIndex] = 0;
    s_outLastInfos.symbolIsWritten[symIndex] = 1;
    if (!s_opt.brief_cxref) {
        sprintf(ttt,"\t%s",typeEnumName[d->b.symType]);
        writeStringRecord(CXFI_REMARK,ttt,"");
    }
    writeStringRecord(CXFI_SYM_NAME, d->name, "\t");
    if (!s_opt.brief_cxref) {
        if (d->vApplClass != s_noneFileIndex) {
            sprintf(ttt,"\ton %s",s_fileTab.tab[d->vApplClass]->name);
            writeStringRecord(CXFI_REMARK,ttt,"\n");
        }
    }
    if (!s_opt.brief_cxref) {
        if (d->vApplClass != s_noneFileIndex) {
            sprintf(ttt,"\tfun %s",s_fileTab.tab[d->vFunClass]->name);
            writeStringRecord(CXFI_REMARK,ttt,"\n");
        }
    }
    //& fprintf(cxOut,"\n\n");
    //fprintf(cxOut,"\t");
    fputc('\t', cxOut);
}

#define writeOptionalSymbolItem(symIndex) {                        \
        if (! s_outLastInfos.symbolIsWritten[symIndex]) {   \
            writeSymbolItem(symIndex);                        \
        }                                                   \
    }

#define writeCxReferenceBase(symbolNum, usage, requiredAccess, file, line, coll) { \
        char ttt[TMP_STRING_SIZE];                                      \
        writeOptionalSymbolItem(symbolNum);                                    \
        if (usage == UsageMacroBaseFileUsage) {                         \
            /* optimize the number of those references to 1*/           \
            assert(symbolNum>=0 && symbolNum<MAX_CX_SYMBOL_TAB);        \
            if (s_outLastInfos.macroBaseFileGeneratedForSym[symbolNum]) return; \
            s_outLastInfos.macroBaseFileGeneratedForSym[symbolNum] = 1; \
        }                                                               \
        writeOptionalCompactRecord(CXFI_USAGE, usage, "");                     \
        writeOptionalCompactRecord(CXFI_REQ_ACCESS, requiredAccess, "");       \
        writeOptionalCompactRecord(CXFI_SYM_INDEX, symbolNum, "");             \
        writeOptionalCompactRecord(CXFI_FILE_INDEX, file, "");                 \
        writeOptionalCompactRecord(CXFI_LINE_INDEX, line, "");                 \
        writeOptionalCompactRecord(CXFI_COLL_INDEX, coll, "");                 \
        writeCompactRecord(CXFI_REFERENCE, 0, "");                        \
        if (!s_opt.brief_cxref) {                                         \
            sprintf(ttt,"\t%-7s in %30s:%u:%d\n",usageEnumName[usage]+5,   \
                    s_fileTab.tab[file]->name,line,coll);               \
            writeStringRecord(CXFI_REMARK,ttt,"");                        \
        }                                                               \
    }

static void writeCxReference(Reference *reference, int symbolNum) {
    writeCxReferenceBase(symbolNum, reference->usage.base, reference->usage.requiredAccess,
                         reference->p.file, reference->p.line, reference->p.col);
}

static void writeSubClassInfo(int sup, int inf, int origin) {
    char ttt[TMP_STRING_SIZE];
    writeOptionalCompactRecord(CXFI_FILE_INDEX, origin, "\n");
    writeOptionalCompactRecord(CXFI_SUPER_CLASS, sup, "");
    writeOptionalCompactRecord(CXFI_INFER_CLASS, inf, "");
    writeCompactRecord(CXFI_CLASS_EXT, 0, "");
    if (!s_opt.brief_cxref) {
        sprintf(ttt,"\t\t%s",s_fileTab.tab[inf]->name);
        writeStringRecord(CXFI_REMARK,ttt,"\n");
        sprintf(ttt,"  extends\t%s",s_fileTab.tab[sup]->name);
        writeStringRecord(CXFI_REMARK,ttt,"\n");
    }
}

static void writeFileIndexItem(struct fileItem *fi, int ii) {
    writeOptionalCompactRecord(CXFI_FILE_INDEX, ii, "\n");
    writeOptionalCompactRecord(CXFI_FILE_UMTIME, fi->lastUpdateMtime, " ");
    writeOptionalCompactRecord(CXFI_FILE_FUMTIME, fi->lastFullUpdateMtime, " ");
    writeOptionalCompactRecord(CXFI_INPUT_FROM_CL, fi->b.commandLineEntered, "");
    if (fi->b.isInterface) {
        writeOptionalCompactRecord(CXFI_ACCESS_BITS, ACCESS_INTERFACE, "");
    } else {
        writeOptionalCompactRecord(CXFI_ACCESS_BITS, ACCESS_DEFAULT, "");
    }
    writeStringRecord(CXFI_FILE_NAME, fi->name, " ");
}

static void writeFileSourceIndexItem(struct fileItem *fileItem, int ii) {
    if (fileItem->b.sourceFile != s_noneFileIndex) {
        writeOptionalCompactRecord(CXFI_FILE_INDEX, ii, "\n");
        writeCompactRecord(CXFI_SOURCE_INDEX, fileItem->b.sourceFile, " ");
    }
}

static void genClassHierarchyItems(struct fileItem *fi, int ii) {
    ClassHierarchyReference *p;
    for(p=fi->superClasses; p!=NULL; p=p->next) {
        writeSubClassInfo(p->superClass, ii, p->ofile);
    }
}


static ClassHierarchyReference *findSuperiorInSuperClasses(int superior, FileItem *iFile) {
    ClassHierarchyReference *p;
    for(p=iFile->superClasses; p!=NULL && p->superClass!=superior; p=p->next)
        ;

    return p;
}


static void createSubClassInfo(int superior, int inferior, int origin, int genfl) {
    FileItem      *iFile, *sFile;
    ClassHierarchyReference   *p, *pp;

    iFile = s_fileTab.tab[inferior];
    sFile = s_fileTab.tab[superior];
    assert(iFile && sFile);
    p = findSuperiorInSuperClasses(superior, iFile);
    if (p==NULL) {
        p = newClassHierarchyReference(origin, superior, iFile->superClasses);
        iFile->superClasses = p;
        assert(s_opt.taskRegime);
        if (s_opt.taskRegime == RegimeXref) {
            if (genfl == CX_FILE_ITEM_GEN)
                writeSubClassInfo(superior, inferior, origin);
        }
        pp = newClassHierarchyReference(origin, inferior, sFile->superClasses);
        sFile->inferiorClasses = pp;
    }
}

void addSubClassItemToFileTab( int sup, int inf, int origin) {
    if (sup >= 0 && inf >= 0) {
        createSubClassInfo(sup, inf, origin, NO_CX_FILE_ITEM_GEN);
    }
}


void addSubClassesItemsToFileTab(Symbol *ss, int origin) {
    int cf1;
    SymbolList *sups;

    if (ss->bits.symType != TypeStruct) return;
    /*fprintf(dumpOut,"testing %s\n",ss->name);*/
    assert(ss->bits.javaFileIsLoaded);
    if (!ss->bits.javaFileIsLoaded)
        return;
    cf1 = ss->u.s->classFile;
    assert(cf1 >= 0 &&  cf1 < MAX_FILES);
    /*fprintf(dumpOut,"loaded: #sups == %d\n",ns);*/
    for(sups=ss->u.s->super; sups!=NULL; sups=sups->next) {
        assert(sups->d && sups->d->bits.symType == TypeStruct);
        addSubClassItemToFileTab( sups->d->u.s->classFile, cf1, origin);
    }
}

/* *************************************************************** */

static void genRefItem0(SymbolReferenceItem *d, int forceGen) {
    Reference *reference;
    int symIndex;

    log_trace("function '%s'", d->name);
    symIndex = 0;
    assert(strlen(d->name)+1 < MAX_CX_SYMBOL_SIZE);
    strcpy(s_outLastInfos._symbolTabNames[symIndex], d->name);
    fillSymbolRefItemExceptBits(&s_outLastInfos._symbolTab[symIndex],
                                s_outLastInfos._symbolTabNames[symIndex],
                                d->fileHash, // useless put 0
                                d->vApplClass, d->vFunClass);
    fillSymbolRefItemBits(&s_outLastInfos._symbolTab[symIndex].b,
                           d->b.symType, d->b.storage,
                           d->b.scope, d->b.accessFlags, d->b.category, 0);
    s_outLastInfos.symbolTab[symIndex] = &s_outLastInfos._symbolTab[symIndex];
    s_outLastInfos.symbolIsWritten[symIndex] = 0;
    if (d->b.category == CategoryLocal) return;
    if (d->refs == NULL && !forceGen) return;
    for(reference = d->refs; reference!=NULL; reference=reference->next) {
        log_trace("checking ref: loading=%d --< %s:%d", s_fileTab.tab[reference->p.file]->b.cxLoading,
                  s_fileTab.tab[reference->p.file]->name, reference->p.line);
        if (s_opt.update==UP_CREATE || s_fileTab.tab[reference->p.file]->b.cxLoading) {
            /*& s_opt.update==UP_CREATE; why it is there &*/
            writeCxReference(reference, symIndex);
        } else {
            log_trace("Some kind of update (%d) or not loading (%d), so don't writeCxReference()",
                      s_opt.update, s_fileTab.tab[reference->p.file]->b.cxLoading);
            assert(0);
        }
    }
    //&fflush(cxOut);
}

static void genRefItem(SymbolReferenceItem *dd) {
    genRefItem0(dd,0);
}

#define COMPOSE_CXFI_CHECK_NUM(filen,hashMethod,exactPositionLinkFlag) ( \
                                                                        ((filen)*XFILE_HASH_MAX+hashMethod)*2+exactPositionLinkFlag \
                                                                        )
#define DECOMPOSE_CXFI_CHECK_NUM(num,filen,hashMethod,exactPositionLinkFlag){ \
        unsigned tmp;                                                   \
        tmp = num;                                                      \
        exactPositionLinkFlag = tmp % 2;                                \
        tmp = tmp / 2;                                                  \
        hashMethod = tmp % XFILE_HASH_MAX;                              \
        tmp = tmp / XFILE_HASH_MAX;                                     \
        filen = tmp;                                                    \
    }

static void genCxFileHead(void) {
    char sr[MAX_CHARS];
    char ttt[TMP_STRING_SIZE];
    int i;
    memset(&s_outLastInfos, 0, sizeof(s_outLastInfos));
    for(i=0; i<MAX_CHARS; i++) {
        s_outLastInfos.counter[i] = -1;
    }
    get_version_string(ttt);
    writeStringRecord(CXFI_VERSION, ttt, "\n\n");
    fprintf(cxOut,"\n\n\n");
    for(i=0; i<MAX_CHARS && s_cxGeneratedSingleRecords[i] != -1; i++) {
        sr[i] = s_cxGeneratedSingleRecords[i];
    }
    assert(i < MAX_CHARS);
    sr[i]=0;
    writeStringRecord(CXFI_SINGLE_RECORDS, sr, "");
    writeCompactRecord(CXFI_REFNUM, s_opt.referenceFileCount, " ");
    writeCompactRecord(CXFI_CHECK_NUMBER, COMPOSE_CXFI_CHECK_NUM(
                                                               MAX_FILES,
                                                               s_opt.xfileHashingMethod,
                                                               s_opt.exactPositionResolve
                                                               ), " ");
}

static void openInOutReferenceFiles(int updateFlag, char *filename) {
    if (updateFlag) {
        char *tempname = create_temporary_filename();
        strcpy(tmpFileName, tempname);
        copyFileFromTo(filename, tmpFileName);
    }

    assert(filename);
    cxOut = openFile(filename,"w");
    if (cxOut == NULL)
        fatalError(ERR_CANT_OPEN, filename, XREF_EXIT_ERR);

    if (updateFlag) {
        inputFile = openFile(tmpFileName, "r");
        if (inputFile==NULL)
            warningMessage(ERR_CANT_OPEN_FOR_READ, tmpFileName);
    } else {
        inputFile = NULL;
    }
}

static void closeReferenceFile(char *fname) {
    if (inputFile != NULL) {
        closeFile(inputFile);
        inputFile = NULL;
        removeFile(tmpFileName);
    }
    closeFile(cxOut);
    cxOut = stdout;
}

static void createDirIfNotExists(char *dirname) {
    struct stat st;

    if (stat(dirname, &st)==0) {
        if ((st.st_mode & S_IFMT) == S_IFDIR) return;
        removeFile(dirname);
    }
    createDir(dirname);
}

/* fnamesuff contains '/' at the beginning */

static void genPartialFileTabRefFile(int updateFlag,
                                     char *dirname,
                                     char *suffix,
                                     void mapfun(FileItem *, int),
                                     void mapfun2(FileItem *, int)) {
    char filename[MAX_FILE_NAME_SIZE];

    sprintf(filename, "%s%s", dirname, suffix);
    assert(strlen(filename) < MAX_FILE_NAME_SIZE-1);
    openInOutReferenceFiles(updateFlag, filename);
    genCxFileHead();
    fileTabMapWithIndex(&s_fileTab, mapfun);
    if (mapfun2!=NULL)
        fileTabMapWithIndex(&s_fileTab, mapfun2);
    scanCxFile(fullScanFunctionSequence);
    closeReferenceFile(filename);
}

static void generateRefsFromMemory(int fileOrder) {
    int                 tsize;
    SymbolReferenceItem *pp;

    tsize = s_cxrefTab.size;
    for (int i=0; i<tsize; i++) {
        for (pp=s_cxrefTab.tab[i]; pp!=NULL; pp=pp->next) {
            if (pp->b.category == CategoryLocal)
                continue;
            if (pp->refs == NULL)
                continue;
            if (pp->fileHash == fileOrder)
                genRefItem0(pp,0);
        }
    }
}

void genReferenceFile(bool updating, char *filename) {
    char    fileName[MAX_FILE_NAME_SIZE];
    char    *dirname;
    int     i;

    if (!updating)
        removeFile(fileName);

    recursivelyCreateFileDirIfNotExists(fileName);
    if (s_opt.referenceFileCount <= 1) {
        /* single reference file */
        openInOutReferenceFiles(updating, filename);
        /*&     fileTabMap(&s_fileTab, javaInitSubClassInfo); &*/
        genCxFileHead();
        fileTabMapWithIndex(&s_fileTab, writeFileIndexItem);
        fileTabMapWithIndex(&s_fileTab, writeFileSourceIndexItem);
        fileTabMapWithIndex(&s_fileTab, genClassHierarchyItems);
        scanCxFile(fullScanFunctionSequence);
        refTabMap(&s_cxrefTab, genRefItem);
        closeReferenceFile(filename);
    } else {
        /* several reference files */
        dirname = filename;
        createDirIfNotExists(dirname);
        genPartialFileTabRefFile(updating,dirname,REFERENCE_FILENAME_FILES,
                                 writeFileIndexItem, writeFileSourceIndexItem);
        genPartialFileTabRefFile(updating,dirname,REFERENCE_FILENAME_CLASSES,
                                 genClassHierarchyItems, NULL);
        for (i=0; i<s_opt.referenceFileCount; i++) {
            sprintf(fileName, "%s%s%04d", dirname, REFERENCE_FILENAME_PREFIX, i);
            assert(strlen(fileName) < MAX_FILE_NAME_SIZE-1);
            openInOutReferenceFiles(updating, fileName);
            genCxFileHead();
            scanCxFile(fullScanFunctionSequence);
            //&refTabMap4(&s_cxrefTab, genPartialRefItem, i);
            generateRefsFromMemory(i);
            closeReferenceFile(fileName);
        }
    }
}

/* ************************* READ **************************** */

static void cxrfSetSingleRecords(int size,
                                 int ri,
                                 CharacterBuffer *cb,
                                 int additionalArg
                                 ) {
    int i, ch;

    assert(ri == CXFI_SINGLE_RECORDS);
    for(i=0; i<size-1; i++) {
        ch = getChar(cb);
        s_inLastInfos.singleRecord[ch] = 1;
    }
}


static void writeCxFileCompatibilityError(char *message) {
    static time_t lastMessageTime;
    if (s_opt.taskRegime == RegimeEditServer) {
        if (lastMessageTime < s_fileProcessStartTime) {
            errorMessage(ERR_ST, message);
            lastMessageTime = time(NULL);
        }
    } else {
        fatalError(ERR_ST, message, XREF_EXIT_ERR);
    }
}


static void cxrfVersionCheck(int size,
                             int ri,
                             CharacterBuffer *cb,
                             int additionalArg
                             ) {
    char versionString[TMP_STRING_SIZE];
    char thisVersionString[TMP_STRING_SIZE];
    int i, ch;

    assert(ri == CXFI_VERSION);
    for(i=0; i<size-1; i++) {
        ch = getChar(cb);
        versionString[i]=ch;
    }
    versionString[i]=0;
    get_version_string(thisVersionString);
    if (strcmp(versionString, thisVersionString)) {
        writeCxFileCompatibilityError("The Tag file was not generated by the current version of C-xrefactory, recreate it");
    }
}

static void cxrfCheckNumber(int size,
                            int ri,
                            CharacterBuffer *cb,
                            int additionalArg
                            ) {
    int magicn, filen, hashMethod, exactPositionLinkFlag;
    char tmpBuff[TMP_BUFF_SIZE];

    assert(ri == CXFI_CHECK_NUMBER);
    if (s_opt.create)
        return; // no check when creating new file

    magicn = s_inLastInfos.counter[CXFI_CHECK_NUMBER];
    DECOMPOSE_CXFI_CHECK_NUM(magicn,filen,hashMethod,exactPositionLinkFlag);
    if (filen != MAX_FILES) {
        sprintf(tmpBuff,"The Tag file was generated with different MAX_FILES, recreate it");
        writeCxFileCompatibilityError(tmpBuff);
    }
    if (hashMethod != s_opt.xfileHashingMethod) {
        sprintf(tmpBuff,"The Tag file was generated with different hash method, recreate it");
        writeCxFileCompatibilityError(tmpBuff);
    }
    log_trace("checking %d <-> %d", exactPositionLinkFlag, s_opt.exactPositionResolve);
    if (exactPositionLinkFlag != s_opt.exactPositionResolve) {
        if (exactPositionLinkFlag) {
            sprintf(tmpBuff,"The Tag file was generated with '-exactpositionresolve' flag, recreate it");
        } else {
            sprintf(tmpBuff,"The Tag file was generated without '-exactpositionresolve' flag, recreate it");
        }
        writeCxFileCompatibilityError(tmpBuff);
    }
}

static int cxrfFileItemShouldBeUpdatedFromCxFile(FileItem *ffi) {
    bool updateFromCxFile = true;

    log_trace("re-read info from '%s' for '%s'?", s_opt.cxrefFileName, ffi->name);
    if (s_opt.taskRegime == RegimeXref) {
        if (ffi->b.cxLoading && ! ffi->b.cxSaved) {
            updateFromCxFile = false;
        } else {
            updateFromCxFile = true;
        }
    }
    if (s_opt.taskRegime == RegimeEditServer) {
        log_trace("last inspected == %d, start at %d\n", ffi->lastInspected, s_fileProcessStartTime);
        if (ffi->lastInspected < s_fileProcessStartTime) {
            updateFromCxFile = true;
        } else {
            updateFromCxFile = false;
        }
    }
    log_trace("%s re-read info from '%s' for '%s'", updateFromCxFile?"yes,":"no, not necessary to",
              s_opt.cxrefFileName, ffi->name);

    return updateFromCxFile;
}

static void cxReadFileName(int size,
                           int ri,
                           CharacterBuffer *cb,
                           int genFl
                           ) {
    char id[MAX_FILE_NAME_SIZE];
    struct fileItem *fileItem;
    int i, ii, fileIndex, len, commandLineFlag, isInterface;
    time_t fumtime, umtime;
    char ch;

    assert(ri == CXFI_FILE_NAME);
    fumtime = (time_t) s_inLastInfos.counter[CXFI_FILE_FUMTIME];
    umtime = (time_t) s_inLastInfos.counter[CXFI_FILE_UMTIME];
    commandLineFlag = s_inLastInfos.counter[CXFI_INPUT_FROM_CL];
    isInterface=((s_inLastInfos.counter[CXFI_ACCESS_BITS] & ACCESS_INTERFACE)!=0);
    ii = s_inLastInfos.counter[CXFI_FILE_INDEX];
    for (i=0; i<size-1; i++) {
        ch = getChar(cb);
        id[i] = ch;
    }
    id[i] = 0;
    len = i;
    assert(len+1 < MAX_FILE_NAME_SIZE);
    assert(ii>=0 && ii<MAX_FILES);
    if (!fileTabExists(&s_fileTab, id)) {
        fileIndex = addFileTabItem(id);
        fileItem = s_fileTab.tab[fileIndex];
        fileItem->b.commandLineEntered = commandLineFlag;
        fileItem->b.isInterface = isInterface;
        if (fileItem->lastFullUpdateMtime == 0) fileItem->lastFullUpdateMtime=fumtime;
        if (fileItem->lastUpdateMtime == 0) fileItem->lastUpdateMtime=umtime;
        assert(s_opt.taskRegime);
        if (s_opt.taskRegime == RegimeXref) {
            if (genFl == CX_GENERATE_OUTPUT) {
                writeFileIndexItem(fileItem, fileIndex);
            }
        }
    } else {
        fileIndex = fileTabLookup(&s_fileTab, id);
        fileItem = s_fileTab.tab[fileIndex];
        if (cxrfFileItemShouldBeUpdatedFromCxFile(fileItem)) {
            fileItem->b.isInterface = isInterface;
            // Set it to none, it will be updated by source item
            fileItem->b.sourceFile = s_noneFileIndex;
        }
        if (s_opt.taskRegime == RegimeEditServer) {
            fileItem->b.commandLineEntered = commandLineFlag;
        }
        if (fileItem->lastFullUpdateMtime == 0) fileItem->lastFullUpdateMtime=fumtime;
        if (fileItem->lastUpdateMtime == 0) fileItem->lastUpdateMtime=umtime;
        //&if (fumtime>fileItem->lastFullUpdateMtime) fileItem->lastFullUpdateMtime=fumtime;
        //&if (umtime>fileItem->lastUpdateMtime) fileItem->lastUpdateMtime=umtime;
    }
    fileItem->b.isFromCxfile = true;
    s_decodeFilesNum[ii]=fileIndex;
    log_trace("%d: '%s' scanned: added as %d",ii,id,fileIndex);
}

static void cxrfSourceIndex(int size,
                            int ri,
                            CharacterBuffer *cb,
                            int genFl
                            ) {
    int file, sfile;

    assert(ri == CXFI_SOURCE_INDEX);
    file = s_inLastInfos.counter[CXFI_FILE_INDEX];
    file = s_decodeFilesNum[file];
    sfile = s_inLastInfos.counter[CXFI_SOURCE_INDEX];
    sfile = s_decodeFilesNum[sfile];
    assert(file>=0 && file<MAX_FILES && s_fileTab.tab[file]);
    // hmmm. here be more generous in getting corrct source info
    if (s_fileTab.tab[file]->b.sourceFile == s_noneFileIndex) {
        //&fprintf(dumpOut,"setting %d source to %d\n", file, sfile);fflush(dumpOut);
        //&fprintf(dumpOut,"setting %s source to %s\n", s_fileTab.tab[file]->name, s_fileTab.tab[sfile]->name);fflush(dumpOut);
        // first check that it is not set directly from source
        if (! s_fileTab.tab[file]->b.cxLoading) {
            s_fileTab.tab[file]->b.sourceFile = sfile;
        }
    }
}

static int scanSymNameString(int size,
                             CharacterBuffer *cb,
                             char *id) {
    int i, len;
    char ch;

    for (i=0; i<size-1; i++) {
        ch = getChar(cb);
        id[i] = ch;
    }
    id[i] = 0;
    len = i;
    assert(len+1 < MAX_CX_SYMBOL_SIZE);

    return len;
}


static void getSymTypeAndClasses(int *_symType, int *_vApplClass,
                                 int *_vFunClass) {
    int symType, vApplClass, vFunClass;
    symType = s_inLastInfos.counter[CXFI_SYM_TYPE];
    vApplClass = s_inLastInfos.counter[CXFI_INFER_CLASS];
    vApplClass = s_decodeFilesNum[vApplClass];
    assert(s_fileTab.tab[vApplClass] != NULL);
    vFunClass = s_inLastInfos.counter[CXFI_SUPER_CLASS];
    vFunClass = s_decodeFilesNum[vFunClass];
    assert(s_fileTab.tab[vFunClass] != NULL);
    *_symType = symType;
    *_vApplClass = vApplClass;
    *_vFunClass = vFunClass;
}



static void cxrfSymbolNameForFullUpdateSchedule(int size,
                                                int ri,
                                                CharacterBuffer *cb,
                                                int additionalArg
                                                ) {
    SymbolReferenceItem *ddd, *memb;
    int out_index, si, symType, len, rr, vApplClass, vFunClass, accessFlags;
    int storage;
    char *id;
    char *ss;

    assert(ri == CXFI_SYM_NAME);
    accessFlags = s_inLastInfos.counter[CXFI_ACCESS_BITS];
    storage = s_inLastInfos.counter[CXFI_STORAGE];
    si = s_inLastInfos.counter[CXFI_SYM_INDEX];
    assert(si>=0 && si<MAX_CX_SYMBOL_TAB);
    id = s_inLastInfos._symbolTabNames[si];
    len = scanSymNameString(size, cb, id);
    getSymTypeAndClasses( &symType, &vApplClass, &vFunClass);
    //&fprintf(dumpOut,":scanning ref of %s %d %d: \n",id,symType,vFunClass);fflush(dumpOut);
    if (symType!=TypeCppInclude || strcmp(id, LINK_NAME_INCLUDE_REFS)!=0) {
        s_inLastInfos.onLineReferencedSym = -1;
        return;
    }
    ddd = &s_inLastInfos._symbolTab[si];
    s_inLastInfos.symbolTab[si] = ddd;
    fillSymbolRefItemExceptBits(ddd, id,
                                cxFileHashNumber(id), //useless, put 0
                                vApplClass, vFunClass);
    fillSymbolRefItemBits(&ddd->b, symType, storage, ScopeGlobal, accessFlags,
                           CategoryGlobal, 0);
    rr = refTabIsMember(&s_cxrefTab, ddd, &out_index, &memb);
    if (rr == 0) {
        CX_ALLOCC(ss, len+1, char);
        strcpy(ss,id);
        CX_ALLOC(memb, SymbolReferenceItem);
        fillSymbolRefItemExceptBits(memb,ss, cxFileHashNumber(ss),
                                    vApplClass, vFunClass);
        fillSymbolRefItemBits(&memb->b, symType, storage,
                               ScopeGlobal, accessFlags, CategoryGlobal,0);
        refTabAdd(&s_cxrefTab, memb, &out_index);
    }
    s_inLastInfos.symbolTab[si] = memb;
    s_inLastInfos.onLineReferencedSym = si;
}

static void cxfileCheckLastSymbolDeadness(void) {
    if (s_inLastInfos.symbolToCheckForDeadness != -1
        && s_inLastInfos.deadSymbolIsDefined) {
        //&sprintf(tmpBuff,"adding %s storage==%s", s_inLastInfos.symbolTab[s_inLastInfos.symbolToCheckForDeadness]->name, storagesName[s_inLastInfos.symbolTab[s_inLastInfos.symbolToCheckForDeadness]->b.storage]);ppcGenRecord(PPC_INFORMATION, tmpBuff, "\n");
        olAddBrowsedSymbol(s_inLastInfos.symbolTab[s_inLastInfos.symbolToCheckForDeadness],
                           &s_olcxCurrentUser->browserStack.top->hkSelectedSym,
                           1,1,0,UsageDefined,0, &s_noPos, UsageDefined);
    }
}


static int symbolIsReportableAsDead(SymbolReferenceItem *ss) {
    if (ss==NULL || ss->name[0]==' ')
        return(0);

    // you need to be strong here, in fact struct record can be used
    // without using struct explicitly
    if (ss->b.symType == TypeStruct)
        return(0);

    // maybe I should collect also all toString() references?
    if (ss->b.storage==StorageMethod && strcmp(ss->name,"toString()")==0)
        return(0);

    // in this first approach restrict this to variables and functions
    if (ss->b.symType == TypeMacro) return(0);
    return(1);
}

static void cxrfSymbolName(int size,
                           int ri,
                           CharacterBuffer *cb,
                           int additionalArg
                           ) {
    SymbolReferenceItem *ddd, *memb;
    S_olSymbolsMenu *cms;
    int not_used1, not_used2;
    int si, symType, len, rr, vApplClass, vFunClass, ols, accessFlags, storage;
    char *id;
    char *ss;

    assert(ri == CXFI_SYM_NAME);
    if (s_opt.taskRegime==RegimeEditServer && additionalArg==DEAD_CODE_DETECTION) {
        // check if previous symbol was dead
        cxfileCheckLastSymbolDeadness();
    }
    accessFlags = s_inLastInfos.counter[CXFI_ACCESS_BITS];
    storage = s_inLastInfos.counter[CXFI_STORAGE];
    si = s_inLastInfos.counter[CXFI_SYM_INDEX];
    assert(si>=0 && si<MAX_CX_SYMBOL_TAB);
    id = s_inLastInfos._symbolTabNames[si];
    len = scanSymNameString( size, cb, id);
    getSymTypeAndClasses(&symType, &vApplClass, &vFunClass);

    ddd = &s_inLastInfos._symbolTab[si];
    s_inLastInfos.symbolTab[si] = ddd;
    fillSymbolRefItemExceptBits(ddd,id,
                                cxFileHashNumber(id), // useless put 0
                                vApplClass, vFunClass);
    fillSymbolRefItemBits(&ddd->b,symType, storage, ScopeGlobal, accessFlags,
                           CategoryGlobal, 0);
    rr = refTabIsMember(&s_cxrefTab, ddd, &not_used1,&memb);
    while (rr && memb->b.category!=CategoryGlobal) rr=refTabNextMember(ddd, &memb);
    assert(s_opt.taskRegime);
    if (s_opt.taskRegime == RegimeHtmlGenerate) {
        if (memb==NULL) {
            CX_ALLOCC(ss, len+1, char);
            strcpy(ss,id);
            CX_ALLOC(memb, SymbolReferenceItem);
            fillSymbolRefItemExceptBits(memb, ss, cxFileHashNumber(ss),
                                        vApplClass, vFunClass);
            fillSymbolRefItemBits(&memb->b,symType, storage,
                                   ScopeGlobal, accessFlags, CategoryGlobal, 0);
            refTabAdd(&s_cxrefTab,memb, &not_used2);
        }
        s_inLastInfos.symbolTab[si] = memb;
    }
    if (s_opt.taskRegime == RegimeXref) {
        if (memb==NULL) memb=ddd;
        genRefItem0(memb,1);
        ddd->refs = memb->refs; // note references to not generate multiple
        memb->refs = NULL;      // HACK, remove them, to not be regenerated
    }
    if (s_opt.taskRegime == RegimeEditServer) {
        if (additionalArg == DEAD_CODE_DETECTION) {
            if (symbolIsReportableAsDead(s_inLastInfos.symbolTab[si])) {
                s_inLastInfos.symbolToCheckForDeadness = si;
                s_inLastInfos.deadSymbolIsDefined = 0;
            } else {
                s_inLastInfos.symbolToCheckForDeadness = -1;
            }
        } else if (s_opt.server_operation!=OLO_TAG_SEARCH) {
            cms = NULL; ols = 0;
            if (additionalArg == CX_MENU_CREATION) {
                cms = createSelectionMenu(ddd);
                if (cms == NULL) {
                    ols = 0;
                } else {
                    if (IS_BEST_FIT_MATCH(cms)) ols = 2;
                    else ols = 1;
                }
            } else if (additionalArg!=CX_BY_PASS) {
                ols=itIsSymbolToPushOlRefences(ddd,s_olcxCurrentUser->browserStack.top,&cms,DEFAULT_VALUE);
            }
            s_inLastInfos.onLineRefMenuItem = cms;
            log_trace("check (%s) %s ols==%d", miscellaneousEnumName[additionalArg], ddd->name, ols);
            if (ols || (additionalArg==CX_BY_PASS&&byPassAcceptableSymbol(ddd))
                ) {
                s_inLastInfos.onLineReferencedSym = si;
                s_inLastInfos.onLineRefIsBestMatchFlag = (ols == 2);
                log_trace("symbol %s is O.K. for %s (ols==%d)", ddd->name, s_opt.browsedSymName, ols);
            } else {
                if (s_inLastInfos.onLineReferencedSym == si) {
                    s_inLastInfos.onLineReferencedSym = -1;
                }
            }
        }
    }
}

static void cxrfReferenceForFullUpdateSchedule(int size,
                                               int ri,
                                               CharacterBuffer *cb,
                                               int additionalArg
                                               ) {
    Position pos;
    UsageBits usageBits;
    int file, line, coll, usage, sym, vApplClass, vFunClass;
    int symType,reqAcc;

    assert(ri == CXFI_REFERENCE);
    usage = s_inLastInfos.counter[CXFI_USAGE];
    reqAcc = s_inLastInfos.counter[CXFI_REQ_ACCESS];
    fillUsageBits(&usageBits, usage, reqAcc);
    sym = s_inLastInfos.counter[CXFI_SYM_INDEX];
    file = s_inLastInfos.counter[CXFI_FILE_INDEX];
    file = s_decodeFilesNum[file];
    assert(s_fileTab.tab[file]!=NULL);
    line = s_inLastInfos.counter[CXFI_LINE_INDEX];
    coll = s_inLastInfos.counter[CXFI_COLL_INDEX];
    getSymTypeAndClasses( &symType, &vApplClass, &vFunClass);
    log_trace("%d %d->%d %d", usage, file, s_decodeFilesNum[file], line);
    fillPosition(&pos,file,line,coll);
    if (s_inLastInfos.onLineReferencedSym ==
        s_inLastInfos.counter[CXFI_SYM_INDEX]) {
        addToRefList(&s_inLastInfos.symbolTab[sym]->refs,
                     &usageBits,&pos,CategoryGlobal);
    }
}

static void cxrfReference(int size,
                          int ri,
                          CharacterBuffer *cb,
                          int additionalArg
                          ) {
    Position pos;
    Reference rr;
    UsageBits usageBits;
    int file, line, coll, usage, sym, reqAcc;
    int copyrefFl;

    assert(ri == CXFI_REFERENCE);
    usage = s_inLastInfos.counter[CXFI_USAGE];
    reqAcc = s_inLastInfos.counter[CXFI_REQ_ACCESS];
    sym = s_inLastInfos.counter[CXFI_SYM_INDEX];
    file = s_inLastInfos.counter[CXFI_FILE_INDEX];
    file = s_decodeFilesNum[file];
    assert(s_fileTab.tab[file]!=NULL);
    line = s_inLastInfos.counter[CXFI_LINE_INDEX];
    coll = s_inLastInfos.counter[CXFI_COLL_INDEX];
    /*&fprintf(dumpOut,"%d %d %d  ", usage,file,line);fflush(dumpOut);&*/
    assert(s_opt.taskRegime);
    if (s_opt.taskRegime == RegimeXref) {
        if (s_opt.keep_old ||
            (s_fileTab.tab[file]->b.cxLoading&&s_fileTab.tab[file]->b.cxSaved)
            ) {
            /* if keep_old or if we repass refs after overflow */
            fillPosition(&pos,file,line,coll);
            fillUsageBits(&usageBits, usage, reqAcc);
            copyrefFl = ! isInRefList(s_inLastInfos.symbolTab[sym]->refs,
                                      &usageBits, &pos, CategoryGlobal);
        } else {
            copyrefFl = ! s_fileTab.tab[file]->b.cxLoading;
        }
        if (copyrefFl) writeCxReferenceBase(sym, usage, reqAcc, file, line, coll);
    } else  if (s_opt.taskRegime == RegimeHtmlGenerate) {
        fillPosition(&pos,file,line,coll);
        fillUsageBits(&usageBits, usage, reqAcc);
        fill_reference(&rr, usageBits, pos, NULL);
        assert(sym>=0 && sym<MAX_CX_SYMBOL_TAB);
        if (additionalArg==CX_HTML_SECOND_PASS) {
            if (rr.usage.base<UsageMaxOLUsages || rr.usage.base==UsageClassTreeDefinition) {
                addToRefList(&s_inLastInfos.symbolTab[sym]->refs,
                             &rr.usage,&rr.p,CategoryGlobal);
            }
        } else if (rr.usage.base==UsageDefined || rr.usage.base==UsageDeclared
                   ||  !s_fileTab.tab[rr.p.file]->b.commandLineEntered ) {
            log_trace("htmladdref %s on %s:%d", s_inLastInfos.symbolTab[sym]->name,
                      s_fileTab.tab[rr.p.file]->name, rr.p.line);
            addToRefList(&s_inLastInfos.symbolTab[sym]->refs,
                         &rr.usage,&rr.p,CategoryGlobal);
        }
    } else if (s_opt.taskRegime == RegimeEditServer) {
        fillPosition(&pos,file,line,coll);
        fillUsageBits(&usageBits, usage, reqAcc);
        fill_reference(&rr, usageBits, pos, NULL);
        if (additionalArg == DEAD_CODE_DETECTION) {
            if (OL_VIEWABLE_REFS(&rr)) {
                // restrict reported symbols to those defined in project
                // input file
                if (IS_DEFINITION_USAGE(rr.usage.base)
                    && s_fileTab.tab[rr.p.file]->b.commandLineEntered
                    ) {
                    s_inLastInfos.deadSymbolIsDefined = 1;
                } else if (! IS_DEFINITION_OR_DECL_USAGE(rr.usage.base)) {
                    s_inLastInfos.symbolToCheckForDeadness = -1;
                }
            }
        } else if (additionalArg == OL_LOOKING_2_PASS_MACRO_USAGE) {
            if (    s_inLastInfos.onLineReferencedSym ==
                    s_inLastInfos.counter[CXFI_SYM_INDEX]
                    &&  rr.usage.base == UsageMacroBaseFileUsage) {
                s_olMacro2PassFile = rr.p.file;
            }
        } else {
            if (s_opt.server_operation == OLO_TAG_SEARCH) {
                if (rr.usage.base==UsageDefined
                    || ((s_opt.tagSearchSpecif==TSS_FULL_SEARCH
                         || s_opt.tagSearchSpecif==TSS_FULL_SEARCH_SHORT)
                        &&  (rr.usage.base==UsageDeclared
                             || rr.usage.base==UsageClassFileDefinition))) {
                    searchSymbolCheckReference(s_inLastInfos.symbolTab[sym],&rr);
                }
            } else if (s_opt.server_operation == OLO_SAFETY_CHECK1) {
                if (    s_inLastInfos.onLineReferencedSym !=
                        s_inLastInfos.counter[CXFI_SYM_INDEX]) {
                    olcxCheck1CxFileReference(s_inLastInfos.symbolTab[sym],
                                              &rr);
                }
            } else {
                if (    s_inLastInfos.onLineReferencedSym ==
                        s_inLastInfos.counter[CXFI_SYM_INDEX]) {
                    if (additionalArg == CX_MENU_CREATION) {
                        assert(s_inLastInfos.onLineRefMenuItem);
                        if (s_opt.keep_old
                            || file!=s_olOriginalFileNumber
                            || !s_fileTab.tab[file]->b.commandLineEntered
                            || s_opt.server_operation==OLO_GOTO
                            || s_opt.server_operation==OLO_CGOTO
                            || s_opt.server_operation==OLO_PUSH_NAME
                            || s_opt.server_operation==OLO_PUSH_SPECIAL_NAME
                            ) {
                            //&fprintf(dumpOut,":adding reference %s:%d\n", s_fileTab.tab[rr.p.file]->name, rr.p.line);
                            olcxAddReferenceToOlSymbolsMenu(s_inLastInfos.onLineRefMenuItem, &rr, s_inLastInfos.onLineRefIsBestMatchFlag);
                        }
                    } else if (additionalArg == CX_BY_PASS) {
                        if (POSITION_EQ(s_olcxByPassPos,rr.p)) {
                            // got the bypass reference
                            //&fprintf(dumpOut,":adding bypass selected symbol %s\n", s_inLastInfos.symbolTab[sym]->name);
                            olAddBrowsedSymbol(s_inLastInfos.symbolTab[sym],
                                               &s_olcxCurrentUser->browserStack.top->hkSelectedSym,
                                               1, 1, 0, usage,0,&s_noPos, UsageNone);
                        }
                    } else if (1
                               /*&
                                 s_opt.keep_old
                                 || file!=s_olOriginalFileNumber
                                 || !s_fileTab.tab[file]->b.commandLineEntered
                                 || s_opt.server_operation==OLO_GOTO || s_opt.server_operation==OLO_CGOTO
                                 &*/
                               ) {
                        // this is only goto definition from completion menu?
                        //&sprintf(tmpBuff,"%s %s:%d\n", usageEnumName[usage],s_fileTab.tab[file]->name,line);ppcGenRecord(PPC_INFORMATION,tmpBuff,"\n");
                        //&fprintf(dumpOut,"%s %s:%d\n", usageEnumName[usage],s_fileTab.tab[file]->name,line);fflush(dumpOut);
                        olcxAddReference(&s_olcxCurrentUser->browserStack.top->r, &rr,
                                         s_inLastInfos.onLineRefIsBestMatchFlag);
                    }
                }
            }
        }
    }
}


static void cxrfRefNum(int fileRefNum,
                       int ri,
                       CharacterBuffer *cb,
                       int additionalArg
                       ) {
    int check;

    check = changeRefNumOption(fileRefNum);
    if (check == 0) {
        assert(s_opt.taskRegime);
        fatalError(ERR_ST,"Tag file was generated with different '-refnum' options, recreate it!", XREF_EXIT_ERR);
    }
}

static void cxrfSubClass(int size,
                         int ri,
                         CharacterBuffer *cb,
                         int additionalArg
                         ) {
    int of, file, sup, inf;

    assert(ri == CXFI_CLASS_EXT);
    file = of = s_inLastInfos.counter[CXFI_FILE_INDEX];
    sup = s_inLastInfos.counter[CXFI_SUPER_CLASS];
    inf = s_inLastInfos.counter[CXFI_INFER_CLASS];
    /*fprintf(dumpOut,"%d %d->%d %d  ", usage,file,s_decodeFilesNum[file],line);*/
    /*fflush(dumpOut);*/
    file = s_decodeFilesNum[file];
    //&if (s_fileTab.tab[file]==NULL) {fprintf(dumpOut,"!%d->%d %d %d ",of,file,sup,inf);}
    assert(s_fileTab.tab[file]!=NULL);
    sup = s_decodeFilesNum[sup];
    assert(s_fileTab.tab[sup]!=NULL);
    inf = s_decodeFilesNum[inf];
    assert(s_fileTab.tab[inf]!=NULL);
    assert(s_opt.taskRegime);
    if (s_opt.taskRegime == RegimeHtmlGenerate) {
        createSubClassInfo(sup, inf, file, NO_CX_FILE_ITEM_GEN);
    }
    if (s_opt.taskRegime == RegimeXref) {
        if (!s_fileTab.tab[file]->b.cxLoading &&
            additionalArg==CX_GENERATE_OUTPUT) {
            writeSubClassInfo(sup, inf, file);  // updating refs
            //&         createSubClassInfo(sup, inf, file, CX_FILE_ITEM_GEN);
        }
    }
    if (s_opt.taskRegime == RegimeEditServer) {
        if (file!=s_input_file_number) {
            log_trace("reading %s < %s", simpleFileName(s_fileTab.tab[inf]->name),simpleFileName(s_fileTab.tab[sup]->name));
            createSubClassInfo(sup, inf, file, NO_CX_FILE_ITEM_GEN);
        }
    }
}


static int scanInteger(CharacterBuffer *cb, int *_ch) {
    int scannedInt, ch = *_ch;
    ch = skipWhiteSpace(cb, ch);
    scannedInt = 0;
    while (isdigit(ch)) {
        scannedInt = scannedInt*10 + ch-'0';
        ch = getChar(&cxfCharacterBuffer);
    }
    *_ch = ch;

    return scannedInt;
}



void scanCxFile(ScanFileFunctionStep *scanFuns) {
    int scannedInt = 0;
    int ch,i;

    ENTER();
    if (inputFile == NULL) {
        log_trace("No input file");
        LEAVE();
        return;
    }

    memset(&s_inLastInfos, 0, sizeof(s_inLastInfos));
    s_inLastInfos.onLineReferencedSym = -1;
    s_inLastInfos.symbolToCheckForDeadness = -1;
    s_inLastInfos.onLineRefMenuItem = NULL;
    s_inLastInfos.singleRecord[CXFI_INFER_CLASS] = s_noneFileIndex;
    s_inLastInfos.singleRecord[CXFI_SUPER_CLASS] = s_noneFileIndex;
    s_decodeFilesNum[s_noneFileIndex] = s_noneFileIndex;
    for(i=0; scanFuns[i].recordCode>0; i++) {
        assert(scanFuns[i].recordCode < MAX_CHARS);
        ch = scanFuns[i].recordCode;
        s_inLastInfos.fun[ch] = scanFuns[i].handleFun;
        s_inLastInfos.additional[ch] = scanFuns[i].additionalArg;
    }
    initCharacterBuffer(&cxfCharacterBuffer, inputFile);
    ch = ' ';
    while(! cxfCharacterBuffer.isAtEOF) {
        CharacterBuffer *cb = &cxfCharacterBuffer;
        scannedInt = scanInteger(cb, &ch);
        if (cxfCharacterBuffer.isAtEOF)
            break;
        assert(ch >= 0 && ch<MAX_CHARS);
        if (s_inLastInfos.singleRecord[ch]) {
            s_inLastInfos.counter[ch] = scannedInt;
        }
        if (s_inLastInfos.fun[ch] != NULL) {
            (*s_inLastInfos.fun[ch])(scannedInt, ch, &cxfCharacterBuffer,
                                     s_inLastInfos.additional[ch]);
        } else if (! s_inLastInfos.singleRecord[ch]) {
            assert(scannedInt>0);
            //& CxSkipNChars(scannedInt-1, next, end, cb);
            {
                int ccount = scannedInt-1;
                while (cb->next + ccount > cb->end) {
                    ccount -= cb->end - cb->next;
                    cb->next = cb->end;
                    ch = getChar(cb);
                    ccount --;
                }
                cb->next += ccount;
            }
        }
        ch = getChar(&cxfCharacterBuffer);
    }
    if (s_opt.taskRegime==RegimeEditServer
        && (s_opt.server_operation==OLO_LOCAL_UNUSED
            || s_opt.server_operation==OLO_GLOBAL_UNUSED)) {
        // check if last symbol was dead
        cxfileCheckLastSymbolDeadness();
    }
    LEAVE();
}


/* fnamesuff contains '/' at the beginning !!! */
int scanReferenceFile(char *fname, char *fns1, char *fns2, /* TODO: bool? */
                      ScanFileFunctionStep *scanFunTab) {
    char fn[MAX_FILE_NAME_SIZE];

    sprintf(fn, "%s%s%s", fname, fns1, fns2);
    assert(strlen(fn) < MAX_FILE_NAME_SIZE-1);
    log_trace(":scanning file %s", fn);
    inputFile = openFile(fn, "r");
    if (inputFile==NULL) {
        return(0);
    } else {
        scanCxFile(scanFunTab);
        closeFile(inputFile);
        inputFile = NULL;
        return(1);
    }
}

void scanReferenceFiles(char *fname, ScanFileFunctionStep *scanFunTab) {
    char nn[MAX_FILE_NAME_SIZE];
    int i;

    if (s_opt.referenceFileCount <= 1) {
        scanReferenceFile(fname,"","",scanFunTab);
    } else {
        scanReferenceFile(fname,REFERENCE_FILENAME_FILES,"",scanFunTab);
        scanReferenceFile(fname,REFERENCE_FILENAME_CLASSES,"",scanFunTab);
        for (i=0; i<s_opt.referenceFileCount; i++) {
            sprintf(nn,"%04d",i);
            scanReferenceFile(fname,REFERENCE_FILENAME_PREFIX,nn,scanFunTab);
        }
    }
}

int smartReadFileTabFile(void) {
    static time_t   readedFileModTime = 0;
    static off_t    readedFileSize = 0;
    static char     readedFileFile[MAX_FILE_NAME_SIZE] = {0};
    char            tt[MAX_FILE_NAME_SIZE];
    struct stat     st;
    int             tmp;
    if (s_opt.referenceFileCount > 1) {
        sprintf(tt, "%s%s", s_opt.cxrefFileName, REFERENCE_FILENAME_FILES);
    } else {
        sprintf(tt, "%s", s_opt.cxrefFileName);
    }
    if (statb(tt,&st)==0) {
        if (    readedFileModTime != st.st_mtime
                ||  readedFileSize != st.st_size
                ||  strcmp(readedFileFile, tt) != 0) {
            log_trace(":(re)reading file tab");
            tmp = scanReferenceFile(tt,"","",normalScanFunctionSequence);
            if (tmp != 0) {
                readedFileModTime = st.st_mtime;
                readedFileSize = st.st_size;
                strcpy(readedFileFile, tt);
            }
        } else {
            log_trace(":saving the (re)reading of file tab");
        }
        return(1);
    }
    return(0);
}

// symbolName can be NULL !!!!!!
void readOneAppropReferenceFile(char *symbolName,
                                ScanFileFunctionStep  *scanFileFunctionTable
                                ) {
    static char fns[MAX_FILE_NAME_SIZE];
    int i,tmp;
    //& if (s_opt.server_operation!=OLO_CGOTO && ! creatingOlcxRefs()) return;
    if (s_opt.cxrefFileName == NULL) return;
    cxOut = stdout;
    if (s_opt.referenceFileCount <= 1) {
        tmp = scanReferenceFile(s_opt.cxrefFileName,"","",scanFileFunctionTable);
        if (tmp == 0) return;
    } else {
        tmp = smartReadFileTabFile();
        if (tmp == 0) return;
        tmp = scanReferenceFile(s_opt.cxrefFileName, REFERENCE_FILENAME_CLASSES, "",
                                scanFileFunctionTable);
        if (tmp == 0) return;
        if (symbolName == NULL) return;
        /* following must be after reading XFiles*/
        i = cxFileHashNumber(symbolName);
        //&fprintf(dumpOut,"reading X%04d\n",i);fflush(dumpOut);
        sprintf(fns, "%04d", i);
        assert(strlen(fns) < MAX_FILE_NAME_SIZE-1);
        tmp = scanReferenceFile(s_opt.cxrefFileName,REFERENCE_FILENAME_PREFIX,fns,
                                scanFileFunctionTable);
        if (tmp == 0) return;
    }
}

/* ************************************************************ */


ScanFileFunctionStep normalScanFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_CHECK_NUMBER, cxrfCheckNumber, 0},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep fullScanFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_VERSION, cxrfVersionCheck, 0},
    {CXFI_CHECK_NUMBER, cxrfCheckNumber, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_GENERATE_OUTPUT},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_GENERATE_OUTPUT},
    {CXFI_SYM_NAME, cxrfSymbolName, DEFAULT_VALUE},
    {CXFI_REFERENCE, cxrfReference, CX_HTML_FIRST_PASS},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_GENERATE_OUTPUT},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep byPassFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_VERSION, cxrfVersionCheck, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, CX_BY_PASS},
    {CXFI_REFERENCE, cxrfReference, CX_BY_PASS},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep symbolLoadMenuRefsFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_VERSION, cxrfVersionCheck, 0},
    {CXFI_CHECK_NUMBER, cxrfCheckNumber, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, DEFAULT_VALUE},
    {CXFI_REFERENCE, cxrfReference, CX_MENU_CREATION},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep symbolMenuCreationFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_VERSION, cxrfVersionCheck, 0},
    {CXFI_CHECK_NUMBER, cxrfCheckNumber, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, CX_MENU_CREATION},
    {CXFI_REFERENCE, cxrfReference, CX_MENU_CREATION},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep fullUpdateFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_VERSION, cxrfVersionCheck, 0},
    {CXFI_CHECK_NUMBER, cxrfCheckNumber, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolNameForFullUpdateSchedule, DEFAULT_VALUE},
    {CXFI_REFERENCE, cxrfReferenceForFullUpdateSchedule, DEFAULT_VALUE},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep secondPassMacroUsageFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, DEFAULT_VALUE},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, OL_LOOKING_2_PASS_MACRO_USAGE},
    {CXFI_REFERENCE, cxrfReference, OL_LOOKING_2_PASS_MACRO_USAGE},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, DEFAULT_VALUE},
    {-1,NULL, 0},
};

ScanFileFunctionStep classHierarchyFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, DEFAULT_VALUE},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_REFNUM, cxrfRefNum, DEFAULT_VALUE},
    {-1,NULL, 0},
};

ScanFileFunctionStep htmlGlobalReferencesFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_CLASS_EXT, cxrfSubClass, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, CX_HTML_SECOND_PASS},
    {CXFI_REFERENCE, cxrfReference, CX_HTML_SECOND_PASS},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {-1,NULL, 0},
};

ScanFileFunctionStep symbolSearchFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, SEARCH_SYMBOL},
    {CXFI_REFERENCE, cxrfReference, CX_HTML_FIRST_PASS},
    {-1,NULL, 0},
};

ScanFileFunctionStep deadCodeDetectionFunctionSequence[]={
    {CXFI_SINGLE_RECORDS, cxrfSetSingleRecords, 0},
    {CXFI_REFNUM, cxrfRefNum, 0},
    {CXFI_FILE_NAME, cxReadFileName, CX_JUST_READ},
    {CXFI_SOURCE_INDEX, cxrfSourceIndex, CX_JUST_READ},
    {CXFI_SYM_NAME, cxrfSymbolName, DEAD_CODE_DETECTION},
    {CXFI_REFERENCE, cxrfReference, DEAD_CODE_DETECTION},
    {-1,NULL, 0},
};
