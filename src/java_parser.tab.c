#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 5 "java_parser.y"

#define RECURSIVE

#define yylval javayylval

#define yyparse javayyparse
#define yylhs javayylhs
#define yylen javayylen
#define yydefred javayydefred
#define yydgoto javayydgoto
#define yysindex javayysindex
#define yyrindex javayyrindex
#define yytable javayytable
#define yycheck javayycheck
#define yyname javayyname
#define yyrule javayyrule
#define yydebug javayydebug
#define yynerrs javayynerrs
#define yyerrflag javayyerrflag
#define yychar javayychar
#define lastyystate javalastyystate
#define yyssp javayyssp
#define yyval javayyval
#define yyss javayyss
#define yyvs javayyvs
#define yygindex javayygindex
#define yyvsp javayyvsp


#include "java_parser.x"

#include "globals.h"
#include "jslsemact.h"
#include "jsemact.h"
#include "editor.h"
#include "cxref.h"
#include "yylex.h"
#include "stdinc.h"
#include "head.h"
#include "misc.h"
#include "commons.h"
#include "html.h"
#include "complete.h"
#include "proto.h"
#include "protocol.h"
#include "extract.h"
#include "semact.h"
#include "symbol.h"
#include "list.h"
#include "strFill.h"

#include "log.h"
#include "utils.h"

#define YYDEBUG 0
#define yyerror styyerror
#define yyErrorRecovery styyErrorRecovery

#define JslAddComposedType(ddd, ttt) jslAppendComposedType(&ddd->u.type, ttt)

#define JslImportSingleDeclaration(iname) {\
    S_symbol *sym;\
    jslClassifyAmbiguousTypeName(iname, &sym);\
    jslTypeSymbolDefinition(iname->idi.name, iname->next, TYPE_ADD_YES,ORDER_PREPEND, 1);\
}

/* Import on demand has to solve following situation (not handled by JSL) */
/* In case that there is a class and package differing only in letter case in name */
/* then even if classified to type it should be reclassified dep on the case */

#define JslImportOnDemandDeclaration(iname) {\
    S_symbol *sym;\
    int st;\
    st = jslClassifyAmbiguousTypeName(iname, &sym);\
    if (st == TypeStruct) {\
        javaLoadClassSymbolsFromFile(sym);\
        jslAddNestedClassesToJslTypeTab(sym, ORDER_APPEND);\
    } else {\
        javaMapDirectoryFiles2(iname,jslAddMapedImportTypeName,NULL,iname,NULL);\
    }\
}

#define CrTypeModifier(xxx,ttt) {\
        xxx = StackMemAlloc(S_typeModifiers);\
        FILLF_typeModifiers(xxx, ttt,f,( NULL,NULL) ,NULL,NULL);\
}

#define PrependModifier(xxx,ttt) {\
        S_typeModifiers *p;\
        p = StackMemAlloc(S_typeModifiers);\
        FILLF_typeModifiers(p, ttt,f,(NULL,NULL) ,NULL,xxx);\
        xxx = p;\
}

#define SetPrimitiveTypePos(res, typ) {\
        if (1 || SyntaxPassOnly()) {\
            XX_ALLOC(res, S_position);\
            *res = typ->p;\
        }\
}
#define SetAssignmentPos(res, tok) {\
        if (1 || SyntaxPassOnly()) {\
            XX_ALLOC(res.p, S_position);\
            *res.p = tok;\
        }\
}
#define PropagateBorns(res, beg, end) {res.b=beg.b; res.e=end.e;}
#define PropagateBornsIfRegularSyntaxPass(res, beg, end) {\
    if (regularPass()) {\
        if (SyntaxPassOnly()) {PropagateBorns(res, beg, end);}\
    }\
}
#define SetNullBorns(res) {res.b=s_noPos; res.e=s_noPos;}

#define NULL_POS NULL

#define AddComposedType(ddd, ttt) appendComposedType(&ddd->u.type, ttt)
#define AllocIdCopy(copy, ident) {copy = StackMemAlloc(S_idIdent); *(copy) = *(ident);}


static bool regularPass(void) { return s_jsl == NULL; }
static bool inSecondJslPass() {
    return !regularPass() && s_jsl->pass==2;
}

#define SyntaxPassOnly() (s_opt.server_operation==OLO_GET_PRIMARY_START || s_opt.server_operation==OLO_GET_PARAM_COORDINATES || s_opt.server_operation==OLO_SYNTAX_PASS_ONLY || s_javaPreScanOnly)

#define ComputingPossibleParameterCompletion() (regularPass() && (! SyntaxPassOnly()) && s_opt.taskRegime==RegimeEditServer && s_opt.server_operation==OLO_COMPLETION)



