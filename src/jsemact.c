#include "jsemact.h"

#include "commons.h"
#include "globals.h"
#include "options.h"
#include "classcaster.h"
#include "misc.h"
#include "extract.h"
#include "yylex.h"
#include "semact.h"
#include "cxref.h"
#include "classfilereader.h"
#include "filedescriptor.h"
#include "editor.h"
#include "symbol.h"
#include "javafqttab.h"
#include "list.h"
#include "fileio.h"

#include "java_parser.h"

#include "parsers.h"
#include "recyacc.h"
#include "jslsemact.h"

#include "protocol.h"

#include "log.h"


typedef enum {
    RESULT_IS_CLASS_FILE,
    RESULT_IS_JAVA_FILE,
    RESULT_NO_FILE_FOUND
} FindJavaFileResult;


S_javaStat *s_javaStat;
S_javaStat s_initJavaStat;


#define IsJavaReferenceType(m) (m==TypeStruct || m==TypeArray)

static int javaNotFqtUsageCorrection(Symbol *sym, int usage);


void fill_nestedSpec(S_nestedSpec *nestedSpec, struct symbol *cl,
                     char membFlag, short unsigned  accFlags) {
    nestedSpec->cl = cl;
    nestedSpec->membFlag = membFlag;
    nestedSpec->accFlags = accFlags;
}

void fillJavaStat(S_javaStat *javaStat, IdList *className, TypeModifier *thisType, Symbol *thisClass,
                  int currentNestedIndex, char *currentPackage, char *unnamedPackagePath,
                  char *namedPackagePath, SymbolTable *locals, IdList *lastParsedName,
                  unsigned methodModifiers, S_currentlyParsedCl parsingPositions, int classFileIndex,
                  S_javaStat *next) {

    javaStat->className = className;
    javaStat->thisType = thisType;
    javaStat->thisClass = thisClass;
    javaStat->currentNestedIndex = currentNestedIndex;
    javaStat->currentPackage = currentPackage;
    javaStat->unnamedPackagePath = unnamedPackagePath;
    javaStat->namedPackagePath = namedPackagePath;
    javaStat->locals = locals;
    javaStat->lastParsedName = lastParsedName;
    javaStat->methodModifiers = methodModifiers;
    javaStat->cp = parsingPositions;
    javaStat->classFileIndex = classFileIndex;
    javaStat->next = next;
}


char *javaCreateComposedName(char *prefix,
                             IdList *className,
                             int classNameSeparator,
                             char *name,
                             char *resBuff,
                             int resBuffSize
) {
    int len, ll;
    bool sss;
    char *ln;
    char separator;
    IdList *ids;

    if (name == NULL)
        name = "";
    if (prefix == NULL)
        prefix = "";
    sss = false;
    len = 0;
    ll = strlen(prefix);
    if (ll!=0)
        sss = true;
    len += ll;
    for (ids=className; ids!=NULL; ids=ids->next) {
        if (sss)
            len ++;
        len += strlen(ids->fname);
        sss = true;
    }
    ll = strlen(name);
    if (sss && ll!=0)
        len++;
    len += ll;
    if (resBuff == NULL) {
        ln = StackMemoryAllocC(len+1, char);
    } else {
        assert(len < resBuffSize);
        ln = resBuff;
    }
    ll = strlen(name);
    len -= ll;
    strcpy(ln+len,name);
    if (ll == 0)
        sss = false;
    else
        sss = true;
    separator = '.';
    for (ids=className; ids!=NULL; ids=ids->next) {
        if (sss) {
            len --;
            ln[len] = separator;
        }
        ll = strlen(ids->fname);
        len -= ll;
        strncpy(ln+len,ids->fname,ll);
        sss = true;
        assert(ids->nameType==TypeStruct || ids->nameType==TypePackage
                || ids->nameType==TypeExpression);
        if (ids->nameType==TypeStruct &&
                ids->next!=NULL && ids->next->nameType==TypeStruct) {
            separator = '$';
        } else {
            separator = classNameSeparator;
        }
    }
    ll = strlen(prefix);
    if (sss && ll!=0) {
        len --;
        ln[len] = separator;
    }
    len -= ll;
    strncpy(ln+len, prefix, ll);
    assert(len == 0);
    return ln;
}

void javaCheckForPrimaryStart(Position *cpos, Position *bpos) {
    if (options.taskRegime != RegimeEditServer) return;
    if (positionsAreEqual(s_cxRefPos, *cpos)) {
        s_primaryStartPosition = *bpos;
    }
}

void javaCheckForPrimaryStartInNameList(IdList *name, Position *pp) {
    IdList *ll;
    if (options.taskRegime != RegimeEditServer) return;
    for(ll=name; ll!=NULL; ll=ll->next) {
        javaCheckForPrimaryStart(&ll->id.p, pp);
    }
}

void javaCheckForStaticPrefixStart(Position *cpos, Position *bpos) {
    if (options.taskRegime != RegimeEditServer) return;
    if (positionsAreEqual(s_cxRefPos, *cpos)) {
        s_staticPrefixStartPosition = *bpos;
    }
}

void javaCheckForStaticPrefixInNameList(IdList *name, Position *pp) {
    IdList *ll;
    if (options.taskRegime != RegimeEditServer) return;
    for(ll=name; ll!=NULL; ll=ll->next) {
        javaCheckForStaticPrefixStart(&ll->id.p, pp);
    }
}

Position *javaGetNameStartingPosition(IdList *name) {
    IdList *ll;
    Position *res;
    res = &s_noPos;
    for(ll=name; ll!=NULL; ll=ll->next) {
        res = &ll->id.p;
    }
    return res;
}

static Reference *javaAddClassCxReference(Symbol *dd, Position *pos, unsigned usage) {
    Reference *res;
    res = addCxReference(dd, pos, usage, noFileIndex, noFileIndex);
    return res;
}

static void javaAddNameCxReference(IdList *id, unsigned usage) {
    char *cname;
    Symbol dd;
    char tmpString[MAX_SOURCE_PATH_SIZE];

    assert(id != NULL);
    cname = javaCreateComposedName(NULL, id, '/', NULL, tmpString, sizeof(tmpString));
    fillSymbol(&dd, id->id.name, cname, id->id.p);
    fillSymbolBits(&dd.bits, AccessDefault, id->nameType, StorageNone);

    /* if you do something else do attention on the union initialisation */
    addCxReference(&dd, &id->id.p, usage, noFileIndex, noFileIndex);
}

Symbol *javaAddType(IdList *class, Access access, Position *p) {
    Symbol *dd;
    dd = javaTypeSymbolDefinition(class, access, ADD_YES);
    dd->bits.access = access;
    addCxReference(dd, p, UsageDefined, noFileIndex, noFileIndex);
    return dd;
}

void javaAddNestedClassesAsTypeDefs(Symbol *cc, IdList *oclassname,
                                    int accessFlags) {
    S_symStructSpec *ss;
    IdList	ll;
    Symbol        *nn;

    assert(cc && cc->bits.symbolType==TypeStruct);
    ss = cc->u.structSpec;
    assert(ss);
    for (int i=0; i<ss->nestedCount; i++) {
        if (ss->nest[i].membFlag) {
            nn = ss->nest[i].cl;
            assert(nn);
            fillId(&ll.id, nn->name, cc, s_noPos);
            fillIdList(&ll, ll.id, nn->name,TypeStruct,oclassname);
            javaTypeSymbolDefinition(&ll, accessFlags, ADD_YES);
        }
    }
}

// resName can be NULL!!!
static bool javaFindFile0(char *classPath, char *separator, char *name,
                          char *suffix, char **resultingName) {
    char fullName[MAX_FILE_NAME_SIZE];
    char *normalizedFileName;
    bool found = false;

    snprintf(fullName, MAX_FILE_NAME_SIZE, "%s%s%s%s", classPath, separator, name, suffix);
    assert(strlen(fullName)+1 < MAX_FILE_NAME_SIZE);

    normalizedFileName = normalizeFileName(fullName, cwd);
    log_trace("looking for file '%s'", normalizedFileName);
    if (editorFileExists(normalizedFileName)) {
        log_trace("found in buffer file '%s'", normalizedFileName);
        found = true;
    }
    if (found && resultingName!=NULL) {
        *resultingName = StackMemoryAllocC(strlen(normalizedFileName)+1, char);
        strcpy(*resultingName, normalizedFileName);
    }
    return found;
}

static int specialFileNameCasesCheck(char *fname) {
#ifdef __WIN32__
    WIN32_FIND_DATA		fdata;
    HANDLE				handle;
    int					dif;
    char				*ss;
    EditorBuffer		*buff;
    // first check if the file is from editor
    buff = editorGetOpenedBuffer(fname);
    if (buff != NULL)
        return true;
    // there is only drive name before the first slash, copy it.
    ss = lastOccurenceInString(fname, '/');
    if (ss==NULL)
        ss = lastOccurenceInString(fname, '\\');
    if (ss==NULL)
        return true;
    log_trace("translating %s", ttt);
    handle = FindFirstFile(fname, &fdata);
    if (handle == INVALID_HANDLE_VALUE)
        return true;
    dif = strcmp(ss+1, fdata.cFileName);
    FindClose(handle);
    log_trace("result %s", ttt);
    return dif==0;
#else
    return true;
#endif
}

/* TODO this function strangely ressembles to javaFindFile, join them ????*/
bool javaTypeFileExist(IdList *name) {
    char *fname;
    IdList tname;
    char tmpString[MAX_SOURCE_PATH_SIZE];

    if (name==NULL)
        return false;
    tname = *name;
    tname.nameType = TypeStruct;

    // first check if I have its class in file table
    // hmm this is causing problems in on-line editing when some misspelled
    // completion strings were added as types, then a package is resolved
    // as a type and a File from inside directory is not completed.
    // I try to solve it by requiring sourcefile index
    fname = javaCreateComposedName(":", &tname, '/', "class",
                                   tmpString, sizeof(tmpString));
    fname[1] = ZIP_SEPARATOR_CHAR;

    if (fileTableExists(&fileTable, fname+1)) {
        int fileIndex = fileTableLookup(&fileTable, fname+1);
        if (fileTable.tab[fileIndex]->b.sourceFileNumber != noFileIndex) {
            return true;
        }
    }

    if (s_javaStat->unnamedPackagePath != NULL) {		/* unnamed package */
        fname = javaCreateComposedName(NULL, &tname, FILE_PATH_SEPARATOR, "java",
                                       tmpString, sizeof(tmpString));
        log_trace("testing existence of file '%s'", fname);
        if (editorFileExists(fname) && specialFileNameCasesCheck(fname))
            return true;
    }
    MapOnPaths(javaSourcePaths, {
            fname = javaCreateComposedName(currentPath, &tname, FILE_PATH_SEPARATOR, "java",
                                           tmpString, sizeof(tmpString));
            log_trace("testing existence of file '%s'", fname);
            if (editorFileExists(fname) && specialFileNameCasesCheck(fname))
                return true;
        });
    for (StringList *cp=javaClassPaths; cp!=NULL; cp=cp->next) {
        fname = javaCreateComposedName(cp->string, &tname, FILE_PATH_SEPARATOR, "class",
                                       tmpString, sizeof(tmpString));
        // hmm. do not need to check statb for .class files
        if (editorFileExists(fname) && specialFileNameCasesCheck(fname))
            return true;
    }
    // Archives...
    fname=javaCreateComposedName(NULL, &tname, '/', "class", tmpString, sizeof(tmpString));
    for (int i=0; i<MAX_JAVA_ZIP_ARCHIVES && zipArchiveTable[i].fn[0]!=0; i++) {
        if (fsIsMember(&zipArchiveTable[i].dir,fname,0,ADD_NO,NULL))
            return true;
    }
    // auto-inferred source-path
    if (s_javaStat->namedPackagePath != NULL) {
        fname = javaCreateComposedName(s_javaStat->namedPackagePath, &tname, FILE_PATH_SEPARATOR, "java",
                                       tmpString, sizeof(tmpString));
        if (editorFileExists(fname) && specialFileNameCasesCheck(fname))
            return true;
    }
    return false;
}

static bool javaFindClassFile(char *name, char **resultingName, struct stat *stat) {
    if (s_javaStat->unnamedPackagePath != NULL) {		/* unnamed package */
        if (javaFindFile0(s_javaStat->unnamedPackagePath, "/", name, ".class",
                          resultingName)) {
            editorFileStatus(*resultingName, stat);
            return true;
        }
    }
    // now other classpaths
    for (StringList *cp=javaClassPaths; cp!=NULL; cp=cp->next) {
        if (javaFindFile0(cp->string, "/", name, ".class", resultingName)) {
            editorFileStatus(*resultingName, stat);
            return true;
        }
    }
    // finally look into java archives
    /* TODO: if it were not for this, we could skip the stat return value */
    for (int i=0; i<MAX_JAVA_ZIP_ARCHIVES && zipArchiveTable[i].fn[0]!=0; i++) {
        log_trace("Looking in '%s'", zipArchiveTable[i].fn);
        if (zipFindFile(name,resultingName,&zipArchiveTable[i])) {
            *stat = zipArchiveTable[i].stat;
            return true;
        }
    }
    return false;
}

static int javaFindSourceFile(char *name, char **resultingName) {
    StringList	*cp;

    if (s_javaStat->unnamedPackagePath != NULL) {		/* unnamed package */
        if (javaFindFile0(s_javaStat->unnamedPackagePath, "/", name, ".java", resultingName))
            return true;
    }
    // sourcepaths
    MapOnPaths(javaSourcePaths, {
        if (javaFindFile0(currentPath, "/", name, ".java", resultingName))
            return true;
    });
    // now other classpaths
    for (cp=javaClassPaths; cp!=NULL; cp=cp->next) {
        if (javaFindFile0(cp->string, "/", name, ".java", resultingName))
            return true;
    }
    // auto-inferred source-path
    if (s_javaStat->namedPackagePath != NULL) {
        if (javaFindFile0(s_javaStat->namedPackagePath, "/", name, ".java", resultingName))
            return true;
    }
    return false;
}

