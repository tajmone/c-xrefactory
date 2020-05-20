#include "lex.h"
#include "lexmac.h"

#include "globals.h"
#include "commons.h"
#include "parsers.h"
#include "cxref.h"
#include "characterbuffer.h"
#include "yylex.h"
#include "filedescriptor.h"

#include "caching.h"            /* cacheInput() */
#include "jslsemact.h"          /* s_jsl */

#include "log.h"
#include "utils.h"              /* creatingOlcxRefs() */


void gotOnLineCxRefs(Position *ps ) {
    if (creatingOlcxRefs()) {
        s_cache.activeCache = 0;
        s_cxRefPos = *ps;
    }
}

/* ***************************************************************** */
/*                         Lexical Analysis                          */
/* ***************************************************************** */

#define PutLexLine(line,dd) {                               \
        if (line!=0) {                                      \
            PutLexToken(LINE_TOK,dd); PutLexToken(line,dd); \
        }                                                   \
    }

#define PutCurrentLexPosition(ccc,dd,cline,clo,clb,cfile) { \
        int ccol;                                           \
        ccol = COLUMN_POS(ccc,clb,clo);                     \
        PutLexPosition(cfile,cline,ccol,dd);                \
    }                                                       \

#define LexGetChar(ch, cb_next, cb_end, cb, cb_lineBegin, cb_columnOffset) { \
        if (cb_next >= cb_end) {                                        \
            cb->next = cb_next;                                         \
            cb_columnOffset = cb_next-cb_lineBegin;                     \
            if (cb->isAtEOF || fillBuffer(cb) == 0) {                   \
                ch = -1;                                                \
                cb->isAtEOF = true;                                     \
            } else {                                                    \
                cb_next = cb->next; cb_end = cb->end;                   \
                cb_lineBegin = cb_next;                                 \
                ch = * ((unsigned char *)cb_next);                      \
                cb_next = ((char *)cb_next) + 1;                        \
            }                                                           \
        } else {                                                        \
            ch = * ((unsigned char *)cb_next);                          \
            cb_next = ((char *)cb_next) + 1;                            \
        }                                                               \
    }

#define UngetChar(cch, ccc) {                             \
        log_trace("Ungetting %s(%c) at %s", #cch, cch, #ccc);   \
        *--ccc = cch;                                           \
    }

#define DeleteBlank(ch, next, end, begin, lineBegin, columnOffset) {    \
        while (ch==' '|| ch=='\t' || ch=='\004') {                      \
            LexGetChar(ch, next, end, begin, lineBegin, columnOffset);  \
        }                                                               \
    }

#define PassComment(ch,oldCh,ccc,cfin,cb,dd,cline,clb,clo) {            \
        /*  ******* a block comment ******* */                          \
        line = cline;                                                   \
        LexGetChar(ch,ccc,cfin,cb,clb,clo);                             \
        if (ch=='\n') {cline ++; clb = ccc; clo = 0;}                   \
        /* TODO test on cpp directive */                                \
        do {                                                            \
            oldCh = ch;                                                 \
            LexGetChar(ch,ccc,cfin,cb,clb,clo);                         \
            if (ch=='\n') {cline ++; clb = ccc; clo = 0;}               \
            /* TODO test on cpp directive */                            \
        } while ((oldCh != '*' || ch != '/') && ch != -1);              \
        if (ch == -1) warningMessage(ERR_ST,"comment through eof");     \
        PutLexLine(cline-line,dd);                                      \
        LexGetChar(ch,ccc,cfin,cb,clb,clo);                             \
    }

#define conType(val, cch, ccc, ffin, bbb, clb, clo, lex) {      \
        lex = CONSTANT;                                          \
        if (LANGUAGE(LANG_JAVA)) {                               \
            if (cch=='l' || cch=='L') {                          \
                lex = LONG_CONSTANT;                               \
                LexGetChar(cch, ccc, ffin, bbb, clb, clo);         \
            }                                                      \
        } else {                                                   \
            for(; cch=='l'||cch=='L'||cch=='u'||cch=='U'; ){       \
                if (cch=='l' || cch=='L') lex = LONG_CONSTANT;     \
                LexGetChar(cch, ccc, ffin, bbb, clb, clo);         \
            }                                                      \
        }                                                          \
    }