#line 281 "java_parser.y"
typedef union {
    int                                     integer;
    unsigned                                unsign;
    S_symbol                                *symbol;
    SymbolList                            *symbolList;
    S_typeModifiers                         *typeModif;
    S_typeModifiersList                     *typeModifList;
    S_freeTrail                             *trail;
    S_idIdent                               *idIdent;
    S_idIdentList                           *idlist;
    S_exprTokenType                         exprType;
    S_intPair                               intpair;
    S_whileExtractData                      *whiledata;
    S_position                              position;
    S_unsPositionPair                       unsPositionPair;
    S_symbolPositionPair                    symbolPositionPair;
    S_symbolPositionLstPair                 symbolPositionLstPair;
    S_positionList                           *positionLst;
    S_typeModifiersListPositionLstPair      typeModifiersListPositionLstPair;

    S_extRecFindStr                         *erfs;

    S_bb_int                                bbinteger;
    S_bb_unsigned                           bbunsign;
    S_bb_symbol                             bbsymbol;
    S_bb_symbolList                         bbsymbolList;
    S_bb_typeModifiers                      bbtypeModif;
    S_bb_typeModifiersList                  bbtypeModifList;
    S_bb_freeTrail                          bbtrail;
    S_bb_idIdent                            bbidIdent;
    S_bb_idIdentList                        bbidlist;
    S_bb_exprTokenType                      bbexprType;
    S_bb_intPair                            bbintpair;
    S_bb_whileExtractData                   bbwhiledata;
    S_bb_position                           bbposition;
    S_bb_unsPositionPair                    bbunsPositionPair;
    S_bb_symbolPositionPair                 bbsymbolPositionPair;
    S_bb_symbolPositionLstPair              bbsymbolPositionLstPair;
    S_bb_positionLst                        bbpositionLst;
    S_bb_typeModifiersListPositionLstPair   bbtypeModifiersListPositionLstPair;
    S_bb_nestedConstrTokenType              bbnestedConstrTokenType;
} YYSTYPE;
#line 184 "java_parser.tab.c"
#define TYPE_NAME 257
#define CLASS_NAME 258
#define TEMPLATE_NAME 259
#define CONVERSION_OP_ID_PREFIX 260
#define OPERATOR_IDENT 261
#define INC_OP 262
#define DEC_OP 263
#define LEFT_OP 264
#define RIGHT_OP 265
#define LE_OP 266
#define GE_OP 267
#define EQ_OP 268
#define NE_OP 269
#define AND_OP 270
#define OR_OP 271
#define MUL_ASSIGN 272
#define DIV_ASSIGN 273
#define MOD_ASSIGN 274
#define ADD_ASSIGN 275
#define SUB_ASSIGN 276
#define LEFT_ASSIGN 277
#define RIGHT_ASSIGN 278
#define AND_ASSIGN 279
#define XOR_ASSIGN 280
#define OR_ASSIGN 281
#define PTR_OP 282
#define ELIPSIS 283
#define URIGHT_OP 284
#define URIGHT_ASSIGN 285
#define YACC_PERC 286
#define YACC_DPERC 287
#define DPOINT 288
#define POINTM_OP 289
#define PTRM_OP 290
#define STATIC 291
#define BREAK 292
#define CASE 293
#define CHAR 294
#define CONST 295
#define CONTINUE 296
#define DEFAULT 297
#define DO 298
#define DOUBLE 299
#define ELSE 300
#define FLOAT 301
#define FOR 302
#define GOTO 303
#define IF 304
#define INT 305
#define LONG 306
#define RETURN 307
#define SHORT 308
#define SWITCH 309
#define VOID 310
#define VOLATILE 311
#define WHILE 312
#define TYPEDEF 313
#define EXTERN 314
#define AUTO 315
#define REGISTER 316
#define SIGNED 317
#define UNSIGNED 318
#define STRUCT 319
#define UNION 320
#define ENUM 321
#define SIZEOF 322
#define RESTRICT 323
#define _ATOMIC 324
#define _BOOL 325
#define _THREADLOCAL 326
#define _NORETURN 327
#define ANONYME_MOD 328
#define ABSTRACT 329
#define BOOLEAN 330
#define BYTE 331
#define CATCH 332
#define CLASS 333
#define EXTENDS 334
#define FINAL 335
#define FINALLY 336
#define IMPLEMENTS 337
#define IMPORT 338
#define INSTANCEOF 339
#define INTERFACE 340
#define NATIVE 341
#define NEW 342
#define PACKAGE 343
#define PRIVATE 344
#define PROTECTED 345
#define PUBLIC 346
#define SUPER 347
#define SYNCHRONIZED 348
#define THIS 349
#define THROW 350
#define THROWS 351
#define TRANSIENT 352
#define TRY 353
#define TRUE_LITERAL 354
#define FALSE_LITERAL 355
#define NULL_LITERAL 356
#define STRICTFP 357
#define ASSERT 358
#define FRIEND 359
#define OPERATOR 360
#define NAMESPACE 361
#define TEMPLATE 362
#define DELETE 363
#define MUTABLE 364
#define EXPLICIT 365
#define WCHAR_T 366
#define BOOL 367
#define USING 368
#define ASM_KEYWORD 369
#define EXPORT 370
#define VIRTUAL 371
#define INLINE 372
#define TYPENAME 373
#define DYNAMIC_CAST 374
#define STATIC_CAST 375
#define REINTERPRET_CAST 376
#define CONST_CAST 377
#define TYPEID 378
#define TOKEN 379
#define TYPE 380
#define LABEL 381
#define COMPL_FOR_SPECIAL1 382
#define COMPL_FOR_SPECIAL2 383
#define COMPL_THIS_PACKAGE_SPECIAL 384
#define COMPL_TYPE_NAME 385
#define COMPL_STRUCT_NAME 386
#define COMPL_STRUCT_REC_NAME 387
#define COMPL_UP_FUN_PROFILE 388
#define COMPL_ENUM_NAME 389
#define COMPL_LABEL_NAME 390
#define COMPL_OTHER_NAME 391
#define COMPL_CLASS_DEF_NAME 392
#define COMPL_FULL_INHERITED_HEADER 393
#define COMPL_TYPE_NAME0 394
#define COMPL_TYPE_NAME1 395
#define COMPL_PACKAGE_NAME0 396
#define COMPL_EXPRESSION_NAME0 397
#define COMPL_METHOD_NAME0 398
#define COMPL_PACKAGE_NAME1 399
#define COMPL_EXPRESSION_NAME1 400
#define COMPL_METHOD_NAME1 401
#define COMPL_CONSTRUCTOR_NAME0 402
#define COMPL_CONSTRUCTOR_NAME1 403
#define COMPL_CONSTRUCTOR_NAME2 404
#define COMPL_CONSTRUCTOR_NAME3 405
#define COMPL_STRUCT_REC_PRIM 406
#define COMPL_STRUCT_REC_SUPER 407
#define COMPL_QUALIF_SUPER 408
#define COMPL_SUPER_CONSTRUCTOR1 409
#define COMPL_SUPER_CONSTRUCTOR2 410
#define COMPL_THIS_CONSTRUCTOR 411
#define COMPL_IMPORT_SPECIAL 412
#define COMPL_VARIABLE_NAME_HINT 413
#define COMPL_CONSTRUCTOR_HINT 414
#define COMPL_METHOD_PARAM1 415
#define COMPL_METHOD_PARAM2 416
#define COMPL_METHOD_PARAM3 417
#define COMPL_YACC_LEXEM_NAME 418
#define CPP_TOKENS_START 419
#define CPP_INCLUDE 420
#define CPP_DEFINE 421
#define CPP_IFDEF 422
#define CPP_IFNDEF 423
#define CPP_IF 424
#define CPP_ELSE 425
#define CPP_ENDIF 426
#define CPP_ELIF 427
#define CPP_UNDEF 428
#define CPP_PRAGMA 429
#define CPP_LINE 430
#define CPP_DEFINE0 431
#define CPP_TOKENS_END 432
#define CPP_COLLATION 433
#define CPP_DEFINED_OP 434
#define EOI_TOKEN 435
#define CACHING1_TOKEN 436
#define OL_MARKER_TOKEN 437
#define OL_MARKER_TOKEN1 438
#define OL_MARKER_TOKEN2 439
#define TMP_TOKEN1 440
#define TMP_TOKEN2 441
#define CCC_OPER_PARENTHESIS 442
#define CCC_OPER_BRACKETS 443
#define MULTI_TOKENS_START 444
#define IDENTIFIER 445
#define CONSTANT 446
#define LONG_CONSTANT 447
#define FLOAT_CONSTANT 448
#define DOUBLE_CONSTANT 449
#define STRING_LITERAL 450
#define LINE_TOK 451
#define IDENT_TO_COMPLETE 452
#define CPP_MAC_ARG 453
#define IDENT_NO_CPP_EXPAND 454
#define CHAR_LITERAL 455
#define LAST_TOKEN 456
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,   94,   94,   94,   94,   94,   94,   94,   94,   94,
   37,   37,   22,   22,   23,   23,   24,   24,   24,   24,
   24,   25,   25,   39,   39,   40,   40,   41,   41,   42,
   43,   97,   97,   97,   97,    1,    2,    3,    4,    6,
    5,    7,    8,    9,   30,   30,   31,   32,  172,  172,
  173,  173,  174,  174,  175,  175,  176,  176,  102,  102,
  103,  103,  177,  178,  179,  171,  171,  101,  101,  100,
  100,  100,  100,   35,   35,   35,   36,   36,  104,  104,
  105,  105,   33,   33,   33,   33,   33,  106,  106,  106,
  106,   29,   29,   28,   28,   27,   27,   27,   27,   27,
   27,   27,   27,   27,   27,   27,  180,  182,  183,   10,
  184,   10,   10,  185,  186,  108,  187,  108,  108,  109,
  109,  110,  110,  111,  111,  181,  107,  107,  112,  112,
  113,  113,  113,  113,  113,  114,  114,  114,  114,   38,
   50,   53,   53,   45,   45,   45,   46,   46,   46,   95,
   95,  189,  119,   47,   47,   47,  191,   48,   48,   48,
   60,   60,   61,   61,   44,   44,   44,   56,   56,   57,
   57,   98,   98,  115,  115,  192,  116,  193,   52,  117,
  117,  117,  117,  194,  118,  195,  118,  196,  118,  118,
  118,  118,  118,  118,  118,  197,  198,   11,  199,   11,
   11,  122,  122,  123,  123,  121,  121,  120,  120,  124,
  124,  124,  124,  124,  124,   51,  200,   49,   96,   96,
   96,   96,  162,  162,   99,   99,  125,  125,  126,  126,
  126,  126,  127,   55,   55,   55,   54,  201,   54,  128,
  128,  128,  128,  128,  128,  135,  135,  135,  135,  135,
  129,  129,  129,  129,  129,  129,  129,  129,  129,  129,
  129,  129,  150,  150,  140,  130,  136,  141,   93,   93,
   93,   93,   93,   93,   93,   15,   16,   17,   18,  131,
   19,  132,  137,  202,  203,  142,  163,  163,  163,  163,
  151,  151,  204,  152,  153,  153,  153,  154,  154,   21,
  133,  138,  205,  206,  207,  143,  164,  164,  165,   20,
  166,  167,  134,  134,  139,  139,  155,  155,  155,  157,
  157,  156,  156,  144,  144,  145,  145,  146,  146,  148,
  147,  158,  158,  158,  208,  209,  149,  159,  159,  210,
  161,  161,  160,   62,   62,   63,   63,   63,   63,   63,
   63,   63,   63,   63,   63,   63,   63,   63,  170,  211,
  169,  212,  169,   34,   64,  213,  214,   64,   64,  215,
   64,   64,   64,   64,   58,   58,   59,   59,   59,   59,
   65,   65,   65,   65,   12,   12,  168,   13,   13,   14,
   14,   66,   66,   66,   66,   66,   66,  216,   67,  217,
   67,  218,   67,   68,   68,   68,   69,   69,   69,   69,
   69,   70,   71,   72,   72,   72,   72,   72,   73,   74,
   75,   75,   75,   75,   76,   76,   76,   77,   77,   77,
   77,   78,   78,   78,   79,   79,   79,   79,   80,   80,
   80,   80,   80,   80,   81,   81,   81,   82,   82,   83,
   83,   84,   84,   85,   85,   86,   86,   87,   87,   88,
   88,  219,   89,   90,   90,   90,   90,   26,   26,   26,
   26,   26,   26,   26,   26,   26,   26,   26,   26,   91,
   91,   92,  188,  190,
};
short yylen[] = {                                         2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    3,    3,    3,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    1,
    1,    1,    0,    0,    0,    6,    1,    0,    1,    1,
    1,    2,    2,    3,    3,    3,    5,    5,    0,    2,
    2,    3,    0,    3,    2,    3,    3,    1,    1,    1,
    1,    0,    1,    1,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    0,    0,    8,
    0,    6,    3,    0,    0,    8,    0,    6,    3,    0,
    2,    0,    2,    1,    3,    0,    3,    5,    1,    3,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    4,    1,    3,    1,    3,    1,    1,    3,    1,    1,
    1,    0,    5,    4,    4,    1,    0,    5,    3,    1,
    0,    1,    1,    3,    2,    3,    1,    0,    2,    1,
    3,    1,    1,    2,    1,    0,    7,    0,    5,    6,
    5,    5,    2,    0,    6,    0,    6,    0,    8,    2,
    2,    2,    1,    1,    3,    0,    0,    7,    0,    6,
    3,    0,    1,    2,    3,    3,    5,    1,    3,    1,
    1,    1,    1,    1,    1,    1,    0,    5,    4,    3,
    3,    2,    1,    3,    5,    2,    1,    2,    1,    1,
    1,    1,    2,    2,    3,    3,    1,    0,    4,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    5,    1,    3,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    0,    0,    0,    0,    6,
    8,    2,    2,    0,    0,    8,    6,    5,    5,    2,
    1,    2,    0,    3,    1,    2,    1,    3,    2,    6,
    2,    2,    0,    0,    0,   13,    0,    1,    1,   11,
    2,    2,    2,    2,    2,    2,    0,    1,    1,    0,
    1,    1,    3,    3,    2,    3,    2,    3,    2,    3,
    5,    1,    1,    2,    0,    0,    6,    1,    2,    0,
    9,    5,    3,    1,    1,    1,    1,    3,    3,    3,
    3,    3,    3,    1,    1,    1,    1,    2,    0,    0,
    9,    0,    9,    1,    6,    0,    0,    9,    1,    0,
    3,    4,    5,    5,    0,    1,    1,    3,    1,    3,
    5,    5,    5,    5,    1,    2,    3,    0,    1,    2,
    3,    3,    3,    5,    3,    3,    5,    0,    6,    0,
    8,    0,    8,    4,    4,    2,    1,    1,    1,    1,
    1,    2,    2,    1,    1,    2,    2,    1,    2,    2,
    1,    2,    2,    1,    4,    4,    4,    1,    3,    3,
    3,    1,    3,    3,    1,    3,    3,    3,    1,    3,
    3,    3,    3,    3,    1,    3,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    5,    1,
    1,    0,    4,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    0,    0,
};
short yydefred[] = {                                      0,
  126,    0,    1,    0,   67,  107,    0,    0,    0,   64,
    0,    0,   85,   53,   47,    0,   45,   46,    0,    0,
  135,    0,  106,  100,  101,  102,   98,   97,   96,  103,
  105,  104,  156,  134,    0,  127,  136,  137,   94,    0,
    0,  483,  138,  175,  126,  129,  131,  132,  133,  139,
   87,   84,    0,   86,   40,    0,   70,   71,    0,   65,
  174,  226,    0,   99,   95,   21,   23,   22,   19,   20,
   18,    0,   14,   17,    0,    0,   49,    0,  178,    0,
   13,   15,   16,    0,  140,    0,   12,   24,    0,    0,
    0,  152,    0,   54,   48,    0,    0,    0,    0,    0,
   72,   73,    0,  232,    0,    0,    0,    0,  277,  309,
    0,    0,    0,    0,  277,    0,   39,   38,    0,   37,
   42,   43,    2,    3,   10,    0,   60,   55,    0,    4,
    5,    6,    7,    9,    8,    0,  265,  347,    0,  359,
    0,  279,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  345,    0,    0,    0,    0,    0,    0,
  270,  271,  269,  462,    0,  346,    0,  251,    0,  230,
    0,  227,  229,  231,  240,  241,  242,  243,  244,  245,
  252,  253,  254,  255,  256,  257,  258,  259,  260,  261,
  262,    0,    0,    0,    0,  160,   36,  157,    0,  113,
    0,  201,    0,    0,    0,    0,    0,  146,  149,    0,
  142,    0,    0,    0,    0,  176,    0,    0,    0,  128,
  130,   76,   74,    0,   75,    0,   66,  126,    0,    0,
    0,    0,    0,    0,    0,    0,  354,  355,  356,  357,
    0,  409,  410,  419,  414,  415,  418,  424,    0,    0,
    0,  420,   62,   61,  325,    0,  327,    0,  276,    0,
  481,  329,    0,  428,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  460,  480,  461,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  335,    0,
  282,  301,    0,    0,    0,    0,  398,  147,    0,    0,
  233,    0,    0,    0,  412,  413,    0,  268,    0,    0,
  228,    0,  314,    0,    0,  313,  126,  358,  406,    0,
    0,  155,    0,    0,    0,    0,    0,   32,   33,   50,
    0,    0,  154,    0,  141,    0,   30,  170,    0,   27,
  483,   34,   35,  173,  484,  172,   52,    0,    0,    0,
   91,   90,   88,   89,    0,   81,    0,    0,    0,  416,
  417,  422,  423,  324,  326,  276,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  328,    0,
  352,    0,    0,    0,  263,    0,  353,  396,    0,   57,
    0,    0,    0,    0,    0,  330,    0,  349,  119,    0,
    0,  350,  348,   56,    0,    0,    0,    0,    0,  395,
    0,    0,    0,  469,  470,  471,  472,  473,  474,  475,
  477,  478,  479,  476,  468,    0,  351,  266,  225,    0,
    0,  322,    0,    0,  311,  371,    0,  159,    0,    0,
  126,    0,  197,    0,  126,  167,    0,    0,  163,    0,
    0,  148,    0,  150,  145,  151,  143,    0,    0,  153,
   77,   78,   82,    0,    0,    0,  303,  279,  429,  430,
  431,    0,    0,    0,    0,    0,    0,    0,    0,  444,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  276,    0,    0,    0,  402,    0,    0,    0,  385,    0,
    0,    0,    0,  372,  336,    0,    0,  404,    0,    0,
    0,    0,  239,  400,    0,    0,  405,  463,  277,    0,
    0,    0,  121,   29,    0,  109,  112,  204,  126,    0,
  200,    0,    0,    0,  179,    0,    0,  222,  223,    0,
  171,    0,  484,  426,  427,  425,  304,    0,    0,  284,
  279,  331,  264,    0,  390,    0,  381,    0,  386,    0,
  382,   58,  379,    0,    0,  377,  383,  384,    0,    0,
  126,  397,  394,  374,    0,  362,    0,    0,  373,  360,
    0,  323,  158,   31,  124,    0,  126,  198,  205,    0,
    0,  164,  221,    0,  220,  183,    0,  177,    0,    0,
    0,    0,  280,    0,    0,  247,  248,  249,  250,    0,
  459,  285,  300,    0,  387,  391,    0,    0,   44,  279,
    0,  337,    0,  333,  338,  115,  118,    0,  399,    0,
    0,  308,    0,    0,  110,  215,  214,  206,  210,  211,
    0,  483,  213,  216,  212,  126,  208,  219,  224,  193,
  194,    0,    0,    0,    0,    0,    0,  283,  302,    0,
  278,    0,    0,  315,    0,    0,  367,  380,  378,    0,
    0,  334,  339,  126,    0,    0,    0,  278,  125,  217,
    0,  190,  184,  191,  186,  192,    0,    0,    0,    0,
  305,  267,  281,  312,    0,  286,  403,  126,  343,    0,
  116,    0,  401,    0,  277,    0,  207,  209,    0,    0,
  195,  359,    0,  181,  182,    0,  290,    0,  368,    0,
  363,  361,    0,  484,    0,    0,  188,  180,    0,  297,
    0,    0,    0,  291,    0,  295,  342,  483,    0,    0,
  218,    0,    0,    0,    0,  482,    0,  299,  292,    0,
    0,  296,    0,    0,  340,  279,  185,  187,    0,    0,
  298,    0,  288,  289,    0,    0,  310,    0,  306,  287,
  484,  189,  341,
};
short yydgoto[] = {                                       2,
  298,  138,  139,  140,    9,   56,  141,  142,  631,   37,
   38,  507,  567,  568,  366,  259,  703,  289,  143,  315,
  144,  235,   81,   82,   83,  436,   39,   40,  146,  263,
   17,   18,   10,  403,   57,   58,  148,   86,   87,   88,
  533,  338,  595,  459,  211,  212,   42,  199,  653,   43,
  655,   89,  214,  149,  150,  216,  339,  574,  575,  460,
  461,  151,  152,  237,  154,  155,  239,  157,  241,  242,
  243,  264,  245,  246,  247,  248,  265,  266,  267,  268,
  269,  270,  271,  272,  273,  274,  275,  276,  277,  164,
  576,  757,  165,  166,  465,  466,  249,  345,  168,   59,
   60,  169,  256,  227,  228,  356,    6,  170,  450,  536,
  596,   45,   46,   47,   48,   49,  553,  665,   50,  656,
  541,  453,  454,  657,  171,  172,  173,  174,  175,  176,
  177,  178,  179,  180,  615,  616,  617,  618,  619,  181,
  182,  183,  184,  185,  186,  187,  188,  189,  190,  191,
  743,  744,  745,  746,  443,  444,  750,  632,  633,  634,
  635,  550,  706,  643,  192,  316,  674,  509,  193,  297,
    3,  250,   99,   19,  195,  405,    4,   20,  103,    5,
    7,  323,  597,  324,  516,  684,  517,   63,  219,  312,
  320,  341,  204,  719,  720,  754,  325,  539,  326,  716,
  302,  622,  675,  764,  557,  609,  726,  407,  579,  776,
  641,  638,  677,  708,  317,  417,  588,  564,  307,
};
short yysindex[] = {                                   -365,
    0,    0,    0, -254,    0,    0,  -50, -259, -215,    0,
 3493,   92,    0,    0,    0,  262,    0,    0,  112, -147,
    0,   95,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  104,    0,    0,    0,    0, 2703,
  152,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -329,    0,    0, -208,    0,    0, -147,    0,
    0,    0, 2968,    0,    0,    0,    0,    0,    0,    0,
    0, -297,    0,    0, -327, -310,    0,    0,    0,  184,
    0,    0,    0,   82,    0, -171,    0,    0, -120,  212,
  239,    0, 3565,    0,    0,    0,  335,  364,  347,  340,
    0,    0,    0,    0, 1818, 1818,  -58,    2,    0,    0,
  386, 1255,  394,  426,    0, 1688,    0,    0,  447,    0,
    0,    0,    0,    0,    0, 1743,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1743,    0,    0,  452,    0,
 1743,    0, 3045, 3045,  186,  174,  222, -192,  141,    0,
  481,  449,    0,    0,    0,    0,    0,   93,    0,    0,
    0,    0,    0,    0,  486,    0,  224,    0,  498,    0,
 2968,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -18,    0,  226,  499,    0,    0,    0,  -84,    0,
    0,    0,    0,  572,  524,  527, -285,    0,    0,    0,
    0,  150,  -84,  285, -256,    0,  539,  558,   18,    0,
    0,    0,    0,   -4,    0,  613,    0,    0, 1533, 1743,
 1818, 1818, 1818, 1818,  186,  222,    0,    0,    0,    0,
   93,    0,    0,    0,    0,    0,    0,    0,  224,  226,
  499,    0,    0,    0,    0,  600,    0,  605,    0, 1743,
    0,    0,  222,    0,  437,  510,  216,   57,  299,  627,
  580,  553,  408,   -5,    0,    0,    0,  620, 1743,  348,
  640, -192, 1743,  566,  645, -119, 2184,  632,    0,  447,
    0,    0,  359, -270, 1270,  200,    0,    0,  608, -192,
    0,  639, -282, 1743,    0,    0,  681,    0,  368, 3045,
    0,  577,    0, 3126, 3045,    0,    0,    0,    0,  663,
  612,    0,  381,  461,  384,  466, 2325,    0,    0,    0,
  630, 1381,    0, -197,    0,  684,    0,    0,  687,    0,
    0,    0,    0,    0,    0,    0,    0,  674,  677, 1533,
    0,    0,    0,    0,  185,    0,  103,  697,  415,    0,
    0,    0,    0,    0,    0,    0,  698, 1818, 1818, 1818,
 1818, 1818, 1818, 1818, 1818, 1818, 1818, 1688, 1818, 1818,
 1818, 1818, 1818, 1818, 1818, 1818, 1818, 1743,    0,  704,
    0, 1743,  608,  707,    0, 1743,    0,    0,    0,    0,
  665,  708,  717,  665,  718,    0,   95,    0,    0,    0,
  667,    0,    0,    0,  716, -337,  728,  608, 1381,    0,
    0, -302,  678,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1818,    0,    0,    0, 1688,
  731,    0,  719,  735,    0,    0, 2325,    0, -256,  443,
    0, -256,    0,  737,    0,    0, 1688, -192,    0,  743,
  745,    0, 1018,    0,    0,    0,    0, -256,  669,    0,
    0,    0,    0, 1818, 1853, 1818,    0,    0,    0,    0,
    0,  437,  437,  510,  510,  510,  216,  216,  184,    0,
  216,  216,   57,   57,  299,  627,  580,  553,  408,  732,
    0,  752,   95,  736,    0, 1510,  665,  164,    0, -238,
 1451,  665,  164,    0,    0,  381,  538,    0, -195,  758,
  754, 1451,    0,    0,  762,  754,    0,    0,    0, 3202,
  767,  684,    0,    0, -256,    0,    0,    0,    0, -256,
    0,  686, -192,  608,    0, 2325,  690,    0,    0,   22,
    0,  691,    0,    0,    0,    0,    0, 3045, 1818,    0,
    0,    0,    0,  771,    0,  724,    0,  730,    0,  729,
    0,    0,    0,  782,  781,    0,    0,    0,  207,  443,
    0,    0,    0,    0,  385,    0,  785,  791,    0,    0,
 1743,    0,    0,    0,    0,  788,    0,    0,    0,  927,
  608,    0,    0, 1089,    0,    0, 2557,    0, 3045, 3045,
 3045,  776,    0,    0,  537,    0,    0,    0,    0,  -13,
    0,    0,    0, 1451,    0,    0,    0, 1620,    0,    0,
  799,    0,  207,    0,    0,    0,    0,  800,    0, 1451,
  803,    0,  786, -256,    0,    0,    0,    0,    0,    0,
 2735,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  591,    5,    6, 2968, 2968,  536,    0,    0, 3045,
    0,    0, 3045,    0,  740,  810,    0,    0,    0,   95,
 2325,    0,    0,    0, 1451,  817, 1451,    0,    0,    0,
 3640,    0,    0,    0,    0,    0, -210, 2968,  739,  741,
    0,    0,    0,    0,  742,    0,    0,    0,    0,  819,
    0,  827,    0,  828,    0,  811,    0,    0,  832,  835,
    0,    0,  751,    0,    0,  837,    0,  -78,    0,  820,
    0,    0, 3202,    0, 1451, 1451,    0,    0, 1743,    0,
 1743,  822,  -78,    0,  269,    0,    0,    0,  735,  840,
    0,  841,  842,  844,  845,    0,  834,    0,    0,  269,
  760,    0,  765, 2968,    0,    0,    0,    0, 1451,  839,
    0,  768,    0,    0, 2968,   95,    0,  853,    0,    0,
    0,    0,    0,
};
short yyrindex[] = {                                   1894,
    0,    0,    0, 2870,    0,    0,    0, -212,    0,    0,
 3846,    0,    0,    0,    0,    0,    0,    0,    0, 3367,
    0, 4215,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 2801,    0,    0,    0,    0, 3977,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 3381,    0,
    0,    0,  564,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -16,    0, -133,
    0,    0,    0, 3501,    0,    0,    0,    0,  777, 3542,
 3549,    0, 3846,    0,    0,  417,    0,    0,    0,    0,
    0,    0, 3407,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 1168,    0,    0, 3591,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  804,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -62,    0,  838,    0,    0,  293,
 5011, 4696,  977,    0, 4070, 1295, 4319,    0,   28,   39,
    0,    0,    0,    0,    0,    0,  -28,    0,    0,    0,
  -75,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 4414,  -24, 4441,    0,    0,    0,   35,    0,
  -90,    0,  -74,    0,    0,    0,    0,    0,    0,  549,
    0,  289,   35,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  231,    0,
    0,    0,    0,    0,    0, 4971,    0,    0,    0,    0,
 5159,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 5121,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 4356,    0, 5132, 5376, 1184, 1364, 2062, 2020,
 1905,   68,  109,  666,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  469,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  843,    0,    0,    0,    0,    0,    0,
    0,    0,  -86,    0,  787,    0,  864,    0,    0,    0,
    0,    0,    0,    0,    0,   46,    0,    0,   36,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   48,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  477,    0,    0,    0,    0,    0, 3958,    0,
    0,   73,    0,    0,    0,    0,    0,    0,    0,  -80,
    0,    0,    0,    0,    0,    0,    0,  504,    0,    0,
 3985,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  847,    0,    0,  852,    0,    0,  864,    0,    0,  789,
    0,    0,    0,  790,    0,    0,    0,    0,    0,    0,
  873,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 4723,    0,    0,    0,    0,    0,
    0, 5249, 5286, 5403, 5414, 5502, 4033, 5539,    0,    0,
 5650, 5658, 3411, 3738, 2623, 2162, 2413, 1721,  533,    0,
    0,    0,    0,    0,    0,    0, 4850,    0,    0,    0,
  875, 4850,    0,    0,    0,  -86,    0,    0,    0,    0,
  877,  875,    0,    0,    0,  877,    0,    0,    0,    0,
    0,  -23,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   58,    0,    0,    0,    0,    0,    0,
    0, 2434,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 4877,    0,    0,
    0,    0,    0,    0,  882,    0,    0,    0,    0,  789,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  866,    0,    0,    0,    0,  805,    0,    0,    0, 3846,
  478,    0,    0,    0,    0,    0,  564,    0,    0,    0,
    0,    0,    0, 2018,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  875,    0,    0, 4606,    0,    0,    0,
    0,    0, 2094,    0,    0,    0,    0,    0,    0,  875,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -17,  877,  376,  -75,  -75,    0,    0,    0,    0,
    0, 2254,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  875,    0,  875,    0,    0,    0,
 3846,    0,    0,    0,    0,    0,    0,  -75,    0,    0,
    0,    0,    0,    0,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  807,
    0,    0,  885,    0,  875,  875,    0,    0,    0,    0,
    0,    0,  808,    0, 2634,    0,    0,    0,  891,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 2634,
    0,    0,    0,  564,    0,    0,    0,    0,  875,    0,
    0,    0,    0,    0,  -34,    0,    0,    0,    0,    0,
    0,    0,    0,
};
short yygindex[] = {                                      0,
  -30,  328, -279, -277,    0,    0,    0,    0,    0, -221,
 -216,  530,  425,  175, -311, -113,  251, -421, -490,  322,
 -465,  -35,    0,    0,    0,    0,  903,    0,   -1,   -9,
    0,    0,    0,    0,  887,  888,   63,    0,  570, -199,
 -388,  476,  305, -484,  616, -108, -561,  878,    0, -537,
    0,    0,    0,  638,    0,   97,    0,  172,    0,  516,
    0,  358,    0,  -29,    0,  622,   43,  783,  140,  154,
  163,  327,  176,  361,  492,    0,  276,  230,  208,  280,
  586,  590,  592,  589,  594,    0,  419,  540,  373,    0,
  641,    0, -294,    0, -384,  -64,  -32,    0,   -7,    0,
    0, -116,  871,    0,    0,  635, -281,    0,  471,  409,
    0,    0,  895,    0,    0,    0,    0,    0,    0,    0,
  472,    0,    0,  309, -554, -157,    0,   12,  -87,    0,
    0,    0,    0,    0, -269,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  267,  270, -308,    0,  279,    0,    0,    0,  387,
  389,    0,    0,    0,  -59,    0,    0,  -19,    0, -128,
    0,  -38,    0,  963,  816,    0,    0,    0,    0,    0,
  -27,    0,    0,    0,    0,    0,    0,  -37,    0,   54,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 5997
short yytable[] = {                                      16,
  255,  281,   91,   44,   92,   80,  321,  353,   90,   41,
   79,  287,  354,  311,   61,  337,  415,   93,  416,  442,
   28,  314,  359,   36,  194,  422,  314,  145,  347,   47,
  167,   84,  108,  153,  523,  446,  120,  348,  652,  299,
   13,  198,  114,   41,  201,  203,   98,   80,  196,  484,
  286,  697,  666,  147,  477,  210,  558,  388,  208,  117,
  257,  602,  654,  538,  200,  604,  520,  610,  272,   94,
    1,  272,   11,  347,   47,  229,  344,   91,  549,  273,
   80,  202,  273,   90,  208,   44,  272,  404,    8,   26,
  294,   41,  611,  168,  169,  236,  236,  273,  165,   28,
  196,  165,  525,   85,   26,  156,   84,   15,  454,  330,
  698,  454,  364,  153,  153,   95,  379,  197,  380,  610,
  610,  409,   11,  420,   12,  454,  454,  207,  353,  652,
  454,  117,  194,  354,  197,  145,  118,   77,  167,  623,
   35,  153,   15,  474,  611,  611,  605,  197,  293,  456,
   51,  599,  456,  654,  291,  292,  330,  168,  169,   95,
  454,  147,  197,   26,  572,  111,  456,  456,   26,  537,
   54,  456,  206,  393,  197,  117,  340,  740,  282,  610,
   14,  199,  610,   41,  300,  156,  156,   96,   15,  560,
   55,  418,  454,  205,  357,  420,  710,  359,  721,  301,
  350,  456,  158,   97,  611,  336,   95,  611,  680,  775,
  332,  346,  582,  156,  741,  209,  159,   35,  742,  659,
  209,  236,  236,  236,  236,  160,  196,  355,   62,   15,
  215,  293,   41,  456,  197,  592,   15,  313,  161,   47,
  331,  209,  672,  108,  347,  347,  108,  197,  340,  197,
  120,  401,  197,  114,  570,  399,  114,   92,  294,  196,
  694,  696,  294,  410,   11,  387,  215,  296,  337,  309,
  505,  318,  421,  197,  205,  194,  205,  402,  145,   11,
  153,  167,  158,  158,  153,  153,  463,  398,   91,  409,
  409,   80,  524,  483,   90,  322,  159,  159,   92,  637,
  410,  410,  217,  469,  147,  160,  160,   53,  748,  333,
  158,   11,  295,   28,  217,  645,  218,   84,  161,  161,
   52,  438,  376,  377,  159,  197,  445,  663,  334,  218,
  483,  253,  144,  160,  483,  594,  237,  454,  454,   91,
  668,  669,  489,  335,  777,   90,  161,  144,  355,  544,
   11,  237,  156,  238,  305,  306,  156,  156,  236,  236,
  236,  236,  236,  236,  236,  236,  236,  236,   84,  236,
  236,  236,  236,  236,  236,  236,  236,  236,  649,  456,
   92,   47,   11,  650,   25,  226,  254,   92,   27,  458,
  347,  253,  586,  222,   94,  378,   47,  590,  470,  515,
  702,   91,  711,  704,   80,  225,  521,   90,   91,  224,
  534,   80,  526,  534,   90,  591,   25,  722,   91,  422,
   27,   80,  223,  162,   90,  260,  729,  542,   47,  340,
   84,  244,  252,  279,  601,  163,  762,   84,  442,  532,
   95,  612,  532,  571,  594,   66,  254,   84,  578,  158,
   67,  762,   68,  158,  158,  476,   69,   70,  336,   71,
  309,   72,   53,  159,  236,  236,  236,  159,  159,  649,
  614,  280,  160,  370,  650,   51,  160,  160,  368,  373,
  374,   73,   74,  369,   75,  161,  283,  569,  583,  161,
  161,   76,  569,  612,  612,  562,  340,  286,  620,  375,
  153,  534,  282,  162,  162,  217,  294,   91,  311,  458,
   80,  542,  234,   90,  607,  163,  163,   75,  166,  543,
  235,  166,  614,  614,   76,  336,  303,  234,  153,  234,
  532,  162,  412,  693,  695,  235,   84,  235,  629,  304,
  311,  117,  630,  163,  308,   77,  118,  236,  413,  236,
  620,  620,  371,  612,  372,  310,  612,  360,  361,  362,
  363,  741,  236,   92,  236,  742,  381,  382,  194,  613,
   92,  145,  156,  457,  167,  508,  457,  153,  513,  153,
  153,  153,  614,  487,  488,  614,  491,  492,  157,  319,
  457,  457,  147,  737,  330,  457,   78,  147,  651,  414,
  156,  733,  484,  485,  486,  340,  608,  147,  458,  147,
  620,  327,   91,  620,  690,   80,  328,  311,   90,  329,
  667,  291,  292,  396,  395,  457,  194,  194,  691,  145,
  145,  342,  167,  167,  336,  153,  153,  407,  407,  147,
  153,   84,   91,  153,   95,   80,  482,  483,   90,  156,
  343,  156,  156,  156,  349,  147,  147,  457,  364,  194,
  493,  494,  145,  365,  383,  167,  421,  728,  153,  158,
  162,   84,  709,  384,  162,  162,  385,  386,  389,  392,
  391,  438,  163,  159,  445,  397,  163,  163,  147,  651,
  406,  408,  160,  587,  479,  480,  481,  158,  331,  419,
  437,  439,  447,  153,  448,  161,  458,  156,  156,  458,
  765,  159,  156,   85,  449,  156,  451,  452,  699,  700,
  160,  455,  462,  458,  458,  194,  238,  238,  145,  207,
  468,  167,  471,  161,  153,  472,  194,  475,  478,  145,
  156,  435,  167,  458,  501,  153,  158,  503,  158,  158,
  158,  723,  278,  510,  147,  506,  511,  514,  458,  518,
  159,  519,  159,  159,  159,  147,  284,  522,  781,  160,
  527,  160,  160,  160,  300,  156,  285,  529,  530,  535,
  540,  288,  161,  545,  161,  161,  161,  751,  546,  559,
  458,  552,  561,  581,  563,  676,  761,  584,  763,  585,
  554,  589,  556,  457,  158,  158,  156,  593,  600,  158,
  624,  686,  158,  772,  603,  606,  625,  156,  159,  159,
  570,  626,  627,  159,  628,  639,  159,  160,  160,   95,
  640,  644,  160,  670,  783,  160,  671,  158,  681,  685,
  161,  161,  687,   47,  688,  161,  692,  701,  161,   47,
  707,  159,  238,  238,  238,  238,  712,  713,  714,  730,
  160,   59,  705,  724,   47,  725,  727,  731,  732,  734,
  358,  735,  158,  161,  736,  738,  739,  359,  747,  758,
  766,  767,  768,  769,  773,  770,  159,  240,  240,  774,
  162,  771,  780,  782,   47,  160,   92,  779,  464,  168,
  367,  317,  163,  158,  161,  319,  752,  753,  161,  202,
  318,  122,  203,  162,  158,  375,  359,  159,  162,  390,
  251,  251,  376,  394,  307,  320,  160,  123,  159,  279,
  163,  321,  484,  512,  662,  411,  577,  160,  715,  161,
  778,  673,   65,  551,  423,  101,  102,  490,  689,  467,
  161,  441,  424,  425,  426,  427,  428,  429,  430,  431,
  432,  433,  531,  213,  664,  434,  555,  162,  495,  162,
  162,  162,  464,  496,  498,  528,  497,  621,  258,  163,
  499,  163,  163,  163,  473,  647,  580,  221,  636,  238,
  238,  238,  238,  238,  238,  238,  238,  238,  238,  718,
  238,  238,  238,  238,  238,  238,  238,  238,  238,  759,
  598,  749,  760,  240,  240,  240,  240,  275,  100,  682,
  275,  683,  354,    0,    0,  162,  162,    0,  500,    0,
  162,    0,  502,  162,    0,  275,  504,  163,  163,    0,
    0,    0,  163,    0,    0,  163,  251,  251,  251,  251,
  234,  648,    0,    0,    0,    0,    0,  230,  162,  464,
  231,  547,  232,    0,    0,   47,   47,  354,    0,    0,
  163,    0,    0,    0,    0,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   47,    0,    0,    0,   47,    0,
    0,    0,    0,  162,    0,  238,  238,  238,    0,  408,
  408,    0,    0,  464,    0,  163,    0,    0,    0,  464,
  464,  464,  464,  464,  464,  464,  464,  464,  464,    0,
    0,  234,  464,    0,  162,    0,    0,    0,  230,    0,
    0,  231,    0,  232,    0,  162,  163,    0,    0,    0,
  463,    0,  548,  233,    0,    0,  566,  163,    0,    0,
  240,  240,  240,  240,  240,  240,  240,  240,  240,  240,
    0,  240,  240,  240,  240,  240,  240,  240,  240,  240,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  238,    0,  646,  251,  251,  251,  251,  251,  251,  251,
  251,  251,  251,    0,  251,  251,  251,  251,  251,  251,
  251,  251,  251,    0,    0,    0,    0,    0,    0,    0,
    0,  463,    0,  658,  233,    0,   47,   64,    0,    0,
    0,  439,    0,    0,  439,    0,    0,  439,    0,    0,
    0,  642,  354,    0,    0,    0,    0,   23,  354,  354,
    0,  439,  439,  439,  464,  439,  439,    0,   47,    0,
   26,    0,    0,    0,    0,   24,  240,  240,  240,    0,
    0,   25,    0,    0,    0,    0,    0,   26,  679,    0,
   27,   28,   29,  261,   30,    0,  439,  439,   31,  105,
  106,    0,   26,   32,    0,    0,    0,  234,    0,  251,
  251,  251,    0,    0,  230,    0,    0,  231,    0,  232,
    0,    0,  234,    0,    0,    0,    0,  439,  439,  230,
    0,   66,  231,  262,  232,    0,   67,    0,   68,   33,
    0,    0,   69,   70,    0,   71,    0,  114,    0,    0,
    0,    0,    0,    0,    0,  274,    0,    0,  274,    0,
  356,  240,    0,    0,  261,    0,    0,   73,   74,    0,
  105,  106,    0,  274,    0,    0,    0,    0,    0,  117,
    0,    0,  329,    0,  118,    0,  120,    0,    0,    0,
    0,  123,  124,  125,  251,    0,    0,    0,    0,  755,
  233,  756,   66,    0,    0,  356,    0,   67,    0,   68,
    0,    0,    0,   69,   70,  233,   71,    0,  114,    0,
    0,  445,    0,    0,  445,    0,    0,  445,    0,    0,
    0,   77,    0,  234,  128,    0,    0,    0,   73,   74,
  230,  445,  445,  231,    0,  232,  445,    0,    0,    0,
  117,    0,    0,    0,    0,  118,    0,  120,    0,    0,
    0,    0,  123,  124,  125,    0,    0,    0,    0,  439,
  439,  439,  439,  439,  439,    0,  445,  445,  101,    0,
    0,    0,   15,  130,  131,  132,  133,  134,    0,    0,
    0,    0,  135,    0,    0,    0,    0,    0,  101,    0,
    0,    0,   77,  234,    0,  128,    0,  445,  445,    0,
  230,    0,    0,  231,    0,  232,  101,    0,    0,    0,
  101,    0,  101,  463,    0,    0,  233,    0,  101,    0,
  261,  101,  101,  101,    0,  101,  105,  106,    0,  101,
    0,    0,  439,    0,  101,  261,    0,    0,    0,    0,
    0,  105,  106,   15,  130,  131,  132,  133,  134,    0,
    0,    0,  234,  135,    0,    0,    0,    0,   66,  230,
  356,    0,  231,   67,  232,   68,  356,  356,    0,   69,
   70,    0,   71,   66,  114,    0,    0,    0,   67,    0,
   68,    0,    0,    0,   69,   70,  233,   71,    0,  114,
    0,    0,    0,    0,   73,   74,    0,    0,    0,    0,
    0,  352,    0,    0,    0,    0,  117,    0,    0,   73,
   74,  118,  565,  120,    0,    0,    0,    0,  123,  124,
  125,  117,    0,    0,    0,    0,  118,    0,  120,    0,
    0,    0,    0,  123,  124,  125,    0,    0,    0,    0,
    0,  445,  445,  445,  445,  233,  261,    0,    0,    0,
    0,    0,  105,  106,    0,    0,    0,    0,   77,    0,
    0,  128,  234,    0,    0,    0,    0,    0,    0,  230,
    0,    0,  231,   77,  232,    0,  128,    0,    0,    0,
    0,    0,    0,    0,   66,    0,    0,    0,    0,   67,
    0,   68,    0,    0,    0,   69,   70,    0,   71,    0,
  114,    0,    0,    0,    0,    0,    0,    0,    0,   15,
  130,  131,  132,  133,  134,    0,  261,    0,    0,  135,
   73,   74,  105,  106,   15,  130,  131,  132,  133,  134,
    0,    0,  117,    0,  135,    0,    0,  118,    0,  120,
    0,    0,    0,    0,  123,  124,  125,    0,    0,    0,
    0,    0,    0,    0,   66,  233,    0,    0,    0,   67,
    0,   68,    0,    0,    0,   69,   70,    0,   71,    0,
  114,  455,    0,    0,  455,  261,    0,    0,    0,    0,
    0,  105,  106,    0,   77,  234,    0,  128,  455,  455,
   73,   74,  230,  455,    0,  231,    0,  232,  351,    0,
    0,    0,  117,    0,    0,    0,    0,  118,    0,  120,
    0,    0,    0,   66,  123,  124,  125,    0,   67,    0,
   68,    0,    0,  455,   69,   70,    0,   71,    0,  114,
    0,    0,    0,   64,    0,   15,  130,  131,  132,  133,
  134,    0,    0,    0,    0,  135,    0,    0,  573,   73,
   74,    0,    0,   23,   77,  455,    0,  128,    0,    0,
  234,  117,    0,    0,    0,    0,  118,  230,  120,    0,
  231,   24,  232,  123,  124,  125,    0,   25,  233,    0,
    0,    0,    0,   26,    0,  261,   27,   28,   29,    0,
   30,  105,  106,    0,   31,  234,    0,    0,    0,   32,
    0,    0,  230,   63,    0,   15,  130,  131,  132,  133,
  134,    0,    0,   77,    0,  135,  128,    0,    0,    0,
    0,    0,    0,   66,    0,    0,    0,    0,   67,    0,
   68,    0,    0,    0,   69,   70,    0,   71,    0,  114,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  233,    0,  452,    0,    0,  452,   73,
   74,    0,   63,    0,   15,  130,  131,  132,  133,  134,
    0,  117,  452,  452,  135,    0,  118,  452,  120,    0,
    0,    0,    0,  123,  124,  125,    0,    0,  233,    0,
    0,   66,    0,    0,    0,    0,   67,    0,   68,    0,
  455,  455,   69,   70,    0,   71,    0,  452,  261,    0,
    0,    0,    0,    0,  105,  106,    0,  678,    0,    0,
    0,    0,    0,   77,    0,    0,  128,   73,   74,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  452,  452,
    0,    0,    0,    0,    0,    0,   66,    0,    0,    0,
    0,   67,    0,   68,    0,    0,    0,   69,   70,    0,
   71,    0,  114,    0,    0,    0,    0,  240,    0,    0,
  450,    0,    0,  450,   15,  130,  131,  132,  133,  134,
    0,    0,   73,   74,  135,    0,  240,  450,  450,  105,
  106,   77,  450,    0,  117,    0,    0,    0,    0,  118,
    0,  120,    0,    0,    0,    0,  123,  124,  125,  448,
    0,    0,  448,    0,    0,  448,    0,    0,    0,    0,
    0,   66,  450,  450,    0,    0,   67,    0,   68,  448,
  448,    0,   69,   70,  448,   71,    0,  114,    0,    0,
    0,    0,   15,  332,    0,    0,   77,    0,    0,  128,
  240,    0,  240,  450,  450,    0,   66,   73,   74,   63,
    0,   67,  332,   68,  448,  448,    0,   69,   70,  117,
   71,    0,  114,    0,  118,    0,  120,    0,    0,    0,
    0,  123,  124,  125,  452,  452,    0,    0,    0,    0,
    0,    0,   73,   74,   63,  448,  448,   15,  130,  131,
  132,  133,  134,    0,  117,    0,    0,  135,    0,  118,
    0,  120,  451,    0,   63,  451,  123,  124,  125,    0,
    0,   77,    0,    0,  128,    0,  332,    0,  332,  451,
  451,    0,   63,    0,  451,    0,   63,    0,   63,    0,
    0,   63,    0,   63,   63,    0,   63,   63,   63,   63,
    0,   63,    0,    0,    0,   63,   77,    0,    0,  128,
   63,    0,    0,    0,  451,  451,    0,    0,    0,    0,
    0,    0,   15,  130,  131,  132,  133,  134,    0,    0,
    0,    0,  135,  240,    0,    0,    0,    0,    0,  240,
  240,    0,    0,    0,    0,  451,  451,    0,    0,  450,
  450,    0,    0,  314,    0,    0,    0,   15,  130,  131,
  132,  133,  134,    0,    0,    0,    0,  135,  240,  240,
  240,  240,  314,  240,  240,  240,  240,  246,  240,  240,
    0,  240,  240,  240,  240,  240,  240,  240,  240,  240,
    0,  448,  448,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  240,  240,  240,  332,
  240,    0,  240,    0,    0,  332,  332,    0,  240,  240,
    0,  240,  240,  240,  240,  240,  240,  240,    0,  240,
  240,  240,  240,  240,  240,  240,  314,    0,  314,    0,
    0,    0,    0,    0,  332,  332,  332,  332,    0,  332,
  332,  332,  332,  332,  332,  332,    0,  332,  332,  332,
  332,  332,  332,  332,  332,  332,    0,  240,    0,    0,
    0,  240,    0,    0,  240,    0,    0,    0,    0,    0,
    0,    0,  332,  332,  332,    0,  332,    0,  332,    0,
    0,  451,  451,    0,  332,  332,    0,  332,  332,  332,
  332,  332,  332,  332,    0,  332,  332,  332,  332,  332,
  332,  332,    0,  453,    0,    0,  453,    0,    0,    0,
    0,    0,  240,  240,  240,  240,  240,  240,    0,    0,
  453,  453,  240,  483,    0,  453,    0,   66,    0,    0,
    0,    0,   67,  332,   68,    0,    0,  332,   69,   70,
  332,   71,  483,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  453,    0,    0,    0,  314,
    0,    0,    0,   73,   74,  314,  314,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  453,  453,  332,  332,
  332,  332,  332,  332,  314,  314,  314,  314,  332,  314,
  314,  314,  314,  316,  314,  314,  483,  314,  314,  314,
  314,  314,  314,  314,  314,  314,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   77,    0,    0,
  456,    0,  314,  314,  314,  400,  314,    0,  314,    0,
    0,    0,    0,    0,  314,  314,  136,  314,  314,  314,
  314,  314,  314,  314,    0,  314,  314,  314,  314,  314,
  314,  314,    0,    0,    0,  137,    0,    0,   66,    0,
    0,    0,    0,   67,    0,   68,    0,    0,   15,   69,
   70,    0,   71,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  314,    0,    0,    0,  314,    0,    0,
  314,    0,    0,    0,   73,   74,    0,    0,    0,  457,
  449,    0,    0,  449,    0,    0,  449,    0,    0,    0,
    0,    0,    0,  293,    0,    0,    0,    0,    0,   35,
  449,  449,  453,  453,    0,  449,    0,    0,    0,  483,
    0,    0,  293,    0,    0,  483,  483,    0,  314,  314,
  314,  314,  314,  314,    0,    0,    0,    0,  314,    0,
    0,    0,    0,    0,    0,  449,  449,    0,   77,    0,
    0,    0,    0,    0,  483,  483,    0,  483,    0,  483,
    0,  483,  483,    0,  483,  483,    0,  483,  483,  483,
  483,  483,  483,  483,  483,  483,  449,  449,    0,    0,
    0,    0,    0,    0,    0,    0,  293,    0,  484,    0,
    0,    0,  483,  483,  483,    0,  483,    0,  483,   15,
    0,    0,    0,    0,  483,  483,    0,  483,  483,  483,
  483,  483,  483,  483,    0,  483,  483,  483,  483,  483,
  483,  483,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  104,    0,    0,    0,    0,    0,  105,  106,
    0,    0,    0,  483,    0,    0,    0,  483,    0,    0,
  483,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  483,    0,  483,    0,  483,    0,    0,   64,  107,    0,
   66,    0,  108,    0,  109,   67,    0,   68,  110,  483,
  111,   69,   70,  112,   71,  113,  114,   23,  115,   83,
    0,    0,    0,    0,    0,    0,    0,    0,  483,  483,
  483,  483,  483,  483,    0,   24,   73,   74,  483,  293,
    0,  116,  449,  449,    0,  293,  293,   26,  117,    0,
   27,   28,   29,  118,  119,  120,  121,    0,   31,  122,
  123,  124,  125,   32,  126,    0,    0,    0,    0,    0,
    0,    0,    0,  483,  293,  293,    0,  293,   83,  293,
    0,  293,  293,    0,  293,  293,    0,  293,  293,  293,
  293,  293,  293,  293,  293,  293,  127,    0,    0,    0,
   77,    0,    0,  128,    0,    0,    0,    0,    0,    0,
    0,    0,  293,  293,  293,  660,  293,  661,  293,    0,
    0,    0,    0,    0,  293,  293,    0,  293,  293,  293,
  293,  293,  293,  293,    0,  293,  293,  293,  293,  293,
  293,  293,    0,   64,    0,    0,    0,    0,    0,    0,
    0,  129,  130,  131,  132,  133,  134,  136,    0,    0,
    0,  135,    0,   23,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  293,    0,    0,  137,  293,   66,    0,
  293,   24,    0,   67,    0,   68,    0,   25,    0,   69,
   70,    0,   71,   26,   72,    0,   27,   28,   29,    0,
   30,    0,    0,    0,   31,    0,  483,    0,    0,   32,
    0,    0,  483,  483,   73,   74,    0,   75,    0,    0,
    0,    0,    0,    0,   76,    0,    0,    0,  293,  293,
  293,  293,  293,  293,  136,    0,    0,    0,  293,    0,
   35,  483,  483,    0,  483,    0,  483,    0,  483,  483,
    0,  483,  483,  137,  483,  483,  483,  483,  483,  483,
  483,  483,  483,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   83,    0,    0,   77,  483,
  483,  483,    0,  483,    0,  483,    0,    0,    0,    0,
    0,  483,  483,    0,  483,  483,  483,  483,  483,  483,
  483,    0,  483,  483,  483,  483,  483,  483,  483,    0,
   83,    0,    0,    0,    0,  136,    0,   35,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   15,
   83,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  483,    0,    0,    0,  483,    0,    0,  483,   83,    0,
    0,    0,   83,    0,   83,    0,    0,   83,    0,   83,
   83,    0,    0,   83,   83,   83,    0,   83,    0,    0,
    0,   83,    0,  104,    0,    0,   83,    0,    0,  105,
  106,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  136,    0,    0,    0,  483,  483,  483,  483,  483,
  483,    0,    0,    0,    0,  483,    0,    0,   64,  107,
    0,   66,    0,  108,    0,  109,   67,    0,   68,  110,
    0,  111,   69,   70,  112,   71,  113,  114,   23,  115,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   24,   73,   74,    0,
    0,    0,  116,    0,    0,    0,  105,  106,   26,  117,
    0,   27,   28,   29,  118,  119,  120,  121,    0,   31,
  122,  123,  124,  125,   32,  126,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  107,    0,   66,    0,
  108,    0,  109,   67,    0,   68,  110,    0,  111,   69,
   70,  112,   71,  113,  114,    0,  115,  127,    0,    0,
    0,   77,    0,    0,  128,    0,   68,    0,    0,    0,
    0,    0,    0,    0,   73,   74,    0,    0,    0,    0,
   69,    0,    0,    0,    0,    0,  117,  105,  106,    0,
    0,  118,  290,  120,  121,    0,    0,  122,  123,  124,
  125,    0,  126,    0,    0,    0,   79,    0,    0,    0,
    0,    0,  129,  130,  131,  132,  133,  134,    0,   66,
    0,    0,  135,    0,   67,   68,   68,    0,    0,    0,
   69,   70,    0,   71,  127,  114,    0,    0,   77,   69,
    0,  128,    0,    0,    0,    0,    0,    0,  446,    0,
    0,  446,    0,    0,  446,   73,   74,    0,    0,    0,
  440,    0,    0,  105,  106,  126,    0,  117,  446,  446,
    0,    0,  118,  446,  120,    0,    0,    0,    0,  123,
  124,  125,    0,    0,    0,    0,    0,    0,    0,  129,
  130,  131,  132,  133,  134,   66,    0,    0,    0,  135,
   67,    0,   68,  446,  446,    0,   69,   70,    0,   71,
    0,  114,    0,    0,    0,    0,    0,    0,    0,   77,
    0,    0,  128,    0,    0,    0,    0,    0,    0,    0,
    0,   73,   74,    0,  446,  446,    0,    0,   26,    0,
    0,   26,    0,  117,   26,    0,    0,    0,  118,    0,
  120,   34,    0,    0,    0,  123,  124,  125,   26,   26,
   26,    0,   26,   26,    0,    0,    0,    0,    0,    0,
   15,  130,  131,  132,  133,  134,    0,    0,    0,   25,
  135,    0,   25,    0,    0,   25,   27,    0,    0,   27,
    0,    0,   27,   26,   26,   77,    0,    0,  128,   25,
   25,   25,    0,   25,   25,    0,   27,   27,   27,    0,
   27,   27,    0,    0,    0,   35,    0,   36,    0,    0,
    0,    0,   68,   34,   26,   26,    0,    0,    0,    0,
    0,    0,    0,    0,   25,   25,   69,    0,    0,    0,
    0,   27,   27,    0,    0,    0,   15,  130,  131,  132,
  133,  134,    0,    0,    0,    0,  135,   68,    0,    0,
    0,    0,  126,    0,    0,   25,   25,    0,    0,    0,
    0,   69,   27,   27,    0,    0,    0,   68,  446,  446,
  446,  446,    0,    0,    0,    0,    0,   35,    0,  220,
    0,   69,    0,    0,    0,   68,    0,  126,  647,   68,
    0,   68,    0,    0,    0,    0,   68,   68,    0,   69,
   68,   68,   68,   69,   68,   69,    0,  126,   68,    0,
   69,   69,    0,   68,   69,   69,   69,    0,   69,    0,
    0,    0,   69,    0,    0,  126,    0,   69,    0,  126,
    0,  126,    0,    0,    0,    0,  126,  126,   21,    0,
  126,  126,  126,    0,  126,    0,   26,    0,  126,    0,
    0,    0,    0,  126,  717,    0,   26,   26,   26,   26,
   26,   26,    0,    0,    0,  447,    0,    0,  447,    0,
    0,  447,    0,   22,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  447,  447,   25,    0,    0,
  447,    0,    0,   23,   27,    0,    0,   25,   25,   25,
   25,   25,   25,    0,   27,   27,   27,   27,   27,   27,
   21,   24,    0,    0,    0,    0,    0,   25,    0,    0,
  447,  447,    0,   26,    0,    0,   27,   28,   29,   26,
   30,    0,    0,    0,   31,    0,    0,    0,    0,   32,
    0,    0,    0,    0,    0,   22,    0,    0,    0,    0,
    0,  447,  447,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   23,    0,    0,    0,    0,
   25,  103,    0,    0,    0,   33,    0,   27,    0,    0,
    0,    0,    0,   24,    0,  646,    0,    0,   26,   25,
    0,  103,    0,    0,    0,   26,    0,    0,   27,   28,
   29,    0,   30,   26,    0,    0,   31,    0,    0,  103,
    0,   32,    0,  103,    0,  103,    0,    0,    0,    0,
   64,  103,    0,    0,  103,  103,  103,    0,  103,   25,
    0,    0,  103,    0,    0,   26,   27,  103,    0,    0,
   23,    0,    0,    0,   25,    0,    0,   33,    0,    0,
    0,   27,    0,    0,    0,    0,    0,    0,   24,    0,
    0,    0,    0,    0,   25,    0,    0,    0,    0,    0,
   26,    0,    0,   27,   28,   29,   25,   30,    0,    0,
    0,   31,    0,   27,  393,  393,   32,  359,  393,  393,
  393,  393,  393,  393,  393,  447,  447,  447,  447,    0,
    0,    0,    0,    0,    0,  393,  393,  393,  393,  393,
  393,  392,  392,    0,  359,  392,  392,  392,  392,  392,
  392,  392,   33,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  392,  392,  392,  392,  392,  392,  393,    0,
  393,  393,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  442,    0,    0,  442,    0,  392,  442,  392,  392,    0,
    0,  393,  393,    0,    0,    0,    0,    0,    0,    0,
  442,  442,  442,    0,  442,  442,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  355,  355,  392,  392,
  355,  355,  355,  355,  355,  355,  355,    0,    0,    0,
    0,    0,    0,    0,    0,  442,  442,  355,  355,  355,
  465,  355,  355,    0,    0,    0,    0,    0,    0,   92,
    0,    0,    0,    0,   92,    0,   92,    0,    0,    0,
   92,   92,    0,   92,    0,   92,  442,  442,    0,    0,
  355,    0,  355,  355,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   92,   92,    0,   92,    0,
    0,    0,    0,    0,    0,   92,    0,    0,    0,    0,
    0,    0,    0,  355,  355,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  393,    0,    0,    0,    0,    0,  393,
  393,  393,  393,  393,  393,  393,  393,  393,  393,  393,
  393,  393,  393,  393,  393,  393,  393,  393,  393,   92,
  392,  393,  393,    0,    0,    0,  392,  392,  392,  392,
  392,  392,  392,  392,  392,  392,  392,  392,  392,  392,
  392,  392,  392,  392,  392,  392,    0,    0,  392,  392,
   93,    0,    0,    0,    0,   93,    0,   93,    0,    0,
    0,   93,   93,    0,   93,    0,   93,    0,    0,    0,
   92,    0,    0,    0,    0,    0,  393,    0,  442,  442,
  442,  442,  442,  442,    0,    0,   93,   93,    0,   93,
    0,    0,    0,    0,    0,    0,   93,    0,    0,    0,
    0,    0,    0,  392,    0,  355,    0,    0,    0,    0,
    0,  355,  355,  355,  355,  355,  355,  355,  355,  355,
  355,  465,  465,  465,  465,  465,  465,  465,  465,  465,
  465,    0,    0,  355,  465,  357,  357,    0,    0,  357,
  357,  357,  357,  357,  357,  357,    0,    0,    0,    0,
   93,  442,    0,    0,    0,    0,  357,  357,  357,  466,
  357,  357,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  408,  408,    0,  359,  408,  408,  408,  408,
  408,    0,  408,    0,    0,    0,    0,    0,  355,  357,
    0,  357,  357,  408,  408,  408,  464,  408,  408,    0,
    0,   93,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  357,  357,    0,    0,    0,    0,  408,  408,
  369,  369,    0,    0,  369,  369,  369,  369,  369,  369,
  369,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  369,  369,  369,    0,  369,  369,  411,  411,  408,
  408,  411,  411,  411,  411,  411,    0,  411,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  411,  411,
  411,  467,  411,  411,  369,   99,  369,  369,   99,    0,
    0,    0,    0,   99,    0,   99,    0,    0,    0,   99,
   99,    0,   99,    0,   99,   99,    0,    0,    0,    0,
    0,    0,    0,  411,  411,    0,  370,  369,  369,    0,
    0,    0,    0,   99,   99,   99,    0,   99,    0,   99,
    0,    0,    0,    0,   99,   99,    0,    0,   99,   99,
   99,    0,   99,    0,  411,  411,   99,    0,    0,    0,
    0,   99,    0,    0,  357,    0,    0,    0,    0,    0,
  357,  357,  357,  357,  357,  357,  357,  357,  357,  357,
  466,  466,  466,  466,  466,  466,  466,  466,  466,  466,
    0,    0,  357,  466,    0,    0,    0,    0,   99,    0,
    0,    0,    0,    0,    0,    0,    0,  408,  408,  408,
  408,  408,  408,  408,  408,  408,  408,  464,  464,  464,
  464,  464,  464,  464,  464,  464,  464,    0,    0,  408,
  464,    0,  365,  365,    0,    0,  365,  365,  365,  365,
  365,  365,  365,    0,    0,    0,    0,  357,    0,   99,
    0,    0,    0,  365,  365,  365,    0,  365,  365,  369,
    0,    0,    0,    0,    0,  369,  369,  369,  369,  369,
  369,  369,  369,  369,  369,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  408,    0,  365,  369,  365,  365,
    0,    0,  411,  411,  411,  411,  411,  411,  411,  411,
  411,  411,  467,  467,  467,  467,  467,  467,  467,  467,
  467,  467,    0,    0,  411,  467,    0,    0,  366,  365,
  365,    0,  344,  344,    0,    0,  344,  344,  344,  344,
  344,  344,  344,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  369,  344,  344,  344,    0,  344,  344,  353,
  353,    0,    0,  353,  353,  353,  353,  353,  353,  353,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  411,
  353,  353,  353,    0,  353,  353,    0,    0,  344,  344,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  353,    0,  353,  353,    0,    0,  344,
  344,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  353,  353,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  365,    0,    0,    0,    0,    0,  365,  365,  365,
  365,  365,  365,  365,  365,  365,  365,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  388,  388,    0,  365,
  388,  388,  388,  388,  388,  388,  388,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  388,  388,  388,
    0,  388,  388,  389,  389,    0,    0,  389,  389,  389,
  389,  389,  389,  389,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  389,  389,  389,    0,  389,  389,
    0,    0,  388,  388,  365,    0,    0,    0,    0,    0,
    0,  344,    0,    0,    0,    0,    0,  344,  344,  344,
  344,  344,  344,  344,  344,  344,  344,    0,    0,  389,
  389,    0,    0,  388,  388,    0,    0,    0,    0,  344,
    0,    0,    0,    0,  353,  353,  353,  353,  353,  353,
  353,  353,  353,  353,    0,    0,    0,    0,    0,    0,
  389,  389,    0,    0,    0,    0,  353,  408,  408,    0,
  359,  408,  408,  408,  408,  408,    0,  408,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  408,  408,
  408,    0,  408,  408,  344,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  407,  407,    0,
    0,  407,  407,  407,  407,  407,    0,  407,    0,    0,
    0,  353,    0,  408,  408,    0,    0,    0,  407,  407,
  407,    0,  407,  407,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  408,  408,    0,    0,    0,    0,
    0,    0,    0,  407,  407,  388,    0,    0,    0,    0,
    0,  388,  388,  388,  388,  388,  388,  388,  388,  388,
  388,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  389,  388,  407,  407,    0,    0,  389,  389,
  389,  389,  389,  389,  389,  389,  389,  389,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  411,  411,    0,
  389,  411,  411,  411,  411,  411,    0,  411,    0,  432,
    0,    0,  432,    0,  432,  432,  432,    0,  411,  411,
  411,    0,  411,  411,    0,    0,    0,    0,  388,  432,
  432,  432,    0,  432,  432,  421,  421,    0,    0,  421,
  421,  421,  421,  421,    0,  421,    0,    0,    0,    0,
    0,    0,    0,  411,  411,  389,  421,  421,  421,    0,
  421,  421,    0,    0,  432,  432,    0,    0,    0,    0,
    0,    0,  408,  408,  408,  408,  408,  408,  408,  408,
  408,  408,    0,    0,  411,  411,    0,    0,    0,    0,
    0,  421,  421,    0,  408,  432,  432,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  407,  407,  407,  407,  407,  407,  407,  407,
  407,  407,  421,  421,    0,    0,  433,    0,    0,  433,
    0,  433,  433,  433,  407,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  433,  433,  433,  408,
  433,  433,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  434,    0,    0,  434,    0,  434,  434,
  434,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  433,  433,  434,  434,  434,    0,  434,  434,  407,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  433,  433,    0,    0,    0,    0,  434,  434,
    0,    0,  411,  411,  411,  411,  411,  411,  411,  411,
  411,  411,    0,    0,    0,  432,  432,  432,  432,  432,
  432,  432,  432,    0,  411,    0,    0,    0,    0,  434,
  434,    0,    0,  435,    0,  432,  435,    0,    0,  435,
    0,    0,  421,  421,  421,  421,  421,  421,  421,  421,
    0,    0,    0,  435,  435,  435,    0,  435,  435,    0,
  436,    0,  421,  436,    0,    0,  436,    0,    0,    0,
    0,  437,    0,    0,  437,    0,    0,  437,    0,  411,
  436,  436,  436,    0,  436,  436,    0,    0,  435,  435,
  432,  437,  437,  437,    0,  437,  437,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  436,  436,  421,    0,  435,
  435,    0,    0,    0,    0,    0,  437,  437,    0,    0,
    0,    0,  433,  433,  433,  433,  433,  433,  433,  433,
    0,    0,    0,    0,    0,    0,  436,  436,    0,    0,
    0,    0,  433,    0,    0,    0,    0,  437,  437,  438,
    0,    0,  438,    0,    0,  438,    0,    0,    0,  434,
  434,  434,  434,  434,  434,  434,  434,    0,    0,  438,
  438,  438,    0,  438,  438,    0,    0,    0,    0,  434,
    0,    0,    0,    0,    0,    0,  443,    0,    0,  443,
    0,    0,  443,    0,    0,    0,    0,  433,    0,    0,
    0,    0,    0,    0,  438,  438,  443,  443,  443,    0,
  443,  443,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  434,  438,  438,    0,    0,    0,
    0,  443,  443,    0,    0,    0,    0,    0,    0,  435,
  435,  435,  435,  435,  435,  435,  435,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  435,
    0,    0,  443,  443,    0,    0,  436,  436,  436,  436,
  436,  436,  436,  436,    0,    0,    0,  437,  437,  437,
  437,  437,  437,  437,  437,    0,  436,  440,    0,    0,
  440,    0,    0,  440,    0,  441,    0,  437,  441,    0,
    0,  441,    0,    0,    0,    0,    0,  440,  440,  440,
    0,  440,  440,    0,  435,  441,  441,  441,    0,  441,
  441,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  436,  440,  440,    0,    0,    0,    0,    0,    0,
  441,  441,  437,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  438,  438,  438,  438,  438,
  438,  438,  438,  440,  440,    0,    0,    0,    0,    0,
    0,  441,  441,    0,    0,  438,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  443,  443,  443,  443,  443,  443,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  438,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  443,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  440,  440,  440,  440,  440,
  440,    0,    0,  441,  441,  441,  441,  441,  441,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  440,    0,
    0,    0,    0,    0,    0,    0,  441,
};
short yycheck[] = {                                       9,
   59,  115,   41,   11,   42,   41,   91,  229,   41,   11,
   41,  140,  229,  171,   22,  215,  296,   45,  296,  314,
   44,   40,   40,   40,   63,  303,   40,   63,   46,   46,
   63,   41,  123,   63,  419,  317,  123,   42,  600,  148,
  256,   72,  123,  256,   75,   76,   56,    0,  123,  125,
   46,   46,  607,   63,  366,   86,  478,   63,  256,  342,
   59,  546,  600,  452,  392,   44,  404,  558,   41,  399,
  436,   44,  123,   91,   91,  103,   59,  116,  463,   41,
  116,  392,   44,  116,  256,   93,   59,  287,  343,   44,
  125,   93,  558,   59,   59,  105,  106,   59,   41,  123,
  398,   44,  405,   41,   59,   63,  116,  445,   41,  395,
  665,   44,   40,  143,  144,  445,   60,  445,   62,  610,
  611,  392,  256,  406,  384,   58,   59,   46,  350,  691,
   63,  342,  171,  350,  445,  171,  347,  394,  171,  561,
  123,  171,  445,   41,  610,  611,  125,  445,   46,   41,
   59,  540,   44,  691,  143,  144,  395,  123,  123,  445,
   93,  171,  445,   91,  403,  256,   58,   59,  123,  451,
   59,   63,   91,  282,  445,  256,  215,  256,  116,  670,
  396,  256,  673,  396,   44,  143,  144,  396,  445,  501,
  338,  300,  125,   91,  230,  406,  681,  230,  409,   59,
  228,   93,   63,  412,  670,  215,  445,  673,  630,  764,
   61,  219,  408,  171,  293,  413,   63,  123,  297,  604,
  413,  231,  232,  233,  234,   63,  398,  229,  125,  445,
  351,   46,  445,  125,  445,  530,  445,  256,   63,  256,
   91,  413,  256,  334,  262,  263,  337,  445,  287,  445,
  337,  287,  445,  334,   91,  286,  337,  333,  293,  334,
  256,  256,  297,  294,  398,  271,  351,   46,  468,   46,
  399,   46,  303,  445,   91,  314,   91,  287,  314,  413,
  310,  314,  143,  144,  314,  315,  123,  407,  327,  262,
  263,  327,  421,  256,  327,  199,  143,  144,  333,  581,
  262,  263,   91,  341,  314,  143,  144,   46,  730,  213,
  171,  445,   91,  337,   91,  597,   91,  327,  143,  144,
   59,  310,  266,  267,  171,  445,  315,  607,   44,   91,
  293,  390,   44,  171,  297,  535,   44,  270,  271,  378,
  610,  611,  378,   59,  766,  378,  171,   59,  350,  458,
  413,   59,  310,   61,  262,  263,  314,  315,  368,  369,
  370,  371,  372,  373,  374,  375,  376,  377,  378,  379,
  380,  381,  382,  383,  384,  385,  386,  387,  600,  271,
  333,  398,  445,  600,  413,   46,  445,  340,  413,  327,
  395,  390,  521,   59,  399,  339,  413,  526,  345,  407,
  670,  440,  684,  673,  440,   59,  416,  440,  447,   46,
  449,  447,  422,  452,  447,  529,  445,  697,  457,  697,
  445,  457,   59,   63,  457,   40,  708,  455,  445,  468,
  440,  105,  106,   40,  543,   63,  745,  447,  733,  449,
  445,  558,  452,  508,  644,  294,  445,  457,  513,  310,
  299,  760,  301,  314,  315,   41,  305,  306,  468,  308,
   46,  310,   46,  310,  474,  475,  476,  314,  315,  691,
  558,   46,  310,   37,  691,   59,  314,  315,   42,  264,
  265,  330,  331,   47,  333,  310,   40,  507,  519,  314,
  315,  340,  512,  610,  611,  503,  535,   46,  558,  284,
  530,  540,  440,  143,  144,   91,  333,  546,  666,  447,
  546,  539,   44,  546,  552,  143,  144,  333,   41,  457,
   44,   44,  610,  611,  340,  535,   46,   59,  558,   61,
  540,  171,  333,  662,  663,   59,  546,   61,  332,   91,
  698,  342,  336,  171,   59,  394,  347,   44,  349,  559,
  610,  611,   43,  670,   45,   58,  673,  231,  232,  233,
  234,  293,   59,  333,   61,  297,  268,  269,  607,  558,
  340,  607,  530,   41,  607,  401,   44,  607,  404,  609,
  610,  611,  670,  376,  377,  673,  379,  380,   40,   91,
   58,   59,   44,  722,  395,   63,  445,  607,  600,  400,
  558,  715,  373,  374,  375,  644,  553,   59,  546,   61,
  670,   40,  651,  673,  652,  651,   93,  775,  651,   93,
  609,  610,  611,   58,   59,   93,  665,  666,  656,  665,
  666,   93,  665,  666,  644,  665,  666,  262,  263,   91,
  670,  651,  681,  673,  445,  681,  371,  372,  681,  607,
   93,  609,  610,  611,   42,  665,  666,  125,   59,  698,
  381,  382,  698,   59,   38,  698,  697,  705,  698,  530,
  310,  681,  680,   94,  314,  315,  124,  270,   59,   40,
  333,  670,  310,  530,  673,   41,  314,  315,  698,  691,
   59,  333,  530,  522,  368,  369,  370,  558,   91,   61,
  333,  125,   40,  733,   93,  530,   41,  665,  666,   44,
  748,  558,  670,  651,  334,  673,  256,  334,  665,  666,
  558,  256,   93,   58,   59,  764,  105,  106,  764,   46,
   44,  764,   59,  558,  764,   59,  775,   41,   41,  775,
  698,   61,  775,  681,   41,  775,  607,   41,  609,  610,
  611,  698,  112,   46,  764,   91,   40,   40,   93,   93,
  607,   46,  609,  610,  611,  775,  126,   40,  776,  607,
   93,  609,  610,  611,   44,  733,  136,   59,   44,  337,
   44,  141,  607,   41,  609,  610,  611,  734,   44,   58,
  125,  123,   41,  256,   59,  624,  743,   40,  745,   46,
  474,   40,  476,  271,  665,  666,  764,   41,  123,  670,
   40,  640,  673,  760,  125,  125,   93,  775,  665,  666,
   91,   93,   41,  670,   44,   41,  673,  665,  666,  445,
   40,   44,  670,   58,  781,  673,  300,  698,   40,   40,
  665,  666,   40,   40,   59,  670,  256,  312,  673,   46,
   41,  698,  231,  232,  233,  234,  685,   41,  687,   41,
  698,   58,  123,  125,   61,  125,  125,   41,   41,   59,
  230,   40,  733,  698,   40,  125,   40,   40,   59,   58,
   41,   41,   41,   40,  125,   41,  733,  105,  106,  125,
  530,   58,  125,   41,   91,  733,  333,   59,   61,  123,
  260,   59,  530,  764,   41,   59,  735,  736,  733,  123,
   59,  123,  123,   41,  775,   41,   40,  764,  558,  279,
  105,  106,   41,  283,   59,   41,  764,  123,  775,  123,
  558,   41,  125,  404,  607,  295,  512,  775,  688,  764,
  769,  620,   40,  468,  304,   59,   59,  378,  644,  334,
  775,  314,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  447,   86,  607,  285,  475,  607,  383,  609,
  610,  611,  332,  384,  386,  436,  385,  559,  108,  607,
  387,  609,  610,  611,  350,   59,  516,   93,  580,  368,
  369,  370,  371,  372,  373,  374,  375,  376,  377,  691,
  379,  380,  381,  382,  383,  384,  385,  386,  387,  743,
  539,  733,  743,  231,  232,  233,  234,   41,   56,  633,
   44,  633,   46,   -1,   -1,  665,  666,   -1,  388,   -1,
  670,   -1,  392,  673,   -1,   59,  396,  665,  666,   -1,
   -1,   -1,  670,   -1,   -1,  673,  231,  232,  233,  234,
   33,  125,   -1,   -1,   -1,   -1,   -1,   40,  698,  419,
   43,   44,   45,   -1,   -1,  262,  263,   91,   -1,   -1,
  698,   -1,   -1,   -1,   -1,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,   -1,   -1,   -1,  285,   -1,
   -1,   -1,   -1,  733,   -1,  474,  475,  476,   -1,  262,
  263,   -1,   -1,  463,   -1,  733,   -1,   -1,   -1,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,   -1,
   -1,   33,  285,   -1,  764,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,   -1,  775,  764,   -1,   -1,   -1,
  123,   -1,  125,  126,   -1,   -1,  506,  775,   -1,   -1,
  368,  369,  370,  371,  372,  373,  374,  375,  376,  377,
   -1,  379,  380,  381,  382,  383,  384,  385,  386,  387,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  559,   -1,  256,  368,  369,  370,  371,  372,  373,  374,
  375,  376,  377,   -1,  379,  380,  381,  382,  383,  384,
  385,  386,  387,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  123,   -1,  125,  126,   -1,  413,  291,   -1,   -1,
   -1,   38,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,
   -1,  591,  256,   -1,   -1,   -1,   -1,  311,  262,  263,
   -1,   58,   59,   60,  604,   62,   63,   -1,  445,   -1,
  413,   -1,   -1,   -1,   -1,  329,  474,  475,  476,   -1,
   -1,  335,   -1,   -1,   -1,   -1,   -1,  341,  628,   -1,
  344,  345,  346,  256,  348,   -1,   93,   94,  352,  262,
  263,   -1,  445,  357,   -1,   -1,   -1,   33,   -1,  474,
  475,  476,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,
   -1,   -1,   33,   -1,   -1,   -1,   -1,  124,  125,   40,
   -1,  294,   43,   59,   45,   -1,  299,   -1,  301,  393,
   -1,   -1,  305,  306,   -1,  308,   -1,  310,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   41,   -1,   -1,   44,   -1,
   46,  559,   -1,   -1,  256,   -1,   -1,  330,  331,   -1,
  262,  263,   -1,   59,   -1,   -1,   -1,   -1,   -1,  342,
   -1,   -1,   93,   -1,  347,   -1,  349,   -1,   -1,   -1,
   -1,  354,  355,  356,  559,   -1,   -1,   -1,   -1,  739,
  126,  741,  294,   -1,   -1,   91,   -1,  299,   -1,  301,
   -1,   -1,   -1,  305,  306,  126,  308,   -1,  310,   -1,
   -1,   38,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,
   -1,  394,   -1,   33,  397,   -1,   -1,   -1,  330,  331,
   40,   58,   59,   43,   -1,   45,   63,   -1,   -1,   -1,
  342,   -1,   -1,   -1,   -1,  347,   -1,  349,   -1,   -1,
   -1,   -1,  354,  355,  356,   -1,   -1,   -1,   -1,  266,
  267,  268,  269,  270,  271,   -1,   93,   94,  291,   -1,
   -1,   -1,  445,  446,  447,  448,  449,  450,   -1,   -1,
   -1,   -1,  455,   -1,   -1,   -1,   -1,   -1,  311,   -1,
   -1,   -1,  394,   33,   -1,  397,   -1,  124,  125,   -1,
   40,   -1,   -1,   43,   -1,   45,  329,   -1,   -1,   -1,
  333,   -1,  335,  123,   -1,   -1,  126,   -1,  341,   -1,
  256,  344,  345,  346,   -1,  348,  262,  263,   -1,  352,
   -1,   -1,  339,   -1,  357,  256,   -1,   -1,   -1,   -1,
   -1,  262,  263,  445,  446,  447,  448,  449,  450,   -1,
   -1,   -1,   33,  455,   -1,   -1,   -1,   -1,  294,   40,
  256,   -1,   43,  299,   45,  301,  262,  263,   -1,  305,
  306,   -1,  308,  294,  310,   -1,   -1,   -1,  299,   -1,
  301,   -1,   -1,   -1,  305,  306,  126,  308,   -1,  310,
   -1,   -1,   -1,   -1,  330,  331,   -1,   -1,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,  342,   -1,   -1,  330,
  331,  347,   93,  349,   -1,   -1,   -1,   -1,  354,  355,
  356,  342,   -1,   -1,   -1,   -1,  347,   -1,  349,   -1,
   -1,   -1,   -1,  354,  355,  356,   -1,   -1,   -1,   -1,
   -1,  268,  269,  270,  271,  126,  256,   -1,   -1,   -1,
   -1,   -1,  262,  263,   -1,   -1,   -1,   -1,  394,   -1,
   -1,  397,   33,   -1,   -1,   -1,   -1,   -1,   -1,   40,
   -1,   -1,   43,  394,   45,   -1,  397,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  294,   -1,   -1,   -1,   -1,  299,
   -1,  301,   -1,   -1,   -1,  305,  306,   -1,  308,   -1,
  310,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  445,
  446,  447,  448,  449,  450,   -1,  256,   -1,   -1,  455,
  330,  331,  262,  263,  445,  446,  447,  448,  449,  450,
   -1,   -1,  342,   -1,  455,   -1,   -1,  347,   -1,  349,
   -1,   -1,   -1,   -1,  354,  355,  356,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  294,  126,   -1,   -1,   -1,  299,
   -1,  301,   -1,   -1,   -1,  305,  306,   -1,  308,   -1,
  310,   41,   -1,   -1,   44,  256,   -1,   -1,   -1,   -1,
   -1,  262,  263,   -1,  394,   33,   -1,  397,   58,   59,
  330,  331,   40,   63,   -1,   43,   -1,   45,  256,   -1,
   -1,   -1,  342,   -1,   -1,   -1,   -1,  347,   -1,  349,
   -1,   -1,   -1,  294,  354,  355,  356,   -1,  299,   -1,
  301,   -1,   -1,   93,  305,  306,   -1,  308,   -1,  310,
   -1,   -1,   -1,  291,   -1,  445,  446,  447,  448,  449,
  450,   -1,   -1,   -1,   -1,  455,   -1,   -1,  388,  330,
  331,   -1,   -1,  311,  394,  125,   -1,  397,   -1,   -1,
   33,  342,   -1,   -1,   -1,   -1,  347,   40,  349,   -1,
   43,  329,   45,  354,  355,  356,   -1,  335,  126,   -1,
   -1,   -1,   -1,  341,   -1,  256,  344,  345,  346,   -1,
  348,  262,  263,   -1,  352,   33,   -1,   -1,   -1,  357,
   -1,   -1,   40,    0,   -1,  445,  446,  447,  448,  449,
  450,   -1,   -1,  394,   -1,  455,  397,   -1,   -1,   -1,
   -1,   -1,   -1,  294,   -1,   -1,   -1,   -1,  299,   -1,
  301,   -1,   -1,   -1,  305,  306,   -1,  308,   -1,  310,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  126,   -1,   41,   -1,   -1,   44,  330,
  331,   -1,   59,   -1,  445,  446,  447,  448,  449,  450,
   -1,  342,   58,   59,  455,   -1,  347,   63,  349,   -1,
   -1,   -1,   -1,  354,  355,  356,   -1,   -1,  126,   -1,
   -1,  294,   -1,   -1,   -1,   -1,  299,   -1,  301,   -1,
  270,  271,  305,  306,   -1,  308,   -1,   93,  256,   -1,
   -1,   -1,   -1,   -1,  262,  263,   -1,  388,   -1,   -1,
   -1,   -1,   -1,  394,   -1,   -1,  397,  330,  331,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,
   -1,   -1,   -1,   -1,   -1,   -1,  294,   -1,   -1,   -1,
   -1,  299,   -1,  301,   -1,   -1,   -1,  305,  306,   -1,
  308,   -1,  310,   -1,   -1,   -1,   -1,   40,   -1,   -1,
   41,   -1,   -1,   44,  445,  446,  447,  448,  449,  450,
   -1,   -1,  330,  331,  455,   -1,   59,   58,   59,  262,
  263,  394,   63,   -1,  342,   -1,   -1,   -1,   -1,  347,
   -1,  349,   -1,   -1,   -1,   -1,  354,  355,  356,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,  294,   93,   94,   -1,   -1,  299,   -1,  301,   58,
   59,   -1,  305,  306,   63,  308,   -1,  310,   -1,   -1,
   -1,   -1,  445,   40,   -1,   -1,  394,   -1,   -1,  397,
  123,   -1,  125,  124,  125,   -1,  294,  330,  331,  256,
   -1,  299,   59,  301,   93,   94,   -1,  305,  306,  342,
  308,   -1,  310,   -1,  347,   -1,  349,   -1,   -1,   -1,
   -1,  354,  355,  356,  270,  271,   -1,   -1,   -1,   -1,
   -1,   -1,  330,  331,  291,  124,  125,  445,  446,  447,
  448,  449,  450,   -1,  342,   -1,   -1,  455,   -1,  347,
   -1,  349,   41,   -1,  311,   44,  354,  355,  356,   -1,
   -1,  394,   -1,   -1,  397,   -1,  123,   -1,  125,   58,
   59,   -1,  329,   -1,   63,   -1,  333,   -1,  335,   -1,
   -1,  338,   -1,  340,  341,   -1,  343,  344,  345,  346,
   -1,  348,   -1,   -1,   -1,  352,  394,   -1,   -1,  397,
  357,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,
   -1,   -1,  445,  446,  447,  448,  449,  450,   -1,   -1,
   -1,   -1,  455,  256,   -1,   -1,   -1,   -1,   -1,  262,
  263,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,  270,
  271,   -1,   -1,   40,   -1,   -1,   -1,  445,  446,  447,
  448,  449,  450,   -1,   -1,   -1,   -1,  455,  291,  292,
  293,  294,   59,  296,  297,  298,  299,  300,  301,  302,
   -1,  304,  305,  306,  307,  308,  309,  310,  311,  312,
   -1,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,  331,  256,
  333,   -1,  335,   -1,   -1,  262,  263,   -1,  341,  342,
   -1,  344,  345,  346,  347,  348,  349,  350,   -1,  352,
  353,  354,  355,  356,  357,  358,  123,   -1,  125,   -1,
   -1,   -1,   -1,   -1,  291,  292,  293,  294,   -1,  296,
  297,  298,  299,  300,  301,  302,   -1,  304,  305,  306,
  307,  308,  309,  310,  311,  312,   -1,  390,   -1,   -1,
   -1,  394,   -1,   -1,  397,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,  331,   -1,  333,   -1,  335,   -1,
   -1,  270,  271,   -1,  341,  342,   -1,  344,  345,  346,
  347,  348,  349,  350,   -1,  352,  353,  354,  355,  356,
  357,  358,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,
   -1,   -1,  445,  446,  447,  448,  449,  450,   -1,   -1,
   58,   59,  455,   40,   -1,   63,   -1,  294,   -1,   -1,
   -1,   -1,  299,  390,  301,   -1,   -1,  394,  305,  306,
  397,  308,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,  256,
   -1,   -1,   -1,  330,  331,  262,  263,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,  445,  446,
  447,  448,  449,  450,  291,  292,  293,  294,  455,  296,
  297,  298,  299,  300,  301,  302,  123,  304,  305,  306,
  307,  308,  309,  310,  311,  312,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  394,   -1,   -1,
  256,   -1,  329,  330,  331,  402,  333,   -1,  335,   -1,
   -1,   -1,   -1,   -1,  341,  342,   40,  344,  345,  346,
  347,  348,  349,  350,   -1,  352,  353,  354,  355,  356,
  357,  358,   -1,   -1,   -1,   59,   -1,   -1,  294,   -1,
   -1,   -1,   -1,  299,   -1,  301,   -1,   -1,  445,  305,
  306,   -1,  308,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  390,   -1,   -1,   -1,  394,   -1,   -1,
  397,   -1,   -1,   -1,  330,  331,   -1,   -1,   -1,  335,
   38,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,
   -1,   -1,   -1,   40,   -1,   -1,   -1,   -1,   -1,  123,
   58,   59,  270,  271,   -1,   63,   -1,   -1,   -1,  256,
   -1,   -1,   59,   -1,   -1,  262,  263,   -1,  445,  446,
  447,  448,  449,  450,   -1,   -1,   -1,   -1,  455,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,  394,   -1,
   -1,   -1,   -1,   -1,  291,  292,   -1,  294,   -1,  296,
   -1,  298,  299,   -1,  301,  302,   -1,  304,  305,  306,
  307,  308,  309,  310,  311,  312,  124,  125,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,  125,   -1,
   -1,   -1,  329,  330,  331,   -1,  333,   -1,  335,  445,
   -1,   -1,   -1,   -1,  341,  342,   -1,  344,  345,  346,
  347,  348,  349,  350,   -1,  352,  353,  354,  355,  356,
  357,  358,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  256,   -1,   -1,   -1,   -1,   -1,  262,  263,
   -1,   -1,   -1,  390,   -1,   -1,   -1,  394,   -1,   -1,
  397,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   40,   -1,  409,   -1,  411,   -1,   -1,  291,  292,   -1,
  294,   -1,  296,   -1,  298,  299,   -1,  301,  302,   59,
  304,  305,  306,  307,  308,  309,  310,  311,  312,    0,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  445,  446,
  447,  448,  449,  450,   -1,  329,  330,  331,  455,  256,
   -1,  335,  270,  271,   -1,  262,  263,  341,  342,   -1,
  344,  345,  346,  347,  348,  349,  350,   -1,  352,  353,
  354,  355,  356,  357,  358,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  123,  291,  292,   -1,  294,   59,  296,
   -1,  298,  299,   -1,  301,  302,   -1,  304,  305,  306,
  307,  308,  309,  310,  311,  312,  390,   -1,   -1,   -1,
  394,   -1,   -1,  397,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  329,  330,  331,  409,  333,  411,  335,   -1,
   -1,   -1,   -1,   -1,  341,  342,   -1,  344,  345,  346,
  347,  348,  349,  350,   -1,  352,  353,  354,  355,  356,
  357,  358,   -1,  291,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  445,  446,  447,  448,  449,  450,   40,   -1,   -1,
   -1,  455,   -1,  311,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  390,   -1,   -1,   59,  394,  294,   -1,
  397,  329,   -1,  299,   -1,  301,   -1,  335,   -1,  305,
  306,   -1,  308,  341,  310,   -1,  344,  345,  346,   -1,
  348,   -1,   -1,   -1,  352,   -1,  256,   -1,   -1,  357,
   -1,   -1,  262,  263,  330,  331,   -1,  333,   -1,   -1,
   -1,   -1,   -1,   -1,  340,   -1,   -1,   -1,  445,  446,
  447,  448,  449,  450,   40,   -1,   -1,   -1,  455,   -1,
  123,  291,  292,   -1,  294,   -1,  296,   -1,  298,  299,
   -1,  301,  302,   59,  304,  305,  306,  307,  308,  309,
  310,  311,  312,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,  394,  329,
  330,  331,   -1,  333,   -1,  335,   -1,   -1,   -1,   -1,
   -1,  341,  342,   -1,  344,  345,  346,  347,  348,  349,
  350,   -1,  352,  353,  354,  355,  356,  357,  358,   -1,
  291,   -1,   -1,   -1,   -1,   40,   -1,  123,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  445,
  311,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  390,   -1,   -1,   -1,  394,   -1,   -1,  397,  329,   -1,
   -1,   -1,  333,   -1,  335,   -1,   -1,  338,   -1,  340,
  341,   -1,   -1,  344,  345,  346,   -1,  348,   -1,   -1,
   -1,  352,   -1,  256,   -1,   -1,  357,   -1,   -1,  262,
  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   -1,  445,  446,  447,  448,  449,
  450,   -1,   -1,   -1,   -1,  455,   -1,   -1,  291,  292,
   -1,  294,   -1,  296,   -1,  298,  299,   -1,  301,  302,
   -1,  304,  305,  306,  307,  308,  309,  310,  311,  312,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,  331,   -1,
   -1,   -1,  335,   -1,   -1,   -1,  262,  263,  341,  342,
   -1,  344,  345,  346,  347,  348,  349,  350,   -1,  352,
  353,  354,  355,  356,  357,  358,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  292,   -1,  294,   -1,
  296,   -1,  298,  299,   -1,  301,  302,   -1,  304,  305,
  306,  307,  308,  309,  310,   -1,  312,  390,   -1,   -1,
   -1,  394,   -1,   -1,  397,   -1,    0,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  330,  331,   -1,   -1,   -1,   -1,
    0,   -1,   -1,   -1,   -1,   -1,  342,  262,  263,   -1,
   -1,  347,  348,  349,  350,   -1,   -1,  353,  354,  355,
  356,   -1,  358,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,  445,  446,  447,  448,  449,  450,   -1,  294,
   -1,   -1,  455,   -1,  299,   59,  301,   -1,   -1,   -1,
  305,  306,   -1,  308,  390,  310,   -1,   -1,  394,   59,
   -1,  397,   -1,   -1,   -1,   -1,   -1,   -1,   38,   -1,
   -1,   41,   -1,   -1,   44,  330,  331,   -1,   -1,   -1,
  335,   -1,   -1,  262,  263,   59,   -1,  342,   58,   59,
   -1,   -1,  347,   63,  349,   -1,   -1,   -1,   -1,  354,
  355,  356,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  445,
  446,  447,  448,  449,  450,  294,   -1,   -1,   -1,  455,
  299,   -1,  301,   93,   94,   -1,  305,  306,   -1,  308,
   -1,  310,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  394,
   -1,   -1,  397,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  330,  331,   -1,  124,  125,   -1,   -1,   38,   -1,
   -1,   41,   -1,  342,   44,   -1,   -1,   -1,  347,   -1,
  349,   59,   -1,   -1,   -1,  354,  355,  356,   58,   59,
   60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,
  445,  446,  447,  448,  449,  450,   -1,   -1,   -1,   38,
  455,   -1,   41,   -1,   -1,   44,   38,   -1,   -1,   41,
   -1,   -1,   44,   93,   94,  394,   -1,   -1,  397,   58,
   59,   60,   -1,   62,   63,   -1,   58,   59,   60,   -1,
   62,   63,   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,
   -1,   -1,  256,   59,  124,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   94,  256,   -1,   -1,   -1,
   -1,   93,   94,   -1,   -1,   -1,  445,  446,  447,  448,
  449,  450,   -1,   -1,   -1,   -1,  455,  291,   -1,   -1,
   -1,   -1,  256,   -1,   -1,  124,  125,   -1,   -1,   -1,
   -1,  291,  124,  125,   -1,   -1,   -1,  311,  268,  269,
  270,  271,   -1,   -1,   -1,   -1,   -1,  123,   -1,  125,
   -1,  311,   -1,   -1,   -1,  329,   -1,  291,   59,  333,
   -1,  335,   -1,   -1,   -1,   -1,  340,  341,   -1,  329,
  344,  345,  346,  333,  348,  335,   -1,  311,  352,   -1,
  340,  341,   -1,  357,  344,  345,  346,   -1,  348,   -1,
   -1,   -1,  352,   -1,   -1,  329,   -1,  357,   -1,  333,
   -1,  335,   -1,   -1,   -1,   -1,  340,  341,  256,   -1,
  344,  345,  346,   -1,  348,   -1,  256,   -1,  352,   -1,
   -1,   -1,   -1,  357,  125,   -1,  266,  267,  268,  269,
  270,  271,   -1,   -1,   -1,   38,   -1,   -1,   41,   -1,
   -1,   44,   -1,  291,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,  256,   -1,   -1,
   63,   -1,   -1,  311,  256,   -1,   -1,  266,  267,  268,
  269,  270,  271,   -1,  266,  267,  268,  269,  270,  271,
  256,  329,   -1,   -1,   -1,   -1,   -1,  335,   -1,   -1,
   93,   94,   -1,  341,   -1,   -1,  344,  345,  346,  339,
  348,   -1,   -1,   -1,  352,   -1,   -1,   -1,   -1,  357,
   -1,   -1,   -1,   -1,   -1,  291,   -1,   -1,   -1,   -1,
   -1,  124,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  311,   -1,   -1,   -1,   -1,
  339,  291,   -1,   -1,   -1,  393,   -1,  339,   -1,   -1,
   -1,   -1,   -1,  329,   -1,  256,   -1,   -1,  398,  335,
   -1,  311,   -1,   -1,   -1,  341,   -1,   -1,  344,  345,
  346,   -1,  348,  413,   -1,   -1,  352,   -1,   -1,  329,
   -1,  357,   -1,  333,   -1,  335,   -1,   -1,   -1,   -1,
  291,  341,   -1,   -1,  344,  345,  346,   -1,  348,  398,
   -1,   -1,  352,   -1,   -1,  445,  398,  357,   -1,   -1,
  311,   -1,   -1,   -1,  413,   -1,   -1,  393,   -1,   -1,
   -1,  413,   -1,   -1,   -1,   -1,   -1,   -1,  329,   -1,
   -1,   -1,   -1,   -1,  335,   -1,   -1,   -1,   -1,   -1,
  341,   -1,   -1,  344,  345,  346,  445,  348,   -1,   -1,
   -1,  352,   -1,  445,   37,   38,  357,   40,   41,   42,
   43,   44,   45,   46,   47,  268,  269,  270,  271,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,   60,   61,   62,
   63,   37,   38,   -1,   40,   41,   42,   43,   44,   45,
   46,   47,  393,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   61,   62,   63,   91,   -1,
   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   38,   -1,   -1,   41,   -1,   91,   44,   93,   94,   -1,
   -1,  124,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   59,   60,   -1,   62,   63,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,  124,  125,
   41,   42,   43,   44,   45,   46,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   94,   58,   59,   60,
   61,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,  294,
   -1,   -1,   -1,   -1,  299,   -1,  301,   -1,   -1,   -1,
  305,  306,   -1,  308,   -1,  310,  124,  125,   -1,   -1,
   91,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  330,  331,   -1,  333,   -1,
   -1,   -1,   -1,   -1,   -1,  340,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  256,   -1,   -1,   -1,   -1,   -1,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  394,
  256,  284,  285,   -1,   -1,   -1,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,   -1,   -1,  284,  285,
  294,   -1,   -1,   -1,   -1,  299,   -1,  301,   -1,   -1,
   -1,  305,  306,   -1,  308,   -1,  310,   -1,   -1,   -1,
  445,   -1,   -1,   -1,   -1,   -1,  339,   -1,  266,  267,
  268,  269,  270,  271,   -1,   -1,  330,  331,   -1,  333,
   -1,   -1,   -1,   -1,   -1,   -1,  340,   -1,   -1,   -1,
   -1,   -1,   -1,  339,   -1,  256,   -1,   -1,   -1,   -1,
   -1,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,   -1,   -1,  284,  285,   37,   38,   -1,   -1,   41,
   42,   43,   44,   45,   46,   47,   -1,   -1,   -1,   -1,
  394,  339,   -1,   -1,   -1,   -1,   58,   59,   60,   61,
   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   37,   38,   -1,   40,   41,   42,   43,   44,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,  339,   91,
   -1,   93,   94,   58,   59,   60,   61,   62,   63,   -1,
   -1,  445,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   93,   94,
   37,   38,   -1,   -1,   41,   42,   43,   44,   45,   46,
   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   59,   60,   -1,   62,   63,   37,   38,  124,
  125,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,
   60,   61,   62,   63,   91,  291,   93,   94,  294,   -1,
   -1,   -1,   -1,  299,   -1,  301,   -1,   -1,   -1,  305,
  306,   -1,  308,   -1,  310,  311,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   94,   -1,  123,  124,  125,   -1,
   -1,   -1,   -1,  329,  330,  331,   -1,  333,   -1,  335,
   -1,   -1,   -1,   -1,  340,  341,   -1,   -1,  344,  345,
  346,   -1,  348,   -1,  124,  125,  352,   -1,   -1,   -1,
   -1,  357,   -1,   -1,  256,   -1,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
   -1,   -1,  284,  285,   -1,   -1,   -1,   -1,  394,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,   -1,   -1,  284,
  285,   -1,   37,   38,   -1,   -1,   41,   42,   43,   44,
   45,   46,   47,   -1,   -1,   -1,   -1,  339,   -1,  445,
   -1,   -1,   -1,   58,   59,   60,   -1,   62,   63,  256,
   -1,   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,
  267,  268,  269,  270,  271,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  339,   -1,   91,  284,   93,   94,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,   -1,   -1,  284,  285,   -1,   -1,  123,  124,
  125,   -1,   37,   38,   -1,   -1,   41,   42,   43,   44,
   45,   46,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  339,   58,   59,   60,   -1,   62,   63,   37,
   38,   -1,   -1,   41,   42,   43,   44,   45,   46,   47,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  339,
   58,   59,   60,   -1,   62,   63,   -1,   -1,   93,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   91,   -1,   93,   94,   -1,   -1,  124,
  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  256,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   -1,  284,
   41,   42,   43,   44,   45,   46,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
   -1,   62,   63,   37,   38,   -1,   -1,   41,   42,   43,
   44,   45,   46,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   58,   59,   60,   -1,   62,   63,
   -1,   -1,   93,   94,  339,   -1,   -1,   -1,   -1,   -1,
   -1,  256,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,   -1,   -1,   93,
   94,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,  284,
   -1,   -1,   -1,   -1,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,
  124,  125,   -1,   -1,   -1,   -1,  284,   37,   38,   -1,
   40,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,
   60,   -1,   62,   63,  339,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   -1,
   -1,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,  339,   -1,   93,   94,   -1,   -1,   -1,   58,   59,
   60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   94,  256,   -1,   -1,   -1,   -1,
   -1,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  256,  284,  124,  125,   -1,   -1,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   -1,
  284,   41,   42,   43,   44,   45,   -1,   47,   -1,   38,
   -1,   -1,   41,   -1,   43,   44,   45,   -1,   58,   59,
   60,   -1,   62,   63,   -1,   -1,   -1,   -1,  339,   58,
   59,   60,   -1,   62,   63,   37,   38,   -1,   -1,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   94,  339,   58,   59,   60,   -1,
   62,   63,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,
   -1,   93,   94,   -1,  284,  124,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  124,  125,   -1,   -1,   38,   -1,   -1,   41,
   -1,   43,   44,   45,  284,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,  339,
   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   38,   -1,   -1,   41,   -1,   43,   44,
   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   94,   58,   59,   60,   -1,   62,   63,  339,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   93,   94,
   -1,   -1,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,   -1,   -1,   -1,  264,  265,  266,  267,  268,
  269,  270,  271,   -1,  284,   -1,   -1,   -1,   -1,  124,
  125,   -1,   -1,   38,   -1,  284,   41,   -1,   -1,   44,
   -1,   -1,  264,  265,  266,  267,  268,  269,  270,  271,
   -1,   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,
   38,   -1,  284,   41,   -1,   -1,   44,   -1,   -1,   -1,
   -1,   38,   -1,   -1,   41,   -1,   -1,   44,   -1,  339,
   58,   59,   60,   -1,   62,   63,   -1,   -1,   93,   94,
  339,   58,   59,   60,   -1,   62,   63,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   94,  339,   -1,  124,
  125,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,
   -1,   -1,  264,  265,  266,  267,  268,  269,  270,  271,
   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,
   -1,   -1,  284,   -1,   -1,   -1,   -1,  124,  125,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,  264,
  265,  266,  267,  268,  269,  270,  271,   -1,   -1,   58,
   59,   60,   -1,   62,   63,   -1,   -1,   -1,   -1,  284,
   -1,   -1,   -1,   -1,   -1,   -1,   38,   -1,   -1,   41,
   -1,   -1,   44,   -1,   -1,   -1,   -1,  339,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   94,   58,   59,   60,   -1,
   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  339,  124,  125,   -1,   -1,   -1,
   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,  264,
  265,  266,  267,  268,  269,  270,  271,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  284,
   -1,   -1,  124,  125,   -1,   -1,  264,  265,  266,  267,
  268,  269,  270,  271,   -1,   -1,   -1,  264,  265,  266,
  267,  268,  269,  270,  271,   -1,  284,   38,   -1,   -1,
   41,   -1,   -1,   44,   -1,   38,   -1,  284,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
   -1,   62,   63,   -1,  339,   58,   59,   60,   -1,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  339,   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,
   93,   94,  339,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  264,  265,  266,  267,  268,
  269,  270,  271,  124,  125,   -1,   -1,   -1,   -1,   -1,
   -1,  124,  125,   -1,   -1,  284,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  266,  267,  268,  269,  270,  271,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  339,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  339,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  266,  267,  268,  269,  270,
  271,   -1,   -1,  266,  267,  268,  269,  270,  271,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  339,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  339,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 456
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,
0,0,0,0,0,0,0,"':'","';'","'<'","'='","'>'","'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TYPE_NAME",
"CLASS_NAME","TEMPLATE_NAME","CONVERSION_OP_ID_PREFIX","OPERATOR_IDENT",
"INC_OP","DEC_OP","LEFT_OP","RIGHT_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP",
"OR_OP","MUL_ASSIGN","DIV_ASSIGN","MOD_ASSIGN","ADD_ASSIGN","SUB_ASSIGN",
"LEFT_ASSIGN","RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN","PTR_OP",
"ELIPSIS","URIGHT_OP","URIGHT_ASSIGN","YACC_PERC","YACC_DPERC","DPOINT",
"POINTM_OP","PTRM_OP","STATIC","BREAK","CASE","CHAR","CONST","CONTINUE",
"DEFAULT","DO","DOUBLE","ELSE","FLOAT","FOR","GOTO","IF","INT","LONG","RETURN",
"SHORT","SWITCH","VOID","VOLATILE","WHILE","TYPEDEF","EXTERN","AUTO","REGISTER",
"SIGNED","UNSIGNED","STRUCT","UNION","ENUM","SIZEOF","RESTRICT","_ATOMIC",
"_BOOL","_THREADLOCAL","_NORETURN","ANONYME_MOD","ABSTRACT","BOOLEAN","BYTE",
"CATCH","CLASS","EXTENDS","FINAL","FINALLY","IMPLEMENTS","IMPORT","INSTANCEOF",
"INTERFACE","NATIVE","NEW","PACKAGE","PRIVATE","PROTECTED","PUBLIC","SUPER",
"SYNCHRONIZED","THIS","THROW","THROWS","TRANSIENT","TRY","TRUE_LITERAL",
"FALSE_LITERAL","NULL_LITERAL","STRICTFP","ASSERT","FRIEND","OPERATOR",
"NAMESPACE","TEMPLATE","DELETE","MUTABLE","EXPLICIT","WCHAR_T","BOOL","USING",
"ASM_KEYWORD","EXPORT","VIRTUAL","INLINE","TYPENAME","DYNAMIC_CAST",
"STATIC_CAST","REINTERPRET_CAST","CONST_CAST","TYPEID","TOKEN","TYPE","LABEL",
"COMPL_FOR_SPECIAL1","COMPL_FOR_SPECIAL2","COMPL_THIS_PACKAGE_SPECIAL",
"COMPL_TYPE_NAME","COMPL_STRUCT_NAME","COMPL_STRUCT_REC_NAME",
"COMPL_UP_FUN_PROFILE","COMPL_ENUM_NAME","COMPL_LABEL_NAME","COMPL_OTHER_NAME",
"COMPL_CLASS_DEF_NAME","COMPL_FULL_INHERITED_HEADER","COMPL_TYPE_NAME0",
"COMPL_TYPE_NAME1","COMPL_PACKAGE_NAME0","COMPL_EXPRESSION_NAME0",
"COMPL_METHOD_NAME0","COMPL_PACKAGE_NAME1","COMPL_EXPRESSION_NAME1",
"COMPL_METHOD_NAME1","COMPL_CONSTRUCTOR_NAME0","COMPL_CONSTRUCTOR_NAME1",
"COMPL_CONSTRUCTOR_NAME2","COMPL_CONSTRUCTOR_NAME3","COMPL_STRUCT_REC_PRIM",
"COMPL_STRUCT_REC_SUPER","COMPL_QUALIF_SUPER","COMPL_SUPER_CONSTRUCTOR1",
"COMPL_SUPER_CONSTRUCTOR2","COMPL_THIS_CONSTRUCTOR","COMPL_IMPORT_SPECIAL",
"COMPL_VARIABLE_NAME_HINT","COMPL_CONSTRUCTOR_HINT","COMPL_METHOD_PARAM1",
"COMPL_METHOD_PARAM2","COMPL_METHOD_PARAM3","COMPL_YACC_LEXEM_NAME",
"CPP_TOKENS_START","CPP_INCLUDE","CPP_DEFINE","CPP_IFDEF","CPP_IFNDEF","CPP_IF",
"CPP_ELSE","CPP_ENDIF","CPP_ELIF","CPP_UNDEF","CPP_PRAGMA","CPP_LINE",
"CPP_DEFINE0","CPP_TOKENS_END","CPP_COLLATION","CPP_DEFINED_OP","EOI_TOKEN",
"CACHING1_TOKEN","OL_MARKER_TOKEN","OL_MARKER_TOKEN1","OL_MARKER_TOKEN2",
"TMP_TOKEN1","TMP_TOKEN2","CCC_OPER_PARENTHESIS","CCC_OPER_BRACKETS",
"MULTI_TOKENS_START","IDENTIFIER","CONSTANT","LONG_CONSTANT","FLOAT_CONSTANT",
"DOUBLE_CONSTANT","STRING_LITERAL","LINE_TOK","IDENT_TO_COMPLETE","CPP_MAC_ARG",
"IDENT_NO_CPP_EXPAND","CHAR_LITERAL","LAST_TOKEN",
};
char *yyrule[] = {
"$accept : Goal",
"Goal : CompilationUnit",
"Literal : TRUE_LITERAL",
"Literal : FALSE_LITERAL",
"Literal : CONSTANT",
"Literal : LONG_CONSTANT",
"Literal : FLOAT_CONSTANT",
"Literal : DOUBLE_CONSTANT",
"Literal : CHAR_LITERAL",
"Literal : STRING_LITERAL",
"Literal : NULL_LITERAL",
"Type : PrimitiveType",
"Type : ReferenceType",
"PrimitiveType : NumericType",
"PrimitiveType : BOOLEAN",
"NumericType : IntegralType",
"NumericType : FloatingPointType",
"IntegralType : BYTE",
"IntegralType : SHORT",
"IntegralType : INT",
"IntegralType : LONG",
"IntegralType : CHAR",
"FloatingPointType : FLOAT",
"FloatingPointType : DOUBLE",
"ReferenceType : ClassOrInterfaceType",
"ReferenceType : ArrayType",
"ClassOrInterfaceType : Name",
"ClassOrInterfaceType : CompletionTypeName",
"ExtendClassOrInterfaceType : Name",
"ExtendClassOrInterfaceType : CompletionTypeName",
"ClassType : ClassOrInterfaceType",
"InterfaceType : ClassOrInterfaceType",
"ArrayType : PrimitiveType '[' ']'",
"ArrayType : Name '[' ']'",
"ArrayType : ArrayType '[' ']'",
"ArrayType : CompletionTypeName '[' ']'",
"Identifier : IDENTIFIER",
"This : THIS",
"Super : SUPER",
"New : NEW",
"Import : IMPORT",
"Package : PACKAGE",
"Throw : THROW",
"Try : TRY",
"Catch : CATCH",
"Name : SimpleName",
"Name : QualifiedName",
"SimpleName : IDENTIFIER",
"QualifiedName : Name '.' IDENTIFIER",
"CompletionTypeName : COMPL_TYPE_NAME0",
"CompletionTypeName : Name '.' COMPL_TYPE_NAME1",
"CompletionFQTypeName : COMPL_PACKAGE_NAME0",
"CompletionFQTypeName : Name '.' COMPL_TYPE_NAME1",
"CompletionPackageName : COMPL_PACKAGE_NAME0",
"CompletionPackageName : Name '.' COMPL_PACKAGE_NAME1",
"CompletionExpressionName : COMPL_EXPRESSION_NAME0",
"CompletionExpressionName : Name '.' COMPL_EXPRESSION_NAME1",
"CompletionConstructorName : COMPL_CONSTRUCTOR_NAME0",
"CompletionConstructorName : Name '.' COMPL_CONSTRUCTOR_NAME1",
"LabelDefininigIdentifier : IDENTIFIER",
"LabelDefininigIdentifier : COMPL_LABEL_NAME",
"LabelUseIdentifier : IDENTIFIER",
"LabelUseIdentifier : COMPL_LABEL_NAME",
"$$1 :",
"$$2 :",
"$$3 :",
"CompilationUnit : $$1 PackageDeclaration_opt $$2 ImportDeclarations_opt $$3 TypeDeclarations_opt",
"CompilationUnit : InCachingRecovery",
"ImportDeclarations_opt :",
"ImportDeclarations_opt : ImportDeclarations",
"ImportDeclarations : SingleTypeImportDeclaration",
"ImportDeclarations : TypeImportOnDemandDeclaration",
"ImportDeclarations : ImportDeclarations SingleTypeImportDeclaration",
"ImportDeclarations : ImportDeclarations TypeImportOnDemandDeclaration",
"SingleTypeImportDeclaration : Import Name ';'",
"SingleTypeImportDeclaration : Import CompletionFQTypeName ';'",
"SingleTypeImportDeclaration : Import COMPL_IMPORT_SPECIAL ';'",
"TypeImportOnDemandDeclaration : Import Name '.' '*' ';'",
"TypeImportOnDemandDeclaration : Import CompletionPackageName '.' '*' ';'",
"TypeDeclarations_opt :",
"TypeDeclarations_opt : TypeDeclarations _bef_",
"TypeDeclarations : _bef_ TypeDeclaration",
"TypeDeclarations : TypeDeclarations _bef_ TypeDeclaration",
"PackageDeclaration_opt :",
"PackageDeclaration_opt : Package Name ';'",
"PackageDeclaration_opt : Package error",
"PackageDeclaration_opt : Package CompletionPackageName ';'",
"PackageDeclaration_opt : PACKAGE COMPL_THIS_PACKAGE_SPECIAL ';'",
"TypeDeclaration : ClassDeclaration",
"TypeDeclaration : InterfaceDeclaration",
"TypeDeclaration : ';'",
"TypeDeclaration : error",
"Modifiers_opt :",
"Modifiers_opt : Modifiers",
"Modifiers : Modifier",
"Modifiers : Modifiers Modifier",
"Modifier : PUBLIC",
"Modifier : PROTECTED",
"Modifier : PRIVATE",
"Modifier : STATIC",
"Modifier : ABSTRACT",
"Modifier : FINAL",
"Modifier : NATIVE",
"Modifier : SYNCHRONIZED",
"Modifier : STRICTFP",
"Modifier : TRANSIENT",
"Modifier : VOLATILE",
"InCachingRecovery : CACHING1_TOKEN ClassBody",
"$$4 :",
"$$5 :",
"ClassDeclaration : Modifiers_opt CLASS Identifier $$4 Super_opt Interfaces_opt $$5 ClassBody",
"$$6 :",
"ClassDeclaration : Modifiers_opt CLASS Identifier $$6 error ClassBody",
"ClassDeclaration : Modifiers_opt CLASS COMPL_CLASS_DEF_NAME",
"$$7 :",
"$$8 :",
"FunctionInnerClassDeclaration : Modifiers_opt CLASS Identifier $$7 Super_opt Interfaces_opt $$8 ClassBody",
"$$9 :",
"FunctionInnerClassDeclaration : Modifiers_opt CLASS Identifier $$9 error ClassBody",
"FunctionInnerClassDeclaration : Modifiers_opt CLASS COMPL_CLASS_DEF_NAME",
"Super_opt :",
"Super_opt : EXTENDS ExtendClassOrInterfaceType",
"Interfaces_opt :",
"Interfaces_opt : IMPLEMENTS InterfaceTypeList",
"InterfaceTypeList : InterfaceType",
"InterfaceTypeList : InterfaceTypeList ',' InterfaceType",
"_bef_ :",
"ClassBody : _bef_ '{' '}'",
"ClassBody : _bef_ '{' ClassBodyDeclarations _bef_ '}'",
"ClassBodyDeclarations : ClassBodyDeclaration",
"ClassBodyDeclarations : ClassBodyDeclarations _bef_ ClassBodyDeclaration",
"ClassBodyDeclaration : ClassMemberDeclaration",
"ClassBodyDeclaration : ClassInitializer",
"ClassBodyDeclaration : ConstructorDeclaration",
"ClassBodyDeclaration : ';'",
"ClassBodyDeclaration : error",
"ClassMemberDeclaration : ClassDeclaration",
"ClassMemberDeclaration : InterfaceDeclaration",
"ClassMemberDeclaration : FieldDeclaration",
"ClassMemberDeclaration : MethodDeclaration",
"AssignementType : Type",
"FieldDeclaration : Modifiers_opt AssignementType VariableDeclarators ';'",
"VariableDeclarators : VariableDeclarator",
"VariableDeclarators : VariableDeclarators ',' VariableDeclarator",
"VariableDeclarator : VariableDeclaratorId",
"VariableDeclarator : VariableDeclaratorId '=' VariableInitializer",
"VariableDeclarator : error",
"VariableDeclaratorId : Identifier",
"VariableDeclaratorId : VariableDeclaratorId '[' ']'",
"VariableDeclaratorId : COMPL_VARIABLE_NAME_HINT",
"VariableInitializer : Expression",
"VariableInitializer : ArrayInitializer",
"$$10 :",
"MethodDeclaration : MethodHeader Start_block $$10 MethodBody Stop_block",
"MethodHeader : Modifiers_opt AssignementType MethodDeclarator Throws_opt",
"MethodHeader : Modifiers_opt VOID MethodDeclarator Throws_opt",
"MethodHeader : COMPL_FULL_INHERITED_HEADER",
"$$11 :",
"MethodDeclarator : Identifier $$11 '(' FormalParameterList_opt ')'",
"MethodDeclarator : MethodDeclarator '[' ']'",
"MethodDeclarator : COMPL_METHOD_NAME0",
"FormalParameterList_opt :",
"FormalParameterList_opt : FormalParameterList",
"FormalParameterList : FormalParameter",
"FormalParameterList : FormalParameterList ',' FormalParameter",
"FormalParameter : Type VariableDeclaratorId",
"FormalParameter : FINAL Type VariableDeclaratorId",
"FormalParameter : error",
"Throws_opt :",
"Throws_opt : THROWS ClassTypeList",
"ClassTypeList : ClassType",
"ClassTypeList : ClassTypeList ',' ClassType",
"MethodBody : Block",
"MethodBody : ';'",
"ClassInitializer : STATIC Block",
"ClassInitializer : Block",
"$$12 :",
"ConstructorDeclaration : Modifiers_opt ConstructorDeclarator Throws_opt $$12 Start_block ConstructorBody Stop_block",
"$$13 :",
"ConstructorDeclarator : Identifier $$13 '(' FormalParameterList_opt ')'",
"ConstructorBody : '{' Start_block ExplicitConstructorInvocation BlockStatements Stop_block '}'",
"ConstructorBody : '{' Start_block ExplicitConstructorInvocation Stop_block '}'",
"ConstructorBody : '{' Start_block BlockStatements Stop_block '}'",
"ConstructorBody : '{' '}'",
"$$14 :",
"ExplicitConstructorInvocation : This _erfs_ $$14 '(' ArgumentList_opt ')'",
"$$15 :",
"ExplicitConstructorInvocation : Super _erfs_ $$15 '(' ArgumentList_opt ')'",
"$$16 :",
"ExplicitConstructorInvocation : Primary '.' Super _erfs_ $$16 '(' ArgumentList_opt ')'",
"ExplicitConstructorInvocation : This error",
"ExplicitConstructorInvocation : Super error",
"ExplicitConstructorInvocation : Primary error",
"ExplicitConstructorInvocation : COMPL_SUPER_CONSTRUCTOR1",
"ExplicitConstructorInvocation : COMPL_THIS_CONSTRUCTOR",
"ExplicitConstructorInvocation : Primary '.' COMPL_SUPER_CONSTRUCTOR1",
"$$17 :",
"$$18 :",
"InterfaceDeclaration : Modifiers_opt INTERFACE Identifier $$17 ExtendsInterfaces_opt $$18 InterfaceBody",
"$$19 :",
"InterfaceDeclaration : Modifiers_opt INTERFACE Identifier $$19 error InterfaceBody",
"InterfaceDeclaration : Modifiers_opt INTERFACE COMPL_CLASS_DEF_NAME",
"ExtendsInterfaces_opt :",
"ExtendsInterfaces_opt : ExtendsInterfaces",
"ExtendsInterfaces : EXTENDS ExtendClassOrInterfaceType",
"ExtendsInterfaces : ExtendsInterfaces ',' ExtendClassOrInterfaceType",
"InterfaceBody : _bef_ '{' '}'",
"InterfaceBody : _bef_ '{' InterfaceMemberDeclarations _bef_ '}'",
"InterfaceMemberDeclarations : InterfaceMemberDeclaration",
"InterfaceMemberDeclarations : InterfaceMemberDeclarations _bef_ InterfaceMemberDeclaration",
"InterfaceMemberDeclaration : ClassDeclaration",
"InterfaceMemberDeclaration : InterfaceDeclaration",
"InterfaceMemberDeclaration : ConstantDeclaration",
"InterfaceMemberDeclaration : AbstractMethodDeclaration",
"InterfaceMemberDeclaration : ';'",
"InterfaceMemberDeclaration : error",
"ConstantDeclaration : FieldDeclaration",
"$$20 :",
"AbstractMethodDeclaration : MethodHeader Start_block $$20 ';' Stop_block",
"ArrayInitializer : '{' VariableInitializers ',' '}'",
"ArrayInitializer : '{' VariableInitializers '}'",
"ArrayInitializer : '{' ',' '}'",
"ArrayInitializer : '{' '}'",
"VariableInitializers : VariableInitializer",
"VariableInitializers : VariableInitializers ',' VariableInitializer",
"Block : '{' Start_block BlockStatements Stop_block '}'",
"Block : '{' '}'",
"BlockStatements : BlockStatement",
"BlockStatements : BlockStatements BlockStatement",
"BlockStatement : LocalVariableDeclarationStatement",
"BlockStatement : FunctionInnerClassDeclaration",
"BlockStatement : Statement",
"BlockStatement : error",
"LocalVariableDeclarationStatement : LocalVariableDeclaration ';'",
"LocalVarDeclUntilInit : Type VariableDeclaratorId",
"LocalVarDeclUntilInit : FINAL Type VariableDeclaratorId",
"LocalVarDeclUntilInit : LocalVariableDeclaration ',' VariableDeclaratorId",
"LocalVariableDeclaration : LocalVarDeclUntilInit",
"$$21 :",
"LocalVariableDeclaration : LocalVarDeclUntilInit $$21 '=' VariableInitializer",
"Statement : StatementWithoutTrailingSubstatement",
"Statement : LabeledStatement",
"Statement : IfThenStatement",
"Statement : IfThenElseStatement",
"Statement : WhileStatement",
"Statement : ForStatement",
"StatementNoShortIf : StatementWithoutTrailingSubstatement",
"StatementNoShortIf : LabeledStatementNoShortIf",
"StatementNoShortIf : IfThenElseStatementNoShortIf",
"StatementNoShortIf : WhileStatementNoShortIf",
"StatementNoShortIf : ForStatementNoShortIf",
"StatementWithoutTrailingSubstatement : Block",
"StatementWithoutTrailingSubstatement : EmptyStatement",
"StatementWithoutTrailingSubstatement : ExpressionStatement",
"StatementWithoutTrailingSubstatement : SwitchStatement",
"StatementWithoutTrailingSubstatement : DoStatement",
"StatementWithoutTrailingSubstatement : BreakStatement",
"StatementWithoutTrailingSubstatement : ContinueStatement",
"StatementWithoutTrailingSubstatement : ReturnStatement",
"StatementWithoutTrailingSubstatement : SynchronizedStatement",
"StatementWithoutTrailingSubstatement : ThrowStatement",
"StatementWithoutTrailingSubstatement : TryStatement",
"StatementWithoutTrailingSubstatement : AssertStatement",
"AssertStatement : ASSERT Expression ';'",
"AssertStatement : ASSERT Expression ':' Expression ';'",
"EmptyStatement : ';'",
"LabeledStatement : LabelDefininigIdentifier ':' Statement",
"LabeledStatementNoShortIf : LabelDefininigIdentifier ':' StatementNoShortIf",
"ExpressionStatement : StatementExpression ';'",
"StatementExpression : Assignment",
"StatementExpression : PreIncrementExpression",
"StatementExpression : PreDecrementExpression",
"StatementExpression : PostIncrementExpression",
"StatementExpression : PostDecrementExpression",
"StatementExpression : MethodInvocation",
"StatementExpression : ClassInstanceCreationExpression",
"_ncounter_ :",
"_nlabel_ :",
"_ngoto_ :",
"_nfork_ :",
"IfThenStatement : IF '(' Expression ')' _nfork_ Statement",
"IfThenElseStatementPrefix : IF '(' Expression ')' _nfork_ StatementNoShortIf ELSE _ngoto_",
"IfThenElseStatement : IfThenElseStatementPrefix Statement",
"IfThenElseStatementNoShortIf : IfThenElseStatementPrefix StatementNoShortIf",
"$$22 :",
"$$23 :",
"SwitchStatement : SWITCH '(' Expression ')' _ncounter_ $$22 $$23 SwitchBlock",
"SwitchBlock : '{' Start_block SwitchBlockStatementGroups SwitchLabels Stop_block '}'",
"SwitchBlock : '{' Start_block SwitchBlockStatementGroups Stop_block '}'",
"SwitchBlock : '{' Start_block SwitchLabels Stop_block '}'",
"SwitchBlock : '{' '}'",
"SwitchBlockStatementGroups : SwitchBlockStatementGroup",
"SwitchBlockStatementGroups : SwitchBlockStatementGroups SwitchBlockStatementGroup",
"$$24 :",
"SwitchBlockStatementGroup : SwitchLabels $$24 BlockStatements",
"SwitchLabels : SwitchLabel",
"SwitchLabels : SwitchLabels SwitchLabel",
"SwitchLabels : error",
"SwitchLabel : CASE ConstantExpression ':'",
"SwitchLabel : DEFAULT ':'",
"WhileStatementPrefix : WHILE _nlabel_ '(' Expression ')' _nfork_",
"WhileStatement : WhileStatementPrefix Statement",
"WhileStatementNoShortIf : WhileStatementPrefix StatementNoShortIf",
"$$25 :",
"$$26 :",
"$$27 :",
"DoStatement : DO _nlabel_ _ncounter_ _ncounter_ $$25 $$26 Statement WHILE $$27 '(' Expression ')' ';'",
"MaybeExpression :",
"MaybeExpression : Expression",
"ForKeyword : FOR",
"ForStatementPrefix : '(' ForInit_opt ';' _nlabel_ MaybeExpression ';' _ngoto_ _nlabel_ ForUpdate_opt ')' _nfork_",
"ForStatementBody : ForStatementPrefix Statement",
"ForStatementNoShortIfBody : ForStatementPrefix StatementNoShortIf",
"ForStatement : ForKeyword ForStatementBody",
"ForStatement : ForKeyword error",
"ForStatementNoShortIf : ForKeyword ForStatementNoShortIfBody",
"ForStatementNoShortIf : ForKeyword error",
"ForInit_opt :",
"ForInit_opt : StatementExpressionList",
"ForInit_opt : LocalVariableDeclaration",
"ForUpdate_opt :",
"ForUpdate_opt : StatementExpressionList",
"StatementExpressionList : StatementExpression",
"StatementExpressionList : StatementExpressionList ',' StatementExpression",
"BreakStatement : BREAK LabelUseIdentifier ';'",
"BreakStatement : BREAK ';'",
"ContinueStatement : CONTINUE LabelUseIdentifier ';'",
"ContinueStatement : CONTINUE ';'",
"ReturnStatement : RETURN Expression ';'",
"ReturnStatement : RETURN ';'",
"ThrowStatement : Throw Expression ';'",
"SynchronizedStatement : SYNCHRONIZED '(' Expression ')' Block",
"TryCatches : Catches",
"TryCatches : Finally",
"TryCatches : Catches Finally",
"$$28 :",
"$$29 :",
"TryStatement : Try _nfork_ $$28 Block $$29 TryCatches",
"Catches : CatchClause",
"Catches : Catches CatchClause",
"$$30 :",
"CatchClause : Catch '(' FormalParameter ')' _nfork_ Start_block $$30 Block Stop_block",
"CatchClause : Catch '(' FormalParameter ')' ';'",
"Finally : FINALLY _nfork_ Block",
"Primary : PrimaryNoNewArray",
"Primary : ArrayCreationExpression",
"PrimaryNoNewArray : Literal",
"PrimaryNoNewArray : This",
"PrimaryNoNewArray : Name '.' THIS",
"PrimaryNoNewArray : PrimitiveType '.' CLASS",
"PrimaryNoNewArray : Name '.' CLASS",
"PrimaryNoNewArray : ArrayType '.' CLASS",
"PrimaryNoNewArray : VOID '.' CLASS",
"PrimaryNoNewArray : '(' Expression ')'",
"PrimaryNoNewArray : ClassInstanceCreationExpression",
"PrimaryNoNewArray : FieldAccess",
"PrimaryNoNewArray : MethodInvocation",
"PrimaryNoNewArray : ArrayAccess",
"PrimaryNoNewArray : CompletionTypeName '.'",
"_erfs_ :",
"$$31 :",
"NestedConstructorInvocation : Primary '.' New Name _erfs_ $$31 '(' ArgumentList_opt ')'",
"$$32 :",
"NestedConstructorInvocation : Name '.' New Name _erfs_ $$32 '(' ArgumentList_opt ')'",
"NewName : Name",
"ClassInstanceCreationExpression : New _erfs_ NewName '(' ArgumentList_opt ')'",
"$$33 :",
"$$34 :",
"ClassInstanceCreationExpression : New _erfs_ NewName '(' ArgumentList_opt ')' $$33 $$34 ClassBody",
"ClassInstanceCreationExpression : NestedConstructorInvocation",
"$$35 :",
"ClassInstanceCreationExpression : NestedConstructorInvocation $$35 ClassBody",
"ClassInstanceCreationExpression : New _erfs_ CompletionConstructorName '('",
"ClassInstanceCreationExpression : Primary '.' New COMPL_CONSTRUCTOR_NAME3 '('",
"ClassInstanceCreationExpression : Name '.' New COMPL_CONSTRUCTOR_NAME2 '('",
"ArgumentList_opt :",
"ArgumentList_opt : ArgumentList",
"ArgumentList : Expression",
"ArgumentList : ArgumentList ',' Expression",
"ArgumentList : COMPL_UP_FUN_PROFILE",
"ArgumentList : ArgumentList ',' COMPL_UP_FUN_PROFILE",
"ArrayCreationExpression : New _erfs_ PrimitiveType DimExprs Dims_opt",
"ArrayCreationExpression : New _erfs_ PrimitiveType Dims ArrayInitializer",
"ArrayCreationExpression : New _erfs_ ClassOrInterfaceType DimExprs Dims_opt",
"ArrayCreationExpression : New _erfs_ ClassOrInterfaceType Dims ArrayInitializer",
"DimExprs : DimExpr",
"DimExprs : DimExprs DimExpr",
"DimExpr : '[' Expression ']'",
"Dims_opt :",
"Dims_opt : Dims",
"Dims : '[' ']'",
"Dims : Dims '[' ']'",
"FieldAccess : Primary '.' Identifier",
"FieldAccess : Super '.' Identifier",
"FieldAccess : Name '.' Super '.' Identifier",
"FieldAccess : Primary '.' COMPL_STRUCT_REC_PRIM",
"FieldAccess : Super '.' COMPL_STRUCT_REC_SUPER",
"FieldAccess : Name '.' Super '.' COMPL_QUALIF_SUPER",
"$$36 :",
"MethodInvocation : Name _erfs_ $$36 '(' ArgumentList_opt ')'",
"$$37 :",
"MethodInvocation : Primary '.' Identifier _erfs_ $$37 '(' ArgumentList_opt ')'",
"$$38 :",
"MethodInvocation : Super '.' Identifier _erfs_ $$38 '(' ArgumentList_opt ')'",
"ArrayAccess : Name '[' Expression ']'",
"ArrayAccess : PrimaryNoNewArray '[' Expression ']'",
"ArrayAccess : CompletionExpressionName '['",
"PostfixExpression : Primary",
"PostfixExpression : Name",
"PostfixExpression : PostIncrementExpression",
"PostfixExpression : PostDecrementExpression",
"PostfixExpression : CompletionExpressionName",
"PostIncrementExpression : PostfixExpression INC_OP",
"PostDecrementExpression : PostfixExpression DEC_OP",
"UnaryExpression : PreIncrementExpression",
"UnaryExpression : PreDecrementExpression",
"UnaryExpression : '+' UnaryExpression",
"UnaryExpression : '-' UnaryExpression",
"UnaryExpression : UnaryExpressionNotPlusMinus",
"PreIncrementExpression : INC_OP UnaryExpression",
"PreDecrementExpression : DEC_OP UnaryExpression",
"UnaryExpressionNotPlusMinus : PostfixExpression",
"UnaryExpressionNotPlusMinus : '~' UnaryExpression",
"UnaryExpressionNotPlusMinus : '!' UnaryExpression",
"UnaryExpressionNotPlusMinus : CastExpression",
"CastExpression : '(' ArrayType ')' UnaryExpression",
"CastExpression : '(' PrimitiveType ')' UnaryExpression",
"CastExpression : '(' Expression ')' UnaryExpressionNotPlusMinus",
"MultiplicativeExpression : UnaryExpression",
"MultiplicativeExpression : MultiplicativeExpression '*' UnaryExpression",
"MultiplicativeExpression : MultiplicativeExpression '/' UnaryExpression",
"MultiplicativeExpression : MultiplicativeExpression '%' UnaryExpression",
"AdditiveExpression : MultiplicativeExpression",
"AdditiveExpression : AdditiveExpression '+' MultiplicativeExpression",
"AdditiveExpression : AdditiveExpression '-' MultiplicativeExpression",
"ShiftExpression : AdditiveExpression",
"ShiftExpression : ShiftExpression LEFT_OP AdditiveExpression",
"ShiftExpression : ShiftExpression RIGHT_OP AdditiveExpression",
"ShiftExpression : ShiftExpression URIGHT_OP AdditiveExpression",
"RelationalExpression : ShiftExpression",
"RelationalExpression : RelationalExpression '<' ShiftExpression",
"RelationalExpression : RelationalExpression '>' ShiftExpression",
"RelationalExpression : RelationalExpression LE_OP ShiftExpression",
"RelationalExpression : RelationalExpression GE_OP ShiftExpression",
"RelationalExpression : RelationalExpression INSTANCEOF ReferenceType",
"EqualityExpression : RelationalExpression",
"EqualityExpression : EqualityExpression EQ_OP RelationalExpression",
"EqualityExpression : EqualityExpression NE_OP RelationalExpression",
"AndExpression : EqualityExpression",
"AndExpression : AndExpression '&' EqualityExpression",
"ExclusiveOrExpression : AndExpression",
"ExclusiveOrExpression : ExclusiveOrExpression '^' AndExpression",
"InclusiveOrExpression : ExclusiveOrExpression",
"InclusiveOrExpression : InclusiveOrExpression '|' ExclusiveOrExpression",
"ConditionalAndExpression : InclusiveOrExpression",
"ConditionalAndExpression : ConditionalAndExpression AND_OP InclusiveOrExpression",
"ConditionalOrExpression : ConditionalAndExpression",
"ConditionalOrExpression : ConditionalOrExpression OR_OP ConditionalAndExpression",
"ConditionalExpression : ConditionalOrExpression",
"ConditionalExpression : ConditionalOrExpression '?' Expression ':' ConditionalExpression",
"AssignmentExpression : ConditionalExpression",
"AssignmentExpression : Assignment",
"$$39 :",
"Assignment : LeftHandSide $$39 AssignmentOperator AssignmentExpression",
"LeftHandSide : Name",
"LeftHandSide : FieldAccess",
"LeftHandSide : ArrayAccess",
"LeftHandSide : CompletionExpressionName",
"AssignmentOperator : '='",
"AssignmentOperator : MUL_ASSIGN",
"AssignmentOperator : DIV_ASSIGN",
"AssignmentOperator : MOD_ASSIGN",
"AssignmentOperator : ADD_ASSIGN",
"AssignmentOperator : SUB_ASSIGN",
"AssignmentOperator : LEFT_ASSIGN",
"AssignmentOperator : RIGHT_ASSIGN",
"AssignmentOperator : URIGHT_ASSIGN",
"AssignmentOperator : AND_ASSIGN",
"AssignmentOperator : XOR_ASSIGN",
"AssignmentOperator : OR_ASSIGN",
"Expression : AssignmentExpression",
"Expression : error",
"ConstantExpression : Expression",
"Start_block :",
"Stop_block :",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
#ifndef RECURSIVE
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
int lastyystate;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#else
#include "recyacc.h"
#endif
#define yystacksize YYSTACKSIZE
#line 4371 "java_parser.y"

void javaParsingInitializations(void) {
            S_symbol *ss;
            //&javaMapDirectoryFiles2(s_javaLangName,
            //&			javaAddMapedTypeName, NULL, s_javaLangName, NULL);
            ss = javaTypeSymbolDefinition(s_javaLangObjectName,ACC_DEFAULT, TYPE_ADD_NO);
            s_javaObjectSymbol = ss;
            FILLF_typeModifiers(&s_javaObjectModifier,TypeStruct,t,ss,NULL,NULL);
            s_javaObjectModifier.u.t = ss;

            ss = javaTypeSymbolDefinition(s_javaLangStringName,ACC_DEFAULT, TYPE_ADD_NO);
            s_javaStringSymbol = ss;
            FILLF_typeModifiers(&s_javaStringModifier,TypeStruct,t,ss,NULL,NULL);
            s_javaStringModifier.u.t = ss;

            ss = javaTypeSymbolDefinition(s_javaLangClassName,ACC_DEFAULT, TYPE_ADD_NO);
            FILLF_typeModifiers(&s_javaClassModifier,TypeStruct,t,ss,NULL,NULL);
            s_javaClassModifier.u.t = ss;
            s_javaCloneableSymbol = javaTypeSymbolDefinition(s_javaLangCloneableName,ACC_DEFAULT, TYPE_ADD_NO);
            s_javaIoSerializableSymbol = javaTypeSymbolDefinition(s_javaIoSerializableName,ACC_DEFAULT, TYPE_ADD_NO);

            javaInitArrayObject();
}

static S_completionFunTab spCompletionsTab[]  = {
    { COMPL_THIS_PACKAGE_SPECIAL,	javaCompleteThisPackageName },
    { COMPL_CLASS_DEF_NAME,			javaCompleteClassDefinitionNameSpecial },
    { COMPL_FULL_INHERITED_HEADER,	javaCompleteFullInheritedMethodHeader },
    { COMPL_CONSTRUCTOR_NAME0,		javaCompleteHintForConstructSingleName },
    { COMPL_VARIABLE_NAME_HINT,		javaHintVariableName },
    { COMPL_UP_FUN_PROFILE,			javaHintCompleteMethodParameters },
    {0,NULL}
};

static S_completionFunTab completionsTab[]  = {
    { COMPL_TYPE_NAME0,				javaCompleteTypeSingleName },
    { COMPL_TYPE_NAME1,				javaCompleteTypeCompName },
    { COMPL_PACKAGE_NAME0,			javaCompletePackageSingleName },
    { COMPL_PACKAGE_NAME1,			javaCompletePackageCompName },
    { COMPL_EXPRESSION_NAME0,		javaCompleteExprSingleName },
    { COMPL_EXPRESSION_NAME1,		javaCompleteExprCompName },
    { COMPL_CONSTRUCTOR_NAME0,		javaCompleteConstructSingleName },
    { COMPL_CONSTRUCTOR_NAME1,		javaCompleteConstructCompName },
    { COMPL_CONSTRUCTOR_NAME2,		javaCompleteConstructNestNameName },
    { COMPL_CONSTRUCTOR_NAME3,		javaCompleteConstructNestPrimName },
    { COMPL_STRUCT_REC_PRIM,		javaCompleteStrRecordPrimary },
    { COMPL_STRUCT_REC_SUPER,		javaCompleteStrRecordSuper },
    { COMPL_QUALIF_SUPER,			javaCompleteStrRecordQualifiedSuper },
    { COMPL_CLASS_DEF_NAME,			javaCompleteClassDefinitionName },
    { COMPL_THIS_CONSTRUCTOR,		javaCompleteThisConstructor },
    { COMPL_SUPER_CONSTRUCTOR1,		javaCompleteSuperConstructor },
    { COMPL_SUPER_CONSTRUCTOR2,		javaCompleteSuperNestedConstructor },
    { COMPL_METHOD_NAME0,			javaCompleteUpMethodSingleName },
    { COMPL_METHOD_NAME1,			javaCompleteMethodCompName },
    {0,NULL}
};


static S_completionFunTab hintCompletionsTab[]  = {
    { COMPL_TYPE_NAME0,				javaHintCompleteNonImportedTypes },
// Finally I do not know if this is practical
//&	{ COMPL_IMPORT_SPECIAL,			javaHintImportFqt },
    {0,NULL}
};

void makeJavaCompletions(char *s, int len, S_position *pos) {
    int tok, yyn, i;
    S_cline compLine;

    log_trace("completing \"%s\" in state %d", s, lastyystate);
    strncpy(s_completions.idToProcess, s, MAX_FUN_NAME_SIZE);
    s_completions.idToProcess[MAX_FUN_NAME_SIZE-1] = 0;
    FILL_completions(&s_completions, len, *pos, 0, 0, 0, 0, 0, 0);

    /* special wizard completions */
    for (i=0;(tok=spCompletionsTab[i].token)!=0; i++) {
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            log_trace("completing %d==%s in state %d", i, s_tokenName[tok], lastyystate);
            (*spCompletionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions)
                return;
        }
    }

    /* If there is a wizard completion, RETURN now */
    if (s_completions.ai != 0 && s_opt.server_operation != OLO_SEARCH) return;
    for (i=0;(tok=completionsTab[i].token)!=0; i++) {
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            log_trace("completing %d==%s in state %d", i, s_tokenName[tok], lastyystate);
            (*completionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions)
                return;
        }
    }

    /* basic language tokens */
    for (tok=0; tok<LAST_TOKEN; tok++) {
        if (tok==IDENTIFIER) continue;
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            if (s_tokenName[tok]!= NULL) {
                if (isalpha(*s_tokenName[tok]) || *s_tokenName[tok]=='_') {
                    FILL_cline(&compLine, s_tokenName[tok], NULL, TypeKeyword,0, 0, NULL,NULL);
                    processName(s_tokenName[tok], &compLine, 0, &s_completions);
                } else {
                    /*& FILL_cline(&compLine, s_tokenName[tok], NULL, TypeToken,0, 0, NULL,NULL); */
                }
            }
        }
    }

    /* If the completion window is shown, or there is no completion,
       add also hints (should be optionally) */
    //&if (s_completions.comPrefix[0]!=0  && (s_completions.ai != 0)
    //&	&& s_opt.cxrefs != OLO_SEARCH) return;

    for (i=0;(tok=hintCompletionsTab[i].token)!=0; i++) {
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            (*hintCompletionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions)
                return;
        }
    }
}
#line 2688 "java_parser.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#define ERR_RECOVERY_ON 1
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        lastyystate = yystate;
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag == 1)  yyErrorRecovery();
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
    goto yynewerror;
