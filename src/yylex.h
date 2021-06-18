#ifndef YYLEX_H
#define YYLEX_H

#include "proto.h"
#include "editor.h"


typedef struct macroBody {
    short int argn;
    int size;
    char *name;			/* the name of the macro */
    char **args;		/* names of arguments */
    char *body;
} MacroBody;

typedef struct macroArgumentTableElement {
    char *name;
    char *linkName;
    int order;
} MacroArgumentTableElement;

typedef struct lexInput {
    char *currentLexemP;
    char *endOfBuffer;
    char *beginningOfBuffer;
    char *macroName;
    InputType inputType;
} LexInput;

extern char *yytext;
extern int macroStackIndex;
extern LexInput currentInput;


extern void fillLexInput(LexInput *lexInput, char *currentLexem, char *endOfBuffer,
                         char *beginningOfBuffer, char *macroName, InputType margExpFlag);
extern void ppMemInit(void);
extern void initAllInputs(void);
extern void initInput(FILE *file, EditorBuffer *buffer, char *prepend, char *fileName);
extern void addIncludeReference(int filenum, Position *pos);
extern void addThisFileDefineIncludeReference(int filenum);
extern void pushInclude(FILE *f, EditorBuffer *buff, char *name, char *prepend);
extern void popInclude(void);
extern int addFileTabItem(char *name);
extern void addMacroDefinedByOption(char *opt);
extern char *placeIdent(void);
extern int cachedInputPass(int cpoint, char **cfromto);
extern int cexp_yylex(void);
extern int yylex(void);

#endif
