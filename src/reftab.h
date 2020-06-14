#ifndef _REFTAB_H_
#define _REFTAB_H_

#include "proto.h"

#define HASH_TAB_NAME refTab
#define HASH_TAB_TYPE ReferenceTable
#define HASH_ELEM_TYPE SymbolReferenceItem

#include "hashlist.th"

/* TODO: this is somewhat irregular naming, "cx" or not? */
extern ReferenceTable s_cxrefTab;

#ifndef _IN_REFTAB_C_
#undef HASH_TAB_NAME
#undef HASH_TAB_TYPE
#undef HASH_ELEM_TYPE
#endif

#endif