yynewerror:
    yyerror("syntax error");
    goto yyerrlab;
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < ERR_RECOVERY_ON)
    {
        yyerrflag = ERR_RECOVERY_ON;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
#line 424 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 3:
#line 435 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 4:
#line 446 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeInt);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbinteger, yyvsp[0].bbinteger);
                }
            }
        }
break;
case 5:
#line 457 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeLong);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 6:
#line 468 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeFloat);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 7:
#line 479 "java_parser.y"
{
            if (regularPass()) {
                CrTypeModifier(yyval.bbexprType.d.t,TypeDouble);
                yyval.bbexprType.d.r = NULL;
                yyval.bbexprType.d.pp = &s_noPos;
                if (SyntaxPassOnly()) {PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);}
            }
        }
break;
case 8:
#line 487 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeChar);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &s_noPos;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 9:
#line 498 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = &s_javaStringModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    XX_ALLOC(yyval.bbexprType.d.pp, S_position);
                    *yyval.bbexprType.d.pp = yyvsp[0].bbposition.d;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 10:
#line 510 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeNull);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    XX_ALLOC(yyval.bbexprType.d.pp, S_position);
                    *yyval.bbexprType.d.pp = yyvsp[0].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 11:
#line 527 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbol.d = typeSpecifier1(yyvsp[0].bbunsPositionPair.d.u);
                    s_cps.lastDeclaratorType = NULL;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbunsPositionPair, yyvsp[0].bbunsPositionPair);
                }
            };
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = jslTypeSpecifier1(yyvsp[0].bbunsPositionPair.d.u);
            }
        }
