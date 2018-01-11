#ifndef _MATAB_H_
#define _MATAB_H_

/* Macro argument table - instance of hashtable */

#include "proto.h"

#define HASH_TAB_NAME maTab
#define HASH_ELEM_TYPE S_macroArgTabElem

#include "hashtab.th"

extern struct maTab s_maTab;

#ifndef _MATAB_
#undef HASH_TAB_NAME
#undef HASH_ELEM_TYPE
#endif

#endif
