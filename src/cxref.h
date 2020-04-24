#ifndef CXREF_H
#define CXREF_H

#include "proto.h"
#include "symbol.h"
#include "olcxtab.h"

extern void fill_reference(S_reference *reference, UsageBits usage, Position position, S_reference *next);
extern void fill_symbolRefItem(SymbolReferenceItem *symbolRefItem, char *name, unsigned fileHash, int vApplClass, int vFunClass, struct symbolReferenceItemBits bits);
extern void fill_symbolRefItemBits(SymbolReferenceItemBits *symbolRefItemBits, unsigned symType,
                                   unsigned storage, unsigned scope, unsigned accessFlags,
                                   unsigned category, unsigned htmlWasLn);
extern void fill_olSymbolsMenu(S_olSymbolsMenu *olSymbolsMenu, struct symbolReferenceItem	s,
                               char selected, char visible, unsigned ooBits, char olUsage,
                               short int vlevel, short int refn, short int defRefn,
                               char defUsage, struct position defpos, int outOnLine,
                               struct editorMarkerList *markers,	/* for refactory only */
                               struct olSymbolsMenu *next);
extern void fillUsageBits(UsageBits *STRUCTP, unsigned base, unsigned requiredAccess);
extern int olcxReferenceInternalLessFunction(S_reference *r1, S_reference *r2);
extern bool olSymbolRefItemLess(SymbolReferenceItem *s1, SymbolReferenceItem *s2);
extern void tagSearchCompactShortResults(void);
extern void printTagSearchResults(void);
extern S_olSymbolsMenu *olCreateSpecialMenuItem(char *fieldName, int cfi,int storage);
extern int itIsSameCxSymbol(SymbolReferenceItem *p1, SymbolReferenceItem *p2);
extern int itIsSameCxSymbolIncludingFunClass(SymbolReferenceItem *p1, SymbolReferenceItem *p2);
extern int itIsSameCxSymbolIncludingApplClass(SymbolReferenceItem *p1, SymbolReferenceItem *p2);
extern int olcxItIsSameCxSymbol(SymbolReferenceItem *p1, SymbolReferenceItem *p2);
extern void olcxRecomputeSelRefs( S_olcxReferences *refs );
extern void olProcessSelectedReferences(S_olcxReferences *rstack,
                                        void (*referencesMapFun)(S_olcxReferences *rstack,
                                                                 S_olSymbolsMenu *ss));
extern void olcxPopOnly(void);
extern S_reference * olcxCopyRefList(S_reference *ll);
extern void olStackDeleteSymbol( S_olcxReferences *refs);
extern int getFileNumberFromName(char *name);
extern void generateOnlineCxref(Position *p, char *commandString, int usage,
                                char *suffix, char *suffix2
                                );
extern S_reference *olcxAddReferenceNoUsageCheck(S_reference **rlist,
                                                 S_reference *ref,
                                                 int bestMatchFlag);
extern S_reference *olcxAddReference(S_reference **rlist,
                                     S_reference *ref,
                                     int bestMatchFlag);
extern void olcxFreeReferences(S_reference *r);
extern int isSmallerOrEqClass(int inf, int sup);
extern int olcxPushLessFunction(S_reference *r1, S_reference *r2);
extern int olcxListLessFunction(S_reference *r1, S_reference *r2);
extern char *getJavaDocUrl_st(SymbolReferenceItem *rr);
extern char *getLocalJavaDocFile_st(char *fileUrl);
extern char *getFullUrlOfJavaDoc_st(char *fileUrl);
extern int htmlJdkDocAvailableForUrl(char *ss);
extern S_reference *duplicateReference(S_reference *r);
extern S_reference * addCxReferenceNew(Symbol *p, Position *pos,
                                       UsageBits *ub, int vFunCl, int vApplCl);
extern S_reference * addCxReference(Symbol *p, Position *pos, Usage usage,
                                    int vFunClass,int vApplClass);
extern S_reference *addSpecialFieldReference(char *name, int storage,
                                             int fnum, Position *p, int usage);
extern void addClassTreeHierarchyReference(int fnum, Position *p, int usage);
extern void addCfClassTreeHierarchyRef(int fnum, int usage);
extern void addTrivialCxReference (char *name, int symType, int storage,
                                   Position *pos, int usage);
extern void olcxAddReferences(S_reference *list, S_reference **dlist, int fnum,
                              int bestMatchFlag);