break;
case 12:
#line 540 "java_parser.y"
{
            yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbol, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
        }
break;
case 14:
#line 548 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeBoolean;
            if (regularPass()) {
                SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
        }
break;
case 17:
#line 563 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeByte;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 18:
#line 568 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeShort;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 19:
#line 573 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeInt;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 20:
#line 578 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeLong;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 21:
#line 583 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeChar;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 22:
#line 591 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeFloat;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 23:
#line 596 "java_parser.y"
{
            yyval.bbunsPositionPair.d.u  = TypeDouble;
            if (regularPass()) SetPrimitiveTypePos(yyval.bbunsPositionPair.d.p, yyvsp[0].bbidIdent.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 25:
#line 605 "java_parser.y"
{
            yyval.bbsymbol.d = yyvsp[0].bbsymbolPositionPair.d.s;
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbol, yyvsp[0].bbsymbolPositionPair, yyvsp[0].bbsymbolPositionPair);
        }
break;
case 26:
#line 612 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    javaClassifyToTypeName(yyvsp[0].bbidlist.d,UsageUsed, &yyval.bbsymbol.d, USELESS_FQT_REFS_ALLOWED);
                    yyval.bbsymbol.d = javaTypeNameDefinition(yyvsp[0].bbidlist.d);
                    assert(yyval.bbsymbol.d->u.type);
                    s_cps.lastDeclaratorType = yyval.bbsymbol.d->u.type->u.t;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                }
            };
            if (inSecondJslPass()) {
                S_symbol *str;
                jslClassifyAmbiguousTypeName(yyvsp[0].bbidlist.d, &str);
                yyval.bbsymbol.d = jslTypeNameDefinition(yyvsp[0].bbidlist.d);
            }
        }
