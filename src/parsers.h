#ifndef _PARSERS__H
#define _PARSERS__H

#ifdef __WIN32__

#ifdef CONST
#undef CONST
#endif

#ifdef VOID
#undef VOID
#endif

#ifdef THIS
#undef THIS
#endif

#ifdef DELETE
#undef DELETE
#endif

#endif

/* Include one of the generated parser definitions for common token codes */
#include "c_parser.tab.h"

extern YYSTYPE cyylval;
extern YYSTYPE javayylval;
extern YYSTYPE javaslyylval;
extern YYSTYPE cccyylval;
extern YYSTYPE yaccyylval;

extern YYSTYPE *uniyylval;

#endif