// if file exists, then set its name
static FindJavaFileResult javaFindFile(Symbol *classSymbol,
                                       char **sourceFileNameP,
                                       char **classFileNameP
) {
    int sourceIndex;
    bool classFound;
    bool sourceFound;
    struct stat classStat;
    char *linkName, *slname;

    log_trace("looking for Java file '%s'", classSymbol->linkName);
    linkName = slname = classSymbol->linkName;
    if (strchr(linkName, '$')!=NULL) {
        char innerName[MAX_FILE_NAME_SIZE];
        char *dollarPosition;
        // looking for an inner class, source must be included in outer file
        strcpy(innerName, classSymbol->linkName);
        slname = innerName;
        dollarPosition = strchr(innerName, '$');
        assert(dollarPosition);
        *dollarPosition = 0;
    }
    *classFileNameP = *sourceFileNameP = "";
    //&fprintf(dumpOut,"!looking for %s.classf(in %s)== %d\n", linkName, slname, classSymbol->u.structSpec->classFile); fflush(dumpOut);fprintf(dumpOut,"!looking for %s %s\n", linkName, fileTable.tab[classSymbol->u.structSpec->classFile]->name); fflush(dumpOut);
    sourceFound = javaFindSourceFile(slname, sourceFileNameP);
    assert(classSymbol->u.structSpec && fileTable.tab[classSymbol->u.structSpec->classFile]);
    sourceIndex = fileTable.tab[classSymbol->u.structSpec->classFile]->b.sourceFileNumber;

    if (!sourceFound && sourceIndex!=-1 && sourceIndex!=noFileIndex) {
        // try the source indicated by source field of filetab
        assert(fileTable.tab[sourceIndex]);
        //&fprintf(dumpOut,"checking %s\n", fileTable.tab[sourceIndex]->name);
        sourceFound = javaFindFile0("","",fileTable.tab[sourceIndex]->name, "", sourceFileNameP);
        //&fprintf(dumpOut,"result %d %s\n", sourceFound, *sourceFileNameP);
    }

    /* We need to retain the stat value for class files since it can be inside an archive */
    classFound = javaFindClassFile(linkName, classFileNameP, &classStat);
    if (!classFound)
        *classFileNameP = NULL;
    if (!sourceFound)
        *sourceFileNameP = NULL;

    log_trace("found source file: %s, found class file: %s)", sourceFound?"yes":"no", classFound?"yes":"no");
    if (options.javaSlAllowed == 0) {
        if (classFound)
            return RESULT_IS_CLASS_FILE;
        else
            return RESULT_NO_FILE_FOUND;
    }
    if (!classFound && !sourceFound)
        return RESULT_NO_FILE_FOUND;
    if (classFound && !sourceFound)
        return RESULT_IS_CLASS_FILE;
    if (!classFound && sourceFound)
        return RESULT_IS_JAVA_FILE;
    assert(sourceFound && classFound);

    if (fileModificationTime(*sourceFileNameP) > classStat.st_mtime) {
        return RESULT_IS_JAVA_FILE;
    } else {
        return RESULT_IS_CLASS_FILE;
    }
}

static int javaFqtNameIsFromThePackage(char *cpack, char *classFqName) {
    char   *p1,*p2;

    for(p1=cpack, p2=classFqName; *p1 == *p2; p1++,p2++) ;
    if (*p1 != 0) return false;
    if (*p2 == 0) return false;
    //& if (*p2 != '/') return false;
    for(p2++; *p2; p2++) if (*p2 == '/') return false;
    return true;
}

int javaFqtNamesAreFromTheSamePackage(char *nn1, char *nn2) {
    char   *p1,*p2;

    if (nn1==NULL || nn2==NULL) return false;
//&fprintf(dumpOut,"checking equal package %s %s\n", nn1, nn2);
    for(p1=nn1, p2=nn2; *p1 == *p2 && *p1 && *p2; p1++,p2++) ;
    for(; *p1; p1++) if (*p1 == '/') return false;
    for(; *p2; p2++) if (*p2 == '/') return false;
//*fprintf(dumpOut,"YES EQUALS\n");
    return true;
}

int javaClassIsInCurrentPackage(Symbol *cl) {
    if (s_jsl!=NULL) {
        if (s_jsl->classStat->thisClass == NULL) {
            // probably import class.*; (nested subclasses)
            return javaFqtNameIsFromThePackage(s_jsl->classStat->thisPackage,
                                               cl->linkName);
        } else {
            return javaFqtNamesAreFromTheSamePackage(cl->linkName,
                                                     s_jsl->classStat->thisClass->linkName);
        }
    } else {
        if (s_javaStat->thisClass == NULL) {
            // probably import class.*; (nested subclasses)
            return javaFqtNameIsFromThePackage(s_javaStat->currentPackage,
                                               cl->linkName);
        } else {
            return javaFqtNamesAreFromTheSamePackage(cl->linkName,
                                                     s_javaStat->thisClass->linkName);
        }
    }
}

static Symbol *javaFQTypeSymbolDefinitionCreate(char *name, char *fqName) {
    Symbol *memb;
    SymbolList *pppl;
    char *lname1, *sname;

    CF_ALLOCC(sname, strlen(name)+1, char);
    strcpy(sname, name);

    CF_ALLOCC(lname1, strlen(fqName)+1, char);
    strcpy(lname1, fqName);

    CF_ALLOC(memb, Symbol);
    fillSymbol(memb, sname, lname1, s_noPos);
    fillSymbolBits(&memb->bits, AccessDefault, TypeStruct, StorageNone);

    CF_ALLOC(memb->u.structSpec, S_symStructSpec);

    initSymStructSpec(memb->u.structSpec, /*.records=*/NULL);
    TypeModifier *stype = &memb->u.structSpec->stype;
    /* Assumed to be Struct/Union/Enum? */
    initTypeModifierAsStructUnionOrEnum(stype, /*.kind=*/TypeStruct, /*.u.t=*/memb,
                                            /*.typedefSymbol=*/NULL, /*.next=*/NULL);
    TypeModifier *sptrtype = &memb->u.structSpec->sptrtype;
    initTypeModifierAsPointer(sptrtype, &memb->u.structSpec->stype);

    CF_ALLOC(pppl, SymbolList);
    /* REPLACED: FILL_symbolList(pppl, memb, NULL); with compound literal */
    *pppl = (SymbolList){.d = memb, .next = NULL};

    javaFqtTableAdd(&javaFqtTable, pppl);

    // I think this can be there, as it is very used
    javaCreateClassFileItem(memb);
    // this would be too strong, javaLoadClassSymbolsFromFile(memb);
    /* so, this table is not freed by Trail */
    //&if (stringContainsSubstring(fqName, "ComboBoxTreeFilter")) {fprintf(dumpOut,"\nAAAAAAAAAAAAA : %s %s\n\n", name, fqName);} if (strcmp(fqName, "ComboBoxTreeFilter")==0) assert(0);
    return memb;
}

Symbol *javaFQTypeSymbolDefinition(char *name, char *fqName) {
    Symbol symbol, *member;
    SymbolList ppl, *pppl;

    /* This probably creates a SymbolList element so ..IsMember() can be used */
    /* TODO: create a function to check if a *Symbol* is member... */
    fillSymbol(&symbol, name, fqName, s_noPos);
    fillSymbolBits(&symbol.bits, AccessDefault, TypeStruct, StorageNone);

    /* REPLACED: FILL_symbolList(&ppl, &symbol, NULL); with compound literal */
    ppl = (SymbolList){.d = &symbol, .next = NULL};

    if (javaFqtTableIsMember(&javaFqtTable, &ppl, NULL, &pppl)) {
        member = pppl->d;
    } else {
        member = javaFQTypeSymbolDefinitionCreate(name, fqName);
    }
    return member;
}

Symbol *javaGetFieldClass(char *fieldLinkName, char **fieldAdr) {
    /* also .class suffix can be considered as field !!!!!!!!!!! */
    /* also ; is considered as the end of class fq name */
    /* so, this function is used to determine class file name also */
    /* if not, change '.' to appropriate char */
    /* But this function is very time expensive */
    char sbuf[MAX_FILE_NAME_SIZE];
    char fqbuf[MAX_FILE_NAME_SIZE];
    char *p,*lp,*lpp;
    Symbol        *memb;
    int fqlen,slen;
    lp = fieldLinkName;
    lpp = NULL;
    for(p=fieldLinkName; *p && *p!=';'; p++) {
        if (*p == '/' || *p == '$') lp = p+1;
        if (*p == '.') lpp = p;
    }
    if (lpp != NULL && lpp>lp) p = lpp;
    if (fieldAdr != NULL) *fieldAdr = p;
    fqlen = p-fieldLinkName;
    assert(fqlen+1 < MAX_FILE_NAME_SIZE);
    strncpy(fqbuf,fieldLinkName, fqlen);
    fqbuf[fqlen]=0;
    slen = p-lp;
    strncpy(sbuf,lp,slen);
    sbuf[slen]=0;
    memb = javaFQTypeSymbolDefinition(sbuf, fqbuf);
    return memb;
}


static Symbol *javaAddTypeToSymbolTable(Symbol *original, int accessFlags, Position *importPos,
                                        bool isExplicitlyImported
) {
    Symbol *added;

    original->bits.access = accessFlags;
    original->bits.isExplicitlyImported = isExplicitlyImported;

    added = newSymbolAsCopyOf(original);
    added->pos = *importPos;
    addSymbol(added, symbolTable);

    return original;
}

Symbol *javaTypeSymbolDefinition(IdList *tname,
                                 int accessFlags,
                                 int addType
){
    Symbol pp,*typeSymbol;
    char fqtName[MAX_FILE_NAME_SIZE];

    assert(tname);
    assert(tname->nameType == TypeStruct);

    fillSymbol(&pp, tname->id.name, tname->id.name, s_noPos);
    fillSymbolBits(&pp.bits, accessFlags, TypeStruct, StorageNone);

    javaCreateComposedName(NULL, tname, '/', NULL, fqtName, MAX_FILE_NAME_SIZE);
    typeSymbol = javaFQTypeSymbolDefinition(tname->id.name, fqtName);
    if (addType == ADD_YES) {
        typeSymbol = javaAddTypeToSymbolTable(typeSymbol, accessFlags, &s_noPos, false);
    }
    return typeSymbol;
}

Symbol *javaTypeSymbolUsage(IdList *tname, int accessFlags) {
    Symbol pp,*memb;
    char fqtName[MAX_FILE_NAME_SIZE];

    assert(tname);
    assert(tname->nameType == TypeStruct);

    fillSymbol(&pp, tname->id.name, tname->id.name, s_noPos);
    fillSymbolBits(&pp.bits, accessFlags, TypeStruct, StorageNone);

    if (tname->next==NULL && symbolTableIsMember(symbolTable, &pp, NULL, &memb)) {
        // get canonical copy
        memb = javaFQTypeSymbolDefinition(memb->name, memb->linkName);
        return memb;
    }
    javaCreateComposedName(NULL,tname,'/',NULL,fqtName,MAX_FILE_NAME_SIZE);
    memb = javaFQTypeSymbolDefinition(tname->id.name, fqtName);
    return memb;
}

Symbol *javaTypeNameDefinition(IdList *tname) {
    Symbol    *memb;
    Symbol		*dd;
    TypeModifier		*td;

    memb = javaTypeSymbolUsage(tname, AccessDefault);
    td = newStructTypeModifier(memb);
    dd = newSymbolAsType(memb->name, memb->linkName, tname->id.p, td);

    return dd;
}

static void javaJslLoadSuperClasses(Symbol *cc, int currentParsedFile) {
    SymbolList *ss;
    static int nestingCount = 0;

    nestingCount ++;
    if (nestingCount > MAX_CLASSES) {
        fatalError(ERR_INTERNAL, "unexpected cycle in class hierarchy", XREF_EXIT_ERR);
    }
    for(ss=cc->u.structSpec->super; ss!=NULL; ss=ss->next) {
        cfAddCastsToModule(cc, ss->d);
    }
    nestingCount --;
}

void javaReadSymbolFromSourceFileInit(int sourceFileNum,
                                      JslTypeTab *typeTab ) {
    S_jslStat           *njsl;
    char				*yyg;
    int					yygsize;
    njsl = StackMemoryAlloc(S_jslStat);
    // very space consuming !!!, it takes about 400kb of working memory
    // TODO!!!! to allocate and save only used parts of 'gyyvs - gyyvsp'
    // and 'gyyss - gyyssp' ??? And copying twice? definitely yes!
    //yygsize = sizeof(struct yyGlobalState);
    yygsize = ((char*)(s_yygstate->gyyvsp+1)) - ((char *)s_yygstate);
    yyg = StackMemoryAllocC(yygsize, char);
    fillJslStat(njsl, 0, sourceFileNum, s_language, typeTab, NULL, NULL,
                 uniyylval, (S_yyGlobalState*)yyg, yygsize, s_jsl);
    memcpy(njsl->savedYYstate, s_yygstate, yygsize);
    memcpy(njsl->yyIdentBuf, s_yyIdentBuf,
           sizeof(Id[YYBUFFERED_ID_INDEX]));
    s_jsl = njsl;
    s_language = LANG_JAVA;
}

void javaReadSymbolFromSourceFileEnd(void) {
    s_language = s_jsl->language;
    uniyylval = s_jsl->savedyylval;
    memcpy(s_yygstate, s_jsl->savedYYstate, s_jsl->yyStateSize);
    memcpy(s_yyIdentBuf, s_jsl->yyIdentBuf,
           sizeof(Id[YYBUFFERED_ID_INDEX]));
    s_jsl = s_jsl->next;
}

