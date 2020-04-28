#ifndef _ID_H_
#define _ID_H_

#include "type.h"
#include "symbol.h"
#include "position.h"


typedef struct id {
    char *name;
    struct symbol *sd;
    struct position	p;
    struct id *next;
} Id;

typedef struct idList {
    struct id id;
    char *fname;                /* fqt name for java */
    enum type nameType;             /* type of name segment for java */
    struct idList *next;
} IdList;


extern void fillId(Id *id, char *name, Symbol *symbol, Position position);

extern void fillIdList(IdList *idList, Id id, char *fname, Type nameType, IdList *next);
extern void fillfIdList(IdList *idList, char *name, Symbol *symbol, Position position,
                         char *fname, Type nameType, IdList *next);

#endif
