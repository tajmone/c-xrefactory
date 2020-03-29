#ifndef JSLSEMACT_H
#define JSLSEMACT_H

#include "proto.h"
#include "symbol.h"
#include "jsltypetab.h"


typedef struct jslStat {
    int                              pass;
    int                              sourceFileNumber;
    int                              language;
    struct jslTypeTab                *typeTab;
    struct jslClassStat              *classStat;
    struct symbolList                *waitList;
    void/*YYSTYPE*/                  *savedyylval;
    void /*struct yyGlobalState*/    *savedYYstate;
    int                              yyStateSize;
    struct id                        yyIdentBuf[YYBUFFERED_ID_INDEX]; // pending idents
    struct jslStat                   *next;
} S_jslStat;



extern void fillJslStat(S_jslStat *jslStat, int pass, int sourceFileNumber, int language, S_jslTypeTab *typeTab,
                        S_jslClassStat *classStat, SymbolList *waitList, void *savedyylval,
                        void /*S_yyGlobalState*/ *savedYYstate, int yyStateSize, S_jslStat *next);
extern Symbol *jslTypeSpecifier1(unsigned t);
extern Symbol *jslTypeSpecifier2(S_typeModifiers *t);

extern void jslCompleteDeclarator(Symbol *t, Symbol *d);
extern S_typeModifiers *jslPrependComposedType(S_typeModifiers *d, unsigned t);
extern S_typeModifiers *jslAppendComposedType(S_typeModifiers **d, unsigned t);
extern Symbol *jslPrependDirectEnclosingInstanceArgument(Symbol *args);
extern Symbol *jslMethodHeader(unsigned modif, Symbol *type, Symbol *decl, int storage, SymbolList *throws);
extern Symbol *jslTypeNameDefinition(S_idList *tname);
extern Symbol *jslTypeSymbolDefinition(char *ttt2, S_idList *packid,
                                         int add, int order, int isSingleImportedFlag);
extern int jslClassifyAmbiguousTypeName(S_idList *name, Symbol **str);
extern void jslAddNestedClassesToJslTypeTab( Symbol *cc, int order);
extern void jslAddSuperNestedClassesToJslTypeTab( Symbol *cc);

extern void jslAddSuperClassOrInterfaceByName(Symbol *memb,char *super);
extern void jslNewClassDefinitionBegin(S_id *name,
                                       int accessFlags,
                                       Symbol *anonInterf,
                                       int position
                                       );
extern void jslAddDefaultConstructor(Symbol *cl);
extern void jslNewClassDefinitionEnd(void);
extern void jslNewAnonClassDefinitionBegin(S_id *interfName);

extern void jslAddSuperClassOrInterface(Symbol *memb,Symbol *supp);
extern void jslAddMapedImportTypeName(
                                      char *file,
                                      char *path,
                                      char *pack,
                                      S_completions *c,
                                      void *vdirid,
                                      int  *storage
                                      );
extern void jslAddAllPackageClassesFromFileTab(S_idList *pack);


extern S_jslStat *s_jsl;

#endif