#define fpConstFin(cch, ccc, ffin, bbb, clb, clo, lex) {                \
        lex = DOUBLE_CONSTANT;                                          \
        if (cch == '.') {                                               \
            do { LexGetChar(cch, ccc, ffin, bbb, clb, clo);             \
            } while (isdigit(cch));                                     \
        }                                                               \
        if (cch == 'e' || cch == 'E') {                                 \
            LexGetChar(cch, ccc, ffin, bbb, clb, clo);                  \
            if (cch == '+' || cch=='-') LexGetChar(cch, ccc, ffin, bbb, clb, clo); \
            while (isdigit(cch)) LexGetChar(cch, ccc, ffin, bbb, clb, clo); \
        }                                                               \
        if (LANGUAGE(LANG_JAVA)) {                                      \
            if (cch == 'f' || cch == 'F' || cch == 'd' || cch == 'D') { \
                if (cch == 'f' || cch == 'F') lex = FLOAT_CONSTANT;     \
                LexGetChar(cch, ccc, ffin, bbb, clb, clo);              \
            }                                                           \
        } else {                                                        \
            if (cch == 'f' || cch == 'F' || cch == 'l' || cch == 'L') { \
                LexGetChar(cch, ccc, ffin, bbb, clb, clo);              \
            }                                                           \
        }                                                               \
    }

#define ProcessIdentifier(ch, ccc, cfin, cb, dd, cfile, cline, clb, clo, lab){ \
        int idcoll;                                                     \
        char *ddd;                                                      \
        /* ***************  identifier ****************************  */ \
        ddd = dd;                                                       \
        idcoll = COLUMN_POS(ccc,clb,clo);                               \
        PutLexToken(IDENTIFIER,dd);                                     \
        do {                                                            \
            PutLexChar(ch,dd);                                          \
        identCont##lab:                                                 \
            LexGetChar(ch,ccc,cfin,cb, clb, clo);                       \
        } while (isalpha(ch) || isdigit(ch) || ch=='_' || (ch=='$' && (LANGUAGE(LANG_YACC)||LANGUAGE(LANG_JAVA)))); \
        if (ch == '@' && *(dd-1)=='C') {                                \
            int i,len;                                                  \
            len = strlen(s_editCommunicationString);                    \
            for (i=2;i<len;i++) {                                       \
                LexGetChar(ch,ccc,cfin,cb, clb, clo);                   \
                if (ch != s_editCommunicationString[i]) break;          \
            }                                                           \
            if (i>=len) {                                               \
                /* it is the place marker */                            \
                dd--; /* delete the C */                                \
                LexGetChar(ch,ccc,cfin,cb, clb, clo);                   \
                if (ch == CC_COMPLETION) {                              \
                    PutLexToken(IDENT_TO_COMPLETE,ddd);                 \
                    LexGetChar(ch,ccc,cfin,cb, clb, clo);               \
                } else if (ch == CC_CXREF) {                            \
                    s_cache.activeCache = 0;                            \
                    fillPosition(&s_cxRefPos,cfile,cline,idcoll);       \
                    goto identCont##lab;                                \
                } else errorMessage(ERR_INTERNAL,"unknown communication char"); \
            } else {                                                    \
                /* not a place marker, undo reading */                  \
                for(i--;i>=1;i--) {                                     \
                    UngetChar(ch, ccc);                                 \
                    ch = s_editCommunicationString[i];                  \
                }                                                       \
            }                                                           \
        }                                                               \
        PutLexChar(0,dd);                                               \
        PutLexPosition(cfile,cline,idcoll,dd);                          \
    }

