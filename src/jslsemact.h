#ifndef JSLSEMACT_H
#define JSLSEMACT_H

#include "proto.h"

extern Symbol *jslTypeSpecifier1(unsigned t);
extern Symbol *jslTypeSpecifier2(S_typeModifiers *t);

extern void jslCompleteDeclarator(Symbol *t, Symbol *d);
extern S_typeModifiers *jslPrependComposedType(S_typeModifiers *d, unsigned t);
extern S_typeModifiers *jslAppendComposedType(S_typeModifiers **d, unsigned t);
extern Symbol *jslPrependDirectEnclosingInstanceArgument(Symbol *args);
extern Symbol *jslMethodHeader(unsigned modif, Symbol *type, Symbol *decl, int storage, SymbolList *throws);
extern Symbol *jslTypeNameDefinition(S_idIdentList *tname);
extern Symbol *jslTypeSymbolDefinition(char *ttt2, S_idIdentList *packid,
                                         int add, int order, int isSingleImportedFlag);
extern int jslClassifyAmbiguousTypeName(S_idIdentList *name, Symbol **str);
extern void jslAddNestedClassesToJslTypeTab( Symbol *cc, int order);
extern void jslAddSuperNestedClassesToJslTypeTab( Symbol *cc);

extern void jslAddSuperClassOrInterfaceByName(Symbol *memb,char *super);
extern void jslNewClassDefinitionBegin(S_idIdent *name,
                                       int accessFlags,
                                       Symbol *anonInterf,
                                       int position
                                       );
extern void jslAddDefaultConstructor(Symbol *cl);
extern void jslNewClassDefinitionEnd(void);
extern void jslNewAnonClassDefinitionBegin(S_idIdent *interfName);

extern void jslAddSuperClassOrInterface(Symbol *memb,Symbol *supp);
extern void jslAddMapedImportTypeName(
                                      char *file,
                                      char *path,
                                      char *pack,
                                      S_completions *c,
                                      void *vdirid,
                                      int  *storage
                                      );
extern void jslAddAllPackageClassesFromFileTab(S_idIdentList *pack);


extern S_jslStat *s_jsl;

#endif