void javaReadSymbolsFromSourceFileNoFreeing(char *fname, char *asfname) {
    FILE *file;
    EditorBuffer *buffer;
    int cfilenum;
    static int nestingDepth = 0;

    nestingDepth++;

    // ?? is this really necessary?
    // memset(s_yygstate, sizeof(struct yyGlobalState), 0);
    uniyylval = & s_yygstate->gyylval;

    for (int pass=1; pass<=2; pass++) {
        log_debug("[jsl] PASS %d through %s level %d", pass, fname, nestingDepth);
        file = NULL;
        buffer = editorFindFile(fname);
        if (buffer==NULL) {
            file = openFile(fname, "r");
            if (file==NULL) {
                errorMessage(ERR_CANT_OPEN, fname);
                goto fini;
            }
        }
        pushInclude(file, buffer, asfname, "\n");
        cfilenum = currentFile.lexBuffer.buffer.fileNumber;
        s_jsl->pass = pass;
        java_yyparse();
        popInclude();      // this will close the file
        log_debug("[jsl] CLOSE file %s level %d", fname, nestingDepth);
    }

    for (SymbolList *ll=s_jsl->waitList; ll!=NULL; ll=ll->next) {
        javaJslLoadSuperClasses(ll->d, cfilenum);
    }
 fini:
    nestingDepth--;
}

void javaReadSymbolsFromSourceFile(char *fname) {
    JslTypeTab    *typeTab;
    int				fileIndex;
    int				memBalance;

    fileIndex = addFileTabItem(fname);
    memBalance = currentBlock->firstFreeIndex;
    beginBlock();
    typeTab = StackMemoryAlloc(JslTypeTab);
    javaReadSymbolFromSourceFileInit(fileIndex, typeTab);
    jslTypeTabInit(typeTab, MAX_JSL_SYMBOLS);
    javaReadSymbolsFromSourceFileNoFreeing(fname, fname);
    // there may be several unbalanced blocks
    while (memBalance < currentBlock->firstFreeIndex)
        endBlock();
    javaReadSymbolFromSourceFileEnd();
}

static void addJavaFileDependency(int file, char *onfile) {
    int         fileIndex;
    Position	pos;

    // do dependencies only when doing cross reference file
    if (options.taskRegime != RegimeXref)
        return;
    // also do it only for source files
    if (! fileTable.tab[file]->b.commandLineEntered)
        return;
    fileIndex = addFileTabItem(onfile);
    pos = makePosition(file, 0, 0);
    addIncludeReference(fileIndex, &pos);
}


static void javaHackCopySourceLoadedCopyPars(Symbol *memb) {
    Symbol *cl;
    cl = javaFQTypeSymbolDefinition(memb->name, memb->linkName);
    if (cl->bits.javaSourceIsLoaded) {
        memb->bits.access = cl->bits.access;
        memb->bits.storage = cl->bits.storage;
        memb->bits.symbolType = cl->bits.symbolType;
        memb->bits.javaSourceIsLoaded = cl->bits.javaSourceIsLoaded;
    }
}

void javaLoadClassSymbolsFromFile(Symbol *memb) {
    char *sourceName, *className;
    Symbol *cl;
    int cfi, cInd;
    FindJavaFileResult findResult;

    if (memb == NULL)
        return;
    //&fprintf(dumpOut,"!requesting class (%d)%s\n", memb, memb->linkName);
    sourceName = className = "";
    if (!memb->bits.javaFileIsLoaded) {
        memb->bits.javaFileIsLoaded = true;
        // following is a hack due to multiple items in symbol tab !!!
        cl = javaFQTypeSymbolDefinition(memb->name, memb->linkName);
        if (cl!=NULL && cl!=memb)
            cl->bits.javaFileIsLoaded = true;
        cInd = javaCreateClassFileItem(memb);
        addCfClassTreeHierarchyRef(cInd, UsageClassFileDefinition);
        findResult = javaFindFile(memb, &sourceName, &className);
        if (findResult == RESULT_IS_JAVA_FILE) {
            assert(memb->u.structSpec);
            cfi = memb->u.structSpec->classFile;
            assert(fileTable.tab[cfi]);
            // set it to none, if class is inside jslparsing  will re-set it
            fileTable.tab[cfi]->b.sourceFileNumber=noFileIndex;
            javaReadSymbolsFromSourceFile(sourceName);
            if (fileTable.tab[cfi]->b.sourceFileNumber == noFileIndex) {
                // class definition not found in the source file,
                // (moved inner class) retry searching for class file
                findResult = javaFindFile(memb, &sourceName, &className);
            }
            if (!memb->bits.javaSourceIsLoaded) {
                // HACK, probably loaded into another possition of symboltab, make copy
                javaHackCopySourceLoadedCopyPars(memb);
            }
        }
        if (findResult == RESULT_IS_CLASS_FILE) {
            javaReadClassFile(className,memb, LOAD_SUPER);
        } else if (findResult == RESULT_NO_FILE_FOUND) {
            if (displayingErrorMessages()) {
                char tmpBuff[TMP_BUFF_SIZE];
                sprintf(tmpBuff, "class %s not found", memb->name);
                errorMessage(ERR_ST, tmpBuff);
            }
        }
        // I need to get also accessflags for example
        if (cl!=NULL && cl!=memb)
            cl->bits = memb->bits;
        if (sourceName != NULL) {
            addJavaFileDependency(s_olOriginalFileNumber, sourceName);
        }
    }
}


static int findTopLevelNameInternal(char *name,
                                    S_recFindStr *resRfs,
                                    Symbol **resMemb,
                                    int classif,
                                    S_javaStat *startingScope,
                                    int accessibilityCheck,
                                    int visibilityCheck,
                                    S_javaStat **rscope
                                    ) {
    int res;
    Symbol sd;
    S_javaStat *cscope;

    assert((!LANGUAGE(LANG_JAVA)) ||
        (classif==CLASS_TO_EXPR || classif==CLASS_TO_METHOD));
    assert(accessibilityCheck==ACCESSIBILITY_CHECK_YES || accessibilityCheck==ACCESSIBILITY_CHECK_NO);
    assert(visibilityCheck==VISIBILITY_CHECK_YES || visibilityCheck==VISIBILITY_CHECK_NO);

    fillSymbol(&sd, name, name, s_noPos);
    fillSymbolBits(&sd.bits, 0, TypeDefault, StorageNone);

    res = RETURN_NOT_FOUND;
    for(cscope=startingScope;
        cscope!=NULL && cscope->thisClass!=NULL && res!=RETURN_OK;
        cscope=cscope->next
        ) {
        assert(cscope->thisClass);
        if (classif!=CLASS_TO_METHOD && symbolTableIsMember(cscope->locals, &sd, NULL, resMemb)) {
            /* it is an argument or local variable */
            /* this is tricky */
            /* I guess, you cannot have an overloaded function here, so ... */
            log_trace("%s is identified as local var or parameter", name);
            fillRecFindStr(resRfs, NULL, NULL, *resMemb,s_recFindCl++);
            *rscope = NULL;
        } else {
            /* if present, then as a structure record */
            log_trace("putting %s as base class", cscope->thisClass->name);
            fillRecFindStr(resRfs, cscope->thisClass, NULL, NULL,s_recFindCl++);
            recFindPush(cscope->thisClass, resRfs);
            *rscope = cscope;
        }
        res = findStrRecordSym(resRfs, name, resMemb, classif, accessibilityCheck, visibilityCheck);
    }
    return res;
}

int findTopLevelName(char *name, S_recFindStr *resRfs,
                     Symbol **resMemb, int classif) {
    int res;
    S_javaStat *scopeToSearch, *resultScope;

    res = findTopLevelNameInternal(name, resRfs, resMemb, classif,
                                   s_javaStat, ACCESSIBILITY_CHECK_YES, VISIBILITY_CHECK_YES,
                                   &scopeToSearch);
    // O.K. determine class to search
    if (res != RETURN_OK) {
        // no class to search find, anyway this is a compiler error,
        scopeToSearch = s_javaStat;
    }
    if (scopeToSearch!=NULL) {
        log_trace("relooking for %s in %s", name, scopeToSearch->thisClass->name);
        res = findTopLevelNameInternal(name, resRfs, resMemb, classif,
                                       scopeToSearch, ACCESSIBILITY_CHECK_NO, VISIBILITY_CHECK_NO,
                                       &resultScope);
    }
    return res;
}

static int javaIsNestedClass(Symbol *tclas, char *name, Symbol **innmemb) {
    int    i,n;
    S_nestedSpec	*inners;
    Symbol        *clas;

    // take just one super class, no interfaces, for speed reasons
    for(clas=tclas;
        clas!=NULL && clas->u.structSpec->super!=NULL;
        clas=clas->u.structSpec->super->d) {
        assert(clas->bits.symbolType == TypeStruct && clas->u.structSpec);
        n = clas->u.structSpec->nestedCount;
        inners = clas->u.structSpec->nest;
        for(i=0; i<n; i++) {
//& fprintf(dumpOut,"checking %s<->%s\n",inners[i].cl->name, name);fflush(dumpOut);
            if (inners[i].membFlag && strcmp(inners[i].cl->name, name)==0) {
                // the following if makes problem, because when resolving
                // a name Outer.Inner I do not care whether it is static
                // or not. Why I have put this there????
//&				if ((inners[i].cl->bits.access&AccessStatic)==0) {
                    *innmemb = inners[i].cl;
                    return true;
//&				}
            }
        }
    }
    return false;
}

static int javaClassIsInnerNonStaticMemberClass(Symbol *tclas, Symbol *name) {
    int    i,n;
    S_nestedSpec	*inners;
    Symbol        *clas;

    // take just one super class, no interfaces, for speed reasons
    for(clas=tclas;
        clas!=NULL && clas->u.structSpec->super!=NULL;
        clas=clas->u.structSpec->super->d) {
        assert(clas->bits.symbolType == TypeStruct && clas->u.structSpec);
        n = clas->u.structSpec->nestedCount;
        inners = clas->u.structSpec->nest;
        for(i=0; i<n; i++) {
//&fprintf(dumpOut,"checking %s<->%s\n",inners[i].cl->name, name);fflush(dumpOut);
            if (inners[i].membFlag && strcmp(inners[i].cl->linkName, name->linkName)==0
                && (inners[i].cl->bits.access & AccessStatic) == 0) {
                return true;
            }
        }
    }
    return false;
}

#if ZERO
static int javaSimpleNameIsInnerMemberClass(char *name, S_symbol **innmemb) {
    S_javaStat		*cscope;
//&fprintf(dumpOut,"looking for inner class %s\n",name);
    for(	cscope=s_javaStat;
            cscope!=NULL && cscope->thisClass!=NULL;
            cscope=cscope->next
        ) {
        if (javaIsNestedClass(cscope->thisClass, name, innmemb)) {
//&fprintf(dumpOut,"inner class %s found %s %s\n",name,(*innmemb)->name, (*innmemb)->linkName);fflush(dumpOut);
            return true;
        }
    }
    return false;
}
#endif

int javaIsInnerAndCanGetUnnamedEnclosingInstance(Symbol *name, Symbol **outEi) {
    S_javaStat		*cscope;
//&fprintf(dumpOut,"looking for inner class %s\n",name);
    for(	cscope=s_javaStat;
            cscope!=NULL && cscope->thisClass!=NULL;
            cscope=cscope->next
        ) {
        if (javaClassIsInnerNonStaticMemberClass(cscope->thisClass, name)) {
//&fprintf(dumpOut,"inner class %s found %s %s\n",name,(*innmemb)->name, (*innmemb)->linkName);fflush(dumpOut);
            *outEi = cscope->thisClass;
            return true;
        }
    }
    return false;
}

#define JAVA_CLASS_CAN_HAVE_IT(name,str,outImportPos,mm,memb,haveit) {  \
        haveit = true;                                                  \
        *str = mm;                                                      \
        name->nameType = TypeStruct;                                    \
        name->fname = mm->linkName;                                     \
        if (cxrefFlag == ADD_CX_REFS) {                                 \
            ipos = & memb->pos; /* here MUST be memb, not mm, as it contains the import line !!*/ \
            if (ipos->file != noFileIndex && ipos->file != -1) {        \
                javaAddImportConstructionReference(ipos, ipos, UsageUsed); \
            }                                                           \
        }                                                               \
    }

int javaClassifySingleAmbigNameToTypeOrPack(IdList *name,
                                            Symbol **str,
                                            int cxrefFlag
    ){
    Symbol sd, *mm, *memb, *nextmemb;
    bool haveit;
    Position *ipos;

    fillSymbol(&sd, name->id.name, name->id.name, s_noPos);
    fillSymbolBits(&sd.bits, AccessDefault, TypeStruct, StorageNone);

    haveit = false;
    if (symbolTableIsMember(symbolTable, &sd, NULL, &memb)) {
        /* a type */
        assert(memb);
        // O.K. I have to load the class in order to check its access flags
        for(; memb!=NULL; memb=nextmemb) {
            nextmemb = memb;
            symbolTableNextMember(&sd, &nextmemb);
            // take canonical copy (as there can be more than one class
            // item in symtab
            mm = javaFQTypeSymbolDefinition(memb->name, memb->linkName);
            if ((options.ooChecksBits & OOC_ALL_CHECKS)) {
                // do carefully all checks
                if (! haveit) {
                    javaLoadClassSymbolsFromFile(mm);
                    if (javaOuterClassAccessible(mm)) {
                        JAVA_CLASS_CAN_HAVE_IT(name, str, outImportPos, mm, memb, haveit);
                    }
                } else {
                    if ((*str) != mm) {
                        javaLoadClassSymbolsFromFile(mm);
                        if (javaOuterClassAccessible(mm)) {
                            // multiple imports
                            if ((*str)->bits.isExplicitlyImported == mm->bits.isExplicitlyImported) {
                                assert(strcmp((*str)->linkName, mm->linkName)!=0);
                                haveit = false;
                                // this is tricky, mark the import as used
                                // it is "used" to disqualify some references, so
                                // during name reduction refactoring, it will not adding
                                // such import
                                ipos = &memb->pos;
                                if (ipos->file != noFileIndex && ipos->file != -1) {
                                    javaAddImportConstructionReference(ipos, ipos, UsageUsed);
                                }
                                goto breakcycle;
                            }
                        }
                    }
                }
            } else {
                // just find the first accessible
                if (nextmemb == NULL) {
                    JAVA_CLASS_CAN_HAVE_IT(name, str, outImportPos, mm, memb, haveit);
                    goto breakcycle;
                } else {
                    // O.K. there may be an ambiguity resolved by accessibility
                    javaLoadClassSymbolsFromFile(mm);
                    if (javaOuterClassAccessible(mm)) {
                        JAVA_CLASS_CAN_HAVE_IT(name, str, outImportPos, mm, memb, haveit);
                        goto breakcycle;
                    }
                }
            }
        }
    }
 breakcycle:
    if (haveit)
        return TypeStruct;

    name->nameType = TypePackage;
    return TypePackage;
}

