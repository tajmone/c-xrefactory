#ifndef HTML_H
#define HTML_H

#include "proto.h"
#include "symbol.h"

typedef struct htmlData {
    struct position          *cp;
    struct reference         *np;
    struct symbolReferenceItem     *nri;
} S_htmlData;

typedef struct htmlRefList {
    struct symbolReferenceItem	*symbolRefItem;
    struct reference		*reference;
    struct symbolReferenceItem	*slist;		/* hash list containing symbolRefItem, for virtuals */
    struct htmlRefList		*next;
} S_htmlRefList;

extern void genClassHierarchyItemLinks(FILE *ff, S_olSymbolsMenu *itt,
                                       int virtFlag);
extern void htmlGenNonVirtualGlobSymList(FILE *ff, char *fn, SymbolReferenceItem *p );
extern void htmlGenGlobRefsForVirtMethod(FILE *ff, char *fn,
                                         S_olSymbolsMenu *rrr);
extern int htmlRefItemsOrderLess(S_olSymbolsMenu *ss1, S_olSymbolsMenu *ss2);
extern char *htmlNormalizedPath(char *p);
extern void recursivelyCreateFileDirIfNotExists(char *fpath);
extern void concatPaths(char *res, int rsize, char *p1, char *p2, char *p3);
extern void htmlPutChar(FILE *ff, int c);
extern void htmlGenGlobalReferenceLists(char *cxMemFreeBase);
extern void htmlAddJavaDocReference(Symbol  *p, Position  *pos,
                                    int  vFunClass, int  vApplClass);
extern void htmlGetDefinitionReferences(void);
extern void htmlAddFunctionSeparatorReference(void);
extern void generateHtml(void);

#endif