break;
case 27:
#line 629 "java_parser.y"
{ /* rule never reduced */ }
break;
case 28:
#line 634 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    javaClassifyToTypeName(yyvsp[0].bbidlist.d, USAGE_EXTEND_USAGE, &yyval.bbsymbol.d, USELESS_FQT_REFS_ALLOWED);
                    yyval.bbsymbol.d = javaTypeNameDefinition(yyvsp[0].bbidlist.d);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                }
            };
            if (inSecondJslPass()) {
                S_symbol *str;
                jslClassifyAmbiguousTypeName(yyvsp[0].bbidlist.d, &str);
                yyval.bbsymbol.d = jslTypeNameDefinition(yyvsp[0].bbidlist.d);
            }
        }
break;
case 29:
#line 649 "java_parser.y"
{ /* rule never reduced */ }
break;
case 32:
#line 661 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbolPositionPair.d.s = typeSpecifier1(yyvsp[-2].bbunsPositionPair.d.u);
                    yyval.bbsymbolPositionPair.d.s->u.type = prependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
                } else {
                    PropagateBorns(yyval.bbsymbolPositionPair, yyvsp[-2].bbunsPositionPair, yyvsp[0].bbposition);
                }
                yyval.bbsymbolPositionPair.d.p = yyvsp[-2].bbunsPositionPair.d.p;
                s_cps.lastDeclaratorType = NULL;
            };
            if (inSecondJslPass()) {
                yyval.bbsymbolPositionPair.d.s = jslTypeSpecifier1(yyvsp[-2].bbunsPositionPair.d.u);
                yyval.bbsymbolPositionPair.d.s->u.type = jslPrependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
            }
        }
break;
case 33:
#line 677 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    javaClassifyToTypeName(yyvsp[-2].bbidlist.d,UsageUsed, &(yyval.bbsymbolPositionPair.d.s), USELESS_FQT_REFS_ALLOWED);
                    yyval.bbsymbolPositionPair.d.s = javaTypeNameDefinition(yyvsp[-2].bbidlist.d);
                    assert(yyval.bbsymbolPositionPair.d.s && yyval.bbsymbolPositionPair.d.s->u.type);
                    s_cps.lastDeclaratorType = yyval.bbsymbolPositionPair.d.s->u.type->u.t;
                    yyval.bbsymbolPositionPair.d.s->u.type = prependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
                } else {
                    PropagateBorns(yyval.bbsymbolPositionPair, yyvsp[-2].bbidlist, yyvsp[0].bbposition);
                }
                yyval.bbsymbolPositionPair.d.p = javaGetNameStartingPosition(yyvsp[-2].bbidlist.d);
            };
            if (inSecondJslPass()) {
                S_symbol *ss;
                jslClassifyAmbiguousTypeName(yyvsp[-2].bbidlist.d, &ss);
                yyval.bbsymbolPositionPair.d.s = jslTypeNameDefinition(yyvsp[-2].bbidlist.d);
                yyval.bbsymbolPositionPair.d.s->u.type = jslPrependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
            }
        }
break;
case 34:
#line 697 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbsymbolPositionPair.d = yyvsp[-2].bbsymbolPositionPair.d;
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbolPositionPair.d.s->u.type = prependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
                } else {
                    PropagateBorns(yyval.bbsymbolPositionPair, yyvsp[-2].bbsymbolPositionPair, yyvsp[0].bbposition);
                }
            };
            if (inSecondJslPass()) {
                yyval.bbsymbolPositionPair.d = yyvsp[-2].bbsymbolPositionPair.d;
                yyval.bbsymbolPositionPair.d.s->u.type = jslPrependComposedType(yyval.bbsymbolPositionPair.d.s->u.type, TypeArray);
            }
        }
break;
case 35:
#line 711 "java_parser.y"
{ /* rule never used */ }
break;
case 36:
#line 716 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 37:
#line 720 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 38:
#line 724 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 39:
#line 728 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 40:
#line 732 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 41:
#line 736 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 42:
#line 740 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 43:
#line 744 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 44:
#line 748 "java_parser.y"
{
                if (regularPass()) AllocIdCopy(yyval.bbidIdent.d,yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbidIdent, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
break;
case 45:
#line 755 "java_parser.y"
{
            yyval.bbidlist.d = yyvsp[0].bbidlist.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(s_javaStat);
                    s_javaStat->lastParsedName = yyvsp[0].bbidlist.d;
                } else {
                    PropagateBorns(yyval.bbidlist, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                    javaCheckForPrimaryStart(&yyvsp[0].bbidlist.d->idi.p, &yyvsp[0].bbidlist.d->idi.p);
                    javaCheckForStaticPrefixStart(&yyvsp[0].bbidlist.d->idi.p, &yyvsp[0].bbidlist.d->idi.p);
                }
            };
        }
break;
case 46:
#line 768 "java_parser.y"
{
            yyval.bbidlist.d = yyvsp[0].bbidlist.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(s_javaStat);
                    s_javaStat->lastParsedName = yyvsp[0].bbidlist.d;
                } else {
                    PropagateBorns(yyval.bbidlist, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                    javaCheckForPrimaryStartInNameList(yyvsp[0].bbidlist.d, javaGetNameStartingPosition(yyvsp[0].bbidlist.d));
                    javaCheckForStaticPrefixInNameList(yyvsp[0].bbidlist.d, javaGetNameStartingPosition(yyvsp[0].bbidlist.d));
                }
            };
        }
break;
case 47:
#line 784 "java_parser.y"
{
            yyval.bbidlist.d = StackMemAlloc(S_idIdentList);
            FILL_idIdentList(yyval.bbidlist.d, *yyvsp[0].bbidIdent.d, yyvsp[0].bbidIdent.d->name, TypeDefault, NULL);
            PropagateBornsIfRegularSyntaxPass(yyval.bbidlist, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
        }
break;
case 48:
#line 792 "java_parser.y"
{
            yyval.bbidlist.d = StackMemAlloc(S_idIdentList);
            FILL_idIdentList(yyval.bbidlist.d, *yyvsp[0].bbidIdent.d, yyvsp[0].bbidIdent.d->name, TypeDefault, yyvsp[-2].bbidlist.d);
            PropagateBornsIfRegularSyntaxPass(yyval.bbidlist, yyvsp[-2].bbidlist, yyvsp[0].bbidIdent);
        }
break;
case 59:
#line 834 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    labelReference(yyvsp[0].bbidIdent.d,UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
                }
            };
        }
break;
case 60:
#line 843 "java_parser.y"
{ assert(0); /* token never used */ }
break;
case 61:
#line 847 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    labelReference(yyvsp[0].bbidIdent.d,UsageUsed);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
                }
            };
        }
break;
case 62:
#line 856 "java_parser.y"
{ assert(0); /* token never used */ }
break;
case 63:
#line 861 "java_parser.y"
{
            if (regularPass()) {
                assert(s_javaStat);
                *s_javaStat = s_initJavaStat;
                s_javaThisPackageName = "";      /* preset for case if copied somewhere*/
            };
        }
