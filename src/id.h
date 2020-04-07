#ifndef _ID_H_
#define _ID_H_

#include "types.h"
#include "symbol.h"
#include "position.h"


typedef struct id {
    char *name;
    struct symbol *sd;
    struct position	p;
    struct id *next;
} S_id;

typedef struct idList {
    struct id id;
    char *fname;                /* fqt name for java */
    enum type nameType;             /* type of name segment for java */
    struct idList *next;
} S_idList;


extern void fill_id(S_id *id, char *name, Symbol *symbol, S_position position);

extern void fill_idList(S_idList *idList, S_id id, char *fname, Type nameType, S_idList *next);
extern void fillf_idList(S_idList *idList, char *name, Symbol *symbol, int file, int line, int col,
                         char *fname, Type nameType, S_idList *next);

#endif
