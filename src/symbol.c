#include "symbol.h"

#include "misc.h"               /* For XX_ALLOC() */

void fillSymbolBits(S_symbolBits *bits, unsigned accessFlags, unsigned symType, unsigned storage) {
    memset(bits, 0, sizeof(S_symbolBits));
    bits->accessFlags = accessFlags;
    bits->symType = symType;
    bits->storage = storage;
}

void fillSymbol(Symbol *s, char *name, char *linkName, struct position  pos) {
    s->name = name;
    s->linkName = linkName;
    s->pos = pos;
    s->u.type = NULL;
    s->next = NULL;
    fillSymbolBits(&s->bits, ACC_DEFAULT, TypeDefault, StorageDefault);
}


void fillSymbolWithType(Symbol *symbol, char *name, char *linkName, struct position pos, struct typeModifiers *type) {
    fillSymbol(symbol, name, linkName, pos);
    symbol->u.type = type;
}

void fillSymbolWithStruct(Symbol *symbol, char *name, char *linkName, struct position pos, struct symStructSpec *structSpec) {
    fillSymbol(symbol, name, linkName, pos);
    symbol->u.s = structSpec;
}

void fillSymbolWithLabel(Symbol *symbol, char *name, char *linkName, struct position pos, int labelIndex) {
    fillSymbol(symbol, name, linkName, pos);
    symbol->u.labn = labelIndex;
}

Symbol *newSymbol(char *name, char *linkName, struct position pos) {
    Symbol *s;

    XX_ALLOC(s, Symbol);
    fillSymbol(s, name, linkName, pos);

    return s;
}

Symbol *newSymbolIsKeyword(char *name, char *linkName, struct position pos, int keyWordVal) {
    Symbol *s = newSymbol(name, linkName, pos);
    s->u.keyWordVal = keyWordVal;
    return s;
}

Symbol *newSymbolIsType(char *name, char *linkName, struct position pos, struct typeModifiers *type) {
    Symbol *s = newSymbol(name, linkName, pos);
    s->u.type = type;
    return s;
}

Symbol *newSymbolIsEnum(char *name, char *linkName, struct position pos, struct symbolList *enums) {
    Symbol *s = newSymbol(name, linkName, pos);
    s->u.enums = enums;
    return s;
}

Symbol *newSymbolIsLabel(char *name, char *linkName, struct position pos, int labelIndex) {
    Symbol *s = newSymbol(name, linkName, pos);
    s->u.labn = labelIndex;
    return s;
}