break;
case 64:
#line 867 "java_parser.y"
{
            if (regularPass()) {
                if (yyvsp[0].bbidlist.d == NULL) {	/* anonymous package */
                    s_javaThisPackageName = "";
                } else {
                    javaClassifyToPackageName(yyvsp[0].bbidlist.d);
                    s_javaThisPackageName = javaCreateComposedName(NULL,yyvsp[0].bbidlist.d,'/',
                                                                   NULL,NULL,0);
                }
                s_javaStat->currentPackage = s_javaThisPackageName;
                if (! SyntaxPassOnly()) {

                    int             i,j,packlen;
                    char            *cdir, *fname;
                    S_jslTypeTab	*jsltypeTab;
                    struct stat     st;
                    /* it is important to know the package before everything*/
                    /* else, as it must be set on class adding in order to set*/
                    /* isinCurrentPackage field. !!!!!!!!!!!!!!!!*/
                    /* this may be problem for CACHING !!!!*/
                    if (yyvsp[0].bbidlist.d == NULL) {	/* anonymous package */
                        s_javaStat->className = NULL;
                        for(i=0,j=0; cFile.fileName[i]; i++) {
                            if (cFile.fileName[i] == SLASH) j=i;
                        }
                        XX_ALLOCC(cdir, j+1, char);  /* I prefer this*/
                        /*&SM_ALLOCC(ftMemory, cdir, j+1, char);  // will exhauste ftmemory*/
                        strncpy(cdir,cFile.fileName,j); cdir[j]=0;
                        s_javaStat->unNamedPackageDir = cdir;
                        javaCheckIfPackageDirectoryIsInClassOrSourcePath(cdir);
                    } else {
                        javaAddPackageDefinition(yyvsp[0].bbidlist.d);
                        s_javaStat->className = yyvsp[0].bbidlist.d;
                        for(i=0,j=0; cFile.fileName[i]; i++) {
                            if (cFile.fileName[i] == SLASH) j=i;
                        }
                        packlen = strlen(s_javaThisPackageName);
                        if (j>packlen && fnnCmp(s_javaThisPackageName,&cFile.fileName[j-packlen],packlen)==0){
                            XX_ALLOCC(cdir, j-packlen, char); /* I prefer this*/
                            /*&SM_ALLOCC(ftMemory, cdir, j-packlen, char);  // will exhauste ftmemory*/
                            strncpy(cdir, cFile.fileName, j-packlen-1); cdir[j-packlen-1]=0;
                            s_javaStat->namedPackageDir = cdir;
                            s_javaStat->currentPackage = "";
                            javaCheckIfPackageDirectoryIsInClassOrSourcePath(cdir);
                        } else {
                            if (s_opt.taskRegime != RegimeEditServer) {
                                warning(ERR_ST, "package name does not match directory name");
                            }
                        }
                    }
                    javaParsingInitializations();
                    /* make first and second pass through file*/
                    assert(s_jsl == NULL); /* no nesting*/
                    XX_ALLOC(jsltypeTab, S_jslTypeTab);
                    jslTypeTabInit(jsltypeTab, MAX_JSL_SYMBOLS);
                    javaReadSymbolFromSourceFileInit(s_olOriginalFileNumber,
                                                     jsltypeTab);

                    fname = s_fileTab.tab[s_olOriginalFileNumber]->name;
#if 1 /*I_DO_NOT_KNOW, to take also symbols from lastly saved file???*/
                    if (s_opt.taskRegime == RegimeEditServer
                        && s_ropt.refactoringRegime!=RegimeRefactory) {
                        /* this must be before reading 's_olOriginalComFile' !!!*/
                        if (statb(fname, &st)==0) {
                            javaReadSymbolsFromSourceFileNoFreeing(fname, fname);
                        }
                    }
#endif
                    /* this must be last reading of this class before parsing*/
                    if (statb(s_fileTab.tab[s_olOriginalComFileNumber]->name, &st)==0) {
                        javaReadSymbolsFromSourceFileNoFreeing(
                            s_fileTab.tab[s_olOriginalComFileNumber]->name, fname);
                    }

                    javaReadSymbolFromSourceFileEnd();
                    javaAddJslReadedTopLevelClasses(jsltypeTab);
                    assert(s_jsl == NULL);
                }
                /* -----------------------------------------------*/
            } else {
                /* -----------------------------------------------*/
                /* jsl pass initialisation*/
                char            *pname;
                S_jslClassStat  *ss;
                char			ppp[MAX_FILE_NAME_SIZE];
                s_jsl->waitList = NULL;
                if (yyvsp[0].bbidlist.d != NULL) {
                    javaClassifyToPackageName(yyvsp[0].bbidlist.d);
                }
                javaCreateComposedName(NULL,yyvsp[0].bbidlist.d,'/',NULL,ppp,MAX_FILE_NAME_SIZE);
                XX_ALLOCC(pname, strlen(ppp)+1, char);
                strcpy(pname, ppp);
                XX_ALLOC(ss, S_jslClassStat);
                FILL_jslClassStat(ss, yyvsp[0].bbidlist.d, NULL, pname, 0, 0, NULL);
                s_jsl->classStat = ss;
                if (inSecondJslPass()) {
                    char        cdir[MAX_FILE_NAME_SIZE];
                    int         i;
                    int			j;
                    /* add this package types */
                    if (yyvsp[0].bbidlist.d == NULL) {	/* anonymous package */
                        for(i=0,j=0; cFile.fileName[i]; i++) {
                            if (cFile.fileName[i] == SLASH) j=i;
                        }
                        strncpy(cdir,cFile.fileName,j);
                        cdir[j]=0;
                        mapDirectoryFiles(cdir,
                                    jslAddMapedImportTypeName,ALLOW_EDITOR_FILES, "",
                                    "", NULL, NULL, NULL);
                        /* why this is there, it makes problem when moving a class*/
                        /* it stays in fileTab and there is a clash!*/
                        /* [2/8/2003] Maybe I should put it out*/
                        jslAddAllPackageClassesFromFileTab(NULL);
                    } else {
                        javaMapDirectoryFiles2(yyvsp[0].bbidlist.d,jslAddMapedImportTypeName,
                                                NULL,yyvsp[0].bbidlist.d,NULL);
                        /* why this is there, it makes problem when moving a class*/
                        /* it stays in fileTab and there is a clash!*/
                        /* [2/8/2003] Maybe I should put it out*/
                        jslAddAllPackageClassesFromFileTab(yyvsp[0].bbidlist.d);
                    }
                    /* add java/lang package types */
                    javaMapDirectoryFiles2(s_javaLangName,
                            jslAddMapedImportTypeName, NULL, s_javaLangName, NULL);
                }
/*&fprintf(dumpOut," [jsl] current package == '%s'\n", pname);&*/
            }
        }
break;
case 65:
#line 994 "java_parser.y"
{
            if (regularPass()) {
                /* add this package types after imports! */
            } else {
                /* jsl pass initialisation*/
                /* there were original this package types add, but now this is
                   a useless semantic action */
            }
        }
break;
case 68:
#line 1007 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 70:
#line 1014 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
            if (inSecondJslPass()) {
                JslImportSingleDeclaration(yyvsp[0].bbidlist.d);
            }
        }
break;
case 71:
#line 1020 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
            if (inSecondJslPass()) {
                JslImportOnDemandDeclaration(yyvsp[0].bbidlist.d);
            }
        }
break;
case 72:
#line 1026 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbidlist);
            if (inSecondJslPass()) {
                JslImportSingleDeclaration(yyvsp[0].bbidlist.d);
            }
        }
break;
case 73:
#line 1032 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbidlist);
            if (inSecondJslPass()) {
                JslImportOnDemandDeclaration(yyvsp[0].bbidlist.d);
            }
        }
break;
case 74:
#line 1055 "java_parser.y"
{
            yyval.bbidlist.d = yyvsp[-1].bbidlist.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_reference *lastUselessRef;
                    S_symbol *str;
                    /* it was type or packege, but I thing this would be better*/
                    lastUselessRef = javaClassifyToTypeName(yyvsp[-1].bbidlist.d, UsageUsed, &str, USELESS_FQT_REFS_DISALLOWED);
                    /* last useless reference is not useless here!*/
                    if (lastUselessRef!=NULL) lastUselessRef->usg = s_noUsage;
                    s_cps.lastImportLine = yyvsp[-2].bbidIdent.d->p.line;
                    if (yyvsp[-1].bbidlist.d->next!=NULL) {
                        javaAddImportConstructionReference(&yyvsp[-1].bbidlist.d->next->idi.p, &yyvsp[-2].bbidIdent.d->p, UsageDefined);
                    }
                } else {
                    PropagateBorns(yyval.bbidlist, yyvsp[-2].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 75:
#line 1074 "java_parser.y"
{ /* rule never used */ }
break;
case 76:
#line 1075 "java_parser.y"
{ /* rule never used */ }
break;
case 77:
#line 1079 "java_parser.y"
{
            yyval.bbidlist.d = yyvsp[-3].bbidlist.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *str;
                    S_typeModifiers *expr;
                    S_reference *rr, *lastUselessRef;
                    int st __attribute__((unused));
                    st = javaClassifyAmbiguousName(yyvsp[-3].bbidlist.d, NULL,&str,&expr,&rr,
                                                   &lastUselessRef, USELESS_FQT_REFS_DISALLOWED,
                                                   CLASS_TO_TYPE,UsageUsed);
                    if (lastUselessRef!=NULL) lastUselessRef->usg = s_noUsage;
                    s_cps.lastImportLine = yyvsp[-4].bbidIdent.d->p.line;
                    javaAddImportConstructionReference(&yyvsp[-3].bbidlist.d->idi.p, &yyvsp[-4].bbidIdent.d->p, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbidlist, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 78:
#line 1098 "java_parser.y"
{ /* rule never used */ }
break;
case 79:
#line 1101 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 80:
#line 1104 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[-1].bbposition);
        }
break;
case 81:
#line 1110 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 82:
#line 1113 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 83:
#line 1118 "java_parser.y"
{
            yyval.bbidlist.d = NULL;
            if (regularPass()) {
                s_cps.lastImportLine = 0;
                SetNullBorns(yyval.bbidlist);
            }
        }
break;
case 84:
#line 1125 "java_parser.y"
{
            yyval.bbidlist.d = yyvsp[-1].bbidlist.d;
            if (regularPass()) {
                s_cps.lastImportLine = yyvsp[-2].bbidIdent.d->p.line;
                PropagateBornsIfRegularSyntaxPass(yyval.bbidlist, yyvsp[-2].bbidIdent, yyvsp[0].bbposition);
            }
        }
break;
case 85:
#line 1132 "java_parser.y"
{
            yyval.bbidlist.d = NULL;
            if (regularPass()) {
                s_cps.lastImportLine = yyvsp[-1].bbidIdent.d->p.line;
                PropagateBornsIfRegularSyntaxPass(yyval.bbidlist, yyvsp[-1].bbidIdent, yyvsp[-1].bbidIdent);
            }
        }
break;
case 86:
#line 1139 "java_parser.y"
{ /* rule never used */ }
break;
case 87:
#line 1140 "java_parser.y"
{ /* rule never used */ }
break;
case 88:
#line 1144 "java_parser.y"
{
            if (regularPass()) {
                javaSetClassSourceInformation(s_javaThisPackageName, yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
        }
break;
case 89:
#line 1150 "java_parser.y"
{
            if (regularPass()) {
                javaSetClassSourceInformation(s_javaThisPackageName, yyvsp[0].bbidIdent.d);
                PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
            }
        }
break;
case 90:
#line 1156 "java_parser.y"
{}
break;
case 91:
#line 1157 "java_parser.y"
{}
break;
case 92:
#line 1162 "java_parser.y"
{
            yyval.bbunsign.d = ACC_DEFAULT;
            SetNullBorns(yyval.bbunsign);
        }
break;
case 93:
#line 1166 "java_parser.y"
{
            yyval.bbunsign.d = yyvsp[0].bbunsign.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbunsign, yyvsp[0].bbunsign);
        }
break;
case 95:
#line 1174 "java_parser.y"
{
            yyval.bbunsign.d = yyvsp[-1].bbunsign.d | yyvsp[0].bbunsign.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[-1].bbunsign, yyvsp[0].bbunsign);
        }
break;
case 96:
#line 1181 "java_parser.y"
{ yyval.bbunsign.d = ACC_PUBLIC; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 97:
#line 1182 "java_parser.y"
{ yyval.bbunsign.d = ACC_PROTECTED; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 98:
#line 1183 "java_parser.y"
{ yyval.bbunsign.d = ACC_PRIVATE; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 99:
#line 1184 "java_parser.y"
{ yyval.bbunsign.d = ACC_STATIC; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 100:
#line 1185 "java_parser.y"
{ yyval.bbunsign.d = ACC_ABSTRACT; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 101:
#line 1186 "java_parser.y"
{ yyval.bbunsign.d = ACC_FINAL; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 102:
#line 1187 "java_parser.y"
{ yyval.bbunsign.d = ACC_NATIVE; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 103:
#line 1188 "java_parser.y"
{ yyval.bbunsign.d = ACC_SYNCHRONIZED; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 104:
#line 1189 "java_parser.y"
{ yyval.bbunsign.d = 0; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 105:
#line 1190 "java_parser.y"
{ yyval.bbunsign.d = ACC_TRANSIENT; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 106:
#line 1191 "java_parser.y"
{ yyval.bbunsign.d = 0; PropagateBornsIfRegularSyntaxPass(yyval.bbunsign, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 108:
#line 1222 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail = newClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL);
                    }
                } else {
                    jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL, CPOS_ST);
                    jslAddDefaultConstructor(s_jsl->classStat->thisClass);
                }
            }
break;
case 109:
#line 1231 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaAddSuperNestedClassToSymbolTab(s_javaStat->thisClass);
                    }
                } else {
                    jslAddSuperNestedClassesToJslTypeTab(s_jsl->classStat->thisClass);
                }
            }
break;
case 110:
#line 1239 "java_parser.y"
{
                if (regularPass()) {
                    yyval.bbidIdent.d = yyvsp[-5].bbidIdent.d;
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-4].trail);
                    } else {
                        PropagateBorns(yyval.bbidIdent, yyvsp[-7].bbunsign, yyvsp[0].bbposition);
                        if (yyval.bbidIdent.b.file == s_noneFileIndex) PropagateBorns(yyval.bbidIdent, yyvsp[-6].bbidIdent, yyval.bbidIdent);
                        if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbidIdent.b, s_cxRefPos, yyval.bbidIdent.e)
                            && s_spp[SPP_CLASS_DECLARATION_BEGIN_POSITION].file == s_noneFileIndex) {
                            s_spp[SPP_CLASS_DECLARATION_BEGIN_POSITION] = yyval.bbidIdent.b;
                            s_spp[SPP_CLASS_DECLARATION_TYPE_BEGIN_POSITION] = yyvsp[-6].bbidIdent.b;
                            s_spp[SPP_CLASS_DECLARATION_TYPE_END_POSITION] = yyvsp[-6].bbidIdent.e;
                            s_spp[SPP_CLASS_DECLARATION_END_POSITION] = yyval.bbidIdent.e;
                        }
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
            }
break;
case 111:
#line 1260 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail = newClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL);
                    }
                } else {
                    jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL, CPOS_ST);
                }
            }
break;
case 112:
#line 1270 "java_parser.y"
{
                if (regularPass()) {
                    yyval.bbidIdent.d = yyvsp[-3].bbidIdent.d;
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-2].trail);
                    } else {
                        PropagateBorns(yyval.bbidIdent, yyvsp[-5].bbunsign, yyvsp[0].bbposition);
                        if (yyval.bbidIdent.b.file == s_noneFileIndex) PropagateBorns(yyval.bbidIdent, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
            }
break;
case 113:
#line 1283 "java_parser.y"
{ /* never used */ }
break;
case 114:
#line 1288 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail = newClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL);
                    }
                } else {
                    jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL, CPOS_FUNCTION_INNER);
                }
            }
break;
case 115:
#line 1296 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaAddSuperNestedClassToSymbolTab(s_javaStat->thisClass);
                    }
                } else {
                    jslAddSuperNestedClassesToJslTypeTab(s_jsl->classStat->thisClass);
                }
            }
break;
case 116:
#line 1304 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-4].trail);
                    } else {
                        PropagateBorns(yyval.bbposition, yyvsp[-7].bbunsign, yyvsp[0].bbposition);
                        if (yyval.bbposition.b.file == s_noneFileIndex) PropagateBorns(yyval.bbposition, yyvsp[-6].bbidIdent, yyvsp[0].bbposition);
                        if (POSITION_EQ(s_cxRefPos, yyvsp[-5].bbidIdent.d->p)) {
                            s_spp[SPP_CLASS_DECLARATION_BEGIN_POSITION] = yyval.bbposition.b;
                            s_spp[SPP_CLASS_DECLARATION_END_POSITION] = yyval.bbposition.e;
                        }
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
            }
break;
case 117:
#line 1321 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail = newClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL);
                    }
                } else {
                    jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, yyvsp[-2].bbunsign.d, NULL, CPOS_FUNCTION_INNER);
                }
            }
break;
case 118:
#line 1331 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-2].trail);
                    } else {
                        PropagateBorns(yyval.bbposition, yyvsp[-5].bbunsign, yyvsp[0].bbposition);
                        if (yyval.bbposition.b.file == s_noneFileIndex) PropagateBorns(yyval.bbposition, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
            }
break;
case 119:
#line 1343 "java_parser.y"
{ /* never used */ }
break;
case 120:
#line 1349 "java_parser.y"
{
            if (inSecondJslPass()) {
                if (strcmp(s_jsl->classStat->thisClass->linkName,
                            s_javaLangObjectLinkName)!=0) {
                    /* add to any except java/lang/Object itself*/
                    jslAddSuperClassOrInterfaceByName(
                        s_jsl->classStat->thisClass, s_javaLangObjectLinkName);
                }
            }
            SetNullBorns(yyval.bbposition);
        }
break;
case 121:
#line 1360 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                    assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                    javaParsedSuperClass(yyvsp[0].bbsymbol.d->u.type->u.t);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                jslAddSuperClassOrInterface(s_jsl->classStat->thisClass,
                                            yyvsp[0].bbsymbol.d->u.type->u.t);
            }
        }
break;
case 122:
#line 1379 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 123:
#line 1382 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 124:
#line 1388 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                    assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                    javaParsedSuperClass(yyvsp[0].bbsymbol.d->u.type->u.t);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                jslAddSuperClassOrInterface(s_jsl->classStat->thisClass,
                                            yyvsp[0].bbsymbol.d->u.type->u.t);
            }
        }
break;
case 125:
#line 1405 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                    assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                    javaParsedSuperClass(yyvsp[0].bbsymbol.d->u.type->u.t);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                jslAddSuperClassOrInterface(s_jsl->classStat->thisClass,
                                            yyvsp[0].bbsymbol.d->u.type->u.t);
            }
        }
break;
case 126:
#line 1424 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    /* TODO, REDO all this stuff around class/method borns !!!!!!*/
                    if (s_opt.taskRegime == RegimeEditServer) {
                        if (s_cp.parserPassedMarker && !s_cp.thisMethodMemoriesStored){
                            s_cps.cxMemiAtMethodBeginning = s_cp.cxMemiAtFunBegin;
                            s_cps.cxMemiAtMethodEnd = cxMemory->i;
/*&sprintf(tmpBuff,"setting %s, %d,%d   %d,%d", olcxOptionsName[s_opt.server_operation], s_cp.parserPassedMarker, s_cp.thisMethodMemoriesStored, s_cps.cxMemiAtMethodBeginning,s_cps.cxMemiAtMethodEnd),ppcGenRecord(PPC_BOTTOM_INFORMATION,tmpBuff,"\n");*/
                            s_cp.thisMethodMemoriesStored = 1;
                            if (s_opt.server_operation == OLO_MAYBE_THIS) {
                                changeMethodReferencesUsages(LINK_NAME_MAYBE_THIS_ITEM,
                                                             CatLocal, cFile.lb.buffer.fileNumber,
                                                             s_javaStat->thisClass);
                            } else if (s_opt.server_operation == OLO_NOT_FQT_REFS) {
                                changeMethodReferencesUsages(LINK_NAME_NOT_FQT_ITEM,
                                                             CatLocal,cFile.lb.buffer.fileNumber,
                                                             s_javaStat->thisClass);
                            } else if (s_opt.server_operation == OLO_USELESS_LONG_NAME) {
                                changeMethodReferencesUsages(LINK_NAME_IMPORTED_QUALIFIED_ITEM,
                                                             CatGlobal,cFile.lb.buffer.fileNumber,
                                                             s_javaStat->thisClass);
                            }
                            s_cps.cxMemiAtClassBeginning = s_cp.cxMemiAtClassBegin;
                            s_cps.cxMemiAtClassEnd = cxMemory->i;
                            s_cps.classCoordEndLine = cFile.lineNumber+1;
/*&fprintf(dumpOut,"!setting class end line to %d, cb==%d, ce==%d\n", s_cps.classCoordEndLine, s_cps.cxMemiAtClassBeginning, s_cps.cxMemiAtClassEnd);*/
                            if (s_opt.server_operation == OLO_NOT_FQT_REFS_IN_CLASS) {
                                changeClassReferencesUsages(LINK_NAME_NOT_FQT_ITEM,
                                                            CatLocal,cFile.lb.buffer.fileNumber,
                                                            s_javaStat->thisClass);
                            } else if (s_opt.server_operation == OLO_USELESS_LONG_NAME_IN_CLASS) {
                                changeClassReferencesUsages(LINK_NAME_IMPORTED_QUALIFIED_ITEM,
                                                            CatGlobal,cFile.lb.buffer.fileNumber,
                                                            s_javaStat->thisClass);
                            }
                        }
                    }
                    s_cp.cxMemiAtClassBegin = cxMemory->i;
/*&fprintf(dumpOut,"!setting class begin memory %d\n", s_cp.cxMemiAtClassBegin);*/
                    actionsBeforeAfterExternalDefinition();
                }
            }
        }
break;
case 127:
#line 1471 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 128:
#line 1474 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-3].bbposition, yyvsp[0].bbposition);
        }
break;
case 129:
#line 1480 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 130:
#line 1483 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 135:
#line 1493 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 136:
#line 1497 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);}
break;
case 137:
#line 1498 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);}
break;
case 138:
#line 1499 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);}
break;
case 139:
#line 1500 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 140:
#line 1506 "java_parser.y"
{
            yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cps.lastAssignementStruct = yyvsp[0].bbsymbol.d;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
    }
break;
case 141:
#line 1519 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *p,*pp,*memb,*clas;
                    int vClass;
                    S_recFindStr    rfs;
                    s_cps.lastAssignementStruct = NULL;
                    clas = s_javaStat->thisClass;
                    assert(clas != NULL);
                    for(p=yyvsp[-1].bbsymbol.d; p!=NULL; p=pp) {
                        pp = p->next;
                        p->next = NULL;
                        if (p->bits.symType == TypeError) continue;
                        assert(p->bits.symType == TypeDefault);
                        completeDeclarator(yyvsp[-2].bbsymbol.d, p);
                        vClass = s_javaStat->classFileInd;
                        p->bits.accessFlags = yyvsp[-3].bbunsign.d;
                        p->bits.storage = StorageField;
                        if (clas->bits.accessFlags&ACC_INTERFACE) {
                            /* set interface default access flags*/
                            p->bits.accessFlags |= (ACC_PUBLIC | ACC_STATIC | ACC_FINAL);
                        }
                        /*&javaSetFieldLinkName(p);*/
                        iniFind(clas, &rfs);
                        if (findStrRecordSym(&rfs, p->name, &memb, CLASS_TO_ANY,
                                             ACC_CHECK_NO,VISIB_CHECK_NO) == RETURN_NOT_FOUND) {
                            assert(clas->u.s);
                            LIST_APPEND(S_symbol, clas->u.s->records, p);
                        }
                        addCxReference(p, &p->pos, UsageDefined, vClass, vClass);
                        htmlAddJavaDocReference(p, &p->pos, vClass, vClass);
                    }
                    yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                    if (s_opt.taskRegime == RegimeEditServer
                        && s_cp.parserPassedMarker
                        && !s_cp.thisMethodMemoriesStored){
                        s_cps.methodCoordEndLine = cFile.lineNumber+1;
                    }
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-3].bbunsign, yyvsp[0].bbposition);
                    if (yyval.bbsymbol.b.file == s_noneFileIndex) PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbposition);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbsymbol.b, s_cxRefPos, yyval.bbsymbol.e)
                        && s_spp[SPP_FIELD_DECLARATION_BEGIN_POSITION].file==s_noneFileIndex) {
                        s_spp[SPP_FIELD_DECLARATION_BEGIN_POSITION] = yyval.bbsymbol.b;
                        s_spp[SPP_FIELD_DECLARATION_TYPE_BEGIN_POSITION] = yyvsp[-2].bbsymbol.b;
                        s_spp[SPP_FIELD_DECLARATION_TYPE_END_POSITION] = yyvsp[-2].bbsymbol.e;
                        s_spp[SPP_FIELD_DECLARATION_END_POSITION] = yyval.bbsymbol.e;
                    }
                }
            }
            if (inSecondJslPass()) {
                S_symbol *p;
                S_symbol *pp;
                S_symbol *clas;
                int		vClass;
                clas = s_jsl->classStat->thisClass;
                assert(clas != NULL);
                for(p=yyvsp[-1].bbsymbol.d; p!=NULL; p=pp) {
                    pp = p->next;
                    p->next = NULL;
                    if (p->bits.symType == TypeError) continue;
                    assert(p->bits.symType == TypeDefault);
                    assert(clas->u.s);
                    vClass = clas->u.s->classFile;
                    jslCompleteDeclarator(yyvsp[-2].bbsymbol.d, p);
                    p->bits.accessFlags = yyvsp[-3].bbunsign.d;
                    p->bits.storage = StorageField;
                    if (clas->bits.accessFlags&ACC_INTERFACE) {
                        /* set interface default access flags*/
                        p->bits.accessFlags |= (ACC_PUBLIC|ACC_STATIC|ACC_FINAL);
                    }
                    log_debug("[jsl] adding field %s to %s\n",
                              p->name,clas->linkName);
                    LIST_APPEND(S_symbol, clas->u.s->records, p);
                    assert(vClass!=s_noneFileIndex);
                    if (p->pos.file!=s_olOriginalFileNumber && s_opt.server_operation==OLO_PUSH) {
                        /* pre load of saved file akes problem on move field/method, ...*/
                        addCxReference(p, &p->pos, UsageDefined, vClass, vClass);
                    }
                }
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
            }
        }
break;
case 142:
#line 1605 "java_parser.y"
{
            yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyval.bbsymbol.d->bits.symType == TypeDefault || yyval.bbsymbol.d->bits.symType == TypeError);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
        }
break;
case 143:
#line 1615 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[-2].bbsymbol.d && yyvsp[0].bbsymbol.d);
                    if (yyvsp[0].bbsymbol.d->bits.storage == StorageError) {
                        yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                    } else {
                        yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                        yyval.bbsymbol.d->next = yyvsp[-2].bbsymbol.d;
                    }
                    assert(yyval.bbsymbol.d->bits.symType == TypeDefault || yyval.bbsymbol.d->bits.symType == TypeError);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[-2].bbsymbol.d && yyvsp[0].bbsymbol.d);
                if (yyvsp[0].bbsymbol.d->bits.storage == StorageError) {
                    yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                } else {
                    yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                    yyval.bbsymbol.d->next = yyvsp[-2].bbsymbol.d;
                }
                assert(yyval.bbsymbol.d->bits.symType==TypeDefault || yyval.bbsymbol.d->bits.symType==TypeError);
            }
        }
break;
case 145:
#line 1645 "java_parser.y"
{
            yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbexprType);
        }
break;
case 146:
#line 1649 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    XX_ALLOC(yyval.bbsymbol.d, S_symbol);
                    *yyval.bbsymbol.d = s_errorSymbol;
                } else {
                    SetNullBorns(yyval.bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                CF_ALLOC(yyval.bbsymbol.d, S_symbol);
                *yyval.bbsymbol.d = s_errorSymbol;
            }
        }
break;
case 147:
#line 1666 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    /*& $$.d = StackMemAlloc(S_symbol); */
                    /*& FILL_symbolBits(&$$.d->bits,0,0,0,0,0,TypeDefault,StorageDefault,0); */
                    /*& FILL_symbol($$.d,$1.d->name,$1.d->name,$1.d->p,$$.d->bits,type,NULL,NULL); */
                    /*& REPLACED StackMemAlloc()+FILL_symbol() with: */
                    yyval.bbsymbol.d = newSymbol(yyvsp[0].bbidIdent.d->name, yyvsp[0].bbidIdent.d->name, yyvsp[0].bbidIdent.d->p);
                    FILL_symbolBits(&yyval.bbsymbol.d->bits, 0, 0, 0, 0, 0, TypeDefault, StorageDefault, 0);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
                }
            }
            if (inSecondJslPass()) {
                char *name;
                CF_ALLOCC(name, strlen(yyvsp[0].bbidIdent.d->name)+1, char);
                strcpy(name, yyvsp[0].bbidIdent.d->name);
                CF_ALLOC(yyval.bbsymbol.d, S_symbol);
                fillSymbol(yyval.bbsymbol.d, name, name, yyvsp[0].bbidIdent.d->p);
                FILL_symbolBits(&yyval.bbsymbol.d->bits, 0, 0, 0, 0, 0, TypeDefault, StorageDefault, 0);
            }
        }
break;
case 148:
#line 1688 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[-2].bbsymbol.d);
                    yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                    AddComposedType(yyval.bbsymbol.d, TypeArray);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbposition);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[-2].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                JslAddComposedType(yyval.bbsymbol.d, TypeArray);
            }
        }
break;
case 149:
#line 1704 "java_parser.y"
{/* rule never used */}
break;
case 152:
#line 1716 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaMethodBodyBeginning(yyvsp[-1].bbsymbol.d);
                    }
                }
            }
break;
case 153:
#line 1724 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaMethodBodyEnding(&yyvsp[-1].bbposition.d);
                    } else {
                        PropagateBorns(yyval.bbposition, yyvsp[-4].bbsymbol, yyvsp[-1].bbposition);
                        if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyvsp[-4].bbsymbol.b, s_cxRefPos, yyvsp[-4].bbsymbol.e)) {
                            s_spp[SPP_METHOD_DECLARATION_BEGIN_POSITION] = yyval.bbposition.b;
                            s_spp[SPP_METHOD_DECLARATION_END_POSITION] = yyval.bbposition.e;
                        }
                    }
                }
            }
break;
case 154:
#line 1740 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cps.lastAssignementStruct = NULL;
                    yyval.bbsymbol.d = javaMethodHeader(yyvsp[-3].bbunsign.d,yyvsp[-2].bbsymbol.d,yyvsp[-1].bbsymbol.d, StorageMethod);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-3].bbunsign, yyvsp[0].bbsymbolList);
                    if (yyval.bbsymbol.b.file == s_noneFileIndex) PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyval.bbsymbol);
                    if (yyval.bbsymbol.e.file == s_noneFileIndex) PropagateBorns(yyval.bbsymbol, yyval.bbsymbol, yyvsp[-1].bbsymbol);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbsymbol.b, s_cxRefPos, yyvsp[-1].bbsymbol.e)) {
                        s_spp[SPP_METHOD_DECLARATION_TYPE_BEGIN_POSITION] = yyvsp[-2].bbsymbol.b;
                        s_spp[SPP_METHOD_DECLARATION_TYPE_END_POSITION] = yyvsp[-2].bbsymbol.e;
                    }
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = jslMethodHeader(yyvsp[-3].bbunsign.d,yyvsp[-2].bbsymbol.d,yyvsp[-1].bbsymbol.d,StorageMethod, yyvsp[0].bbsymbolList.d);
            }
        }
break;
case 155:
#line 1759 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbol.d = javaMethodHeader(yyvsp[-3].bbunsign.d,&s_defaultVoidDefinition,yyvsp[-1].bbsymbol.d,StorageMethod);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-3].bbunsign, yyvsp[0].bbsymbolList);
                    if (yyval.bbsymbol.b.file == s_noneFileIndex) PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbidIdent, yyval.bbsymbol);
                    if (yyval.bbsymbol.e.file == s_noneFileIndex) PropagateBorns(yyval.bbsymbol, yyval.bbsymbol, yyvsp[-1].bbsymbol);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbsymbol.b, s_cxRefPos, yyvsp[-1].bbsymbol.e)) {
                        s_spp[SPP_METHOD_DECLARATION_TYPE_BEGIN_POSITION] = yyvsp[-2].bbidIdent.b;
                        s_spp[SPP_METHOD_DECLARATION_TYPE_END_POSITION] = yyvsp[-2].bbidIdent.e;
                    }
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = jslMethodHeader(yyvsp[-3].bbunsign.d,&s_defaultVoidDefinition,yyvsp[-1].bbsymbol.d,StorageMethod, yyvsp[0].bbsymbolList.d);
            }
        }
break;
case 156:
#line 1777 "java_parser.y"
{assert(0);}
break;
case 157:
#line 1782 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.symbol = javaCreateNewMethod(yyvsp[0].bbidIdent.d->name, &(yyvsp[0].bbidIdent.d->p), MEM_XX);
                    }
                }
                if (inSecondJslPass()) {
                    yyval.symbol = javaCreateNewMethod(yyvsp[0].bbidIdent.d->name,&(yyvsp[0].bbidIdent.d->p), MEM_CF);
                }
            }
break;
case 158:
#line 1793 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.bbsymbol.d = yyvsp[-3].symbol;
                        assert(yyval.bbsymbol.d && yyval.bbsymbol.d->u.type && yyval.bbsymbol.d->u.type->kind == TypeFunction);
                        FILL_funTypeModif(&yyval.bbsymbol.d->u.type->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-4].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbsymbolPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        PropagateBorns(yyval.bbsymbol, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                    }
                }
                if (inSecondJslPass()) {
                    yyval.bbsymbol.d = yyvsp[-3].symbol;
                    assert(yyval.bbsymbol.d && yyval.bbsymbol.d->u.type && yyval.bbsymbol.d->u.type->kind == TypeFunction);
                    FILL_funTypeModif(&yyval.bbsymbol.d->u.type->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                }
            }
break;
case 159:
#line 1810 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                    AddComposedType(yyval.bbsymbol.d, TypeArray);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbposition);
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                JslAddComposedType(yyval.bbsymbol.d, TypeArray);
            }
        }
break;
case 160:
#line 1824 "java_parser.y"
{ assert(0);}
break;
case 161:
#line 1827 "java_parser.y"
{
            yyval.bbsymbolPositionLstPair.d.s = NULL;
            yyval.bbsymbolPositionLstPair.d.p = NULL;
            SetNullBorns(yyval.bbsymbolPositionLstPair);
        }
break;
case 163:
#line 1836 "java_parser.y"
{
            if (! SyntaxPassOnly()) {
                yyval.bbsymbolPositionLstPair.d.s = yyvsp[0].bbsymbol.d;
            } else {
                yyval.bbsymbolPositionLstPair.d.p = NULL;
                appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &s_noPos);
                PropagateBorns(yyval.bbsymbolPositionLstPair, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
            }
        }
break;
case 164:
#line 1845 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                    LIST_APPEND(S_symbol, yyval.bbsymbolPositionLstPair.d.s, yyvsp[0].bbsymbol.d);
                } else {
                    appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
                    PropagateBorns(yyval.bbsymbolPositionLstPair, yyvsp[-2].bbsymbolPositionLstPair, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                LIST_APPEND(S_symbol, yyval.bbsymbolPositionLstPair.d.s, yyvsp[0].bbsymbol.d);
            }
        }
break;
case 165:
#line 1863 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                    completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-1].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
            }
        }