#define AddAmbCxRef(classif,sym,pos,usage, minacc,oref, rfs) {\
    UsageBits ub;\
    if (classif!=CLASS_TO_METHOD) {\
        if (rfs != NULL && rfs->currClass!=NULL) {\
            assert(rfs && rfs->currClass && \
                rfs->currClass->bits.symbolType==TypeStruct && rfs->currClass->u.structSpec);\
            assert(rfs && rfs->baseClass && \
                rfs->baseClass->bits.symbolType==TypeStruct && rfs->baseClass->u.structSpec);\
            if (options.server_operation!=OLO_ENCAPSULATE \
                || ! javaRecordAccessible(rfs, rfs->baseClass, rfs->currClass, sym, AccessPrivate)) {\
                fillUsageBits(&ub, usage, minacc);\
                oref=addCxReferenceNew(sym,pos, &ub,\
                    rfs->currClass->u.structSpec->classFile,\
                    rfs->baseClass->u.structSpec->classFile);\
            }\
        } else {\
            oref=addCxReference(sym, pos, usage, noFileIndex, noFileIndex);\
        }\
    }\
}

char *javaImportSymbolName_st(int file, int line, int coll) {
    static char res[MAX_CX_SYMBOL_SIZE];
    sprintf(res, "%s:%x:%x:%x%cimport on line %3d", LINK_NAME_IMPORT_STATEMENT,
            file, line, coll,
            LINK_NAME_SEPARATOR,
            /*& simpleFileName(getRealFileNameStatic(fileTable.tab[file]->name)), &*/
            line);
    return res;
}

void javaAddImportConstructionReference(Position *importPos, Position *pos, int usage) {
    char *isymName;
    isymName = javaImportSymbolName_st(importPos->file, importPos->line, importPos->col);
//&fprintf(dumpOut,"using import on %s:%d (%d)  at %s:%d\n", simpleFileName(fileTable.tab[importPos->file]->name), importPos->line, importPos->col, simpleFileName(fileTable.tab[pos->file]->name), pos->line);
    addSpecialFieldReference(isymName, StorageDefault, noFileIndex, pos, usage);
}

static int javaClassifySingleAmbigName( IdList *name,
                                        S_recFindStr *rfs,
                                        Symbol **str,
                                        TypeModifier **expr,
                                        Reference **oref,
                                        int classif, int uusage,
                                        int cxrefFlag
    ) {
    int             res, nfqtusage, minacc;
    S_recFindStr *nullRfs = NULL;

    if (classif==CLASS_TO_EXPR || classif==CLASS_TO_METHOD) {
        /* argument, local variable or class record */
        if (findTopLevelName(name->id.name,rfs,str,classif)==RETURN_OK) {
            *expr = (*str)->u.typeModifier;
            name->nameType = TypeExpression;
            if (cxrefFlag==ADD_CX_REFS) {
                minacc = javaGetMinimalAccessibility(rfs, *str);
                AddAmbCxRef(classif,*str, &name->id.p, uusage, minacc, *oref, rfs);
                if (rfs!=NULL && rfs->currClass != NULL) {
                    // the question is: is a reference to static field
                    // also reference to 'this'? If yes, it will
                    // prevent many methods from beeing turned static.
                    if ((*str)->bits.access & AccessStatic) {
                        nfqtusage = javaNotFqtUsageCorrection(rfs->currClass,UsageNotFQField);
                        addSpecialFieldReference(LINK_NAME_NOT_FQT_ITEM,StorageField,
                                rfs->currClass->u.structSpec->classFile,
                                &name->id.p, nfqtusage);
                    } else {
                        addThisCxReferences(rfs->baseClass->u.structSpec->classFile, &name->id.p);
                    }
                }
            }
            return name->nameType;
        }
    }
    res = javaClassifySingleAmbigNameToTypeOrPack( name, str, cxrefFlag);
    if (res == TypeStruct) {
        if (cxrefFlag==ADD_CX_REFS) {
            AddAmbCxRef(classif, *str, &name->id.p, uusage, MIN_REQUIRED_ACCESS, *oref, nullRfs);
            // the problem is here when invoked as nested "new Name()"?
            nfqtusage = javaNotFqtUsageCorrection((*str), UsageNotFQType);
            addSpecialFieldReference(LINK_NAME_NOT_FQT_ITEM, StorageField,
                                     (*str)->u.structSpec->classFile,
                                     &name->id.p, nfqtusage);
        }
    } else if (res == TypePackage) {
        if (cxrefFlag==ADD_CX_REFS) {
            javaAddNameCxReference(name, uusage);
        }
    } else {
        // Well, I do not know, putting the assert there just to learn
        assert(0);
    }
    return name->nameType;
}

static int javaNotFqtUsageCorrection(Symbol *sym, int usage) {
    int             rr,pplen;
    S_recFindStr    localRfs;
    Symbol        *str;
    TypeModifier *expr;
    Reference     *loref;
    IdList   sname;
    char            *pp, packname[TMP_STRING_SIZE];

    pp = strchr(sym->linkName, '/');
    if (pp==NULL) pp = sym->linkName;
    pplen = pp - sym->linkName;
    assert(pplen < TMP_STRING_SIZE-1);
    strncpy(packname, sym->linkName, pplen);
    packname[pplen] = 0;

    fillfIdList(&sname, packname, NULL, s_noPos, packname, TypeExpression, NULL);
        rr = javaClassifySingleAmbigName(&sname,&localRfs,&str,&expr,&loref,
                                         CLASS_TO_EXPR, UsageNone, NO_CX_REFS);
    if (rr != TypePackage) {
        return UsageNonExpandableNotFQTName;
    }
    return usage;
}

static void javaResetUselessReference(Reference *ref) {
    if (ref != NULL /*& && ref->usage.base == UsageLastUseless &*/) {
        ref->usage.base = UsageOtherUseless;
    }
}

/*
 check whether name as single name will result to str, if yes add
 UsageUselessFqt reference
*/
static void javaCheckForUselessFqt(IdList *name, int classif, Symbol *rstr,
                                   Reference **oref, Reference *lref){
    int             rr, uselessFqt;
    S_recFindStr    localRfs;
    Symbol        *str;
    TypeModifier *expr;
    Reference     *loref;
    IdList   sname;

    uselessFqt = 0;

    //& for(nn=name; nn!=NULL && nn->nameType!=TypePackage; nn=nn->next) ;
    //& if (nn==NULL) return;
    // if it is not fqt (i.e. does not contain package), do nothing
    // TODO, this must be optional !!!!

    sname = *name;
    sname.next = NULL;
    //& rr = javaClassifySingleAmbigNameToTypeOrPack( &sname, &str, NO_CX_REFS); // wrong
    rr = javaClassifySingleAmbigName(&sname,&localRfs,&str,&expr,&loref,
                                      classif, UsageNone, NO_CX_REFS);
    if (rr==TypeStruct) {
        assert(str && rstr);
//&fprintf(dumpOut,"!checking %s == %s  (%d==%d)\n",str->linkName,rstr->linkName,str->u.structSpec->classFile,rstr->u.structSpec->classFile);
        // equality of pointers may be too strong ???
        // what about classfile index comparing
        //if (strcmp(str->linkName, rstr->linkName) == 0) {
        assert(str->u.structSpec!=NULL && rstr->u.structSpec!=NULL);
        if (str->u.structSpec->classFile == rstr->u.structSpec->classFile) {
            assert(name && rstr->u.structSpec);
            *oref = addUselessFQTReference(rstr->u.structSpec->classFile,&name->id.p);
//&fprintf(dumpOut,"!adding TYPE useless reference on %d,%d\n", name->id.p.line, name->id.p.col);
            javaResetUselessReference(lref);
            uselessFqt = 1;
        }
    }
    if (! uselessFqt) {
        assert(name->next != NULL);			// it is long name
        assert(name && rstr->u.structSpec);
        addUnimportedTypeLongReference(rstr->u.structSpec->classFile,&name->id.p);
    }
}

static Reference *javaCheckForUselessTypeName(IdList   *name,
                                                int				classif,
                                                S_recFindStr	*rfs,
                                                Reference     **oref,
                                                Reference     *lref
    ) {
    int             rr;
    S_recFindStr    localRfs;
    Symbol        *str;
    TypeModifier *expr;
    Reference     *loref;
    IdList   sname;
    Reference     *res;

    res = NULL;

    //& for(nn=name; nn!=NULL && nn->nameType!=TypePackage; nn=nn->next) ;
    //& if (nn==NULL) return;
    // if it is not fqt (i.e. does not contain package), do nothing
    // TODO, this must be optional !!!!

    // not a static reference?
    //& if (name->next==NULL || name->next->nameType!=TypeStruct) return;

    sname = *name;
    sname.next = NULL;
    rr = javaClassifySingleAmbigName(&sname,&localRfs,&str,&expr,&loref,
                                      classif, UsageNone, NO_CX_REFS);
    assert(rfs && rfs->currClass && rfs->currClass->u.structSpec && name);
//&fprintf(dumpOut,"!checking rr == %s, %x\n", typeName[rr], localRfs.currClass);
    if (rr==TypeExpression && localRfs.currClass!=NULL) {
//&fprintf(dumpOut,"!checking %d(%s) == %d(%s)\n",rfs->currClass->u.structSpec->classFile,rfs->currClass->linkName,localRfs.currClass->u.structSpec->classFile,localRfs.currClass->linkName);
        // equality of pointers may be too strong ???
        if(rfs->currClass->u.structSpec->classFile==localRfs.currClass->u.structSpec->classFile){
            *oref = addUselessFQTReference(rfs->currClass->u.structSpec->classFile, &name->id.p);
//&fprintf(dumpOut,"!adding useless reference on %d,%d\n", name->id.p.line, name->id.p.col);
            javaResetUselessReference(lref);
        }
    }
    return res;
}

static void javaClassifyNameToNestedType(IdList *name, Symbol *outerc, int uusage, Symbol **str, Reference **oref) {
    name->nameType = TypeStruct;
    *str = javaTypeSymbolUsage(name,AccessDefault);
    javaLoadClassSymbolsFromFile(*str);
    // you have to search the class, it may come from superclass

    if ((options.ooChecksBits & OOC_ALL_CHECKS)==0
        || javaRecordAccessible(NULL,outerc, outerc, *str, (*str)->bits.access)) {
        *oref = javaAddClassCxReference(*str, &name->id.p, uusage);
    }
}

static void classifiedToNestedClass(IdList *name, Symbol **str, Reference **oref, Reference **rdtoref, int classif, int uusage, Symbol *pstr, Reference *prdtoref, int allowUselesFqtRefs) {
    name->nameType = TypeStruct;
    //&*str=javaTypeSymbolUsage(name,AccessDefault);
    javaLoadClassSymbolsFromFile(*str);
    if ((options.ooChecksBits & OOC_ALL_CHECKS)==0
        || javaRecordAccessible(NULL,pstr, pstr, *str, (*str)->bits.access)) {
        *oref = javaAddClassCxReference(*str, &name->id.p, uusage);
        if (allowUselesFqtRefs == USELESS_FQT_REFS_ALLOWED) {
            javaCheckForUselessFqt(name, classif, *str, rdtoref, prdtoref);
        }
    }
}