#define HandleCppToken(ch,ccc,cfin,cb,dd, cfile, cline, clb, clo) {     \
        char *ddd,tt[10];                                               \
        int i,lcoll,scol;                                               \
        lcoll = COLUMN_POS(ccc,clb,clo);                                \
        LexGetChar(ch,ccc,cfin,cb, clb, clo);                           \
        DeleteBlank(ch,ccc,cfin,cb, clb, clo);                          \
        for(i=0; i<9 && (isalpha(ch) || isdigit(ch) || ch=='_') ; i++) { \
            tt[i] = ch;                                                 \
            LexGetChar(ch,ccc,cfin,cb, clb, clo);                       \
        }                                                               \
        tt[i]=0;                                                        \
        if (strcmp(tt,"ifdef") == 0) {                                  \
            PutLexToken(CPP_IFDEF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"ifndef") == 0) {                          \
            PutLexToken(CPP_IFNDEF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"if") == 0) {                              \
            PutLexToken(CPP_IF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"elif") == 0) {                            \
            PutLexToken(CPP_ELIF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"undef") == 0) {                           \
            PutLexToken(CPP_UNDEF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"else") == 0) {                            \
            PutLexToken(CPP_ELSE,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"endif") == 0) {                           \
            PutLexToken(CPP_ENDIF,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else if (strcmp(tt,"include") == 0) {                         \
            char endCh;                                                 \
            PutLexToken(CPP_INCLUDE,dd);                                \
            PutLexPosition(cfile,cline,lcoll,dd);                       \
            DeleteBlank(ch,ccc,cfin,cb, clb, clo);                      \
            if (ch == '\"' || ch == '<') {                              \
                if (ch == '\"') endCh = '\"';                           \
                else endCh = '>';                                       \
                scol = COLUMN_POS(ccc,clb,clo);                         \
                PutLexToken(STRING_LITERAL,dd);                         \
                do { PutLexChar(ch,dd); LexGetChar(ch,ccc,cfin,cb, clb, clo); \
                } while (ch!=endCh && ch!='\n');                        \
                PutLexChar(0,dd);                                       \
                PutLexPosition(cfile,cline,scol,dd);                    \
                if (ch == endCh) LexGetChar(ch,ccc,cfin,cb, clb, clo);  \
            }                                                           \
        } else if (strcmp(tt,"define") == 0) {                          \
            ddd = dd;                                                   \
            PutLexToken(CPP_DEFINE0,dd);                                \
            PutLexPosition(cfile,cline,lcoll,dd);                       \
            DeleteBlank(ch,ccc,cfin,cb, clb, clo);                      \
            NOTE_NEW_LEXEM_POSITION(ccc,cfin,cb,lb,cfile,cline,clb,clo); \
            ProcessIdentifier(ch, ccc, cfin, cb, dd, cfile, cline, clb, clo,lab1); \
            if (ch == '(') {                                            \
                PutLexToken(CPP_DEFINE,ddd);                            \
            }                                                           \
        } else if (strcmp(tt,"pragma") == 0) {                          \
            PutLexToken(CPP_PRAGMA,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        } else {                                                        \
            PutLexToken(CPP_LINE,dd); PutLexPosition(cfile,cline,lcoll,dd); \
        }                                                               \
    }

#define CommentaryBegRef(ccc, cfile, cline, clb, clo) {                 \
        if (s_opt.taskRegime==RegimeHtmlGenerate && s_opt.htmlNoColors==0) { \
            int         lcoll;                                          \
            Position  pos;                                              \
            char        ttt[TMP_STRING_SIZE];                           \
            lcoll = COLUMN_POS(ccc,clb,clo) -1;                         \
            fillPosition(&pos, cfile, cline, lcoll);                    \
            sprintf(ttt,"%x/*",cfile);                                  \
            addTrivialCxReference(ttt,TypeComment,StorageDefault, &pos, UsageDefined); \
        }                                                               \
    }

#define CommentaryEndRef(ccc, cfile, cline, clb, clo, jdoc) {           \
        if (s_opt.taskRegime==RegimeHtmlGenerate) {                     \
            int         lcoll;                                          \
            Position  pos;                                              \
            char        ttt[TMP_STRING_SIZE];                           \
            lcoll = COLUMN_POS(ccc,clb,clo);                            \
            fillPosition(&pos, cfile, cline, lcoll);                    \
            sprintf(ttt,"%x/*",cfile);                                  \
            if (s_opt.htmlNoColors==0) {                                \
                addTrivialCxReference(ttt,TypeComment,StorageDefault, &pos, UsageUsed); \
            }                                                           \
            if (jdoc) {                                                 \
                pos.col -= 2;                                           \
                addTrivialCxReference(ttt,TypeComment,StorageDefault, &pos, UsageJavaDoc); \
            }                                                           \
        }                                                               \
    }

