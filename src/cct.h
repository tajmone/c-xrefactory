#ifndef CCT_H
#define CCT_H

#include "proto.h"
#include "symbol.h"

extern void cctAddSimpleValue(S_cctNode *cc, Symbol *x, int deepFactor);
extern int cctIsMember(S_cctNode *cc, Symbol *x, int deepFactor);
extern void cctAddCctTree(S_cctNode *cc, S_cctNode *x, int deepFactor);
extern void cctDump(S_cctNode *cc, int deep);
extern void cctTest(void);

#endif