int javaClassifyAmbiguousName(
        IdList *name,
        S_recFindStr *rfs,	// can be NULL
        Symbol **str,
        TypeModifier **expr,
        Reference **oref,
        Reference **rdtoref,  // output last useless reference, can be NULL
        int allowUselesFqtRefs,
        int classif,
        int usage) {
    int			pres,rf,classif2,rr;
    int			uusage, minacc;
    Symbol    *pstr;
    S_recFindStr localRfs;
    TypeModifier     *pexpr;
    Reference			*poref, *localrdref, *prdtoref;
    assert(classif==CLASS_TO_TYPE || classif==CLASS_TO_EXPR ||
           classif==CLASS_TO_METHOD);
    uusage = usage;
    if (uusage==UsageUsed && nestingLevel() == 0)
        uusage = USAGE_TOP_LEVEL_USED;
    if (rfs == NULL)
        rfs = &localRfs;
    if (rdtoref == NULL)
        rdtoref = &localrdref;
    *oref = NULL;
    *rdtoref = NULL;
    /* returns TypeStruct, TypeExpression */
    assert(name);
    if (name->next == NULL) {
        /* a single name */
        javaClassifySingleAmbigName(name,rfs,str,expr,oref,classif,uusage, ADD_CX_REFS);
    } else {
        /* composed name */
        if (classif == CLASS_TO_METHOD) {
            classif2 = CLASS_TO_EXPR;
        } else {
            classif2 = classif;
        }
        pres = javaClassifyAmbiguousName(name->next, NULL, &pstr,
                                         &pexpr, &poref, &prdtoref, allowUselesFqtRefs,
                                         classif2,UsageUsed);
        *rdtoref = prdtoref;
        switch (pres) {
        case TypePackage:
            if (javaTypeFileExist(name)) {
                name->nameType = TypeStruct;
                *str = javaTypeSymbolUsage(name, AccessDefault);
                if (allowUselesFqtRefs == USELESS_FQT_REFS_ALLOWED) {
                    javaCheckForUselessFqt(name, classif, *str, rdtoref, prdtoref);
                }
                javaLoadClassSymbolsFromFile(*str);
                if ((options.ooChecksBits & OOC_ALL_CHECKS)==0
                    || javaOuterClassAccessible(*str)) {
                    *oref = javaAddClassCxReference(*str, &name->id.p, uusage);
                }
            } else {
                name->nameType = TypePackage;
                javaAddNameCxReference(name, uusage);
            }
            break;
        case TypeStruct:
            if (classif==CLASS_TO_TYPE) {
                javaLoadClassSymbolsFromFile(pstr);
                name->nameType = TypeStruct;
                if (javaIsNestedClass(pstr,name->id.name,str)) {
                    classifiedToNestedClass(name, str, oref, rdtoref, classif, uusage, pstr, prdtoref, allowUselesFqtRefs);
                } else {
                    javaClassifyNameToNestedType(name, pstr, uusage, str, oref);
                    if (allowUselesFqtRefs == USELESS_FQT_REFS_ALLOWED) {
                        javaCheckForUselessFqt(name,classif,*str,rdtoref,prdtoref);
                    }
                }
            } else {
                javaLoadClassSymbolsFromFile(pstr);
                rf = findStrRecordSym(iniFind(pstr,rfs), name->id.name, str,
                                      classif, ACCESSIBILITY_CHECK_NO, VISIBILITY_CHECK_NO);
                *expr = (*str)->u.typeModifier;
                if (rf == RETURN_OK) {
                    name->nameType = TypeExpression;
                    if ((options.ooChecksBits & OOC_ALL_CHECKS)==0
                        || javaRecordVisibleAndAccessible(rfs, rfs->baseClass, rfs->currClass, *str)) {
                        minacc = javaGetMinimalAccessibility(rfs, *str);
                        AddAmbCxRef(classif,*str,&name->id.p, uusage, minacc, *oref, rfs);
                        if (allowUselesFqtRefs == USELESS_FQT_REFS_ALLOWED) {
                            javaCheckForUselessTypeName(name, classif, rfs,
                                                        rdtoref, prdtoref);
                        }
                    }
                } else {
                    if (javaIsNestedClass(pstr,name->id.name,str)) {
                        classifiedToNestedClass(name, str, oref, rdtoref, classif, uusage, pstr, prdtoref, allowUselesFqtRefs);
                    } else {		/* error, no such field found */
                        name->nameType = TypeExpression;
                        noSuchFieldError(name->id.name);
                    }
                }
            }
            break;
        case TypeExpression:
            if (pexpr->kind == TypeArray) pexpr = &s_javaArrayObjectSymbol.u.structSpec->stype;
//&			if (pexpr->kind == TypeError) {
//&				addTrivialCxReference(LINK_NAME_INDUCED_ERROR,TypeInducedError,StorageDefault,
//&                                   &name->id.p, UsageUsed);
//&			}
            if (pexpr->kind != TypeStruct) {
                *str = &s_errorSymbol;
            } else {
                javaLoadClassSymbolsFromFile(pexpr->u.t);
                rr = findStrRecordSym(iniFind(pexpr->u.t,rfs), name->id.name,
                                      str, classif, ACCESSIBILITY_CHECK_NO, VISIBILITY_CHECK_NO);
                if (rr == RESULT_OK) {
                    if ((options.ooChecksBits & OOC_ALL_CHECKS)==0
                        || javaRecordVisibleAndAccessible(rfs, rfs->baseClass, rfs->currClass, *str)) {
                        minacc = javaGetMinimalAccessibility(rfs, *str);
                        AddAmbCxRef(classif,*str,&name->id.p,uusage, minacc, *oref, rfs);
                    }
                } else {
                    noSuchFieldError(name->id.name);
                }
            }
            *expr = (*str)->u.typeModifier;
            name->nameType = TypeExpression;
            break;
        default: assert(0);
        }
    }
    return name->nameType;
}

#undef AddAmbCxRef

TypeModifier *javaClassifyToExpressionName(IdList *name,
                                              Reference **oref) {
    Symbol    *str;
    TypeModifier		*expr,*res;
    int atype;
    atype = javaClassifyAmbiguousName(name,NULL,&str,&expr,oref,NULL, USELESS_FQT_REFS_ALLOWED,CLASS_TO_EXPR,UsageUsed);
    if (atype == TypeExpression) res = expr;
    else if (atype == TypeStruct) {
        assert(str && str->u.structSpec);
        res = &str->u.structSpec->stype; /* because of casts & s_errorModifier;*/
        assert(res && res->kind == TypeStruct);
    } else res = & s_errorModifier;
    return res;
}

// returns last useless reference (if any)
Reference *javaClassifyToTypeOrPackageName(IdList *tname, int usage, Symbol **str, int allowUselesFqtRefs) {
    TypeModifier		*expr;
    Reference			*rr, *lastUselessRef;
    lastUselessRef = NULL;
    javaClassifyAmbiguousName(tname, NULL, str, &expr, &rr, &lastUselessRef, allowUselesFqtRefs,
                              CLASS_TO_TYPE, usage);
    return lastUselessRef;
}

Reference *javaClassifyToTypeName(IdList *tname, int usage, Symbol **str, int allowUselesFqtRefs) {
    Reference *res;

    res = javaClassifyToTypeOrPackageName(tname, usage, str, allowUselesFqtRefs);
    if (tname->nameType != TypeStruct) {
        // there is probably a problem with class or source path
        tname->nameType = TypeStruct;
        // but following will create double reference, prefer to not add
        //ss = javaTypeSymbolUsage(tname, ACC_DEFAULT);
        //addCxReference(ss, &tname->idi.p, usage, s_noneFileIndex, s_noneFileIndex);
    }
    return res;
}

// !!! this is called also for qualified super
Symbol * javaQualifiedThis(IdList *tname, Id *thisid) {
    Symbol			*str;
    TypeModifier		*expr;
    Reference			*rr, *lastUselessRef;
    int					ttype;
    lastUselessRef = NULL;
    ttype = javaClassifyAmbiguousName(tname, NULL,&str,&expr,&rr,
                                      &lastUselessRef, USELESS_FQT_REFS_ALLOWED,CLASS_TO_TYPE,UsageUsed);
    if (ttype == TypeStruct) {
        addThisCxReferences(str->u.structSpec->classFile, &thisid->p);
/*&
        addSpecialFieldReference(LINK_NAME_MAYBE_THIS_ITEM,StorageField,
                                 str->u.structSpec->classFile, &thisid->p,
                                 UsageMaybeThis);
&*/
        if (str->u.structSpec->classFile == s_javaStat->classFileIndex) {
            // redundant qualified this prefix
            addUselessFQTReference(str->u.structSpec->classFile, &thisid->p);
//&fprintf(dumpOut,"!adding useless reference on %d,%d\n", name->idi.p.line, name->idi.p.coll);
            javaResetUselessReference(lastUselessRef);
        }
    } else {
        str = &s_errorSymbol;
    }
    tname->nameType = TypeStruct;
    return str;
}

void javaClassifyToPackageName( IdList *id ) {
    IdList *ii;
    for (ii=id; ii!=NULL; ii=ii->next) ii->nameType = TypePackage;
}

void javaClassifyToPackageNameAndAddRefs(IdList *id, int usage) {
    IdList *ii;
    javaClassifyToPackageName( id);
    for (ii=id; ii!=NULL; ii=ii->next) javaAddNameCxReference(ii, usage);
}

void javaAddPackageDefinition(IdList *id) {
    javaClassifyToPackageNameAndAddRefs(id, UsageUsed); // UsageDefined);
}

void javaSetFieldLinkName(Symbol *field) {
    char *ln;
    assert(s_javaStat);
    ln = javaCreateComposedName(NULL,s_javaStat->className,'/', field->name, NULL, 0);
    field->linkName = ln;
}


Symbol *javaCreateNewMethod(char *nn, Position *p, int mem) {
    TypeModifier *m;
    Symbol *symbol;
    char *name;

    if (mem==MEMORY_CF) {
        CF_ALLOCC(name, strlen(nn)+1, char);
        strcpy(name, nn);
        CF_ALLOC(m, TypeModifier);
        CF_ALLOC(symbol, Symbol);
    } else {
        name = nn;
        m = StackMemoryAlloc(TypeModifier);
        symbol = StackMemoryAlloc(Symbol);
    }

    initTypeModifierAsFunction(m, NULL, NULL, NULL, NULL);
    fillSymbolWithTypeModifier(symbol, name, name, *p, m);

    return symbol;
}

int javaTypeToString(TypeModifier *type, char *pp, int ppSize) {
    int ppi;
    TypeModifier *tt;
    ppi=0;
    for (tt=type; tt!=NULL; tt=tt->next) {
        if (tt->kind == TypeArray) {
            sprintf(pp+ppi,"[");
            ppi += strlen(pp+ppi);
        } else if (tt->kind == TypeStruct) {
            assert(tt->u.t);
            sprintf(pp+ppi,"L%s;",tt->u.t->linkName);
            ppi += strlen(pp+ppi);
        } else {
            assert(s_javaBaseTypeCharCodes[tt->kind]!=0);
            pp[ppi++] = s_javaBaseTypeCharCodes[tt->kind];
        }
        assert(ppi < ppSize);
    }
    pp[ppi]=0;
    return ppi;
}

int javaIsYetInTheClass(Symbol *clas, char *lname, Symbol **eq) {
    Symbol        *r;
    assert(clas && clas->u.structSpec);
    for (r=clas->u.structSpec->records; r!=NULL; r=r->next) {
    //&fprintf(dumpOut, "[javaIsYetInTheClass] checking %s <-> %s\n",r->linkName, lname);fflush(dumpOut);
        if (strcmp(r->linkName, lname)==0) {
            *eq = r;
            return true;
        }
    }
    *eq = NULL;
    return false;
}


static int javaNumberOfNativeMethodsWithThisName(Symbol *clas, char *name) {
    Symbol        *r;
    int				res;
    res = 0;
    assert(clas && clas->bits.symbolType==TypeStruct && clas->u.structSpec);
    for (r=clas->u.structSpec->records; r!=NULL; r=r->next) {
        if (strcmp(r->name, name)==0 && (r->bits.access&AccessNative)) {
            res++;
        }
    }
    return res;
}


int javaSetFunctionLinkName(Symbol *clas, Symbol *decl, enum memoryClass mem) {
    static char pp[MAX_PROFILE_SIZE];
    char *ln;
    int ppi, res;
    Symbol *args;
    Symbol *memb;

    res = 0;
    if (decl == &s_errorSymbol || decl->bits.symbolType==TypeError)
        return res;
    assert(decl->bits.symbolType == TypeDefault);
    assert(decl->u.typeModifier);
    if (decl->u.typeModifier->kind != TypeFunction)
        return res;
    ppi=0;
//&	if (decl->bits.access & AccessStatic) {
//&		sprintf(pp+ppi,"%s.%s",clas->linkName, decl->name);
//&	} else {
        sprintf(pp+ppi,"%s", decl->name);
//&	}
    ppi += strlen(pp+ppi);
    sprintf(pp+ppi,"(");
    ppi += strlen(pp+ppi);
    for(args=decl->u.typeModifier->u.f.args; args!=NULL; args=args->next) {
        ppi += javaTypeToString(args->u.typeModifier, pp+ppi, MAX_PROFILE_SIZE-ppi);
    }
    sprintf(pp+ppi,")");
    ppi += strlen(pp+ppi);
    assert(ppi<MAX_PROFILE_SIZE);
    if (javaIsYetInTheClass(clas, pp, &memb)) {
        decl->linkName = memb->linkName;
    } else {
        if (mem == MEMORY_CF) {
            CF_ALLOCC(ln, ppi+1, char);
        } else {
            assert(mem==MEMORY_XX);
            ln = StackMemoryAllocC(ppi+1, char);
        }
        strcpy(ln,pp);
        decl->linkName = ln;
        res = 1;
    }
    return res;
}

static void addNativeMethodCxReference(Symbol *decl, Symbol *clas) {
    char nlname[MAX_CX_SYMBOL_SIZE];
    char *s, *d;

    sprintf(nlname, "Java_");
    s = clas->linkName;
    d = nlname + strlen(nlname);
    for(; *s; s++,d++) {
        if (*s=='/' || *s=='\\' || *s=='.') *d = '_';
        else if (*s=='_') {*d++ = '_'; *d = '1';}
        else if (*s=='$') {*d++ = '_'; *d++='0'; *d++='0'; *d++='0'; *d++='2'; *d='4';}
        else *d = *s;
    }
    *d++ = '_';
    if (javaNumberOfNativeMethodsWithThisName(clas, decl->name) > 1) {
        s = decl->linkName;
    } else {
        s = decl->name;
    }
    for(; *s; s++,d++) {
        if (*s=='/' || *s=='\\' || *s=='.') *d = '_';
        else if (*s=='_') {*d++ = '_'; *d = '1';}
        else if (*s==';') {*d++ = '_'; *d = '2';}
        else if (*s=='[') {*d++ = '_'; *d = '3';}
        else if (*s=='$') {*d++ = '_'; *d++='0'; *d++='0'; *d++='0'; *d++='2'; *d='4';}
        else if (*s=='(') {*d++ = '_'; *d = '_';}
        else if (*s==')') *d=0;
        else *d = *s;
    }
    *d = 0;
    assert(d-nlname < MAX_CX_SYMBOL_SIZE-1);
    addTrivialCxReference(nlname, TypeDefault,StorageExtern, &decl->pos,
                          UsageJavaNativeDeclared);
}

int javaLinkNameIsANestedClass(char *cname) {
    // this is a very hack!!   TODO do this seriously
    // an alternative can be 'javaSimpleNameIsInnerMemberClass', but it seems
    // to be even worst
    if (strchr(cname, '$') != NULL) return true;
    return false;
}

