/*

  External declarations from cgram-"module".

  Cannot be named 'cgram.h' since yacc creates cgram.[ch] when generating

*/

#ifndef CGRAM_X
#define CGRAM_X

#include "proto.h"

extern int c_yyparse();
extern void makeCCompletions(char *s, int len, Position *pos);

#endif

/* Local variables: */
/* Mode: c          */
/* End:             */