extern void olSetCallerPosition(Position *pos);
extern S_olCompletion * olCompletionListPrepend(char *name, char *fullText,
                                                char *vclass, int jindent, Symbol *s,
                                                SymbolReferenceItem *ri, S_reference *dfpos,
                                                int symType, int vFunClass,
                                                S_olcxReferences *stack);
extern S_olSymbolsMenu *olCreateNewMenuItem(SymbolReferenceItem *sym, int vApplClass,
                                            int vFunCl, Position *defpos, int defusage,
                                            int selected, int visible,
                                            unsigned ooBits, int olusage, int vlevel
                                            );
extern S_olSymbolsMenu *olAddBrowsedSymbol(SymbolReferenceItem *sym, S_olSymbolsMenu **list,
                                           int selected, int visible, unsigned ooBits,
                                           int olusage, int vlevel,
                                           Position *defpos, int defusage);
extern void renameCollationSymbols(S_olSymbolsMenu *sss);
extern void olCompletionListReverse(void);
extern S_reference **addToRefList(S_reference **list,
                                  UsageBits *pusage,
                                  Position *pos,
                                  int category
                                  );
extern bool isInRefList(S_reference *list,
                        UsageBits *pusage,
                        Position *pos,
                        int category);
extern char *getXrefEnvironmentValue( char *name );
extern int byPassAcceptableSymbol(SymbolReferenceItem *p);
extern int itIsSymbolToPushOlRefences(SymbolReferenceItem *p, S_olcxReferences *rstack,
                                      S_olSymbolsMenu **rss, int checkSelFlag);
extern void olcxAddReferenceToOlSymbolsMenu(S_olSymbolsMenu  *cms, S_reference *rr,
                                            int bestFitTlag);
extern void putOnLineLoadedReferences(SymbolReferenceItem *p);
extern void genOnLineReferences(S_olcxReferences *rstack, S_olSymbolsMenu *cms);
extern S_olSymbolsMenu *createSelectionMenu(SymbolReferenceItem *dd);
extern void mapCreateSelectionMenu(SymbolReferenceItem *dd);
extern int olcxFreeOldCompletionItems(S_olcxReferencesStack *stack);
extern void olcxInit(void);
extern S_userOlcx *olcxSetCurrentUser(char *user);
extern S_reference * getDefinitionRef(S_reference *rr);
extern int safetyCheck2ShouldWarn(void);
extern void olCreateSelectionMenu(int command);
extern void olcxPushEmptyStackItem(S_olcxReferencesStack *stack);
extern void olcxPrintSelectionMenu(S_olSymbolsMenu *sss);
extern int ooBitsGreaterOrEqual(unsigned oo1, unsigned oo2);
extern void olcxPrintClassTree(S_olSymbolsMenu *sss);
extern void olcxReferencesDiff(S_reference **anr1, S_reference **aor2,
                               S_reference **diff);
extern int olcxShowSelectionMenu(void);
extern int getClassNumFromClassLinkName(char *name, int defaultResult);
extern void getLineColCursorPositionFromCommandLineOption( int *l, int *c );
extern void changeClassReferencesUsages(char *linkName, int category, int fnum,
                                        Symbol *cclass);
extern int isStrictlyEnclosingClass(int enclosedClass, int enclosingClass);
extern void changeMethodReferencesUsages(char *linkName, int category, int fnum,
                                         Symbol *cclass);
extern void olcxPushSpecialCheckMenuSym(int command, char *symname);
extern int refOccursInRefs(S_reference *r, S_reference *list);
extern void olcxCheck1CxFileReference(SymbolReferenceItem *ss, S_reference *r);
extern void olcxPushSpecial(char *fieldName, int command);
extern int isPushAllMethodsValidRefItem(SymbolReferenceItem *ri);
extern int symbolsCorrespondWrtMoving(S_olSymbolsMenu *osym, S_olSymbolsMenu *nsym,
                                      int command);
extern void olcxPrintPushingAction(int opt, int afterMenu);
extern void olPushAllReferencesInBetween(int minMemi, int maxMemi);
extern Symbol *getMoveTargetClass(void);
extern int javaGetSuperClassNumFromClassNum(int cn);
extern int javaIsSuperClass(int superclas, int clas);
extern void pushLocalUnusedSymbolsAction(void);
extern void mainAnswerEditAction(void);
extern void freeOldestOlcx(void);
extern S_olSymbolsMenu *olcxFreeSymbolMenuItem(S_olSymbolsMenu *ll);
extern void olcxFreeResolutionMenu( S_olSymbolsMenu *sym );
extern int refCharCode(int usage);

extern void initAvailableRefactorings(void);

#endif