int isANestedClass(Symbol *ss) {
    return javaLinkNameIsANestedClass(ss->linkName);
}

int javaLinkNameIsAnnonymousClass(char *linkname) {
    char *ss;
    // this is a very hack too!!   TODO do this seriously
    ss = linkname;
    while ((ss=strchr(ss, '$'))!=NULL) {
        ss++;
        if (isdigit(*ss)) return true;
    }
    return false;
}

void addThisCxReferences(int classIndex, Position *pos) {
    int usage;
    if (classIndex == s_javaStat->classFileIndex) {
        usage = UsageMaybeThis;
    } else {
        usage = UsageMaybeQualifiedThis;
    }
    addSpecialFieldReference(LINK_NAME_MAYBE_THIS_ITEM,StorageField,
                             classIndex, pos, usage);
}

Reference *addUselessFQTReference(int classIndex, Position *pos) {
    Reference *res;
    res = addSpecialFieldReference(LINK_NAME_IMPORTED_QUALIFIED_ITEM,StorageField,
                                   classIndex, pos, UsageLastUseless);
    return res;
}

Reference *addUnimportedTypeLongReference(int classIndex, Position *pos) {
    Reference *res;
    res = addSpecialFieldReference(LINK_NAME_UNIMPORTED_QUALIFIED_ITEM, StorageField,
                                   classIndex, pos, UsageUsed);
    return res;
}

void addSuperMethodCxReferences(int classIndex, Position *pos) {
    addSpecialFieldReference(LINK_NAME_SUPER_METHOD_ITEM,StorageField,
                             classIndex, pos,
                             UsageSuperMethod);
}

Symbol *javaPrependDirectEnclosingInstanceArgument(Symbol *args) {
    warningMessage(ERR_ST,"[javaPrependDirectEnclosingInstanceArgument] not yet implemented");
    return args;
}

void addMethodCxReferences(unsigned modif, Symbol *method, Symbol *clas) {
    int clasn;
    assert(clas && clas->u.structSpec);
    clasn = clas->u.structSpec->classFile;
    assert(clasn!=noFileIndex);
    addCxReference(method, &method->pos, UsageDefined, clasn, clasn);
    if (modif & AccessNative) {
        addNativeMethodCxReference(method, clas);
    }
}

Symbol *javaMethodHeader(unsigned modif, Symbol *type,
                           Symbol *decl, int storage) {
    int newFun;

    completeDeclarator(type, decl);
    decl->bits.access = modif;
    decl->bits.storage = storage;
    if (s_javaStat->thisClass->bits.access & AccessInterface) {
        // set interface default access flags
        decl->bits.access |= (AccessPublic | AccessAbstract);
    }
    newFun = javaSetFunctionLinkName(s_javaStat->thisClass, decl, MEMORY_XX);
    addMethodCxReferences(modif, decl, s_javaStat->thisClass);
    if (newFun) {
        LIST_APPEND(Symbol, s_javaStat->thisClass->u.structSpec->records, decl);
    }
    return decl;
}

void javaAddMethodParametersToSymTable(Symbol *method) {
    Symbol *p;
    int i;
    for(p=method->u.typeModifier->u.f.args,i=1; p!=NULL; p=p->next,i++) {
        addFunctionParameterToSymTable(method, p, i, s_javaStat->locals);
    }
}

void javaMethodBodyBeginning(Symbol *method) {
    assert(method->u.typeModifier && method->u.typeModifier->kind == TypeFunction);
    s_cp.function = method;
    generateInternalLabelReference(-1, UsageDefined);
    counters.localVar = 0;
    javaAddMethodParametersToSymTable(method);
    method->u.typeModifier->u.m.signature = strchr(method->linkName, '(');
    s_javaStat->methodModifiers = method->bits.access;
}

// this should be merged with _bef_ token!
void javaMethodBodyEnding(Position *endpos) {
    if (options.taskRegime == RegimeEditServer) {
        if (s_cp.parserPassedMarker && !s_cp.thisMethodMemoriesStored){
            s_cps.methodCoordEndLine = currentFile.lineNumber+1;
        }
    }
    // I rely that it is nil, for example in setmove target
    s_cp.function = NULL;
}

void javaAddMapedTypeName(
                            char *file,
                            char *path,
                            char *pack,
                            Completions *c,
                            void *vdirid,
                            int  *storage
                        ) {
    char				*p;
    char                ttt2[MAX_FILE_NAME_SIZE];
    int					len2;
    IdList       dd2,*packid;
    Symbol			*memb;

    /*&fprintf(dumpOut,":import type %s %s %s\n", file, path, pack);&*/
    packid = (IdList *) vdirid;
    for(p=file; *p && *p!='.' && *p!='$'; p++) ;
    if (*p != '.') return;
    if (strcmp(p,".class")!=0 && strcmp(p,".java")!=0) return;
    len2 = p - file;
    strncpy(ttt2, file, len2);
    assert(len2+1 < MAX_FILE_NAME_SIZE);
    ttt2[len2] = 0;
    fillfIdList(&dd2, ttt2, NULL, s_noPos, ttt2, TypeStruct, packid);
    memb = javaTypeSymbolDefinition(&dd2, AccessDefault, ADD_YES);
    log_debug(":import type %s == %s", memb->name, memb->linkName);
}

TypeModifier *javaClassNameType(IdList *typeName) {
    Symbol *st;

    assert(typeName);
    assert(typeName->nameType == TypeStruct);
    st = javaTypeSymbolUsage(typeName, AccessDefault);

    return newStructTypeModifier(st);
}

TypeModifier *javaNestedNewType(Symbol *sym, Id *thenew,
                                IdList *idl) {
    IdList       d1,d2;
    TypeModifier     *res;
    char                *id2;
    Id			*id;
    Symbol			*str;
    Reference			*rr;
    if (idl->next == NULL) {
        // standard nested new
        id = &idl->id;
        assert(sym && sym->linkName);
        id2 = sym->linkName;
        fillfIdList(&d2, id2, sym, s_noPos, id2, TypeStruct, NULL);
        fillIdList(&d1, *id, id->name, TypeStruct, &d2);
        javaClassifyNameToNestedType(&d1, sym, UsageUsed, &str, &rr);
        res = javaClassNameType(&d1);
    } else {
        // O.K. extended case, usually syntax error, but ...
        javaClassifyToTypeName(idl, UsageUsed, &str, USELESS_FQT_REFS_ALLOWED);
        res = javaClassNameType(idl);
        // you may also check that idl->next == sym
        if (res && res->kind == TypeStruct) {
            assert(res->u.t && res->u.t->u.structSpec);
            if (res->u.t->bits.access & AccessStatic) {
                // add the prefix of new as redundant long name
                addUselessFQTReference(res->u.t->u.structSpec->classFile, &thenew->p);
            }
        } else {
            res = &s_errorModifier;
        }
    }
    return res;
}

TypeModifier *javaNewAfterName(IdList *name, Id *thenew, IdList *idl) {
    Symbol *str;
    TypeModifier *expr, *res;
    int atype;
    Reference *rr;

    atype = javaClassifyAmbiguousName(name,NULL,&str,&expr,&rr,NULL, USELESS_FQT_REFS_ALLOWED,CLASS_TO_EXPR,UsageUsed);
    if (atype == TypeExpression) {
        if (expr->kind != TypeStruct) res = & s_errorModifier;
        else res = javaNestedNewType(expr->u.t, thenew, idl);
    } else if (atype == TypeStruct) {
        assert(str);
        assert(str->bits.symbolType == TypeStruct);
        res = javaNestedNewType(str, thenew, idl);
    } else res = & s_errorModifier;
    return res;
}

static int javaExistBaseTypeWideningConversion(int t1, int t2) {
    int i1,i2,res;
    assert(t1>=0 && t1<MAX_TYPE);
    assert(t2>=0 && t2<MAX_TYPE);
/*fprintf(dumpOut,"testing base convertibility of %s to %s\n",typeName[t1],typesName[t2]);fflush(dumpOut);*/
    if (t1 == t2) return true;
    i1 = s_javaTypePCTIConvert[t1];
    i2 = s_javaTypePCTIConvert[t2];
    if (i1 == 0 || i2 == 0) return false;
    assert(i1-1>=0 && i1-1<MAX_PCTIndex-1);
    assert(i2-1>=0 && i2-1<MAX_PCTIndex-1);
    res = s_javaPrimitiveWideningConversions[i1-1][i2-1];
    assert(res == 0 || res == 1);
/*fprintf(dumpOut,"the result is %d\n",res); fflush(dumpOut);*/
    return res;
}

static int javaExistBaseWideningConversion(char c1, char c2) {
    int t1,t2;
/*fprintf(dumpOut,"testing base convertibility of %c to %c\n",c1,c2);fflush(dumpOut);*/
    assert(c1>=0 && c1<MAX_CHARS);
    assert(c2>=0 && c2<MAX_CHARS);
    if (c1 == c2) return true;
    t1 = s_javaCharCodeBaseTypes[c1];
    t2 = s_javaCharCodeBaseTypes[c2];
    return javaExistBaseTypeWideningConversion(t1, t2);
}

#define PassArrayTypeString(tstring) {\
    for(tstring++; *tstring && isdigit(*tstring); tstring++) ;\
}

static char * javaPassToNextParamInTypeString(char *ss) {
    assert(ss);
    while (*ss == '[') PassArrayTypeString(ss) ;
    assert(*ss);
    if (*ss == 'L') {
        for(ss++; *ss && *ss!=';'; ss++) ;
        ss++;
    } else {
        ss++;
    }
    return ss;
}

static Symbol *javaStringTypeObject(char **ss) {
    char        *s;
    Symbol    *res;
    s = *ss;
    if (*s == 'L') {
        res = javaGetFieldClass(s+1,&s);
        s++;
    } else if (*s == '[') {
        res = &s_javaArrayObjectSymbol;
        s = javaPassToNextParamInTypeString(s);
    } else {
        res = NULL;
        s++;
    }
    *ss = s;
    return res;
}

static int javaExistWideningConversion(char **t1, char **t2) {
    char ss1,*s1, *s2;
    char c1,c2;
    Symbol *sym1,*sym2;
    int res = 1;
    s1 = *t1; s2 = *t2;
    assert(s1 && s2);
/*fprintf(dumpOut,"testing convertibility of %s to %s\n",s1,s2);fflush(dumpOut);*/
    while (*s1 == '[' && *s2 == '[') {
        /* dereference array */
        PassArrayTypeString(s1);
        assert(*s1);
        PassArrayTypeString(s2);
        assert(*s2);
    }
    if (*s1 == JAVA_NULL_CODE && *s2 == '[') {
        s1++;
        while (*s2 == '[') PassArrayTypeString(s2);
        if (*s2 == 'L') javaStringTypeObject(&s2);
        else s2++;
        goto finish;
    }
    if (*s1 == 'L' || *s2 == 'L') {
        ss1 = *s1;
        sym1 = javaStringTypeObject(&s1);
        sym2 = javaStringTypeObject(&s2);
        if (ss1 == JAVA_NULL_CODE) {res &= 1; goto finish;}
        if (ss1 == '['
                &&  (sym2 == s_javaCloneableSymbol
                     || sym2 == s_javaIoSerializableSymbol
                     || sym2 == s_javaObjectSymbol)) {
            res &= 1; goto finish;
        }
        if (sym1==NULL || sym2 == NULL) {res &= 0; goto finish;}
        assert(sym1 && sym2 && sym1->u.structSpec);
        if (sym1 == sym2) {res &= 1; goto finish;}
        javaLoadClassSymbolsFromFile(sym1);
/*fprintf(dumpOut,"test cctmembership of %s to %s\n",sym1->linkName, sym2->linkName);*/
        res &= cctIsMember(&sym1->u.structSpec->casts, sym2, 1);
        goto finish;
    } else {
        c1 = *s1++; c2 = *s2++;
        res &= javaExistBaseWideningConversion(c1,c2);
        goto finish;
    }
    assert(0);
finish:
    *t1 = s1; *t2 = s2;
/*fprintf(dumpOut,"the result is %d\n",res); fflush(dumpOut);*/
    return res;
}


static int javaSmallerProfile(Symbol *s1, Symbol *s2) {
    int r;
    char *p1,*p2;
    assert(s1 && s1->bits.symbolType==TypeDefault && s1->u.typeModifier);
    assert(s1->u.typeModifier->kind == TypeFunction && s1->u.typeModifier->u.m.signature);
    assert(s2 && s2->bits.symbolType==TypeDefault && s2->u.typeModifier);
    assert(s2->u.typeModifier->kind == TypeFunction && s2->u.typeModifier->u.m.signature);
    p1 = s1->u.typeModifier->u.m.signature;
    p2 = s2->u.typeModifier->u.m.signature;
/*fprintf(dumpOut,"comparing %s to %s\n",p1,p2); fflush(dumpOut);*/
    assert(*p1 == '(');
    assert(*p2 == '(');
    p1 ++; p2++;
    while (*p1 != ')' && *p2 != ')') {
        r = javaExistWideningConversion(&p1, &p2);
        if (r == 0) return false;
    }
    if (*p1 != ')' || *p2 != ')') return false;
/*fprintf(dumpOut,"the result is 1\n"); fflush(dumpOut);*/
    return true;
}

int javaMethodApplicability(Symbol *memb, char *actArgs) {
    int r;
    char *fargs;
    assert(memb && memb->bits.symbolType==TypeDefault && memb->u.typeModifier);
    assert(memb->u.typeModifier->kind == TypeFunction && memb->u.typeModifier->u.m.signature);
    fargs = memb->u.typeModifier->u.m.signature;
//&sprintf(tmpBuff,"testing applicability of %s to %s\n",fargs,actArgs);ppcBottomInformation(tmpBuff);
    assert(*fargs == '(');
    fargs ++;
    while (*fargs != ')' && *actArgs!=0) {
        r = javaExistWideningConversion(&actArgs, &fargs);
        if (r == 0) return false;
    }
    if (*fargs == ')' && *actArgs == 0)
        return PROFILE_APPLICABLE;
    if (*actArgs == 0)
        return PROFILE_PARTIALLY_APPLICABLE;
    return PROFILE_NOT_APPLICABLE;
}

