#ifndef _LEXEMBUFFER_H_
#define _LEXEMBUFFER_H_

#include "lexem.h"
#include "characterreader.h"
#include "position.h"


typedef struct lexemBuffer {
    char *next;				/* next to read */
    char *end;				/* pointing *after* last valid char */
    char chars[LEX_BUFF_SIZE];
    Position positionRing[LEX_POSITIONS_RING_SIZE];
    unsigned fileOffsetRing[LEX_POSITIONS_RING_SIZE];
    int index;				/* pRing[posi%LEX_POSITIONS_RING_SIZE] */
    CharacterBuffer buffer;
} LexemBuffer;


/* Lexer macros for passing compressed tokens to the parser */
/* In the process of being turned into testable/debuggable functions */

/* Common for both normal and huge cases: */

extern void putLexChar(char ch, char **writePointer);
extern void putLexShort(int shortValue, char **writePointer);
extern void putLexToken(Lexem lexem, char **writePointer);
extern void putLexInt(int value, char **writePointer);

#define PutLexLine(lines, dd) {                                \
        if (lines!=0) {                                        \
            putLexToken(LINE_TOK, &dd);                        \
            putLexToken(lines, &dd);                           \
        }                                                      \
    }


extern unsigned char getLexChar(char **readPointer);
extern int getLexShort(char **readPointer);
extern Lexem getLexToken(char **readPointer);
extern int getLexInt(char **readPointer);

#define GetLexInt(xxx,dd) {                                 \
        xxx = *((unsigned char*)dd++);                      \
        xxx += 256 * *((unsigned char*)dd++);               \
        xxx += 256 * 256 * *((unsigned char*)dd++);         \
        xxx += 256 * 256 * 256 * *((unsigned char*)dd++);   \
    }

#define NextLexChar(dd) (*((unsigned char*)dd))

#define NextLexShort(dd) (                      \
        *((unsigned char*)dd)                   \
        + 256 * *(((unsigned char*)dd)+1)       \
    )

#define NextLexToken(dd) (NextLexShort(dd))

#define NextLexInt(dd) (                            \
        *((unsigned char*)dd)                       \
    + 256 * *(((unsigned char*)dd)+1)               \
    + 256 * 256 * *(((unsigned char*)dd)+2)         \
    + 256 * 256 * 256 * *(((unsigned char*)dd)+3)   \
    )


#ifndef XREF_HUGE

/* NORMAL compacted tokens, HUGE compression is below */
/* Can only store file, line, column < 4194304 */

#define PutLexCompacted(value,dd) {                       \
        assert(((unsigned) value)<4194304);               \
        if (((unsigned)value)>=128) {                     \
            if (((unsigned)value)>=16384) {               \
                *(dd)++ = ((unsigned)value)%128+128;  \
                *(dd)++ = ((unsigned)value)/128%128+128;  \
                *(dd)++ = ((unsigned)value)/16384;        \
            } else {                                      \
                *(dd)++ = ((unsigned)value)%128+128;      \
                *(dd)++ = ((unsigned)value)/128;          \
            }                                             \
        } else {                                          \
            *(dd)++ = ((unsigned char)value);             \
        }                                                 \
    }

#define PutLexPosition(cfile,cline,idcoll,dd) {             \
        assert(cfile>=0 && cfile<MAX_FILES);                \
        PutLexCompacted(cfile,dd);                          \
        PutLexCompacted(cline,dd);                          \
        PutLexCompacted(idcoll,dd);                         \
        log_trace("push idp %d %d %d",cfile,cline,idcoll);  \
}

#define GetLexCompacted(xxx,dd) {                                       \
        xxx = *((unsigned char*)dd++);                                  \
        if (((unsigned)xxx)>=128) {                                     \
            unsigned yyy = *((unsigned char*)dd++);                     \
            if (yyy >= 128) {                                           \
                xxx = ((unsigned)xxx)-128 + 128 * (yyy-128) + 16384 * *((unsigned char*)dd++); \
            } else {                                                    \
                xxx = ((unsigned)xxx)-128 + 128 * yyy;                  \
            }                                                           \
        }                                                               \
    }

#define GetLexPosition(pos,tmpcc) {             \
        GetLexCompacted(pos.file,tmpcc);        \
        GetLexCompacted(pos.line,tmpcc);        \
        GetLexCompacted(pos.col,tmpcc);         \
    }

#define NextLexPosition(pos,tmpcc) {            \
        char *tmptmpcc = tmpcc;                 \
        GetLexPosition(pos, tmptmpcc);          \
    }

#else

/* HUGE only !!!!!, normal compacted encoding is above */

#error HUGE mode is not supported any more, rewrite your application...

#define PutLexFilePos(xxx,dd) PutLexInt(xxx,dd)
#define PutLexNumPos(xxx,dd) PutLexInt(xxx,dd)
#define PutLexPosition(cfile,cline,idcoll,dd) {             \
        PutLexFilePos(cfile,dd);                            \
        PutLexNumPos(cline,dd);                             \
        PutLexNumPos(idcoll,dd);                            \
        log_trace("push idp %d %d %d",cfile,cline,idcoll);  \
    }

#define GetLexFilePos(xxx,dd) GetLexInt(xxx,dd)
#define GetLexNumPos(xxx,dd) GetLexInt(xxx,dd)
#define GetLexPosition(pos,tmpcc) {             \
        GetLexFilePos(pos.file,tmpcc);          \
        GetLexNumPos(pos.line,tmpcc);           \
        GetLexNumPos(pos.coll,tmpcc);           \
    }

#define NextLexFilePos(dd) NextLexInt(dd)
#define NextLexNumPos(dd) NextLexInt(dd)
#define NextLexPosition(pos,tmpcc) {                        \
        pos.file = NextLexFilePos(tmpcc);                   \
        pos.line = NextLexNumPos(tmpcc+sizeof(short));      \
        pos.coll = NextLexNumPos(tmpcc+2*sizeof(short));    \
    }

#endif

extern void initLexemBuffer(LexemBuffer *buffer, FILE *file);

#endif