break;
case 166:
#line 1877 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                    completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbposition, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
            }
        }
break;
case 167:
#line 1891 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    XX_ALLOC(yyval.bbsymbol.d, S_symbol);
                    *yyval.bbsymbol.d = s_errorSymbol;
                } else {
                    SetNullBorns(yyval.bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                CF_ALLOC(yyval.bbsymbol.d, S_symbol);
                *yyval.bbsymbol.d = s_errorSymbol;
            }
        }
break;
case 168:
#line 1907 "java_parser.y"
{
            yyval.bbsymbolList.d = NULL;
            SetNullBorns(yyval.bbsymbolList);
        }
break;
case 169:
#line 1911 "java_parser.y"
{
            yyval.bbsymbolList.d = yyvsp[0].bbsymbolList.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbolList, yyvsp[-1].bbposition, yyvsp[0].bbsymbolList);
        }
break;
case 170:
#line 1918 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbolList, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                CF_ALLOC(yyval.bbsymbolList.d, SymbolList);
                /* REPLACED: FILL_symbolList($$.d, $1.d->u.type->u.t, NULL); with: */
                *yyval.bbsymbolList.d = (SymbolList){.d = yyvsp[0].bbsymbol.d->u.type->u.t, .next = NULL};
            }
        }
break;
case 171:
#line 1928 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbolList, yyvsp[-2].bbsymbolList, yyvsp[0].bbsymbol);
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                CF_ALLOC(yyval.bbsymbolList.d, SymbolList);
                /* REPLACED: FILL_symbolList($$.d, $3.d->u.type->u.t, $1.d); with: */
                *yyval.bbsymbolList.d = (SymbolList){.d = yyvsp[0].bbsymbol.d->u.type->u.t, .next = yyvsp[-2].bbsymbolList.d};
            }
        }
break;
case 173:
#line 1942 "java_parser.y"
{
            yyval.bbposition.d = yyvsp[0].bbposition.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 174:
#line 1951 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 175:
#line 1954 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 176:
#line 1961 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        S_symbol *mh, *args;

                        args = yyvsp[-1].bbsymbol.d;
                        /*&
                          if (! ($1.d & ACC_STATIC)) {
                              args = javaPrependDirectEnclosingInstanceArgument($2.d);
                          }
                          &*/
                        mh=javaMethodHeader(yyvsp[-2].bbunsign.d, &s_errorSymbol, args, StorageConstructor);
                        /* TODO! Merge this with 'javaMethodBodyBeginning'!*/
                        assert(mh->u.type && mh->u.type->kind == TypeFunction);
                        stackMemoryBlockStart();  /* in order to remove arguments*/
                        s_cp.function = mh; /* added for set-target-position checks */
                        /* also needed for pushing label reference */
                        genInternalLabelReference(-1, UsageDefined);
                        s_count.localVar = 0;
                        assert(yyvsp[-1].bbsymbol.d && yyvsp[-1].bbsymbol.d->u.type);
                        javaAddMethodParametersToSymTable(yyvsp[-1].bbsymbol.d);
                        mh->u.type->u.m.sig = strchr(mh->linkName, '(');
                        s_javaStat->cpMethodMods = yyvsp[-2].bbunsign.d;
                    }
                }
                if (inSecondJslPass()) {
                    S_symbol *args;
                    args = yyvsp[-1].bbsymbol.d;
                    jslMethodHeader(yyvsp[-2].bbunsign.d,&s_defaultVoidDefinition,args,
                                    StorageConstructor, yyvsp[0].bbsymbolList.d);
                }
            }
break;
case 177:
#line 1993 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                    if (s_opt.taskRegime == RegimeHtmlGenerate) {
                        htmlAddFunctionSeparatorReference();
                    } else {
                        PropagateBorns(yyval.bbposition, yyvsp[-6].bbunsign, yyvsp[-1].bbposition);
                        if (yyval.bbposition.b.file == s_noneFileIndex) PropagateBorns(yyval.bbposition, yyvsp[-5].bbsymbol, yyval.bbposition);
                    }
                }
                s_cp.function = NULL; /* added for set-target-position checks */
            }
        }
break;
case 178:
#line 2011 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        if (strcmp(yyvsp[0].bbidIdent.d->name, s_javaStat->thisClass->name)==0) {
                            addCxReference(s_javaStat->thisClass, &yyvsp[0].bbidIdent.d->p,
                                           UsageConstructorDefinition,s_noneFileIndex, s_noneFileIndex);
                            yyval.symbol = javaCreateNewMethod(yyvsp[0].bbidIdent.d->name,/*JAVA_CONSTRUCTOR_NAME1,*/
                                                             &(yyvsp[0].bbidIdent.d->p), MEM_XX);
                        } else {
                            /* a type forgotten for a method?*/
                            yyval.symbol = javaCreateNewMethod(yyvsp[0].bbidIdent.d->name,&(yyvsp[0].bbidIdent.d->p),MEM_XX);
                        }
                    }
                }
                if (inSecondJslPass()) {
                    if (strcmp(yyvsp[0].bbidIdent.d->name, s_jsl->classStat->thisClass->name)==0) {
                        yyval.symbol = javaCreateNewMethod(
                                        yyvsp[0].bbidIdent.d->name, /*JAVA_CONSTRUCTOR_NAME1,*/
                                        &(yyvsp[0].bbidIdent.d->p),
                                        MEM_CF);
                    } else {
                        /* a type forgotten for a method?*/
                        yyval.symbol = javaCreateNewMethod(yyvsp[0].bbidIdent.d->name, &(yyvsp[0].bbidIdent.d->p), MEM_CF);
                    }
                }
            }
break;
case 179:
#line 2038 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.bbsymbol.d = yyvsp[-3].symbol;
                        assert(yyval.bbsymbol.d && yyval.bbsymbol.d->u.type && yyval.bbsymbol.d->u.type->kind == TypeFunction);
                        FILL_funTypeModif(&yyval.bbsymbol.d->u.type->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-4].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbsymbolPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        PropagateBorns(yyval.bbsymbol, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                    }
                }
                if (inSecondJslPass()) {
                    yyval.bbsymbol.d = yyvsp[-3].symbol;
                    assert(yyval.bbsymbol.d && yyval.bbsymbol.d->u.type && yyval.bbsymbol.d->u.type->kind == TypeFunction);
                    FILL_funTypeModif(&yyval.bbsymbol.d->u.type->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                };
            }
break;
case 180:
#line 2058 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-5].bbposition, yyvsp[0].bbposition);
        }
break;
case 181:
#line 2061 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 182:
#line 2064 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 183:
#line 2067 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 184:
#line 2075 "java_parser.y"
{
                if (ComputingPossibleParameterCompletion()) {
                    s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(s_javaStat->thisClass, &yyvsp[-1].bbidIdent.d->p);
                }
            }
break;
case 185:
#line 2079 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaConstructorInvocation(s_javaStat->thisClass, &(yyvsp[-5].bbidIdent.d->p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                        s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        PropagateBorns(yyval.bbposition, yyvsp[-5].bbidIdent, yyvsp[0].bbposition);
                    }
                }
            }
break;
case 186:
#line 2091 "java_parser.y"
{
                if (ComputingPossibleParameterCompletion()) {
                    s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(javaCurrentSuperClass(), &yyvsp[-1].bbidIdent.d->p);
                }
            }
break;
case 187:
#line 2095 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        S_symbol *ss;
                        ss = javaCurrentSuperClass();
                        javaConstructorInvocation(ss, &(yyvsp[-5].bbidIdent.d->p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                        s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        PropagateBorns(yyval.bbposition, yyvsp[-5].bbidIdent, yyvsp[0].bbposition);
                    }
                }
            }
break;
case 188:
#line 2109 "java_parser.y"
{
                if (ComputingPossibleParameterCompletion()) {
                    s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(javaCurrentSuperClass(), &(yyvsp[-1].bbidIdent.d->p));
                }
            }
break;
case 189:
#line 2113 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        S_symbol *ss;
                        ss = javaCurrentSuperClass();
                        javaConstructorInvocation(ss, &(yyvsp[-5].bbidIdent.d->p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                        s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        PropagateBorns(yyval.bbposition, yyvsp[-7].bbexprType, yyvsp[0].bbposition);
                    }
                }
            }
break;
case 190:
#line 2126 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 191:
#line 2127 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 192:
#line 2128 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 193:
#line 2129 "java_parser.y"
{assert(0);}
break;
case 194:
#line 2130 "java_parser.y"
{assert(0);}
break;
case 195:
#line 2131 "java_parser.y"
{assert(0);}
break;
case 196:
#line 2138 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.trail=newClassDefinitionBegin(yyvsp[0].bbidIdent.d,(yyvsp[-2].bbunsign.d|ACC_INTERFACE),NULL);
                }
            } else {
                jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, (yyvsp[-2].bbunsign.d|ACC_INTERFACE), NULL, CPOS_ST);
            }
        }
break;
case 197:
#line 2146 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    javaAddSuperNestedClassToSymbolTab(s_javaStat->thisClass);
                }
            } else {
                jslAddSuperNestedClassesToJslTypeTab(s_jsl->classStat->thisClass);
            }
        }
break;
case 198:
#line 2154 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbidIdent.d = yyvsp[-4].bbidIdent.d;
                if (! SyntaxPassOnly()) {
                    newClassDefinitionEnd(yyvsp[-3].trail);
                } else {
                    PropagateBorns(yyval.bbidIdent, yyvsp[-6].bbunsign, yyvsp[0].bbposition);
                    if (yyval.bbidIdent.b.file == s_noneFileIndex) PropagateBorns(yyval.bbidIdent, yyvsp[-5].bbposition, yyval.bbidIdent);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbidIdent.b, s_cxRefPos, yyval.bbidIdent.e)
                        && s_spp[SPP_CLASS_DECLARATION_BEGIN_POSITION].file == s_noneFileIndex) {
                        s_spp[SPP_CLASS_DECLARATION_BEGIN_POSITION] = yyval.bbidIdent.b;
                        s_spp[SPP_CLASS_DECLARATION_TYPE_BEGIN_POSITION] = yyvsp[-5].bbposition.b;
                        s_spp[SPP_CLASS_DECLARATION_TYPE_END_POSITION] = yyvsp[-5].bbposition.e;
                        s_spp[SPP_CLASS_DECLARATION_END_POSITION] = yyval.bbidIdent.e;
                    }
                }
            } else {
                jslNewClassDefinitionEnd();
            }
        }
break;
case 199:
#line 2175 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail=newClassDefinitionBegin(yyvsp[0].bbidIdent.d,(yyvsp[-2].bbunsign.d|ACC_INTERFACE),NULL);
                    }
                } else {
                    jslNewClassDefinitionBegin(yyvsp[0].bbidIdent.d, (yyvsp[-2].bbunsign.d|ACC_INTERFACE), NULL, CPOS_ST);
                }
            }
break;
case 200:
#line 2185 "java_parser.y"
{
                if (regularPass()) {
                    yyval.bbidIdent.d = yyvsp[-3].bbidIdent.d;
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-2].trail);
                    } else {
                        PropagateBorns(yyval.bbidIdent, yyvsp[-5].bbunsign, yyvsp[0].bbposition);
                        if (yyval.bbidIdent.b.file == s_noneFileIndex) PropagateBorns(yyval.bbidIdent, yyvsp[-4].bbposition, yyval.bbidIdent);
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
            }
break;
case 201:
#line 2198 "java_parser.y"
{ /* never used */ }
break;
case 202:
#line 2201 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
            if (inSecondJslPass()) {
                jslAddSuperClassOrInterfaceByName(s_jsl->classStat->thisClass,
                                                s_javaLangObjectLinkName);
            }
        }
break;
case 204:
#line 2212 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                    assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                    javaParsedSuperClass(yyvsp[0].bbsymbol.d->u.type->u.t);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                jslAddSuperClassOrInterface(s_jsl->classStat->thisClass,
                                            yyvsp[0].bbsymbol.d->u.type->u.t);
            }
        }
break;
case 205:
#line 2229 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                    assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                    javaParsedSuperClass(yyvsp[0].bbsymbol.d->u.type->u.t);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbsymbol);
                }
            }
            if (inSecondJslPass()) {
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->bits.symType == TypeDefault && yyvsp[0].bbsymbol.d->u.type);
                assert(yyvsp[0].bbsymbol.d->u.type->kind == TypeStruct);
                jslAddSuperClassOrInterface(s_jsl->classStat->thisClass,
                                            yyvsp[0].bbsymbol.d->u.type->u.t);
            }
        }
break;
case 206:
#line 2249 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 207:
#line 2252 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-3].bbposition, yyvsp[0].bbposition);
        }
break;
case 209:
#line 2259 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 210:
#line 2265 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);}
break;
case 211:
#line 2266 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);}
break;
case 212:
#line 2267 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);}
break;
case 213:
#line 2268 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);}
break;
case 214:
#line 2269 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);}
break;
case 215:
#line 2270 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 217:
#line 2279 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaMethodBodyBeginning(yyvsp[-1].bbsymbol.d);
                    }
                }
            }
break;
case 218:
#line 2287 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        javaMethodBodyEnding(&yyvsp[-1].bbposition.d);
                    } else {
                        PropagateBorns(yyval.bbsymbol, yyvsp[-4].bbsymbol, yyvsp[-1].bbposition);
                    }
                }
            }
break;
case 219:
#line 2301 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[-3].bbposition, yyvsp[0].bbposition);}
break;
case 220:
#line 2302 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[-2].bbposition, yyvsp[0].bbposition);}
break;
case 221:
#line 2303 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[-2].bbposition, yyvsp[0].bbposition);}
break;
case 222:
#line 2304 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbposition);}
break;
case 223:
#line 2308 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
        }
break;
case 224:
#line 2311 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbexprType);
        }
break;
case 225:
#line 2319 "java_parser.y"
{
            yyval.bbposition.d = yyvsp[0].bbposition.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 226:
#line 2323 "java_parser.y"
{
            yyval.bbposition.d = yyvsp[0].bbposition.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 228:
#line 2331 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 232:
#line 2340 "java_parser.y"
{SetNullBorns(yyval.bbposition);}
break;
case 233:
#line 2344 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbsymbol, yyvsp[0].bbposition);
        }
break;
case 234:
#line 2350 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    addNewDeclaration(yyvsp[-1].bbsymbol.d,yyvsp[0].bbsymbol.d,NULL,StorageAuto,s_javaStat->locals);
                    yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-1].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
        }
break;
case 235:
#line 2360 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    addNewDeclaration(yyvsp[-1].bbsymbol.d,yyvsp[0].bbsymbol.d,NULL,StorageAuto,s_javaStat->locals);
                    yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbposition, yyvsp[0].bbsymbol);
                }
            }
        }
break;
case 236:
#line 2370 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[-2].bbsymbol.d->bits.symType != TypeError) {
                        addNewDeclaration(yyvsp[-2].bbsymbol.d,yyvsp[0].bbsymbol.d,NULL,StorageAuto,s_javaStat->locals);
                    }
                    yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-2].bbsymbol, yyvsp[0].bbsymbol);
                }
            }
        }
break;
case 237:
#line 2385 "java_parser.y"
{
            if (regularPass()) yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            PropagateBornsIfRegularSyntaxPass(yyval.bbsymbol, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
        }
break;
case 238:
#line 2389 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cps.lastAssignementStruct = yyvsp[0].bbsymbol.d;
                }
            }
        }
break;
case 239:
#line 2395 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cps.lastAssignementStruct = NULL;
                    yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d;
                } else {
                    PropagateBorns(yyval.bbsymbol, yyvsp[-3].bbsymbol, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 263:
#line 2446 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 264:
#line 2449 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 265:
#line 2455 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 266:
#line 2461 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 267:
#line 2467 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 268:
#line 2473 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbexprType, yyvsp[0].bbposition);
        }
break;
case 269:
#line 2479 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 270:
#line 2480 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 271:
#line 2481 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 272:
#line 2482 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 273:
#line 2483 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 274:
#line 2484 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 275:
#line 2485 "java_parser.y"
{PropagateBornsIfRegularSyntaxPass(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);}
break;
case 276:
#line 2488 "java_parser.y"
{if (regularPass()) EXTRACT_COUNTER_SEMACT(yyval.bbinteger.data);}
break;
case 277:
#line 2491 "java_parser.y"
{if (regularPass()) EXTRACT_LABEL_SEMACT(yyval.bbinteger.data);}
break;
case 278:
#line 2494 "java_parser.y"
{if (regularPass()) EXTRACT_GOTO_SEMACT(yyval.bbinteger.data);}
break;
case 279:
#line 2497 "java_parser.y"
{if (regularPass()) EXTRACT_FORK_SEMACT(yyval.bbinteger.data);}
break;
case 280:
#line 2502 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-1].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-5].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 281:
#line 2514 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-3].bbinteger.data, UsageDefined);
                    yyval.bbinteger.data = yyvsp[0].bbinteger.data;
                } else {
                    PropagateBorns(yyval.bbinteger, yyvsp[-7].bbposition, yyvsp[-1].bbposition);
                }
            }
        }
break;
case 282:
#line 2527 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-1].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbinteger, yyvsp[0].bbposition);
                }
            }
        }
break;
case 283:
#line 2539 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-1].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbinteger, yyvsp[0].bbposition);
                }
            }
        }
break;
case 284:
#line 2551 "java_parser.y"
{/*6*/
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.symbol = addContinueBreakLabelSymbol(1000*yyvsp[0].bbinteger.data,SWITCH_LABEL_NAME);
                }
            }
        }
break;
case 285:
#line 2557 "java_parser.y"
{/*7*/
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.symbol = addContinueBreakLabelSymbol(yyvsp[-1].bbinteger.data, BREAK_LABEL_NAME);
                    genInternalLabelReference(yyvsp[-1].bbinteger.data, UsageFork);
                }
            }
        }
break;
case 286:
#line 2564 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genSwitchCaseFork(1);
                    ExtrDeleteContBreakSym(yyvsp[-1].symbol);
                    ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                    genInternalLabelReference(yyvsp[-3].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-7].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 287:
#line 2579 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-5].bbposition, yyvsp[0].bbposition);
        }
break;
case 288:
#line 2582 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 289:
#line 2585 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 290:
#line 2588 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 292:
#line 2595 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 293:
#line 2601 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genSwitchCaseFork(0);
                }
            }
        }
break;
case 294:
#line 2607 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 296:
#line 2614 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 297:
#line 2617 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 298:
#line 2623 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 299:
#line 2626 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 300:
#line 2632 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (s_opt.server_operation == OLO_EXTRACT) {
                        S_symbol *cl, *bl;
                        cl = bl = NULL;        /* just to avoid warning message*/
                        cl = addContinueBreakLabelSymbol(yyvsp[-4].bbinteger.data, CONTINUE_LABEL_NAME);
                        bl = addContinueBreakLabelSymbol(yyvsp[0].bbinteger.data, BREAK_LABEL_NAME);
                        XX_ALLOC(yyval.bbwhiledata.d, S_whileExtractData);
                        FILL_whileExtractData(yyval.bbwhiledata.d, yyvsp[-4].bbinteger.data, yyvsp[0].bbinteger.data, cl, bl);
                    } else {
                        yyval.bbwhiledata.d = NULL;
                    }
                } else {
                    PropagateBorns(yyval.bbwhiledata, yyvsp[-5].bbposition, yyvsp[-1].bbposition);
                }
            }
        }
break;
case 301:
#line 2653 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[-1].bbwhiledata.d != NULL) {
                        ExtrDeleteContBreakSym(yyvsp[-1].bbwhiledata.d->i4);
                        ExtrDeleteContBreakSym(yyvsp[-1].bbwhiledata.d->i3);
                        genInternalLabelReference(yyvsp[-1].bbwhiledata.d->i1, UsageUsed);
                        genInternalLabelReference(yyvsp[-1].bbwhiledata.d->i2, UsageDefined);
                    }
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbwhiledata, yyvsp[0].bbposition);
                }
            }
        }
break;
case 302:
#line 2670 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[-1].bbwhiledata.d != NULL) {
                        ExtrDeleteContBreakSym(yyvsp[-1].bbwhiledata.d->i4);
                        ExtrDeleteContBreakSym(yyvsp[-1].bbwhiledata.d->i3);
                        genInternalLabelReference(yyvsp[-1].bbwhiledata.d->i1, UsageUsed);
                        genInternalLabelReference(yyvsp[-1].bbwhiledata.d->i2, UsageDefined);
                    }
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbwhiledata, yyvsp[0].bbposition);
                }
            }
        }
break;
case 303:
#line 2687 "java_parser.y"
{ /*5*/
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.symbol = addContinueBreakLabelSymbol(yyvsp[-1].bbinteger.data, CONTINUE_LABEL_NAME);
                }
            }
        }
break;
case 304:
#line 2693 "java_parser.y"
{/*6*/
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.symbol = addContinueBreakLabelSymbol(yyvsp[-1].bbinteger.data, BREAK_LABEL_NAME);
                }
            }
        }
break;
case 305:
#line 2699 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                    ExtrDeleteContBreakSym(yyvsp[-3].symbol);
                    genInternalLabelReference(yyvsp[-5].bbinteger.data, UsageDefined);
                }
            }
        }
break;
case 306:
#line 2707 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-11].bbinteger.data, UsageFork);
                    genInternalLabelReference(yyvsp[-9].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-12].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 307:
#line 2719 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 308:
#line 2722 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
        }
break;
case 309:
#line 2728 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockStart();
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 310:
#line 2742 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *ss __attribute__((unused));
                    genInternalLabelReference(yyvsp[-7].bbinteger.data, UsageUsed);
                    genInternalLabelReference(yyvsp[-4].bbinteger.data, UsageDefined);
                    ss = addContinueBreakLabelSymbol(yyvsp[-3].bbinteger.data, CONTINUE_LABEL_NAME);
                    ss = addContinueBreakLabelSymbol(yyvsp[0].bbinteger.data, BREAK_LABEL_NAME);
                    yyval.bbintpair.d.i1 = yyvsp[-3].bbinteger.data;
                    yyval.bbintpair.d.i2 = yyvsp[0].bbinteger.data;
                } else {
                    PropagateBorns(yyval.bbintpair, yyvsp[-10].bbposition, yyvsp[-1].bbposition);
                }
            }
        }
break;
case 311:
#line 2760 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    deleteContinueBreakLabelSymbol(BREAK_LABEL_NAME);
                    deleteContinueBreakLabelSymbol(CONTINUE_LABEL_NAME);
                    genInternalLabelReference(yyvsp[-1].bbintpair.d.i1, UsageUsed);
                    genInternalLabelReference(yyvsp[-1].bbintpair.d.i2, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbintpair, yyvsp[0].bbposition);
                }
            }
        }
break;
case 312:
#line 2775 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    deleteContinueBreakLabelSymbol(BREAK_LABEL_NAME);
                    deleteContinueBreakLabelSymbol(CONTINUE_LABEL_NAME);
                    genInternalLabelReference(yyvsp[-1].bbintpair.d.i1, UsageUsed);
                    genInternalLabelReference(yyvsp[-1].bbintpair.d.i2, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbintpair, yyvsp[0].bbposition);
                }
            }
        }
break;
case 313:
#line 2790 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 314:
#line 2799 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                } else {
                    SetNullBorns(yyval.bbposition);
                }
            }
        }
break;
case 315:
#line 2811 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 316:
#line 2820 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                } else {
                    SetNullBorns(yyval.bbposition);
                }
            }
        }
break;
case 317:
#line 2832 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 318:
#line 2835 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 319:
#line 2838 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbsymbol, yyvsp[0].bbsymbol);
        }
break;
case 320:
#line 2843 "java_parser.y"
{
            SetNullBorns(yyval.bbposition);
        }
break;
case 321:
#line 2846 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 322:
#line 2852 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
        }
break;
case 323:
#line 2855 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbexprType);
        }
break;
case 324:
#line 2861 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 325:
#line 2864 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genContinueBreakReference(BREAK_LABEL_NAME);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 326:
#line 2876 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 327:
#line 2879 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genContinueBreakReference(CONTINUE_LABEL_NAME);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 328:
#line 2891 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(-1, UsageUsed);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 329:
#line 2900 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(-1, UsageUsed);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 330:
#line 2912 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (s_opt.server_operation==OLO_EXTRACT) {
                        addCxReference(yyvsp[-1].bbexprType.d.t->u.t, &yyvsp[-2].bbidIdent.d->p, UsageThrown, s_noneFileIndex, s_noneFileIndex);
                    }
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-2].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 331:
#line 2926 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-4].bbposition, yyvsp[0].bbposition);
        }
break;
case 334:
#line 2934 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 335:
#line 2941 "java_parser.y"
{
                if (s_opt.server_operation == OLO_EXTRACT) {
                    addTrivialCxReference("TryCatch", TypeTryCatchMarker,StorageDefault,
                                            &yyvsp[-1].bbidIdent.d->p, UsageTryCatchBegin);
                }
            }
break;
case 336:
#line 2948 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        genInternalLabelReference(yyvsp[-2].bbinteger.data, UsageDefined);
                    }
                }
            }
break;
case 337:
#line 2955 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-5].bbidIdent, yyvsp[0].bbposition);
            if (s_opt.server_operation == OLO_EXTRACT) {
                addTrivialCxReference("TryCatch", TypeTryCatchMarker,StorageDefault,
                                        &yyvsp[-5].bbidIdent.d->p, UsageTryCatchEnd);
            }
        }
break;
case 339:
#line 2967 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 340:
#line 2974 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        if (yyvsp[-3].bbsymbol.d->bits.symType != TypeError) {
                            addNewSymbolDef(yyvsp[-3].bbsymbol.d, StorageAuto, s_javaStat->locals,
                                            UsageDefined);
                            if (s_opt.server_operation == OLO_EXTRACT) {
                                assert(yyvsp[-3].bbsymbol.d->bits.symType==TypeDefault);
                                addCxReference(yyvsp[-3].bbsymbol.d->u.type->u.t, &yyvsp[-5].bbidIdent.d->p, UsageCatched, s_noneFileIndex, s_noneFileIndex);
                            }
                        }
                    }
                }
            }
break;
case 341:
#line 2989 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        genInternalLabelReference(yyvsp[-4].bbinteger.data, UsageDefined);
                    } else {
                        PropagateBorns(yyval.bbposition, yyvsp[-8].bbidIdent, yyvsp[-1].bbposition);
                    }
                }
            }
break;
case 342:
#line 2998 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (s_opt.server_operation == OLO_EXTRACT) {
                        assert(yyvsp[-2].bbsymbol.d->bits.symType==TypeDefault);
                        addCxReference(yyvsp[-2].bbsymbol.d->u.type->u.t, &yyvsp[-4].bbidIdent.d->p, UsageCatched, s_noneFileIndex, s_noneFileIndex);
                    }
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-4].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 343:
#line 3013 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    genInternalLabelReference(yyvsp[-1].bbinteger.data, UsageDefined);
                } else {
                    PropagateBorns(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
                }
            }
        }
break;
case 344:
#line 3027 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbexprType.d = yyvsp[0].bbexprType.d;
                if (! SyntaxPassOnly()) {
                    s_javaCompletionLastPrimary = s_structRecordCompletionType = yyval.bbexprType.d.t;
                } else {
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 345:
#line 3037 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbexprType.d = yyvsp[0].bbexprType.d;
                if (! SyntaxPassOnly()) {
                    s_javaCompletionLastPrimary = s_structRecordCompletionType = yyval.bbexprType.d.t;
                } else {
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 347:
#line 3051 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(s_javaStat && s_javaStat->thisType);
/*fprintf(dumpOut,"this == %s\n",s_javaStat->thisType->u.t->linkName);*/
                    yyval.bbexprType.d.t = s_javaStat->thisType;
                    addThisCxReferences(s_javaStat->classFileInd, &yyvsp[0].bbidIdent.d->p);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[0].bbidIdent.d->p;
                    javaCheckForStaticPrefixStart(&yyvsp[0].bbidIdent.d->p, &yyvsp[0].bbidIdent.d->p);
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbidIdent, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 348:
#line 3066 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    javaQualifiedThis(yyvsp[-2].bbidlist.d, yyvsp[0].bbidIdent.d);
                    yyval.bbexprType.d.t = javaClassNameType(yyvsp[-2].bbidlist.d);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[-2].bbidlist.d);
                    javaCheckForStaticPrefixStart(&yyvsp[0].bbidIdent.d->p, javaGetNameStartingPosition(yyvsp[-2].bbidlist.d));
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbidlist, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 349:
#line 3079 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = &s_javaClassModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = yyvsp[-2].bbunsPositionPair.d.p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbunsPositionPair, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 350:
#line 3090 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *str;
                    javaClassifyToTypeName(yyvsp[-2].bbidlist.d,UsageUsed, &str, USELESS_FQT_REFS_ALLOWED);
                    yyval.bbexprType.d.t = &s_javaClassModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[-2].bbidlist.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbidlist, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 351:
#line 3103 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = &s_javaClassModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = yyvsp[-2].bbsymbolPositionPair.d.p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbsymbolPositionPair, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 352:
#line 3114 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = &s_javaClassModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    SetPrimitiveTypePos(yyval.bbexprType.d.pp, yyvsp[-2].bbidIdent.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbidIdent, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 353:
#line 3125 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbexprType.d = yyvsp[-1].bbexprType.d;
                if (SyntaxPassOnly()) {
                    XX_ALLOC(yyval.bbexprType.d.pp, S_position);
                    *yyval.bbexprType.d.pp = yyvsp[-2].bbposition.d;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbposition, yyvsp[0].bbposition);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyval.bbexprType.b, s_cxRefPos, yyval.bbexprType.e)
                        && s_spp[SPP_PARENTHESED_EXPRESSION_LPAR_POSITION].file == s_noneFileIndex) {
                        s_spp[SPP_PARENTHESED_EXPRESSION_LPAR_POSITION] = yyvsp[-2].bbposition.b;
                        s_spp[SPP_PARENTHESED_EXPRESSION_RPAR_POSITION] = yyvsp[0].bbposition.b;
                        s_spp[SPP_PARENTHESED_EXPRESSION_BEGIN_POSITION] = yyvsp[-1].bbexprType.b;
                        s_spp[SPP_PARENTHESED_EXPRESSION_END_POSITION] = yyvsp[-1].bbexprType.e;
                    }
                }
            }
        }
break;
case 358:
#line 3146 "java_parser.y"
{ assert(0); /* rule never used */ }
break;
case 359:
#line 3149 "java_parser.y"
{
            yyval.erfs = s_cp.erfsForParamsComplet;
        }
break;
case 360:
#line 3156 "java_parser.y"
{
                if (ComputingPossibleParameterCompletion()) {
                    S_typeModifiers *mm;
                    s_cp.erfsForParamsComplet = NULL;
                    if (yyvsp[-4].bbexprType.d.t->kind == TypeStruct) {
                        mm = javaNestedNewType(yyvsp[-4].bbexprType.d.t->u.t, yyvsp[-2].bbidIdent.d, yyvsp[-1].bbidlist.d);
                        if (mm->kind != TypeError) {
                            s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(mm->u.t, &(yyvsp[-1].bbidlist.d->idi.p));
                        }
                    }
                }
            }
break;
case 361:
#line 3168 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    if (yyvsp[-8].bbexprType.d.t->kind == TypeStruct) {
                        yyval.bbnestedConstrTokenType.d.t = javaNestedNewType(yyvsp[-8].bbexprType.d.t->u.t, yyvsp[-6].bbidIdent.d, yyvsp[-5].bbidlist.d);
                    } else {
                        yyval.bbnestedConstrTokenType.d.t = &s_errorModifier;
                    }
                    javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidlist.d->idi.p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    assert(yyval.bbnestedConstrTokenType.d.t);
                    yyval.bbnestedConstrTokenType.d.nid = yyvsp[-5].bbidlist.d;
                    if (yyval.bbnestedConstrTokenType.d.t->kind != TypeError) {
                        javaConstructorInvocation(yyval.bbnestedConstrTokenType.d.t->u.t, &(yyvsp[-5].bbidlist.d->idi.p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    }
                } else {
                    yyval.bbnestedConstrTokenType.d.pp = yyvsp[-8].bbexprType.d.pp;
                    PropagateBorns(yyval.bbnestedConstrTokenType, yyvsp[-8].bbexprType, yyvsp[0].bbposition);
                }
            }
        }
break;
case 362:
#line 3190 "java_parser.y"
{
                if (ComputingPossibleParameterCompletion()) {
                    S_typeModifiers *mm;
                    s_cp.erfsForParamsComplet = NULL;
                    mm = javaNewAfterName(yyvsp[-4].bbidlist.d, yyvsp[-2].bbidIdent.d, yyvsp[-1].bbidlist.d);
                    if (mm->kind != TypeError) {
                        s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(mm->u.t, &(yyvsp[-1].bbidlist.d->idi.p));
                    }
                }
            }