Symbol *javaGetSuperClass(Symbol *cc) {
    SymbolList		*sups;
    assert(cc->bits.symbolType == TypeStruct && cc->u.structSpec);
    sups = cc->u.structSpec->super;
    if (sups == NULL)
        return &s_errorSymbol;	/* class Object only */
    return sups->d;
}

Symbol *javaCurrentSuperClass(void) {
    TypeModifier     *tt;
    Symbol			*cc;

    assert(s_javaStat);
    tt = s_javaStat->thisType;
    assert(tt->kind == TypeStruct);
    cc = tt->u.t;
    return javaGetSuperClass(cc);
}

/* ********************* method invocations ************************** */

static TypeModifier *javaMethodInvocation(
                                        S_recFindStr *rfs,
                                        Symbol *memb,
                                        Id *name,
                                        S_typeModifierList *args,
                                        int invocationType,
                                        Position *superPos) {
    char				actArg[MAX_PROFILE_SIZE];
    Symbol            * appl[MAX_APPL_OVERLOAD_FUNS];
    int                 funCl[MAX_APPL_OVERLOAD_FUNS];
    unsigned			minacc[MAX_APPL_OVERLOAD_FUNS];
    SymbolList		*ee;
    S_typeModifierList *aaa;
    UsageBits			ub;
    int					smallesti, baseCl, vApplCl, vFunCl, usedusage;
    int					i,appli,actArgi,rr;

    assert(rfs->baseClass);  // method must be inside a class
    assert(rfs->baseClass->bits.symbolType == TypeStruct);
    baseCl = rfs->baseClass->u.structSpec->classFile;
    assert(baseCl != -1);

//&sprintf(tmpBuff,"java method invocation\n"); ppcBottomInformation(tmpBuff);
//&sprintf(tmpBuff,"the method is %s == '%s'\n",memb->name,memb->linkName);ppcBottomInformation(tmpBuff);
    assert(memb && memb->bits.symbolType==TypeDefault && memb->u.typeModifier->kind == TypeFunction);
    for(aaa=args; aaa!=NULL; aaa=aaa->next) {
        if (aaa->d->kind == TypeError) {
//&fprintf(dumpOut,"induced missinterpred at %d\n", name->p.line);
            addTrivialCxReference(LINK_NAME_INDUCED_ERROR,TypeInducedError,StorageDefault,
                                  &name->p, UsageUsed);
            return &s_errorModifier;
        }
    }
    *actArg = 0; actArgi = 0;
    for(aaa=args; aaa!=NULL; aaa=aaa->next) {
        actArgi += javaTypeToString(aaa->d,actArg+actArgi,MAX_PROFILE_SIZE-actArgi);
    }
//&sprintf(tmpBuff,"arguments types == %s\n",actArg);ppcBottomInformation(tmpBuff);
    appli = 0;
    do {
        assert(memb != NULL);
//&sprintf(tmpBuff,"testing: %s\n",memb->linkName);ppcBottomInformation(tmpBuff);
        if (javaRecordVisibleAndAccessible(rfs, rfs->baseClass, rfs->currClass, memb)
            && javaMethodApplicability(memb,actArg) == PROFILE_APPLICABLE) {
            appl[appli] = memb;
            minacc[appli] = javaGetMinimalAccessibility(rfs, memb);
            assert(rfs && rfs->currClass && rfs->currClass->bits.symbolType==TypeStruct);
            funCl[appli] = rfs->currClass->u.structSpec->classFile;
            assert(funCl[appli] != -1);
            appli++;
//&sprintf(tmpBuff,"applicable: %s of %s\n",memb->linkName,rfs->currClass->linkName);ppcBottomInformation(tmpBuff);
        }
        rr = findStrRecordSym(rfs, name->name, &memb,
                              CLASS_TO_METHOD, ACCESSIBILITY_CHECK_NO, VISIBILITY_CHECK_NO);
        if(invocationType==CONSTRUCTOR_INVOCATION&&rfs->baseClass!=rfs->currClass){
            // constructors are not inherited
            rr = RETURN_NOT_FOUND;
        }
    } while (rr==RETURN_OK);
    if (appli == 0)
        return &s_errorModifier;
//&sprintf(tmpBuff,"looking for smallest\n");ppcBottomInformation(tmpBuff);
    smallesti = 0;
    for (i=1; i<appli; i++) {
        if (! javaSmallerProfile(appl[smallesti], appl[i])) smallesti = i;
/*&		if (strcmp(appl[smallesti]->u.typeModifier->u.m.signature, appl[i]->u.typeModifier->u.m.signature)==0) {&*/
            /* virtual application, take one from the super-class */
/*&			smallesti = i;&*/
/*&		}&*/
    }
    for (i=0; i<appli; i++) {
        if (! javaSmallerProfile(appl[smallesti], appl[i]))
            return &s_errorModifier;
    }
//&sprintf(tmpBuff,"the invoked method is %s of %s\n\n",appl[smallesti]->linkName,fileTable.tab[funCl[smallesti]]->name);ppcBottomInformation(tmpBuff);
    assert(appl[smallesti]->bits.symbolType == TypeDefault);
    assert(appl[smallesti]->u.typeModifier->kind == TypeFunction);
    assert(funCl[smallesti] != -1);
    vFunCl = funCl[smallesti];
    vApplCl = baseCl;
//&	if (appl[smallesti]->bits.access & AccessStatic) {
//&		vFunCl = vApplCl = noFileIndex;
//&	}
    usedusage = UsageUsed;
    if (invocationType == CONSTRUCTOR_INVOCATION) {
        // this is just because java2html, so that constructors invocations
        // are linked to constructors rather than classes
        usedusage = UsageConstructorUsed;
    }
    if (invocationType == SUPER_METHOD_INVOCATION) {
        usedusage = UsageMethodInvokedViaSuper;
        addSuperMethodCxReferences(vFunCl, superPos);
    }
    fillUsageBits(&ub, usedusage, minacc[smallesti]);
    addCxReferenceNew(appl[smallesti], &name->p, &ub, vFunCl, vApplCl);
    if (options.server_operation == OLO_EXTRACT) {
        for(ee=appl[smallesti]->u.typeModifier->u.m.exceptions; ee!=NULL; ee=ee->next) {
            addCxReference(ee->d, &name->p, UsageThrown, noFileIndex, noFileIndex);
        }
    }
    return appl[smallesti]->u.typeModifier->next;
}


static void methodAppliedOnNonClass(char *rec) {
    char message[TMP_BUFF_SIZE];
    if (options.debug || options.errors) {
        sprintf(message, "'%s' not applied on a class", rec);
        errorMessage(ERR_ST, message);
    }
}

static void methodNameNotRecognized(char *rec) {
    char message[TMP_BUFF_SIZE];
    if (options.debug || options.errors) {
        sprintf(message, "'%s' not recognized as method name", rec);
        errorMessage(ERR_ST, message);
    }
}

S_extRecFindStr *javaCrErfsForMethodInvocationN(IdList *name) {
    S_extRecFindStr		*erfs;
    TypeModifier		*expr;
    Reference			*rr;
    int					nt;
    erfs = StackMemoryAlloc(S_extRecFindStr);
    erfs->params = NULL;
    nt = javaClassifyAmbiguousName(name, &erfs->s,&erfs->memb,&expr,&rr,NULL, USELESS_FQT_REFS_ALLOWED,CLASS_TO_METHOD,UsageUsed);
    if (nt != TypeExpression) {
        methodNameNotRecognized(name->id.name);
        return NULL;
    }
    if (expr == &s_errorModifier)
        return NULL;
    return erfs;
}

TypeModifier *javaMethodInvocationN(	IdList *name,
                                        S_typeModifierList *args
                                    ) {
    S_extRecFindStr		*erfs;
    TypeModifier		*res;
    erfs = javaCrErfsForMethodInvocationN(name);
    if (erfs == NULL)
        return &s_errorModifier;
    res = javaMethodInvocation(&erfs->s, erfs->memb, &name->id, args,REGULAR_METHOD,&s_noPos);
    return res;
}

S_extRecFindStr *javaCrErfsForMethodInvocationT(TypeModifier *tt,
                                                Id *name
    ) {
    S_extRecFindStr		*erfs;
    int					rr;
    log_trace("invocation of %s", name->name);
    if (tt->kind == TypeArray) tt = &s_javaArrayObjectSymbol.u.structSpec->stype;
    if (tt->kind != TypeStruct) {
        methodAppliedOnNonClass(name->name);
        return NULL;
    }
    erfs = StackMemoryAlloc(S_extRecFindStr);
    erfs->params = NULL;
    javaLoadClassSymbolsFromFile(tt->u.t);
    rr = findStrRecordSym(iniFind(tt->u.t,&erfs->s), name->name, &erfs->memb,
                        CLASS_TO_METHOD, ACCESSIBILITY_CHECK_NO,VISIBILITY_CHECK_NO);
    if (rr != RETURN_OK) {
        noSuchFieldError(name->name);
        return NULL;
    }
    return erfs;
}

TypeModifier *javaMethodInvocationT(TypeModifier *tt,
                                       Id *name,
                                       S_typeModifierList *args
                                       ) {
    S_extRecFindStr		*erfs;
    TypeModifier		*res;
    erfs = javaCrErfsForMethodInvocationT(tt, name);
    if (erfs == NULL)
        return &s_errorModifier;
    res = javaMethodInvocation(&erfs->s, erfs->memb, name, args,REGULAR_METHOD,&s_noPos);
    return res;
}

S_extRecFindStr *javaCrErfsForMethodInvocationS(Id *super, Id *name) {
    Symbol            *ss;
    S_extRecFindStr		*erfs;
    int					rr;
    ss = javaCurrentSuperClass();
    if (ss == &s_errorSymbol || ss->bits.symbolType==TypeError)
        return NULL;
    assert(ss && ss->bits.symbolType == TypeStruct);
    assert(ss->bits.javaFileIsLoaded);
    erfs = StackMemoryAlloc(S_extRecFindStr);
    erfs->params = NULL;
/*	I do not know, once will come the day I will know
    if (s_javaStat->cpMethod != NULL) {
        erfs->s.accessed = s_javaStat->cpMethod->b.accessFlags;
    }
*/
    rr = findStrRecordSym(iniFind(ss, &erfs->s), name->name, &erfs->memb,
                        CLASS_TO_METHOD,ACCESSIBILITY_CHECK_NO,VISIBILITY_CHECK_NO);
    if (rr != RETURN_OK)
        return NULL;
    return erfs;
}

TypeModifier *javaMethodInvocationS(Id *super,
                                       Id *name,
                                       S_typeModifierList *args
    ) {
    S_extRecFindStr		*erfs;
    TypeModifier		*res;
    erfs = javaCrErfsForMethodInvocationS(super, name);
    if (erfs==NULL)
        return &s_errorModifier;
    res = javaMethodInvocation(&erfs->s, erfs->memb, name, args, SUPER_METHOD_INVOCATION,&super->p);
    assert(erfs->s.currClass && erfs->s.currClass->u.structSpec);
    return res;
}

S_extRecFindStr *javaCrErfsForConstructorInvocation(Symbol *clas,
                                                    Position *pos
    ) {
    S_extRecFindStr		*erfs;
    int					rr;
    if (clas == &s_errorSymbol || clas->bits.symbolType==TypeError)
        return NULL;
    assert(clas && clas->bits.symbolType == TypeStruct);
    javaLoadClassSymbolsFromFile(clas);
    erfs = StackMemoryAlloc(S_extRecFindStr);
    erfs->params = NULL;
    assert(clas->bits.javaFileIsLoaded);
    rr = findStrRecordSym(iniFind(clas, &erfs->s), clas->name, &erfs->memb,
                        CLASS_TO_METHOD,ACCESSIBILITY_CHECK_NO,VISIBILITY_CHECK_NO);
    if (rr != RETURN_OK)
        return NULL;
    return erfs;
}

TypeModifier *javaConstructorInvocation(Symbol *clas,
                                           Position *pos,
                                           S_typeModifierList *args
    ) {
    S_extRecFindStr		*erfs;
    TypeModifier		*res;
    Id			name;
    erfs = javaCrErfsForConstructorInvocation(clas, pos);
    if (erfs == NULL)
        return &s_errorModifier;
    if (erfs->s.baseClass != erfs->s.currClass)
        return &s_errorModifier;
    fillId(&name, clas->name, NULL, *pos);
    res = javaMethodInvocation(&erfs->s, erfs->memb, &name, args,CONSTRUCTOR_INVOCATION,&s_noPos);
    return res;
}


/* ************************ expression evaluations ********************* */


static int javaIsNumeric(TypeModifier *tt) {
    assert(tt);
    switch (tt->kind) {
    case TypeByte: case TypeShort: case TypeChar:
    case TypeInt: case TypeLong:
    case TypeDouble: case TypeFloat:
        return true;
    default:
        return false;
    }
}

TypeModifier *javaCheckNumeric(TypeModifier *tt) {
    if (javaIsNumeric(tt))
        return tt;
    else
        return &s_errorModifier;
}

TypeModifier *javaNumericPromotion(TypeModifier *tt) {
    assert(tt);
    switch (tt->kind) {
    case TypeByte:
    case TypeShort:
    case TypeChar:
        return newSimpleTypeModifier(TypeInt);
    case TypeInt:
    case TypeLong:
    case TypeDouble:
    case TypeFloat:
        return tt;
    default:
        return &s_errorModifier;
    }
}