#define NOTE_NEW_LEXEM_POSITION(ccc, cfin, cb, lb, cfile, cline, clb, clo){ \
        int index = lb->index % LEX_POSITIONS_RING_SIZE;                \
        lb->fileOffsetRing[index] = ABS_FILE_POS(cb,cfin,ccc);          \
        lb->positionRing[index].file = cfile;                           \
        lb->positionRing[index].line = cline;                           \
        lb->positionRing[index].col = COLUMN_POS(ccc,clb,clo);          \
        lb->index ++;                                                   \
    }

#define PUT_EMPTY_COMPLETION_ID(ccc, dd, cline, clo, clb, cfile, llen) { \
        PutLexToken(IDENT_TO_COMPLETE,dd);                              \
        PutLexChar(0,dd);                                               \
        PutLexPosition(cfile,cline,                                     \
                       COLUMN_POS(ccc,clb,clo) - (llen), dd);           \
    }

bool getLexBuf(S_lexBuf *lb) {
    int ch;
    CharacterBuffer *cb;
    char *cb_next, *cb_end;
    int cb_lineNumber;
    int cb_columnOffset;
    char *cb_lineBegin;

    char *cc, *dd, *lmax, *lexStartDd;
    unsigned chval=0;
    int rlex;
    char oldCh;
    int line,size,cb_fileNumber,lexStartCol, lexStartFilePos, column;

    /* first test whether the input is cached */
    if (s_cache.activeCache && inStacki==0 && macroStackIndex==0) {
        cacheInput();
        s_cache.lexcc = lb->chars;
    }

    lmax = lb->chars + LEX_BUFF_SIZE - MAX_LEXEM_SIZE;
    for(dd=lb->chars,cc=lb->next; cc<lb->end; cc++,dd++)
        *dd = *cc;
    lb->next = lb->chars;

    cb = &lb->buffer;
    cb_lineNumber = cb->lineNumber;
    cb_lineBegin = cb->lineBegin;
    cb_columnOffset = cb->columnOffset;

    cb_next = cb->next;
    cb_end = cb->end;
    cb_fileNumber = cb->fileNumber;

    LexGetChar(ch, cb_next, cb_end, cb, cb_lineBegin, cb_columnOffset);

    do {
        DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
        if (dd >= lmax) {
            UngetChar(ch,cb_next);
            break;
        }
        NOTE_NEW_LEXEM_POSITION(cb_next,cb_end,cb,lb,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
        /*  yytext = ccc; */
        lexStartDd = dd;
        lexStartCol = COLUMN_POS(cb_next,cb_lineBegin,cb_columnOffset);
        if (ch == '_' || isalpha(ch) || (ch=='$' && (LANGUAGE(LANG_YACC)||LANGUAGE(LANG_JAVA)))) {
            ProcessIdentifier(ch, cb_next, cb_end, cb, dd, cb_fileNumber, cb_lineNumber, cb_lineBegin, cb_columnOffset, lab2);
            goto nextLexem;
        } else if (isdigit(ch)) {
            /* ***************   number *******************************  */
            long unsigned val=0;
            lexStartFilePos = ABS_FILE_POS(cb,cb_end,cb_next);
            if (ch=='0') {
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch=='x' || ch=='X') {
                    /* hexa */
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    while (isdigit(ch)||(ch>='a'&&ch<='f')||(ch>='A'&&ch<='F')) {
                        if (ch>='a') val = val*16+ch-'a'+10;
                        else if (ch>='A') val = val*16+ch-'A'+10;
                        else val = val*16+ch-'0';
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    }
                } else {
                    /* octal */
                    while (isdigit(ch) && ch<='8') {
                        val = val*8+ch-'0';
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    }
                }
            } else {
                /* decimal */
                while (isdigit(ch)) {
                    val = val*10+ch-'0';
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                }
            }
            if (ch == '.' || ch=='e' || ch=='E'
                || ((ch=='d' || ch=='D'|| ch=='f' || ch=='F') && LANGUAGE(LANG_JAVA))) {
                /* floating point */
                fpConstFin(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset,rlex);
                PutLexToken(rlex,dd);
                PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                PutLexInt(ABS_FILE_POS(cb,cb_end,cb_next)-lexStartFilePos, dd);
                goto nextLexem;
            }
            /* integer */
            conType(val,ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset, rlex);
            PutLexToken(rlex,dd);
            PutLexInt(val,dd);
            PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
            PutLexInt(ABS_FILE_POS(cb,cb_end,cb_next)-lexStartFilePos, dd);
            goto nextLexem;
        } else switch (ch) {
                /* ************   special character *********************  */
            case '.':
                lexStartFilePos = ABS_FILE_POS(cb,cb_end,cb_next);
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '.' && LANGUAGE(LANG_C|LANG_YACC)) {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if (ch == '.') {
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        PutLexToken(ELIPSIS,dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                        goto nextLexem;
                    } else {
                        UngetChar(ch,cb_next);
                        ch = '.';
                    }
                    PutLexToken('.',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    goto nextLexem;
                } else if (isdigit(ch)) {
                    /* floating point constant */
                    UngetChar(ch,cb_next);
                    ch = '.';
                    fpConstFin(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset,rlex);
                    PutLexToken(rlex,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    PutLexInt(ABS_FILE_POS(cb,cb_end,cb_next)-lexStartFilePos, dd);
                    goto nextLexem;
                } else {
                    PutLexToken('.',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    goto nextLexem;
                }

            case '-':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch=='=') {
                    PutLexToken(SUB_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                } else if (ch=='-') {PutLexToken(DEC_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;}
                else if (ch=='>' && LANGUAGE(LANG_C|LANG_YACC)) {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    PutLexToken(PTR_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;
                } else {PutLexToken('-',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '+':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') { PutLexToken(ADD_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;}
                else if (ch == '+') { PutLexToken(INC_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset); goto nextLexem; }
                else {PutLexToken('+',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '>':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '>') {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if(ch=='>' && LANGUAGE(LANG_JAVA)){
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        if(ch=='='){PutLexToken(URIGHT_ASSIGN,dd);
                            PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                            LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                            goto nextLexem;}
                        else {PutLexToken(URIGHT_OP,dd);
                            PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}
                    } else if(ch=='='){PutLexToken(RIGHT_ASSIGN,dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        goto nextLexem;}
                    else {PutLexToken(RIGHT_OP,dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}
                } else if (ch == '='){PutLexToken(GE_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;}
                else {PutLexToken('>',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '<':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '<') {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if(ch=='='){PutLexToken(LEFT_ASSIGN,dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        goto nextLexem;}
                    else {PutLexToken(LEFT_OP,dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}
                } else if (ch == '='){PutLexToken(LE_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;}
                else {PutLexToken('<',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '*':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(MUL_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else {PutLexToken('*',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '%':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(MOD_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                /*&
                  else if (LANGUAGE(LANG_YACC) && ch == '{') {
                      PutLexToken(YACC_PERC_LPAR,dd);
                      PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                      LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                      goto nextLexem;
                  }
                  else if (LANGUAGE(LANG_YACC) && ch == '}') {
                      PutLexToken(YACC_PERC_RPAR,dd);
                      PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                      LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                      goto nextLexem;
                  }
                  &*/
                else {PutLexToken('%',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '&':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(AND_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else if (ch == '&') {
                    PutLexToken(AND_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else if (ch == '*') {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if (ch == '/') {
                        /* a code comment, ignore */
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        CommentaryEndRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset,0);
                        goto nextLexem;
                    } else {
                        UngetChar(ch,cb_next);
                        ch = '*';
                        PutLexToken('&',dd);
                        PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;
                    }}
                else {PutLexToken('&',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '^':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(XOR_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else {PutLexToken('^',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '|':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(OR_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else if (ch == '|') {
                    PutLexToken(OR_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else {PutLexToken('|',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case '=':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(EQ_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else {PutLexToken('=',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    goto nextLexem;}

            case '!':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(NE_OP,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else {PutLexToken('!',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);goto nextLexem;}

            case ':':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                PutLexToken(':',dd);
                PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                goto nextLexem;

            case '\'':
                chval = 0;
                lexStartFilePos = ABS_FILE_POS(cb,cb_end,cb_next);
                do {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    while (ch=='\\') {
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        /* TODO escape sequences */
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    }
                    if (ch != '\'') chval = chval * 256 + ch;
                } while (ch != '\'' && ch != '\n');
                if (ch=='\'') {
                    PutLexToken(CHAR_LITERAL,dd);
                    PutLexInt(chval,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    PutLexInt(ABS_FILE_POS(cb,cb_end,cb_next)-lexStartFilePos, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                }
                goto nextLexem;

            case '\"':
                line = cb_lineNumber;
                size = 0;
                PutLexToken(STRING_LITERAL,dd);
                do {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    size ++;
                    if (ch!='\"' && size<MAX_LEXEM_SIZE-10) PutLexChar(ch,dd);
                    if (ch=='\\') {
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        size ++;
                        if (size < MAX_LEXEM_SIZE-10) PutLexChar(ch,dd);
                        /* TODO escape sequences */
                        if (ch == '\n') {cb_lineNumber ++;
                            cb_lineBegin = cb_next;
                            cb_columnOffset = 0;}
                        ch = 0;
                    }
                    if (ch == '\n') {
                        cb_lineNumber ++;
                        cb_lineBegin = cb_next;
                        cb_columnOffset = 0;
                        if (s_opt.strictAnsi && (s_opt.debug || s_opt.show_errors)) {
                            warningMessage(ERR_ST,"string constant through end of line");
                        }
                    }
                    // in Java CR LF can't be a part of string, even there
                    // are benchmarks making Xrefactory coredump if CR or LF
                    // is a part of strings
                } while (ch != '\"' && (ch != '\n' || !s_opt.strictAnsi) && ch != -1);
                if (ch == -1 && s_opt.taskRegime!=RegimeEditServer) {
                    warningMessage(ERR_ST,"string constant through EOF");
                }
                PutLexChar(0,dd);
                PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                PutLexLine(cb_lineNumber-line,dd);
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                goto nextLexem;

            case '/':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '=') {
                    PutLexToken(DIV_ASSIGN,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    goto nextLexem;
                }
                else if (ch=='*') {
                    int javadoc=0;
                    CommentaryBegRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if (ch == '&') {
                        /* ****** a program comment, ignore */
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        goto nextLexem;
                    } else {
                        if (ch=='*' && LANGUAGE(LANG_JAVA)) javadoc = 1;
                        UngetChar(ch,cb_next);
                        ch = '*';
                    }   /* !!! COPY BLOCK TO '/n' */
                    PassComment(ch,oldCh,cb_next,cb_end,cb,dd,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                    CommentaryEndRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset,javadoc);
                    goto nextLexem;
                } else if (ch=='/' && s_opt.cpp_comment) {
                    /*  ******* a // comment ******* */
                    CommentaryBegRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if (ch == '&') {
                        /* ****** a program comment, ignore */
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        CommentaryEndRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset,0);
                        goto nextLexem;
                    }
                    line = cb_lineNumber;
                    while (ch!='\n' && ch != -1) {
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        if (ch == '\\') {
                            LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                            if (ch=='\n') {cb_lineNumber ++;
                                cb_lineBegin = cb_next;
                                cb_columnOffset = 0;}
                            LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        }
                    }
                    CommentaryEndRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset,0);
                    PutLexLine(cb_lineNumber-line,dd);
                    goto nextLexem;
                } else {
                    PutLexToken('/',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                    goto nextLexem;
                }

            case '\\':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '\n') {
                    cb_lineNumber ++;
                    cb_lineBegin = cb_next;
                    cb_columnOffset = 0;
                    PutLexLine(1, dd);
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                } else {
                    PutLexToken('\\',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                }
                goto nextLexem;

            case '\n':
                column = COLUMN_POS(cb_next,cb_lineBegin,cb_columnOffset);
                if (column >= MAX_REFERENCABLE_COLUMN) {
                    fatalError(ERR_ST, "position over MAX_REFERENCABLE_COLUMN, read TROUBLES in README file", XREF_EXIT_ERR);
                }
                if (cb_lineNumber >= MAX_REFERENCABLE_LINE) {
                    fatalError(ERR_ST, "position over MAX_REFERENCABLE_LINE, read TROUBLES in README file", XREF_EXIT_ERR);
                }
                cb_lineNumber ++;
                cb_lineBegin = cb_next;
                cb_columnOffset = 0;
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '/') {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    if (ch == '*') {
                        CommentaryBegRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                        LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        if (ch == '&') {
                            /* ****** a code comment, ignore */
                            LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        } else {
                            int javadoc=0;
                            if (ch == '*' && LANGUAGE(LANG_JAVA)) javadoc = 1;
                            UngetChar(ch,cb_next);
                            ch = '*';
                            PassComment(ch,oldCh,cb_next,cb_end,cb,dd,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                            CommentaryEndRef(cb_next,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset,javadoc);
                            DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        }
                    } else {
                        UngetChar(ch,cb_next);
                        ch = '/';
                    }
                }
                PutLexToken('\n',dd);
                PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                if (ch == '#' && LANGUAGE(LANG_C|LANG_YACC)) {
                    NOTE_NEW_LEXEM_POSITION(cb_next,cb_end,cb,lb,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                    HandleCppToken(ch,cb_next,cb_end,cb,dd,cb_fileNumber,cb_lineNumber,cb_lineBegin,cb_columnOffset);
                }
                goto nextLexem;

            case '#':
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                if (ch == '#') {
                    LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    PutLexToken(CPP_COLLATION,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                } else {
                    PutLexToken('#',dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                }
                goto nextLexem;

            case -1:
                /* ** probably end of file ** */
                goto nextLexem;
            default:
                if (ch >= 32) {         /* small chars ignored */
                    PutLexToken(ch,dd);
                    PutLexPosition(cb_fileNumber, cb_lineNumber, lexStartCol, dd);
                }
                LexGetChar(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                goto nextLexem;
            }
        assert(0);
    nextLexem:
        if (s_opt.taskRegime == RegimeEditServer) {
            int pi,len,lastlex,parChar,apos;
            Position *ps;
            int pos1,currentLexemPosition;
            pi = (lb->index-1) % LEX_POSITIONS_RING_SIZE;
            ps = & lb->positionRing[pi];
            currentLexemPosition = lb->fileOffsetRing[pi];
            if (    cb_fileNumber == s_olOriginalFileNumber
                    && cb_fileNumber != s_noneFileIndex
                    && cb_fileNumber != -1
                    && s_jsl==NULL
                    ) {
                if (s_opt.server_operation == OLO_EXTRACT && lb->index>=2) {
                    DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    pos1 = ABS_FILE_POS(cb, cb_end, cb_next);
                    //&idcoll = COLUMN_POS(cb_next,cb_lineBegin,cb_columnOffset);
                    //&fprintf(dumpOut,":pos1==%d, olCursorPos==%d, olMarkPos==%d\n",pos1,s_opt.olCursorPos,s_opt.olMarkPos);
                    // all this is very, very HACK!!!
                    if (pos1 >= s_opt.olCursorPos && ! s_cps.marker1Flag) {
                        if (LANGUAGE(LANG_JAVA)) parChar = ';';
                        else {
                            if (s_cps.marker2Flag) parChar='}';
                            else parChar = '{';
                        }
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(';',dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(';',dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(OL_MARKER_TOKEN,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        s_cps.marker1Flag=1;
                    } else if (pos1 >= s_opt.olMarkPos && ! s_cps.marker2Flag){
                        if (LANGUAGE(LANG_JAVA)) parChar = ';';
                        else {
                            if (s_cps.marker1Flag) parChar='}';
                            else parChar = '{';
                        }
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(';',dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(';',dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(OL_MARKER_TOKEN,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        PutLexToken(parChar,dd);
                        PutLexPosition(ps->file,ps->line,ps->col,dd);
                        s_cps.marker2Flag=1;
                    }
                } else if (     s_opt.server_operation == OLO_COMPLETION
                                ||  s_opt.server_operation == OLO_SEARCH) {
                    DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                    apos = ABS_FILE_POS(cb, cb_end, cb_next);
                    if (currentLexemPosition < s_opt.olCursorPos
                        && (apos >= s_opt.olCursorPos
                            || (ch == -1 && apos+1 == s_opt.olCursorPos))) {
                        //&sprintf(tmpBuff,"currentLexemPosition, s_opt.olCursorPos, ABS_FILE_POS, ch == %d, %d, %d, %d\n",currentLexemPosition, s_opt.olCursorPos, apos, ch);ppcGenTmpBuff();
                        //&fprintf(dumpOut,":check\n");fflush(dumpOut);
                        lastlex = NextLexToken(lexStartDd);
                        if (lastlex == IDENTIFIER) {
                            len = s_opt.olCursorPos-currentLexemPosition;
                            //&fprintf(dumpOut,":check %s[%d] <-> %d\n", lexStartDd+TOKEN_SIZE, len,strlen(lexStartDd+TOKEN_SIZE));fflush(dumpOut);
                            if (len <= strlen(lexStartDd+TOKEN_SIZE)) {
                                if (s_opt.server_operation == OLO_SEARCH) {
                                    char *ddd;
                                    ddd = lexStartDd;
                                    PutLexToken(IDENT_TO_COMPLETE, ddd);
                                } else {
                                    dd = lexStartDd;
                                    PutLexToken(IDENT_TO_COMPLETE, dd);
                                    dd += len;
                                    PutLexChar(0,dd);
                                    PutLexPosition(ps->file,ps->line,ps->col,dd);
                                }
                                //&fprintf(dumpOut,":ress %s\n", lexStartDd+TOKEN_SIZE);fflush(dumpOut);
                            } else {
                                // completion after an identifier
                                PUT_EMPTY_COMPLETION_ID(cb_next,dd,cb_lineNumber,cb_columnOffset,cb_lineBegin,
                                                        cb_fileNumber,
                                                        apos-s_opt.olCursorPos);
                            }
                        } else if ((lastlex == LINE_TOK || lastlex == STRING_LITERAL)
                                   && (apos-s_opt.olCursorPos != 0)) {
                            // completion inside special lexems, do
                            // NO COMPLETION
                        } else {
                            // completion after another lexem
                            PUT_EMPTY_COMPLETION_ID(cb_next,dd,cb_lineNumber,cb_columnOffset,cb_lineBegin,
                                                    cb_fileNumber,
                                                    apos-s_opt.olCursorPos);
                        }
                    }
                    // TODO, make this in a more standard way, !!!
                } else {
                    //&fprintf(dumpOut,":testing %d <= %d <= %d\n", currentLexemPosition, s_opt.olCursorPos, ABS_FILE_POS(cb, cb_end, cb_next));
                    if (currentLexemPosition <= s_opt.olCursorPos
                        && ABS_FILE_POS(cb, cb_end, cb_next) >= s_opt.olCursorPos) {
                        gotOnLineCxRefs( ps);
                        lastlex = NextLexToken(lexStartDd);
                        if (lastlex == IDENTIFIER) {
                            strcpy(s_olstring, lexStartDd+TOKEN_SIZE);
                        }
                    }
                    if (LANGUAGE(LANG_JAVA)) {
                        // there is a problem with this, when browsing at CPP construction
                        // that is why I restrict it to Java language! It is usefull
                        // only for Java refactorings
                        DeleteBlank(ch,cb_next,cb_end,cb,cb_lineBegin,cb_columnOffset);
                        apos = ABS_FILE_POS(cb, cb_end, cb_next);
                        if (apos >= s_opt.olCursorPos && ! s_cps.marker1Flag) {
                            PutLexToken(OL_MARKER_TOKEN,dd);
                            PutLexPosition(ps->file,ps->line,ps->col,dd);
                            s_cps.marker1Flag=1;
                        }
                    }
                }
            }
        }
    } while (ch != -1);

    cb->next = cb_next;
    cb->end = cb_end;
    cb->lineNumber = cb_lineNumber;
    cb->lineBegin = cb_lineBegin;
    cb->columnOffset = cb_columnOffset;
    lb->end = dd;

    if (lb->end == lb->chars)
        return false;
    else
        return true;
}