break;
case 363:
#line 3200 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    yyval.bbnestedConstrTokenType.d.t = javaNewAfterName(yyvsp[-8].bbidlist.d, yyvsp[-6].bbidIdent.d, yyvsp[-5].bbidlist.d);
                    yyval.bbnestedConstrTokenType.d.nid = yyvsp[-5].bbidlist.d;
                    if (yyval.bbnestedConstrTokenType.d.t->kind != TypeError) {
                        javaConstructorInvocation(yyval.bbnestedConstrTokenType.d.t->u.t, &(yyvsp[-5].bbidlist.d->idi.p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    }
                } else {
                    yyval.bbnestedConstrTokenType.d.pp = javaGetNameStartingPosition(yyvsp[-8].bbidlist.d);
                    javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidlist.d->idi.p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    PropagateBorns(yyval.bbnestedConstrTokenType, yyvsp[-8].bbidlist, yyvsp[0].bbposition);
                }
            }
        }
break;
case 364:
#line 3219 "java_parser.y"
{
            if (ComputingPossibleParameterCompletion()) {
                S_symbol            *ss;
                S_symbol			*str;
                S_typeModifiers		*expr;
                S_reference			*rr, *lastUselessRef;
                javaClassifyAmbiguousName(yyvsp[0].bbidlist.d, NULL,&str,&expr,&rr, &lastUselessRef, USELESS_FQT_REFS_ALLOWED,
                                          CLASS_TO_TYPE,UsageUsed);
                yyvsp[0].bbidlist.d->nameType = TypeStruct;
                ss = javaTypeSymbolUsage(yyvsp[0].bbidlist.d, ACC_DEFAULT);
                s_cp.erfsForParamsComplet = javaCrErfsForConstructorInvocation(ss, &(yyvsp[0].bbidlist.d->idi.p));
            }
            yyval.bbidlist = yyvsp[0].bbidlist;
        }
break;
case 365:
#line 3236 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *ss, *tt, *ei;
                    S_symbol *str;
                    S_typeModifiers *expr;
                    S_reference *rr, *lastUselessRef;

                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                    lastUselessRef = NULL;
                    javaClassifyAmbiguousName(yyvsp[-3].bbidlist.d, NULL,&str,&expr,&rr, &lastUselessRef, USELESS_FQT_REFS_ALLOWED,
                                              CLASS_TO_TYPE,UsageUsed);
                    yyvsp[-3].bbidlist.d->nameType = TypeStruct;
                    ss = javaTypeSymbolUsage(yyvsp[-3].bbidlist.d, ACC_DEFAULT);
                    if (isANestedClass(ss)) {
                        if (javaIsInnerAndCanGetUnnamedEnclosingInstance(ss, &ei)) {
                            /* before it was s_javaStat->classFileInd, but be more precise*/
                            /* in reality you should keep both to discover references*/
                            /* to original class from class nested in method.*/
                            addThisCxReferences(ei->u.s->classFile, &yyvsp[-5].bbidIdent.d->p);
                            /* I have removed following because it makes problems when*/
                            /* expanding to FQT names, WHY IT WAS HERE ???*/
                            /*&addSpecialFieldReference(LINK_NAME_NOT_FQT_ITEM,StorageField,*/
                            /*&              s_javaStat->classFileInd, &$1.d->p,*/
                            /*&              UsageNotFQField);*/
                        } else {
                            /* here I should annulate class reference, as it is an error*/
                            /* because can't get enclosing instance, this is sufficient to*/
                            /* pull-up/down to report a problem*/
                            /* BERK, It was completely wrong, because it is completely legal*/
                            /* and annulating of reference makes class renaming wrong!*/
                            /* Well, it is legal only for static nested classes.*/
                            /* But for security reasons, I will keep it in comment,*/
                            /*&if (! (ss->bits.accessFlags&ACC_STATIC)) {*/
                            /*&	if (rr!=NULL) rr->usg.base = s_noUsage;*/
                            /*&}*/
                        }
                    }
                    javaConstructorInvocation(ss, &(yyvsp[-3].bbidlist.d->idi.p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    tt = javaTypeNameDefinition(yyvsp[-3].bbidlist.d);
                    yyval.bbexprType.d.t = tt->u.type;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    javaHandleDeclaratorParamPositions(&yyvsp[-3].bbidlist.d->idi.p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    yyval.bbexprType.d.pp = &yyvsp[-5].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-5].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 366:
#line 3286 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        S_symbol *ss;
                        s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                        javaClassifyToTypeName(yyvsp[-3].bbidlist.d,UsageUsed, &ss, USELESS_FQT_REFS_ALLOWED);
                        yyval.symbol = javaTypeNameDefinition(yyvsp[-3].bbidlist.d);
                        ss = javaTypeSymbolUsage(yyvsp[-3].bbidlist.d, ACC_DEFAULT);
                        javaConstructorInvocation(ss, &(yyvsp[-3].bbidlist.d->idi.p), yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    } else {
                        javaHandleDeclaratorParamPositions(&yyvsp[-3].bbidlist.d->idi.p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                        /* seems that there is no problem like in previous case,*/
                        /* interfaces are never inner.*/
                    }
                } else {
                    S_symbol *str, *cls;
                    jslClassifyAmbiguousTypeName(yyvsp[-3].bbidlist.d, &str);
                    cls = jslTypeNameDefinition(yyvsp[-3].bbidlist.d);
                    jslNewClassDefinitionBegin(&s_javaAnonymousClassName,
                                                ACC_DEFAULT, cls, CPOS_ST);
                }
            }
break;
case 367:
#line 3308 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.trail = newClassDefinitionBegin(&s_javaAnonymousClassName,ACC_DEFAULT, yyvsp[-1].symbol);
                    }
                }
            }
break;
case 368:
#line 3315 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    newClassDefinitionEnd(yyvsp[-1].trail);
                    assert(yyvsp[-2].symbol && yyvsp[-2].symbol->u.type);
                    yyval.bbexprType.d.t = yyvsp[-2].symbol->u.type;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-8].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-8].bbidIdent, yyvsp[0].bbposition);
                }
            } else {
                jslNewClassDefinitionEnd();
            }
        }
break;
case 369:
#line 3330 "java_parser.y"
{
            yyval.bbexprType.d.t = yyvsp[0].bbnestedConstrTokenType.d.t;
            yyval.bbexprType.d.pp = yyvsp[0].bbnestedConstrTokenType.d.pp;
            yyval.bbexprType.d.r = NULL;
            PropagateBorns(yyval.bbexprType, yyvsp[0].bbnestedConstrTokenType, yyvsp[0].bbnestedConstrTokenType);
        }
break;
case 370:
#line 3337 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        yyval.bbexprType.d.t = yyvsp[0].bbnestedConstrTokenType.d.t;
                        yyval.bbexprType.d.pp = yyvsp[0].bbnestedConstrTokenType.d.pp;
                        yyval.bbexprType.d.r = NULL;
                        if (yyval.bbexprType.d.t->kind != TypeError) {
                            yyval.trail = newClassDefinitionBegin(&s_javaAnonymousClassName, ACC_DEFAULT, yyval.bbexprType.d.t->u.t);
                        } else {
                            yyval.trail = newAnonClassDefinitionBegin(& yyvsp[0].bbnestedConstrTokenType.d.nid->idi);
                        }
                    } else {
                        yyval.bbexprType.d.pp = yyvsp[0].bbnestedConstrTokenType.d.pp;
                    }
                } else {
                    jslNewAnonClassDefinitionBegin(& yyvsp[0].bbnestedConstrTokenType.d.nid->idi);
                }
            }
break;
case 371:
#line 3356 "java_parser.y"
{
                if (regularPass()) {
                    if (! SyntaxPassOnly()) {
                        newClassDefinitionEnd(yyvsp[-1].trail);
                    } else {
                        PropagateBorns(yyval.bbexprType, yyvsp[-2].bbnestedConstrTokenType, yyvsp[0].bbposition);
                    }
                } else {
                    jslNewClassDefinitionEnd();
                }
        }
break;
case 372:
#line 3367 "java_parser.y"
{
            assert(0); /* rule never used */
        }
break;
case 373:
#line 3370 "java_parser.y"
{
            assert(0); /* rule never used */
        }
break;
case 374:
#line 3373 "java_parser.y"
{
            assert(0); /* rule never used */
        }
break;
case 375:
#line 3385 "java_parser.y"
{
            yyval.bbtypeModifiersListPositionLstPair.d.t = NULL;
            yyval.bbtypeModifiersListPositionLstPair.d.p = NULL;
            SetNullBorns(yyval.bbtypeModifiersListPositionLstPair);
        }
break;
case 377:
#line 3394 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    XX_ALLOC(yyval.bbtypeModifiersListPositionLstPair.d.t, S_typeModifiersList);
                    FILL_typeModifiersList(yyval.bbtypeModifiersListPositionLstPair.d.t, yyvsp[0].bbexprType.d.t, NULL);
                    if (s_cp.erfsForParamsComplet!=NULL) {
                        s_cp.erfsForParamsComplet->params = yyval.bbtypeModifiersListPositionLstPair.d.t;
                    }
                } else {
                    yyval.bbtypeModifiersListPositionLstPair.d.p = NULL;
                    appendPositionToList(&yyval.bbtypeModifiersListPositionLstPair.d.p, &s_noPos);
                    PropagateBorns(yyval.bbtypeModifiersListPositionLstPair, yyvsp[0].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 378:
#line 3409 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_typeModifiersList *p;
                    yyval.bbtypeModifiersListPositionLstPair.d = yyvsp[-2].bbtypeModifiersListPositionLstPair.d;
                    XX_ALLOC(p, S_typeModifiersList);
                    FILL_typeModifiersList(p, yyvsp[0].bbexprType.d.t, NULL);
                    LIST_APPEND(S_typeModifiersList, yyval.bbtypeModifiersListPositionLstPair.d.t, p);
                    if (s_cp.erfsForParamsComplet!=NULL) s_cp.erfsForParamsComplet->params = yyval.bbtypeModifiersListPositionLstPair.d.t;
                } else {
                    appendPositionToList(&yyval.bbtypeModifiersListPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
                    PropagateBorns(yyval.bbtypeModifiersListPositionLstPair, yyvsp[-2].bbtypeModifiersListPositionLstPair, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 379:
#line 3424 "java_parser.y"
{assert(0);}
break;
case 380:
#line 3425 "java_parser.y"
{assert(0);}
break;
case 381:
#line 3430 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    int i;
                    CrTypeModifier(yyval.bbexprType.d.t,yyvsp[-2].bbunsPositionPair.d.u);
                    for(i=0; i<yyvsp[-1].bbinteger.data; i++) PrependModifier(yyval.bbexprType.d.t, TypeArray);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-4].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbidIdent, yyvsp[0].bbinteger);
                    if (yyval.bbexprType.e.file == s_noneFileIndex) PropagateBorns(yyval.bbexprType, yyval.bbexprType, yyvsp[-1].bbinteger);
                }
            }
        }
break;
case 382:
#line 3444 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    int i;
                    CrTypeModifier(yyval.bbexprType.d.t,yyvsp[-2].bbunsPositionPair.d.u);
                    for(i=0; i<yyvsp[-1].bbinteger.data; i++) PrependModifier(yyval.bbexprType.d.t, TypeArray);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-4].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbidIdent, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 383:
#line 3457 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    int i;
                    assert(yyvsp[-2].bbsymbol.d && yyvsp[-2].bbsymbol.d->u.type);
                    yyval.bbexprType.d.t = yyvsp[-2].bbsymbol.d->u.type;
                    for(i=0; i<yyvsp[-1].bbinteger.data; i++) PrependModifier(yyval.bbexprType.d.t, TypeArray);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-4].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbidIdent, yyvsp[0].bbinteger);
                    if (yyval.bbexprType.e.file == s_noneFileIndex) PropagateBorns(yyval.bbexprType, yyval.bbexprType, yyvsp[-1].bbinteger);
                }
            }
        }
break;
case 384:
#line 3472 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    int i;
                    assert(yyvsp[-2].bbsymbol.d && yyvsp[-2].bbsymbol.d->u.type);
                    yyval.bbexprType.d.t = yyvsp[-2].bbsymbol.d->u.type;
                    for(i=0; i<yyvsp[-1].bbinteger.data; i++) PrependModifier(yyval.bbexprType.d.t, TypeArray);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-4].bbidIdent.d->p;
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbidIdent, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 385:
#line 3490 "java_parser.y"
{
            if (regularPass()) yyval.bbinteger.data = 1;
            PropagateBornsIfRegularSyntaxPass(yyval.bbinteger, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 386:
#line 3494 "java_parser.y"
{
            if (regularPass()) yyval.bbinteger.data = yyvsp[-1].bbinteger.data+1;
            PropagateBornsIfRegularSyntaxPass(yyval.bbinteger, yyvsp[-1].bbinteger, yyvsp[0].bbposition);
        }
break;
case 387:
#line 3501 "java_parser.y"
{
            PropagateBornsIfRegularSyntaxPass(yyval.bbposition, yyvsp[-2].bbposition, yyvsp[0].bbposition);
        }
break;
case 388:
#line 3506 "java_parser.y"
{
            if (regularPass()) yyval.bbinteger.data = 0;
            SetNullBorns(yyval.bbinteger);
        }
break;
case 390:
#line 3514 "java_parser.y"
{
            if (regularPass()) yyval.bbinteger.data = 1;
            PropagateBornsIfRegularSyntaxPass(yyval.bbinteger, yyvsp[-1].bbposition, yyvsp[0].bbposition);
        }
break;
case 391:
#line 3518 "java_parser.y"
{
            if (regularPass()) yyval.bbinteger.data = yyvsp[-2].bbinteger.data+1;
            PropagateBornsIfRegularSyntaxPass(yyval.bbinteger, yyvsp[-2].bbinteger, yyvsp[0].bbposition);
        }
break;
case 392:
#line 3525 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *rec=NULL;
                    assert(yyvsp[-2].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                    yyval.bbexprType.d.pp = yyvsp[-2].bbexprType.d.pp;
                    if (yyvsp[-2].bbexprType.d.t->kind == TypeStruct) {
                        javaLoadClassSymbolsFromFile(yyvsp[-2].bbexprType.d.t->u.t);
                        yyval.bbexprType.d.r = findStrRecordFromType(yyvsp[-2].bbexprType.d.t, yyvsp[0].bbidIdent.d, &rec, CLASS_TO_EXPR);
                        assert(rec);
                        yyval.bbexprType.d.t = rec->u.type;
                    } else if (s_language == LANG_JAVA) {
                        yyval.bbexprType.d.t = javaArrayFieldAccess(yyvsp[0].bbidIdent.d);
                    } else {
                        yyval.bbexprType.d.t = &s_errorModifier;
                    }
                    assert(yyval.bbexprType.d.t);
                } else {
                    yyval.bbexprType.d.pp = yyvsp[-2].bbexprType.d.pp;
                    javaCheckForPrimaryStart(&yyvsp[0].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 393:
#line 3550 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *ss,*rec=NULL;

                    yyval.bbexprType.d.r = NULL;
                    yyval.bbexprType.d.pp = &yyvsp[-2].bbidIdent.d->p;
                    ss = javaCurrentSuperClass();
                    if (ss != &s_errorSymbol && ss->bits.symType!=TypeError) {
                        javaLoadClassSymbolsFromFile(ss);
                        yyval.bbexprType.d.r = findStrRecordFromSymbol(ss, yyvsp[0].bbidIdent.d, &rec, CLASS_TO_EXPR, yyvsp[-2].bbidIdent.d);
                        assert(rec);
                        yyval.bbexprType.d.t = rec->u.type;
                    } else {
                        yyval.bbexprType.d.t = &s_errorModifier;
                    }
                    assert(yyval.bbexprType.d.t);
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-2].bbidIdent.d->p;
                    javaCheckForPrimaryStart(&yyvsp[0].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaCheckForStaticPrefixStart(&yyvsp[0].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbidIdent, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 394:
#line 3575 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_symbol *ss,*rec=NULL;

                    ss = javaQualifiedThis(yyvsp[-4].bbidlist.d, yyvsp[-2].bbidIdent.d);
                    if (ss != &s_errorSymbol && ss->bits.symType!=TypeError) {
                        javaLoadClassSymbolsFromFile(ss);
                        ss = javaGetSuperClass(ss);
                        yyval.bbexprType.d.r = findStrRecordFromSymbol(ss, yyvsp[0].bbidIdent.d, &rec, CLASS_TO_EXPR, NULL);
                        assert(rec);
                        yyval.bbexprType.d.t = rec->u.type;
                    } else {
                        yyval.bbexprType.d.t = &s_errorModifier;
                    }
                    yyval.bbexprType.d.r = NULL;
                    assert(yyval.bbexprType.d.t);
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[-4].bbidlist.d);
                    javaCheckForPrimaryStart(&yyvsp[-2].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaCheckForPrimaryStart(&yyvsp[0].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaCheckForStaticPrefixStart(&yyvsp[-2].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaCheckForStaticPrefixStart(&yyvsp[0].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbidlist, yyvsp[0].bbidIdent);
                }
            }
        }
break;
case 395:
#line 3602 "java_parser.y"
{ assert(0); }
break;
case 396:
#line 3603 "java_parser.y"
{ assert(0); }
break;
case 397:
#line 3604 "java_parser.y"
{ assert(0); }
break;
case 398:
#line 3608 "java_parser.y"
{
            if (ComputingPossibleParameterCompletion()) {
                s_cp.erfsForParamsComplet = javaCrErfsForMethodInvocationN(yyvsp[-1].bbidlist.d);
            }
        }
break;
case 399:
#line 3612 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaMethodInvocationN(yyvsp[-5].bbidlist.d,yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    yyval.bbexprType.d.r = NULL;
                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[-5].bbidlist.d);
                    javaCheckForPrimaryStartInNameList(yyvsp[-5].bbidlist.d, yyval.bbexprType.d.pp);
                    javaCheckForStaticPrefixInNameList(yyvsp[-5].bbidlist.d, yyval.bbexprType.d.pp);
                    javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidlist.d->idi.p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-5].bbidlist, yyvsp[0].bbposition);
                }
            }
        }
break;
case 400:
#line 3627 "java_parser.y"
{
            if (ComputingPossibleParameterCompletion()) {
                s_cp.erfsForParamsComplet = javaCrErfsForMethodInvocationT(yyvsp[-3].bbexprType.d.t, yyvsp[-1].bbidIdent.d);
            }
        }
break;
case 401:
#line 3631 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaMethodInvocationT(yyvsp[-7].bbexprType.d.t,yyvsp[-5].bbidIdent.d,yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    yyval.bbexprType.d.r = NULL;
                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                } else {
                    yyval.bbexprType.d.pp = yyvsp[-7].bbexprType.d.pp;
                    javaCheckForPrimaryStart(&yyvsp[-5].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-7].bbexprType, yyvsp[0].bbposition);
                }
            }
        }
break;
case 402:
#line 3645 "java_parser.y"
{
            if (ComputingPossibleParameterCompletion()) {
                s_cp.erfsForParamsComplet = javaCrErfsForMethodInvocationS(yyvsp[-3].bbidIdent.d, yyvsp[-1].bbidIdent.d);
            }
        }
break;
case 403:
#line 3649 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaMethodInvocationS(yyvsp[-7].bbidIdent.d, yyvsp[-5].bbidIdent.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.t);
                    yyval.bbexprType.d.r = NULL;
                    s_cp.erfsForParamsComplet = yyvsp[-4].erfs;
                } else {
                    yyval.bbexprType.d.pp = &yyvsp[-7].bbidIdent.d->p;
                    javaCheckForPrimaryStart(&yyvsp[-7].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaCheckForPrimaryStart(&yyvsp[-5].bbidIdent.d->p, yyval.bbexprType.d.pp);
                    javaHandleDeclaratorParamPositions(&yyvsp[-5].bbidIdent.d->p, &yyvsp[-2].bbposition.d, yyvsp[-1].bbtypeModifiersListPositionLstPair.d.p, &yyvsp[0].bbposition.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-7].bbidIdent, yyvsp[0].bbposition);
                }
            }
        }
break;
case 404:
#line 3673 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    S_typeModifiers *tt;
                    tt = javaClassifyToExpressionName(yyvsp[-3].bbidlist.d, &(yyval.bbexprType.d.r));
                    if (tt->kind==TypeArray) yyval.bbexprType.d.t=tt->next;
                    else yyval.bbexprType.d.t = &s_errorModifier;
                    assert(yyval.bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[-3].bbidlist.d);
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbidlist, yyvsp[0].bbposition);
                }
            }
        }
break;
case 405:
#line 3688 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[-3].bbexprType.d.t->kind==TypeArray) yyval.bbexprType.d.t=yyvsp[-3].bbexprType.d.t->next;
                    else yyval.bbexprType.d.t = &s_errorModifier;
                    assert(yyval.bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = yyvsp[-3].bbexprType.d.pp;
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbexprType, yyvsp[0].bbposition);
                }
            }
        }
break;
case 406:
#line 3701 "java_parser.y"
{ /* rule never used */ }
break;
case 408:
#line 3706 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaClassifyToExpressionName(yyvsp[0].bbidlist.d, &(yyval.bbexprType.d.r));
                } else {
                    yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[0].bbidlist.d);
                    javaCheckForPrimaryStartInNameList(yyvsp[0].bbidlist.d, yyval.bbexprType.d.pp);
                    javaCheckForStaticPrefixInNameList(yyvsp[0].bbidlist.d, yyval.bbexprType.d.pp);
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                }
            }
        }
break;
case 411:
#line 3720 "java_parser.y"
{ /* rule never used */ }
break;
case 412:
#line 3724 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaCheckNumeric(yyvsp[-1].bbexprType.d.t);
                    RESET_REFERENCE_USAGE(yyvsp[-1].bbexprType.d.r, UsageAddrUsed);
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbexprType, yyvsp[0].bbposition);
                }
            }
        }
break;
case 413:
#line 3738 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaCheckNumeric(yyvsp[-1].bbexprType.d.t);
                    RESET_REFERENCE_USAGE(yyvsp[-1].bbexprType.d.r, UsageAddrUsed);
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbexprType, yyvsp[0].bbposition);
                }
            }
        }
break;
case 416:
#line 3754 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 417:
#line 3765 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 419:
#line 3780 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaCheckNumeric(yyvsp[0].bbexprType.d.t);
                    RESET_REFERENCE_USAGE(yyvsp[0].bbexprType.d.r, UsageAddrUsed);
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 420:
#line 3794 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaCheckNumeric(yyvsp[0].bbexprType.d.t);
                    RESET_REFERENCE_USAGE(yyvsp[0].bbexprType.d.r, UsageAddrUsed);
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 422:
#line 3809 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 423:
#line 3820 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[0].bbexprType.d.t->kind == TypeBoolean) yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                    else yyval.bbexprType.d.t = &s_errorModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-1].bbposition, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 425:
#line 3836 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    assert(yyvsp[-2].bbsymbolPositionPair.d.s && yyvsp[-2].bbsymbolPositionPair.d.s->u.type);
                    yyval.bbexprType.d.t = yyvsp[-2].bbsymbolPositionPair.d.s->u.type;
                    yyval.bbexprType.d.r = NULL;
                    assert(yyval.bbexprType.d.t->kind == TypeArray);
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbposition, yyvsp[0].bbexprType);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyvsp[0].bbexprType.b, s_cxRefPos, yyvsp[0].bbexprType.e)
                        && s_spp[SPP_CAST_LPAR_POSITION].file == s_noneFileIndex) {
                        s_spp[SPP_CAST_LPAR_POSITION] = yyvsp[-3].bbposition.b;
                        s_spp[SPP_CAST_RPAR_POSITION] = yyvsp[-1].bbposition.b;
                        s_spp[SPP_CAST_TYPE_BEGIN_POSITION] = yyvsp[-2].bbsymbolPositionPair.b;
                        s_spp[SPP_CAST_TYPE_END_POSITION] = yyvsp[-2].bbsymbolPositionPair.e;
                        s_spp[SPP_CAST_EXPRESSION_BEGIN_POSITION] = yyvsp[0].bbexprType.b;
                        s_spp[SPP_CAST_EXPRESSION_END_POSITION] = yyvsp[0].bbexprType.e;
                    }
                }
            }
        }
break;
case 426:
#line 3858 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    XX_ALLOC(yyval.bbexprType.d.t, S_typeModifiers);
                    FILLF_typeModifiers(yyval.bbexprType.d.t,yyvsp[-2].bbunsPositionPair.d.u,t,NULL,NULL,NULL);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbposition, yyvsp[0].bbexprType);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyvsp[0].bbexprType.b, s_cxRefPos, yyvsp[0].bbexprType.e)
                        && s_spp[SPP_CAST_LPAR_POSITION].file == s_noneFileIndex) {
                        s_spp[SPP_CAST_LPAR_POSITION] = yyvsp[-3].bbposition.b;
                        s_spp[SPP_CAST_RPAR_POSITION] = yyvsp[-1].bbposition.b;
                        s_spp[SPP_CAST_TYPE_BEGIN_POSITION] = yyvsp[-2].bbunsPositionPair.b;
                        s_spp[SPP_CAST_TYPE_END_POSITION] = yyvsp[-2].bbunsPositionPair.e;
                        s_spp[SPP_CAST_EXPRESSION_BEGIN_POSITION] = yyvsp[0].bbexprType.b;
                        s_spp[SPP_CAST_EXPRESSION_END_POSITION] = yyvsp[0].bbexprType.e;
                    }
                }
            }
        }
break;
case 427:
#line 3879 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbposition, yyvsp[0].bbexprType);
                    if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyvsp[0].bbexprType.b, s_cxRefPos, yyvsp[0].bbexprType.e)
                        && s_spp[SPP_CAST_LPAR_POSITION].file == s_noneFileIndex) {
                        s_spp[SPP_CAST_LPAR_POSITION] = yyvsp[-3].bbposition.b;
                        s_spp[SPP_CAST_RPAR_POSITION] = yyvsp[-1].bbposition.b;
                        s_spp[SPP_CAST_TYPE_BEGIN_POSITION] = yyvsp[-2].bbexprType.b;
                        s_spp[SPP_CAST_TYPE_END_POSITION] = yyvsp[-2].bbexprType.e;
                        s_spp[SPP_CAST_EXPRESSION_BEGIN_POSITION] = yyvsp[0].bbexprType.b;
                        s_spp[SPP_CAST_EXPRESSION_END_POSITION] = yyvsp[0].bbexprType.e;
                    }
                }
            }
        }
break;
case 429:
#line 3914 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBinaryNumericPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 430:
#line 3925 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBinaryNumericPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 431:
#line 3936 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBinaryNumericPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 433:
#line 3951 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    int st1, st2;
                    st1 = javaIsStringType(yyvsp[-2].bbexprType.d.t);
                    st2 = javaIsStringType(yyvsp[0].bbexprType.d.t);
                    if (st1 && st2) {
                        yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t;
                    } else if (st1) {
                        yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t;
                        /* TODO add reference to 'toString' on $3.d*/
                    } else if (st2) {
                        yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                        /* TODO add reference to 'toString' on $1.d*/
                    } else {
                        yyval.bbexprType.d.t = javaBinaryNumericPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    }
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 434:
#line 3975 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBinaryNumericPromotion(yyvsp[-2].bbexprType.d.t, yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 436:
#line 3990 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[-2].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 437:
#line 4001 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[-2].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 438:
#line 4012 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaNumericPromotion(yyvsp[-2].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 440:
#line 4027 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 441:
#line 4038 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 442:
#line 4049 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 443:
#line 4060 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 444:
#line 4071 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbsymbol);
                }
            }
        }
break;
case 446:
#line 4086 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 447:
#line 4097 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 449:
#line 4112 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBitwiseLogicalPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 451:
#line 4127 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBitwiseLogicalPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 453:
#line 4142 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaBitwiseLogicalPromotion(yyvsp[-2].bbexprType.d.t,yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 455:
#line 4157 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 457:
#line 4172 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    CrTypeModifier(yyval.bbexprType.d.t,TypeBoolean);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-2].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 459:
#line 4187 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = javaConditionalPromotion(yyvsp[-2].bbexprType.d.t, yyvsp[0].bbexprType.d.t);
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    PropagateBorns(yyval.bbexprType, yyvsp[-4].bbexprType, yyvsp[0].bbexprType);
                }
            }
        }
break;
case 462:
#line 4206 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    if (yyvsp[0].bbexprType.d.t!=NULL && yyvsp[0].bbexprType.d.t->kind==TypeStruct) {
                        s_cps.lastAssignementStruct = yyvsp[0].bbexprType.d.t->u.t;
                    }
                }
                yyval.bbexprType.d = yyvsp[0].bbexprType.d;
            }
        }
break;
case 463:
#line 4215 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    s_cps.lastAssignementStruct = NULL;
                    if (yyvsp[-3].bbexprType.d.r != NULL && s_opt.server_operation == OLO_EXTRACT) {
                        S_reference *rr;
                        rr = duplicateReference(yyvsp[-3].bbexprType.d.r);
                        yyvsp[-3].bbexprType.d.r->usg = s_noUsage;
                        if (yyvsp[-1].bbunsPositionPair.d.u == '=') {
                            RESET_REFERENCE_USAGE(rr, UsageLvalUsed);
                        } else {
                            RESET_REFERENCE_USAGE(rr, UsageAddrUsed);
                        }
                    } else {
                        if (yyvsp[-1].bbunsPositionPair.d.u == '=') {
                            RESET_REFERENCE_USAGE(yyvsp[-3].bbexprType.d.r, UsageLvalUsed);
                        } else {
                            RESET_REFERENCE_USAGE(yyvsp[-3].bbexprType.d.r, UsageAddrUsed);
                        }
                        yyval.bbexprType.d.t = yyvsp[-3].bbexprType.d.t;
                        yyval.bbexprType.d.r = NULL;
                        /*
                          fprintf(dumpOut,": java Type Dump\n"); fflush(dumpOut);
                          javaTypeDump($1.d.t);
                          fprintf(dumpOut,"\n = \n"); fflush(dumpOut);
                          javaTypeDump($4.d.t);
                          fprintf(dumpOut,"\ndump end\n"); fflush(dumpOut);
                        */
                    }
                } else {
                    PropagateBorns(yyval.bbexprType, yyvsp[-3].bbexprType, yyvsp[0].bbexprType);
                    if (s_opt.taskRegime == RegimeEditServer) {
                        if (POSITION_IS_BETWEEN_IN_THE_SAME_FILE(yyvsp[-3].bbexprType.b, s_cxRefPos, yyvsp[-3].bbexprType.e)) {
                            s_spp[SPP_ASSIGNMENT_OPERATOR_POSITION] = yyvsp[-1].bbunsPositionPair.b;
                            s_spp[SPP_ASSIGNMENT_END_POSITION] = yyvsp[0].bbexprType.e;
                        }
                    }
                    yyval.bbexprType.d.pp = NULL_POS;
                }
            }
        }
break;
case 464:
#line 4259 "java_parser.y"
{
            if (regularPass()) {
                yyval.bbexprType.d.pp = javaGetNameStartingPosition(yyvsp[0].bbidlist.d);
                if (! SyntaxPassOnly()) {
                    S_reference *rr;
                    yyval.bbexprType.d.t = javaClassifyToExpressionName(yyvsp[0].bbidlist.d, &rr);
                    yyval.bbexprType.d.r = rr;
                } else {
                    PropagateBorns(yyval.bbexprType, yyvsp[0].bbidlist, yyvsp[0].bbidlist);
                }
            }
        }
break;
case 467:
#line 4273 "java_parser.y"
{ /* rule never used */ }
break;
case 468:
#line 4277 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = '=';
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 469:
#line 4281 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = MUL_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 470:
#line 4285 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = DIV_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 471:
#line 4289 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = MOD_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 472:
#line 4293 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = ADD_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 473:
#line 4297 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = SUB_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 474:
#line 4301 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = LEFT_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 475:
#line 4305 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = RIGHT_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 476:
#line 4309 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = URIGHT_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 477:
#line 4313 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = AND_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 478:
#line 4317 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = XOR_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 479:
#line 4321 "java_parser.y"
{
            if (regularPass()) yyval.bbunsPositionPair.d.u = OR_ASSIGN;
            PropagateBornsIfRegularSyntaxPass(yyval.bbunsPositionPair, yyvsp[0].bbposition, yyvsp[0].bbposition);
        }
break;
case 481:
#line 4329 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    yyval.bbexprType.d.t = &s_errorModifier;
                    yyval.bbexprType.d.r = NULL;
                } else {
                    yyval.bbexprType.d.pp = NULL_POS;
                    SetNullBorns(yyval.bbexprType);
                }
            }
        }
break;
case 483:
#line 4349 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockStart();
                }
            }
        }
break;
case 484:
#line 4358 "java_parser.y"
{
            if (regularPass()) {
                if (! SyntaxPassOnly()) {
                    stackMemoryBlockFree();
                }
            }
        }
break;
#line 7220 "java_parser.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
           lastyystate = yystate;
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