TypeModifier *javaBinaryNumericPromotion(TypeModifier *t1, TypeModifier *t2) {
    int m1,m2,resultingType;

    m1 = t1->kind;
    m2 = t2->kind;
    assert(t1 && t2);
    resultingType = TypeInt;
    if (m1 == TypeDouble || m2 == TypeDouble) resultingType = TypeDouble;
    else if (m1 == TypeFloat || m2 == TypeFloat) resultingType = TypeFloat;
    else if (m1 == TypeLong || m2 == TypeLong) resultingType = TypeLong;

    return newSimpleTypeModifier(resultingType);
}

TypeModifier *javaBitwiseLogicalPromotion(	TypeModifier *t1,
                                                TypeModifier *t2
                                            ) {
    assert(t1 && t2);
    if (t1->kind == TypeBoolean && t2->kind == TypeBoolean)
        return t1;
    return javaBinaryNumericPromotion(t1,t2);
}

int javaIsStringType(TypeModifier *tt) {
    if (tt->kind != TypeStruct)
        return false;
    return tt->u.t == s_javaStringSymbol;
}

static int javaEqualTypes(TypeModifier *t1,TypeModifier *t2) {
    int m;
lastRecursionLabel:
    if (t1->kind != t2->kind) return false;
    m = t1->kind;
    if (m == TypeStruct || m == TypeUnion)
        return t1->u.t == t2->u.t;
    if (m == TypeArray) {
        t1 = t1->next; t2 = t2->next;
        goto lastRecursionLabel;
    }
    assert(m != TypeFunction);
    return true;
}

static int javaTypeConvertible(TypeModifier *t1,
                               TypeModifier *t2
) {
    Symbol    *s1,*s2;
lastRecLabel:
    if (javaIsNumeric(t1) && javaIsNumeric(t2)) {
        return javaExistBaseTypeWideningConversion(t1->kind, t2->kind);
    }
    if (t1->kind != t2->kind)
        return false;
    if (t1->kind == TypeArray) {
        t1 = t1->next; t2 = t2->next;
        goto lastRecLabel;
    }
    if (t1->kind == TypeStruct) {
        int res;
        s1 = t1->u.t; s2 = t2->u.t;
        assert(s1 && s2);
        assert(s1->bits.symbolType == TypeStruct && s1->u.structSpec);
        javaLoadClassSymbolsFromFile(s1);
        res = cctIsMember(&s1->u.structSpec->casts, s2, 1);
//&fprintf(dumpOut,"!checking convertibility %s->%s, res==%d\n",s1->linkName, s2->linkName, res);fflush(dumpOut);
        return res;
    }
    return 0;
}

TypeModifier *javaConditionalPromotion(	TypeModifier *t1,
                                            TypeModifier *t2
                                        ) {
    if (javaEqualTypes(t1,t2))
        return t1;
    if (javaIsNumeric(t1) && javaIsNumeric(t2)) {
        if (t1->kind == TypeShort && t2->kind == TypeByte)
            return t1;
        if (t1->kind == TypeByte && t2->kind == TypeShort)
            return t2;
        /* TO FINISH FOR BYTE, SHORT, CHAR CONSTANT */
        return javaBinaryNumericPromotion(t1,t2);
    }
    if (t1->kind == TypeNull && IsJavaReferenceType(t2->kind))
        return t2;
    if (t2->kind == TypeNull && IsJavaReferenceType(t1->kind))
        return t1;
    if (! IsJavaReferenceType(t1->kind) || ! IsJavaReferenceType(t2->kind)) {
        return &s_errorModifier;
    }
    if (javaTypeConvertible(t1,t2))
        return t2;
    if (javaTypeConvertible(t2,t1))
        return t1;
    return &s_errorModifier;
}

void javaTypeDump(TypeModifier *tt) {
    assert(tt);
    if (tt->kind == TypeArray) {
        javaTypeDump(tt->next);
        fprintf(dumpOut,"[]");
    } else if (tt->kind == TypeStruct) {
        fprintf(dumpOut,"%s",tt->u.t->linkName);
    } else {
        fprintf(dumpOut,"%s",typeNamesTable[tt->kind]);
    }
}

void javaAddJslReadedTopLevelClasses(JslTypeTab  *jslTypeTab) {
    int					i;
    JslSymbolList     *ss;
    for(i=0; i<jslTypeTab->size; i++) {
        if (jslTypeTab->tab[i]!=NULL) {
            LIST_REVERSE(JslSymbolList, jslTypeTab->tab[i]);
            for(ss=jslTypeTab->tab[i]; ss!=NULL; ss=ss->next) {
                javaAddTypeToSymbolTable(ss->d, ss->d->bits.access, &ss->position, ss->isExplicitlyImported);
            }
            LIST_REVERSE(JslSymbolList, jslTypeTab->tab[i]);
        }
    }
}

static void javaAddNestedClassToSymbolTab( Symbol *str ) {
    S_symStructSpec *ss;
    int i;

    assert(str && str->bits.symbolType==TypeStruct);
    ss = str->u.structSpec;
    assert(ss);
    for(i=0; i<ss->nestedCount; i++) {
        if (ss->nest[i].membFlag && javaRecordAccessible(NULL,str, str, ss->nest[i].cl, ss->nest[i].accFlags)) {
            javaAddTypeToSymbolTable(ss->nest[i].cl, ss->nest[i].cl->bits.access, &s_noPos, false);
        }
    }
}

void javaAddSuperNestedClassToSymbolTab( Symbol *cc ) {
    SymbolList *ss;
    for(ss=cc->u.structSpec->super; ss != NULL; ss=ss->next) {
        javaAddSuperNestedClassToSymbolTab(ss->d);
    }
    javaAddNestedClassToSymbolTab(cc);
}


struct freeTrail *newClassDefinitionBegin(Id *name,
                                          Access access,
                                          Symbol *anonymousInterface) {
    IdList   *p;
    Symbol        *dd,*ddd;
    FreeTrail     *res;
    S_javaStat      *oldStat;
    int             nnest,noff,classf;
    S_nestedSpec	*nst,*nn;
    SymbolTable	*locals;
    Id		idi;

    assert(s_javaStat);
    oldStat = s_javaStat;
    s_javaStat = StackMemoryAlloc(S_javaStat);
    *s_javaStat = *oldStat;
    s_javaStat->next = oldStat;
    locals = StackMemoryAlloc(SymbolTable);
    symbolTableInit(locals, MAX_CL_SYMBOLS);
/*&fprintf(dumpOut,"adding new class %s\n",name->name);fflush(dumpOut);&*/
    if (oldStat->next!=NULL) {
        /* ** nested class ** */
        if (oldStat->thisClass->bits.access & AccessInterface) {
            access |= (AccessPublic | AccessStatic);
        }
        nnest = oldStat->thisClass->u.structSpec->nestedCount;
        nst = oldStat->thisClass->u.structSpec->nest;
        noff = oldStat->currentNestedIndex;
        oldStat->currentNestedIndex ++;
//&sprintf(tmpBuff,"checking %d of %d of %s(%d)\n", noff,nnest,oldStat->thisClass->linkName, oldStat->thisClass);ppcBottomInformation(tmpBuff);
        assert(noff >=0 && noff<nnest);
        nn = & nst[noff];
        // nested class, it should be the same order as in first pass
        // but name can be different for anonymous classes?
//&fprintf(dumpOut,"comparing '%s' <-> '%s'\n", nn->cl->name, name->name);fflush(dumpOut);
//&		innerNamesCorrect = (strcmp(nn->cl->name, name->name)==0);
//&		assert(innerNamesCorrect);
        dd = nn->cl;
        fillId(&idi,dd->linkName, NULL, name->p);
        p = StackMemoryAlloc(IdList);
        fillIdList(p, idi, dd->linkName, TypeStruct, NULL);
        ddd = javaAddType(p, access, &name->p);
        assert(dd==ddd);
        //&javaCreateClassFileItem(dd);
    } else {
        /* probably base class */
        p = StackMemoryAlloc(IdList);
        fillIdList(p,*name,name->name,TypeStruct,s_javaStat->className);
        dd = javaAddType(p, access, &name->p);
        assert(dd->bits.symbolType == TypeStruct);
        s_spp[SPP_LAST_TOP_LEVEL_CLASS_POSITION] = name->p;
    }
    res = currentBlock->trail;
    classf = dd->u.structSpec->classFile;
    if (classf == -1)
        classf = noFileIndex;
    fillJavaStat(s_javaStat,p,&dd->u.structSpec->stype,dd,0, oldStat->currentPackage,
                  oldStat->unnamedPackagePath, oldStat->namedPackagePath,
                  locals, oldStat->lastParsedName,AccessDefault,s_cp,classf,oldStat);
    // added 8/8/2001 for clearing s_cp.function for SET_TARGET_POSITION check
    s_cp = s_cpInit;
//&fprintf(dumpOut,"clearing s_cp\n");
    return res;
}

struct freeTrail *newAnonClassDefinitionBegin(Id *interfName) {
    struct freeTrail * res;
    IdList	*ll;
    Symbol		*interf, *str;
    ll = StackMemoryAlloc(IdList);
    fillIdList(ll, *interfName, interfName->name, TypeDefault, NULL);
    javaClassifyToTypeName(ll,UsageUsed,&str, USELESS_FQT_REFS_ALLOWED);
    interf = javaTypeNameDefinition(ll);
    res = newClassDefinitionBegin(&s_javaAnonymousClassName, AccessDefault,
                                  interf);
    return res;
}

void newClassDefinitionEnd(FreeTrail *trail) {
    assert(s_javaStat && s_javaStat->next);
    removeFromTrailUntil(trail);
    /* TODO: WTF?!??! */
    // the following line makes that method extraction does not work,
    // make attention with it, ? really
    s_cp = s_javaStat->cp;
    s_javaStat = s_javaStat->next;
    log_trace("recovering s_cp to %d", s_cp.cxMemoryIndexdiAtClassBegin);
}

void javaInitArrayObject(void) {
    static Symbol s_lengthSymbol;
    static S_symStructSpec s_arraySpec;

    assert(s_javaObjectSymbol != NULL);
    javaLoadClassSymbolsFromFile(s_javaObjectSymbol);

    fillSymbolWithTypeModifier(&s_lengthSymbol, "length", "java/lang/array.length",
                       s_noPos, &defaultIntModifier);

    initSymStructSpec(&s_arraySpec, /*.records=*/&s_lengthSymbol);
    /* Assumed to be Struct/Union/Enum? */
    initTypeModifierAsStructUnionOrEnum(&s_arraySpec.stype, /*.kind=*/TypeStruct,
                                        /*.u.t=*/&s_javaArrayObjectSymbol,
                                        /*.typedefSymbol=*/NULL, /*.next=*/NULL);
    initTypeModifierAsPointer(&s_arraySpec.sptrtype, &s_arraySpec.stype);

    fillSymbolWithStruct(&s_javaArrayObjectSymbol, "__arrayObject__", "__arrayObject__",
                         s_noPos, &s_arraySpec);
    fillSymbolBits(&s_javaArrayObjectSymbol.bits, AccessPublic, TypeStruct, StorageDefault);
    s_javaArrayObjectSymbol.u.structSpec = &s_arraySpec;

    javaCreateClassFileItem(&s_javaArrayObjectSymbol);
    addSuperClassOrInterfaceByName(&s_javaArrayObjectSymbol,s_javaLangObjectLinkName,
                                   noFileIndex, LOAD_SUPER);
}

TypeModifier *javaArrayFieldAccess(Id *id) {
    Symbol *rec=NULL;
    findStructureFieldFromType(&s_javaArrayObjectSymbol.u.structSpec->stype, id, &rec, CLASS_TO_EXPR);
    assert(rec);
    return rec->u.typeModifier;
}

void javaParsedSuperClass(Symbol *symbol) {
    SymbolList *pp;
    assert(s_javaStat->thisClass && s_javaStat->thisClass->bits.symbolType==TypeStruct);
    assert(s_javaStat->thisClass->u.structSpec);
    assert(symbol && symbol->bits.symbolType==TypeStruct && symbol->u.structSpec);
    for(pp=s_javaStat->thisClass->u.structSpec->super; pp!=NULL; pp=pp->next) {
        if (pp->d == symbol) break;
    }
    if (pp==NULL) {
//&fprintf(dumpOut,"manual super class %s of %s == %s\n",symbol->linkName,s_javaStat->thisClass->linkName, fileTable.tab[s_javaStat->thisClass->u.structSpec->classFile]->name);fflush(dumpOut);
        //&assert(0); // this should never comed now
        javaLoadClassSymbolsFromFile(symbol);
        addSuperClassOrInterface(s_javaStat->thisClass, symbol,
                                 currentFile.lexBuffer.buffer.fileNumber);
    }
}

void javaSetClassSourceInformation(char *package, Id *classId) {
    char    fqt[MAX_FILE_NAME_SIZE];
    char    className[2*MAX_FILE_NAME_SIZE];
    int		fileIndex;

    assert(classId!=NULL);
    if (*package == 0) {
        sprintf(fqt, "%s", classId->name);
    } else {
        sprintf(fqt, "%s/%s", package, classId->name);
    }
    SPRINT_FILE_TAB_CLASS_NAME(className, fqt);
    fileIndex = addFileTabItem(className);
    fileTable.tab[fileIndex]->b.sourceFileNumber = classId->p.file;
}


void javaCheckIfPackageDirectoryIsInClassOrSourcePath(char *dir) {
    char tmpBuff[TMP_BUFF_SIZE];

    if (options.taskRegime == RegimeEditServer)
        return;
    for (StringList *pp=javaClassPaths; pp!=NULL; pp=pp->next) {
        if (compareFileNames(dir, pp->string)==0)
            return;
    }
    MapOnPaths(javaSourcePaths, {
            if (compareFileNames(dir, currentPath)==0)
                return;
        });
    sprintf(tmpBuff, "Directory %s is not listed in paths", dir);
    warningMessage(ERR_ST, tmpBuff);
}
