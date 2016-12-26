#ifndef lint
static char yysccsid[] = "@(#)yaccpar   1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 8 "../../src/cgram.y"

#define yylval cyylval

#define yyparse cyyparse
#define yylhs cyylhs
#define yylen cyylen
#define yydefred cyydefred
#define yydgoto cyydgoto
#define yysindex cyysindex
#define yyrindex cyyrindex
#define yytable cyytable
#define yycheck cyycheck
#define yyname cyyname
#define yyrule cyyrule
#define yydebug cyydebug
#define yynerrs cyynerrs
#define yyerrflag cyyerrflag
#define yychar cyychar
#define lastyystate clastyystate
#define yyssp cyyssp
#define yyval cyyval
#define yyss cyyss
#define yyvs cyyvs
#define yygindex cyygindex
#define yyvsp cyyvsp

#include "stdinc.h"
#include "head.h"
#include "proto.h"      /*SBD*/


#define YYDEBUG 0
#define yyerror styyerror
#define yyErrorRecovery styyErrorRecovery

#define SetStrCompl1(xxx) {                         \
        assert(s_opt.taskRegime);                   \
        if (s_opt.taskRegime == RegimeEditServer) { \
            s_structRecordCompletionType = xxx;     \
            assert(s_structRecordCompletionType);   \
        }                                           \
    }
#define SetStrCompl2(xxx) {                                         \
        assert(s_opt.taskRegime);                                   \
        if (s_opt.taskRegime == RegimeEditServer) {                 \
            if (xxx->m==TypePointer || xxx->m==TypeArray) {         \
                s_structRecordCompletionType = xxx->next;           \
                assert(s_structRecordCompletionType);               \
            } else s_structRecordCompletionType = &s_errorModifier; \
        }                                                           \
    }

#define CrTypeModifier(xxx,ttt) {                                   \
        xxx = crSimpleTypeMofifier(ttt);                            \
        xxx = StackMemAlloc(S_typeModifiers);                       \
        FILLF_typeModifiers(xxx, ttt,f,( NULL,NULL) ,NULL,NULL);    \
    }

#define AddComposedType(ddd, ttt) appendComposedType(&ddd->u.type, ttt)

#line 216 "../../src/cgram.y"
typedef union {
    int                                 integer;
    unsigned                            unsign;
    S_symbol                            *symbol;
    S_symbolList                        *symbolList;
    S_typeModifiers                     *typeModif;
    S_typeModifiersList                 *typeModifList;
    S_freeTrail                         *trail;
    S_idIdent                           *idIdent;
    S_idIdentList                       *idlist;
    S_exprTokenType                     exprType;
    S_intPair                           intpair;
    S_whileExtractData                  *whiledata;
    S_position                          position;
    S_unsPositionPair                   unsPositionPair;
    S_symbolPositionPair                symbolPositionPair;
    S_symbolPositionLstPair             symbolPositionLstPair;
    S_positionLst                       *positionLst;
    S_typeModifiersListPositionLstPair  typeModifiersListPositionLstPair;

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
#line 116 "y.tab.c"
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
#define ANONYME_MOD 323
#define ABSTRACT 324
#define BOOLEAN 325
#define BYTE 326
#define CATCH 327
#define CLASS 328
#define EXTENDS 329
#define FINAL 330
#define FINALLY 331
#define IMPLEMENTS 332
#define IMPORT 333
#define INSTANCEOF 334
#define INTERFACE 335
#define NATIVE 336
#define NEW 337
#define PACKAGE 338
#define PRIVATE 339
#define PROTECTED 340
#define PUBLIC 341
#define SUPER 342
#define SYNCHRONIZED 343
#define THIS 344
#define THROW 345
#define THROWS 346
#define TRANSIENT 347
#define TRY 348
#define TRUE_LITERAL 349
#define FALSE_LITERAL 350
#define NULL_LITERAL 351
#define STRICTFP 352
#define ASSERT 353
#define FRIEND 354
#define OPERATOR 355
#define NAMESPACE 356
#define TEMPLATE 357
#define DELETE 358
#define MUTABLE 359
#define EXPLICIT 360
#define WCHAR_T 361
#define BOOL 362
#define USING 363
#define ASM_KEYWORD 364
#define EXPORT 365
#define VIRTUAL 366
#define INLINE 367
#define TYPENAME 368
#define DYNAMIC_CAST 369
#define STATIC_CAST 370
#define REINTERPRET_CAST 371
#define CONST_CAST 372
#define TYPEID 373
#define TOKEN 374
#define TYPE 375
#define LABEL 376
#define COMPL_FOR_SPECIAL1 377
#define COMPL_FOR_SPECIAL2 378
#define COMPL_THIS_PACKAGE_SPECIAL 379
#define COMPL_TYPE_NAME 380
#define COMPL_STRUCT_NAME 381
#define COMPL_STRUCT_REC_NAME 382
#define COMPL_UP_FUN_PROFILE 383
#define COMPL_ENUM_NAME 384
#define COMPL_LABEL_NAME 385
#define COMPL_OTHER_NAME 386
#define COMPL_CLASS_DEF_NAME 387
#define COMPL_FULL_INHERITED_HEADER 388
#define COMPL_TYPE_NAME0 389
#define COMPL_TYPE_NAME1 390
#define COMPL_PACKAGE_NAME0 391
#define COMPL_EXPRESSION_NAME0 392
#define COMPL_METHOD_NAME0 393
#define COMPL_PACKAGE_NAME1 394
#define COMPL_EXPRESSION_NAME1 395
#define COMPL_METHOD_NAME1 396
#define COMPL_CONSTRUCTOR_NAME0 397
#define COMPL_CONSTRUCTOR_NAME1 398
#define COMPL_CONSTRUCTOR_NAME2 399
#define COMPL_CONSTRUCTOR_NAME3 400
#define COMPL_STRUCT_REC_PRIM 401
#define COMPL_STRUCT_REC_SUPER 402
#define COMPL_QUALIF_SUPER 403
#define COMPL_SUPER_CONSTRUCTOR1 404
#define COMPL_SUPER_CONSTRUCTOR2 405
#define COMPL_THIS_CONSTRUCTOR 406
#define COMPL_IMPORT_SPECIAL 407
#define COMPL_VARIABLE_NAME_HINT 408
#define COMPL_CONSTRUCTOR_HINT 409
#define COMPL_METHOD_PARAM1 410
#define COMPL_METHOD_PARAM2 411
#define COMPL_METHOD_PARAM3 412
#define COMPL_YACC_LEXEM_NAME 413
#define CPP_TOKENS_START 414
#define CPP_INCLUDE 415
#define CPP_DEFINE 416
#define CPP_IFDEF 417
#define CPP_IFNDEF 418
#define CPP_IF 419
#define CPP_ELSE 420
#define CPP_ENDIF 421
#define CPP_ELIF 422
#define CPP_UNDEF 423
#define CPP_PRAGMA 424
#define CPP_LINE 425
#define CPP_DEFINE0 426
#define CPP_TOKENS_END 427
#define CPP_COLLATION 428
#define CPP_DEFINED_OP 429
#define EOI_TOKEN 430
#define CACHING1_TOKEN 431
#define OL_MARKER_TOKEN 432
#define OL_MARKER_TOKEN1 433
#define OL_MARKER_TOKEN2 434
#define TMP_TOKEN1 435
#define TMP_TOKEN2 436
#define CCC_OPER_PARENTHESIS 437
#define CCC_OPER_BRACKETS 438
#define MULTI_TOKENS_START 439
#define IDENTIFIER 440
#define CONSTANT 441
#define LONG_CONSTANT 442
#define FLOAT_CONSTANT 443
#define DOUBLE_CONSTANT 444
#define STRING_LITERAL 445
#define LINE_TOK 446
#define IDENT_TO_COMPLETE 447
#define CPP_MAC_ARG 448
#define IDENT_NO_CPP_EXPAND 449
#define CHAR_LITERAL 450
#define LAST_TOKEN 451
#define YYERRCODE 256
short yylhs[] = {                                        -1,
                                                         54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
                                                         72,   72,   55,   55,   74,   55,   75,   55,   76,   55,
                                                         55,   55,    4,    4,   45,   45,   44,   44,   44,   44,
                                                         56,   56,   56,   56,   56,   56,   56,   56,   56,   77,
                                                         77,   77,   77,   57,   57,   57,   57,   58,   58,   58,
                                                         58,   59,   59,   59,   60,   60,   60,   61,   61,   61,
                                                         61,   61,   62,   62,   62,   63,   63,   64,   64,   65,
                                                         65,   66,   66,   67,   67,   68,   68,   68,   69,   69,
                                                         7,    7,    7,    7,    7,    7,    7,    7,    7,    7,
                                                         7,   70,   70,   79,   16,   80,   80,   80,   82,   26,
                                                         83,   26,   26,   25,   25,    6,   28,   28,   28,   28,
                                                         28,   28,   28,   28,   28,   28,   28,   28,   27,   27,
                                                         27,   27,   84,   84,   81,   81,   17,   13,   13,   13,
                                                         13,   13,   15,   15,   15,   86,   86,   14,   14,   14,
                                                         14,   14,   14,   14,   14,   14,   46,   46,   47,   47,
                                                         47,   48,   48,    2,    2,    5,    5,   33,   33,   34,
                                                         34,   35,   35,   20,   20,   20,   20,   49,   49,   49,
                                                         50,    3,    3,   37,   37,   36,   36,   29,   29,   29,
                                                         29,   18,   18,   19,   19,   19,   19,   19,   19,   19,
                                                         19,    8,    8,    8,    8,   22,   22,   21,   21,   23,
                                                         23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
                                                         42,   42,   43,   43,   43,   41,   41,   40,   40,   30,
                                                         30,   30,   51,   51,   52,   52,   52,   53,   53,   53,
                                                         53,   53,   53,   53,   53,   53,   85,   85,   85,   85,
                                                         78,   78,   89,   89,   89,   89,   89,   89,   89,   89,
                                                         96,   96,   96,   90,   97,   97,   98,   98,   73,   73,
                                                         99,   99,  101,  101,  100,  100,  100,  100,   71,   71,
                                                         91,    9,   10,   11,   12,   92,  102,   92,  103,  104,
                                                         92,  105,  106,  107,   93,  108,  109,  110,   93,  111,
                                                         112,   93,   93,   93,   94,   94,   94,   94,   94,  113,
                                                         114,  114,  114,  114,  114,  115,  115,  116,  116,   95,
                                                         95,    0,    0,  117,  117,  117,  118,  118,  119,  118,
                                                         118,  118,  118,  118,  118,  118,   24,   24,   24,   24,
                                                         32,   32,   39,   39,   38,   38,   38,   31,   31,   87,
                                                         88,    1,    1,
};
short yylen[] = {                                         2,
                                                          1,    1,    1,    1,    1,    1,    1,    3,    3,    1,
                                                          1,    2,    1,    4,    0,    5,    0,    4,    0,    4,
                                                          2,    2,    1,    1,    0,    1,    1,    3,    1,    3,
                                                          1,    2,    2,    2,    2,    2,    2,    4,    2,    1,
                                                          1,    1,    1,    1,    4,    6,    7,    1,    3,    3,
                                                          3,    1,    3,    3,    1,    3,    3,    1,    3,    3,
                                                          3,    3,    1,    3,    3,    1,    3,    1,    3,    1,
                                                          3,    1,    3,    1,    3,    1,    5,    4,    1,    3,
                                                          1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
                                                          1,    1,    3,    1,    0,    3,    3,    1,    0,    4,
                                                          0,    5,    1,    1,    1,    1,    1,    1,    1,    2,
                                                          2,    2,    2,    2,    2,    2,    1,    2,    1,    2,
                                                          1,    2,    0,    4,    0,    2,    2,    1,    1,    1,
                                                          1,    1,    1,    1,    1,    0,    1,    1,    1,    1,
                                                          1,    1,    1,    1,    1,    1,    1,    1,    2,    4,
                                                          3,    2,    1,    1,    1,    1,    1,    1,    2,    4,
                                                          1,    1,    3,    0,    2,    1,    3,    2,    4,    4,
                                                          2,    1,    1,    1,    2,    1,    3,    1,    3,    1,
                                                          1,    1,    2,    1,    3,    3,    4,    3,    4,    4,
                                                          1,    1,    2,    2,    3,    1,    2,    1,    1,    1,
                                                          1,    1,    2,    2,    2,    2,    2,    2,    1,    2,
                                                          1,    3,    1,    3,    1,    1,    3,    1,    3,    2,
                                                          1,    1,    1,    2,    1,    1,    2,    3,    2,    3,
                                                          3,    4,    2,    3,    3,    4,    1,    3,    4,    1,
                                                          4,    6,    2,    2,    2,    2,    2,    2,    2,    2,
                                                          2,    3,    2,    2,    1,    1,    1,    1,    2,    6,
                                                          0,    1,    2,    3,    1,    2,    1,    2,    0,    1,
                                                          2,    0,    0,    0,    0,    6,    0,   10,    0,    0,
                                                          8,    1,    0,    0,    9,    0,    0,    0,   13,    0,
                                                          0,   15,    5,    8,    3,    2,    2,    2,    3,    0,
                                                          0,    1,    1,    4,    4,    1,    3,    2,    3,    6,
                                                          7,    1,    3,    1,    3,    1,    3,    3,    0,    4,
                                                          4,    6,    6,    3,    2,    2,    3,    2,    4,    1,
                                                          1,    2,    2,    3,    2,    4,    3,    1,    2,    0,
                                                          0,    1,    1,
};
short yydefred[] = {                                    300,
                                                        0,    0,  316,    0,  300,  314,    0,    0,  130,  138,
                                                        133,  145,  144,  140,  141,  139,  146,  134,  128,    0,
                                                        131,  132,  142,  143,  156,  157,    0,  135,    0,  117,
                                                        191,  342,    0,    0,  326,  184,    0,  107,    0,  119,
                                                        108,  121,    0,    0,    0,    0,    0,    0,    0,  331,
                                                        0,  109,  147,    0,  148,    0,    0,    0,  324,    0,
                                                        343,  173,    0,  172,    0,    0,    0,  194,  196,    0,
                                                        155,  154,    0,    0,    0,  328,    0,  127,    0,    0,
                                                        0,  318,  317,    0,    0,  106,  129,  118,  110,  120,
                                                        111,  122,  112,  116,  114,  113,  115,    0,  332,    0,
                                                        0,    0,  315,  259,    0,    0,  321,  180,  181,    0,
                                                        176,    0,    0,    0,    0,    0,    0,   10,    1,    3,
                                                        4,    5,    6,    0,    2,    0,    0,    0,   40,   41,
                                                        42,   43,   13,    0,    0,   48,    0,    0,    0,    0,
                                                        0,    0,    0,    0,    0,    0,   79,   92,    0,    7,
                                                        0,  185,  195,  197,  240,   95,  237,  126,    0,  222,
                                                        215,  213,  188,    0,  218,    0,    0,    0,    0,  221,
                                                        186,   44,   94,    0,    0,    0,  327,  333,    0,    0,
                                                        320,  161,  151,    0,    0,  158,    0,    0,    0,    0,
                                                        0,    0,    0,  170,    0,   32,   33,   39,    0,   37,
                                                        12,    0,    0,    0,    0,   35,   36,   21,   22,    0,
                                                        0,    0,    0,   82,   83,   84,   85,   86,   87,   88,
                                                        89,   90,   91,   81,    0,    0,    0,    0,    0,    0,
                                                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                        0,    0,    0,    0,    0,    0,   34,  340,    0,    0,
                                                        0,    0,    0,  220,  224,    0,    0,  189,  190,    0,
                                                        187,  329,  335,    0,  334,  209,  200,  201,    0,    0,
                                                        0,  202,  150,  159,  169,  263,   98,    0,  267,  265,
                                                        0,    0,  322,   95,  179,  177,    0,    0,    0,    0,
                                                        8,    9,    0,    0,    0,    0,   80,   49,   50,   51,
                                                        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                        0,    0,    0,    0,    0,    0,    0,   93,  323,    0,
                                                        0,  238,  124,  233,    0,    0,  229,    0,    0,    0,
                                                        0,  217,  219,  212,  214,  337,    0,    0,    0,  162,
                                                        0,  210,  203,  204,  205,  207,  206,  208,    0,    0,
                                                        0,    0,    0,  273,    0,    0,    0,    0,    0,  273,
                                                        0,  256,    0,  255,    0,    0,    0,    0,  244,  243,
                                                        245,  246,  247,  248,  249,   95,    0,  268,    0,  266,
                                                        264,   38,   95,   45,   14,   29,    0,    0,   27,   24,
                                                        23,   18,   20,   78,    0,  341,  239,  340,  234,  228,
                                                        230,  235,    0,  231,    0,  336,  165,    0,    0,  160,
                                                        297,    0,  296,  253,  272,    0,  258,  257,    0,    0,
                                                        298,    0,    0,    0,  137,    0,   96,   99,    0,   97,
                                                        271,    0,  254,  251,  260,    0,    0,   16,   77,  241,
                                                        0,  236,  232,  167,  163,  252,  272,  282,    0,  295,
                                                        0,  299,    0,    0,    0,    0,  101,  250,    0,   46,
                                                        30,   28,  341,  286,    0,  275,  272,    0,    0,  100,
                                                        0,   47,  242,  287,  293,    0,   95,  279,  275,    0,
                                                        0,    0,  102,   95,    0,    0,  280,  283,  310,    0,
                                                        0,  306,    0,    0,    0,    0,    0,  274,   95,  284,
                                                        0,    0,    0,  311,    0,  288,  294,  273,  277,  281,
                                                        95,    0,    0,  307,    0,    0,   95,  285,  304,  305,
                                                        0,    0,  278,    0,  275,    0,  290,  289,  291,   95,
                                                        292,
};
short yydgoto[] = {                                       1,
                                                          36,   73,   65,  392,   37,   38,  225,   39,  447,  415,
                                                          508,  477,   40,   41,   42,  432,   43,  176,   45,  340,
                                                          269,   70,  271,   46,  164,  366,   48,   49,  111,  165,
                                                          50,   51,  185,  186,  341,  112,  113,  180,   99,  166,
                                                          325,  168,  169,  387,  388,   52,   53,   54,   55,   56,
                                                          170,  255,  256,  133,  134,  172,  136,  137,  138,  139,
                                                          140,  141,  142,  143,  144,  145,  146,  147,  148,  367,
                                                          368,  150,  205,  211,  212,  213,  151,  249,  174,  279,
                                                          76,  456,  471,   78,  158,  426,  105,  379,  280,  370,
                                                          371,  372,  373,  374,  375,  376,  377,  419,  189,  281,
                                                          190,  517,  487,  499,  449,  500,  511,  474,  484,  515,
                                                          529,  530,    2,  492,  493,  482,    5,    6,  100,
};
short yysindex[] = {                                      0,
                                                          0, -144,    0, 2617,    0,    0,   48,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0, -240,
                                                          0,    0,    0,    0,    0,    0, -118,    0,  179,    0,
                                                          0,    0,  188,  -35,    0,    0, -173,    0,    8,    0,
                                                          0,    0,  170, -129,   19,   41,   20, 4100, 2212,    0,
                                                          4133,    0,    0,  122,    0,  155,    0,  172,    0,  193,
                                                          0,    0, -231,    0,    0, 2287,  284,    0,    0,  -35,
                                                          0,    0,    0,   19,  219,    0,  303,    0,  893, 1771,
                                                          188,    0,    0,  170, -129,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   69,    0,   48,
                                                          -87, -231,    0,    0,  -28, -144,    0,    0,    0,  316,
                                                          0,  335,  285, 2298, 2298, -226, 2364,    0,    0,    0,
                                                          0,    0,    0,  -33,    0, 1611, 2287, 2287,    0,    0,
                                                          0,    0,    0,    6,  416,    0,  424,  198,  299,  -19,
                                                          -91,  415,  370,  346,  215,  -51,    0,    0,  159,    0,
                                                          2287,    0,    0,    0,    0,    0,    0,    0,  -33,    0,
                                                          0,    0,    0,  126,    0,  443,  427,  451,  453,    0,
                                                          0,    0,    0,  435,  170, -129,    0,    0,  170,  228,
                                                          0,    0,    0, 1268,  -83,    0,  413, -226,  258,  164,
                                                          422, 2287, -231,    0, 1837,    0,    0,    0, 1611,    0,
                                                          0,   93,  511,  210,  519,    0,    0,    0,    0, 2287,
                                                          514,  516,  296,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0, 2287, 2287, 2287, 2287, 2287, 2287,
                                                          2287, 2287, 2287, 2287, 2287, 2287, 2287, 2287, 2287, 2287,
                                                          2287, 2287, 2287, 1850, 2287,  508,    0,    0,   -7,  550,
                                                          2711, 1912,  183,    0,    0,   32, 3990,    0,    0, -236,
                                                          0,    0,    0,   14,    0,    0,    0,    0,  -23, 3345,
                                                          3375,    0,    0,    0,    0,    0,    0, 1302,    0,    0,
                                                          258, -226,    0,    0,    0,    0,  552, 2948,   84, 2004,
                                                          0,    0,   83, 1932, -233, -233,    0,    0,    0,    0,
                                                          424,  424,  198,  198,  299,  299,  299,  299,  -19,  -19,
                                                          -91,  415,  370,  346,  215, 2287,  -31,    0,    0,  219,
                                                          450,    0,    0,    0,  554,  556,    0,  522,   32, 3126,
                                                          2026,    0,    0,    0,    0,    0,  170, 2287,  564,    0,
                                                          256,    0,    0,    0,    0,    0,    0,    0,    0,  565,
                                                          2287,  568,  576,    0,  595, -229,  597, 2043,  600,    0,
                                                          -105,    0,    0,    0,  139,  259,  601,  582,    0,    0,
                                                          0,    0,    0,    0,    0,    0,  588,    0,  525,    0,
                                                          0,    0,    0,    0,    0,    0,  611,  617,    0,    0,
                                                          0,    0,    0,    0, 2287,    0,    0,    0,    0,    0,
                                                          0,    0,  624,    0,  573,    0,    0, 2287,  -23,    0,
                                                          0,  612,    0,    0,    0, 2287,    0,    0,  608, 2287,
                                                          0,  290, 2287,  631,    0,  632,    0,    0,  188,    0,
                                                          0, 1723,    0,    0,    0,    1, 2096,    0,    0,    0,
                                                          219,    0,    0,    0,    0,    0,    0,    0,  615,    0,
                                                          261,    0,  343, 2287, 2287,  170,    0,    0,  555,    0,
                                                          0,    0,    0,    0,  304,    0,    0,  344,   57,    0,
                                                          170,    0,    0,    0,    0, 2287,    0,    0,    0,  623,
                                                          -299,  232,    0,    0,  625,  383,    0,    0,    0,  646,
                                                          647,    0,  654,  640, -299,  391,  323,    0,    0,    0,
                                                          2287, 2287, -299,    0,  654,    0,    0,    0,    0,    0,
                                                          0,  364,  389,    0,  664, 2287,    0,    0,    0,    0,
                                                          2287,  665,    0,  402,    0,  649,    0,    0,    0,    0,
                                                          0,
};
short yyrindex[] = {                                      0,
                                                          0,  216,    0,    0,    0,    0,  108, 2398,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0, 2907,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,   34,    0,    0,  586,    0,    0,    0,
                                                          0,    0,  302, 3231, 3025,    0,    0,   29,   -8,    0,
                                                          590,    0,    0,    0,    0,    0,  185,  609,    0, 2757,
                                                          0,    0,    0,    0, 2531,    0,    0,    0,    0,   73,
                                                          0,    0, 2571, 3058,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  302, 3262,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          4178,    0,    0,    0,  810,  293,    0,    0,    0,   13,
                                                          0,  580,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0, 3440,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0, 3554, 3713,    0, 3723, 1205, 3966, 2146,
                                                          1256, 2031,  273,   99,  585,   36,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  406,    0,  670,    0,    0,  673,    0,
                                                          0,    0,    0,    0,  302,  151,    0,    0,  302,    0,
                                                          0,    0,    0,    0, 4178,    0,    0,    0, 1398, 1101,
                                                          2855,    0,  591,    0,    0,    0,    0,    0,    0,    0,
                                                          0,  674,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,  421,    0,    0,  479,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,  309,  130,
                                                          -36,    0,    0,    0,    0,    0,    0,  658,    0,    0,
                                                          1197,    0,    0,    0,    0,    0,    0,    0,  677,    0,
                                                          0,    0,    0,  680,    0,    0,    0,    0,    0,    0,
                                                          3801, 3811, 3848, 3959, 4048, 4085, 4092, 4200, 2861, 3365,
                                                          4118, 2511, 1104,  248, 1695,    0,    0,    0,    0,    0,
                                                          1413,    0,    0,    0,    0,    0,    0,    0,  501,    0,
                                                          0,    0,    0,    0,    0,    0,  302,    0,  342,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,  513,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          679,    0, 3686,    0,    0,    0,   62,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,  681,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,  309,    0,
                                                          0,    0,    0,    0,    0,  658,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,  658,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,  302,    0,    0, 1413,    0,
                                                          0,    0,    0,    0, 2138,    0,    0,    0,    0,    0,
                                                          302,    0,    0,    0,    0,  658,    0,    0,    0,    0,
                                                          269,    0,    0,    0,    0,  714,    0,    0,    0,  279,
                                                          280,    0,  298,    0,  269,    0, 2158,    0,    0,    0,
                                                          0,    0,  269,    0,  313,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,  682,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,
};
short yygindex[] = {                                      0,
                                                          3,    0,    0,  428,    0,   42,    0,   -5, -351, -314,
                                                          227, -403,  534,   38,  678,   -2,  203,   35,  -21,  320,
                                                          0,  546,    0,    0,   16,    0,    0,    0,  538,  477,
                                                          0,    0,    0,  551,    0,    0,  635,    0,    0,    0,
                                                          -77,    0,    0,    0,    0,   58,    0,    0,    0,    0,
                                                          -34, -207, -200,    0,    0,  -65,  449,  356,  358,  384,
                                                          393,  499,  500,  502,  503,  498,  505,  369,  408,  -63,
                                                          -323,   78,    2,    0,    0,    0,    0,  359,   44,  463,
                                                          7,    0,    0,    0, -304,    0, -235, -332, -137,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,   10,  243,  255,    0,  645,  -46,    0,
};
#define YYTABLESIZE 4558
short yytable[] = {                                       4,
                                                          135,  167,  149,  199,   63,  199,   34,  199,   59,  135,
                                                          103,  244,  320,  107,   57,  396,   33,   74,   34,   47,
                                                          61,  199,  199,   61,  108,   61,  395,   61,   68,   64,
                                                          61,  105,  105,  105,  338,  105,  321,  183,   44,   72,
                                                          235,  273,  236,  326,  459,  424,  334,   33,  196,  197,
                                                          105,  200,  329,   33,    4,   34,  178,    4,   79,   33,
                                                          135,   34,  204,  440,  153,  110,   98,   67,  104,  104,
                                                          104,  330,  104,  192,  192,  488,   76,  192,   83,   76,
                                                          326,   85,  105,   61,   81,   91,   95,  104,  329,   89,
                                                          177,  203,  448,   76,   76,  464,  210,  480,  184,   82,
                                                          245,  181,  270,    4,  110,   93,   97,  325,   33,   80,
                                                          34,    3,  193,  193,  481,  478,  193,  322,  198,  104,
                                                          270,  527,  331,  288,  192,  460,  245,  178,   76,  135,
                                                          473,  204,  288,  135,   34,  204,  463,  178,   61,   72,
                                                          490,  202,   72,  380,  135,  124,  293,  325,  390,  325,
                                                          476,  330,  485,  248,  109,  417,   72,   72,  253,  135,
                                                          76,   72,  441,  193,  287,  251,  325,   34,  182,  198,
                                                          58,  198,  182,  198,  252,  385,  237,  238,   33,  135,
                                                          34,  262,  184,  252,  313,  263,  278,  198,  198,   11,
                                                          276,   72,  522,  516,  123,  110,  289,  427,  254,  246,
                                                          284,  201,  245,   32,   60,   18,   32,   71,   32,  123,
                                                          32,  123,  135,   32,  202,  312,  252,   28,   66,  243,
                                                          199,  268,  251,   72,   95,  267,   95,   33,  135,   34,
                                                          75,   74,  325,   61,   77,  285,  250,  103,  433,  243,
                                                          229,  272,  230,   95,  101,  253,  233,  234,  105,   84,
                                                          291,  132,  403,  245,  135,   95,  127,   95,  126,   11,
                                                          128,  129,  335,  130,   61,   62,   32,  208,  209,  336,
                                                          61,  264,  494,  252,   95,   18,   61,  102,  278,  369,
                                                          364,    4,  289,  175,  381,   67,  265,   28,   73,  495,
                                                          192,   73,  135,  365,  422,  328,  104,  391,  391,  409,
                                                          179,  466,  429,  339,  245,   73,   73,  344,  346,  301,
                                                          73,  343,  301,   70,  410,  106,   70,  430,  398,  302,
                                                          303,   32,  302,  303,  152,   61,  301,  345,  348,  193,
                                                          70,   70,   95,  245,   95,   70,  302,  303,  308,  486,
                                                          73,  156,  159,  406,  131,  125,  496,  188,  452,  199,
                                                          135,   95,  164,  309,  135,  308,  451,  135,  418,  453,
                                                          125,  510,   31,  325,  325,   70,  135,  164,   72,   72,
                                                          309,  135,   73,  518,  405,  135,  192,  105,  193,  523,
                                                          248,  407,   61,  467,  479,  166,  245,  245,  135,  135,
                                                          468,  469,  531,   31,  412,   61,   70,   70,  325,   31,
                                                          166,  325,  325,  199,  519,   31,  325,  245,  325,  194,
                                                          135,  124,  325,  325,  104,  325,   32,  325,  325,  192,
                                                          325,  325,  325,  325,  325,  325,  325,  325,  325,  520,
                                                          325,  105,  245,  369,  364,  135,  135,  512,  513,   61,
                                                          95,   95,  526,  339,   61,  245,  223,   32,  173,  223,
                                                          135,  444,  239,   32,   31,  135,  398,  524,  193,   32,
                                                          228,  225,  470,  240,  225,  226,  337,  258,  104,  241,
                                                          227,  325,   95,  192,  155,   95,  224,  483,   95,   95,
                                                          114,  115,  157,   95,  242,   95,  257,  325,  116,   95,
                                                          95,  259,   95,  325,   95,   95,  260,   95,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,   32,   95,
                                                          95,   31,  193,  277,   95,  198,   95,   73,   73,  226,
                                                          95,   95,  226,   95,   31,   95,   95,  261,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,  275,   95,  282,
                                                          117,  227,   70,   70,  227,  250,  283,  325,   95,   95,
                                                          250,  290,  250,  294,  250,  250,  103,  250,  491,  292,
                                                          173,  295,  231,  232,   95,   32,  319,  428,   31,  198,
                                                          95,  103,  491,   31,  397,  206,  207,  296,   32,   95,
                                                          491,   90,   94,   95,  301,  302,   95,   95,  303,  304,
                                                          323,   95,  382,   95,  399,   95,  400,   95,   95,  247,
                                                          95,   95,   95,   95,  118,   95,   95,   95,   95,   95,
                                                          95,   95,   95,   95,  401,   95,  305,  306,  307,  308,
                                                          173,  408,   32,  411,   95,   74,  413,   32,   74,  309,
                                                          310,  457,  297,  414,  416,  250,  420,  250,  250,  423,
                                                          431,  340,   74,   74,  245,  434,  340,   74,  340,  435,
                                                          340,  340,  318,  340,  437,   95,   95,  438,  119,  120,
                                                          121,  122,  123,  124,  442,  443,  450,  340,  125,  446,
                                                          454,  455,   95,  465,  298,  299,  300,   74,   95,  472,
                                                          475,  489,  498,  497,  394,  501,  502,  214,  215,  216,
                                                          217,  218,  219,  220,  221,  222,  223,  503,  504,  173,
                                                          507,  389,  506,  521,  174,  525,  173,  528,  153,   74,
                                                          216,   69,  319,  211,  223,  175,  269,  225,  136,  173,
                                                          25,   26,  269,  393,  509,   92,   96,  157,  445,  270,
                                                          286,  340,   95,  333,  340,  274,  187,  311,  384,  312,
                                                          315,  436,  313,  378,  314,  514,  276,  154,  317,  505,
                                                          191,  276,    0,  276,    0,  276,  276,    0,  276,    0,
                                                          0,    0,    0,  439,    0,    0,    0,    0,  250,  250,
                                                          0,    0,  276,    0,  250,  250,  173,    0,    0,    0,
                                                          0,    0,  250,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  250,  250,  250,  250,  250,  250,  250,
                                                          250,  250,    0,  250,  250,  250,  250,  250,  250,  250,
                                                          250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
                                                          250,  250,  250,  250,  250,  250,  276,    0,  276,  276,
                                                          0,    0,  261,    0,  462,    0,    0,  261,  157,  261,
                                                          0,  261,  261,    0,  261,   74,    0,    0,    0,    0,
                                                          0,   69,    0,    0,  340,  340,    0,    0,  261,    0,
                                                          340,  340,    0,    0,    0,    0,  250,    0,  340,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,  250,    0,    0,    0,    0,  250,  250,  340,
                                                          340,  340,  340,  340,  340,  340,  340,  340,    0,  340,
                                                          340,  340,  340,  340,  340,  340,  340,  340,  340,  340,
                                                          340,  340,  340,  340,  340,  340,  340,  340,  340,  340,
                                                          340,  340,  261,  163,    0,  261,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,  154,  347,    0,
                                                          0,    0,  250,  250,  250,  250,  250,  250,    0,    0,
                                                          0,    0,  250,    0,    0,    0,    0,    0,    0,  276,
                                                          276,    0,  340,    0,    0,  276,  276,    0,    0,    0,
                                                          0,    0,    0,  276,  340,    0,    0,    0,  340,    0,
                                                          0,    0,    0,  340,  340,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,  276,  276,  276,  276,  276,  276,
                                                          276,  276,  276,    0,  276,  276,  276,  276,  276,  276,
                                                          276,  276,  276,  276,  276,  276,  276,  276,  276,  276,
                                                          276,  276,  276,  276,  276,  276,  276,    0,  425,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,  340,  340,
                                                          340,  340,  340,  340,    0,    0,    0,    0,  340,    0,
                                                          0,    0,    0,    0,    0,  261,  261,    0,    0,    0,
                                                          0,  261,  261,    0,    0,    0,    0,  276,    0,  261,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  276,    0,    0,    0,    0,  276,  276,
                                                          261,  261,  261,  261,  261,  261,  261,  261,  261,    0,
                                                          261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
                                                          261,  261,  261,  261,  261,  261,  261,  261,  261,  261,
                                                          261,  261,  261,  262,    0,    0,    0,    0,  262,    0,
                                                          262,    0,  262,  262,   71,  262,    0,   71,  160,   86,
                                                          0,    0,    0,  276,  276,  276,  276,  276,  276,  262,
                                                          0,   71,   71,  276,    0,    0,   71,    0,    0,    0,
                                                          0,    0,    0,  261,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    9,    0,    0,   10,   11,    0,  261,
                                                          0,   12,    0,   13,  261,  261,   71,   14,   15,    0,
                                                          16,    0,   17,   18,    0,   19,   87,   21,   22,   23,
                                                          24,   25,   26,   27,    0,   28,    0,    0,    0,    0,
                                                          0,    0,    0,  262,    0,    0,  262,   71,   71,   95,
                                                          0,    0,    0,    0,   95,    0,   95,    0,   95,   95,
                                                          0,   95,   55,    0,    0,   55,    0,    0,   55,  261,
                                                          261,  261,  261,  261,  261,   95,    0,    0,    0,  261,
                                                          0,    0,   55,   55,   55,    0,   55,   55,    0,    0,
                                                          0,    0,   30,    0,    0,    0,    0,    0,  161,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,   66,    0,    0,   66,   55,   55,   66,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,   66,   66,    0,    0,    0,   66,   95,
                                                          0,  341,   95,    0,    0,    0,    0,    0,   55,   55,
                                                          0,    0,  162,    0,  132,    0,    0,    0,    0,  127,
                                                          0,  126,    0,  128,  129,    0,  130,    0,   66,   66,
                                                          0,    0,    0,    0,    0,    0,  262,  262,    0,    0,
                                                          0,    0,  262,  262,    0,    0,    0,    0,    0,    0,
                                                          262,    0,    0,   71,   71,    0,    0,    0,    0,   66,
                                                          66,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,  262,  262,  262,  262,  262,  262,  262,  262,  262,
                                                          0,  262,  262,  262,  262,  262,  262,  262,  262,  262,
                                                          262,  262,  262,  262,  262,  262,  262,  262,  262,  262,
                                                          262,  262,  262,  262,   58,    0,    0,  131,    0,    0,
                                                          95,    0,    0,    0,    0,   95,    0,   95,    0,   95,
                                                          95,    0,   95,    0,    0,   95,    0,    0,    0,    0,
                                                          95,    0,   95,   95,   95,   95,   95,   95,   95,   95,
                                                          0,    0,    0,    0,  262,    0,   95,    0,   55,   55,
                                                          55,   55,   55,   55,   55,   55,    0,    0,    0,    0,
                                                          262,    0,    0,    0,    0,  262,  262,   95,   95,   95,
                                                          95,   95,   95,   95,   95,   95,    0,   95,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
                                                          95,    0,    0,   95,   86,   66,   66,    0,    0,    0,
                                                          0,    0,    0,    0,    0,   95,    0,    0,   95,    0,
                                                          262,  262,  262,  262,  262,  262,    0,    0,    0,    0,
                                                          262,    0,    0,    0,    0,    0,    0,  349,    8,    0,
                                                          95,   10,   11,  114,  115,    0,   12,    0,   13,    0,
                                                          0,  116,   14,   15,    0,   16,   95,   17,   18,    0,
                                                          0,   95,   95,    0,   23,   24,   25,   26,   27,    0,
                                                          28,    0,    9,  350,  351,   10,   11,  352,  353,  354,
                                                          12,    0,   13,  355,  356,  357,   14,   15,  358,   16,
                                                          359,   17,   18,  360,   19,   87,   21,   22,   23,   24,
                                                          25,   26,   27,  117,   28,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,   95,   95,   95,   95,
                                                          95,   95,    0,  132,    0,    0,   95,  266,  127,    0,
                                                          126,    0,  128,  129,   95,  130,    0,    0,    0,   95,
                                                          95,    0,    0,    0,    0,  361,    0,   95,   95,    0,
                                                          0,    0,    0,    0,   95,   95,    0,    0,    0,    0,
                                                          0,   30,   95,    0,    0,    0,  362,  118,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,    0,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
                                                          95,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,   58,   95,   75,  131,    0,   75,    0,
                                                          0,  363,  120,  121,  122,  123,  124,    0,    0,    0,
                                                          0,  125,   75,   75,    0,  132,    0,   75,    0,    0,
                                                          127,   95,  126,    0,  128,  129,    0,  130,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   95,    0,    0,
                                                          0,    0,   95,   95,    0,    0,    0,   75,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,   95,    0,
                                                          0,    0,    0,  132,    0,    0,    0,    0,  127,    0,
                                                          126,    0,  128,  129,    0,  130,    0,    0,    0,   75,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   95,   95,   95,
                                                          95,   95,   95,    0,    0,   58,    0,   95,  131,    0,
                                                          0,    0,   95,   95,   95,   95,   95,   95,    0,    0,
                                                          0,    0,   95,  171,    0,    0,    0,   86,    0,  132,
                                                          0,    0,  114,  115,  127,    0,  126,    0,  128,  129,
                                                          116,  130,  132,    0,    0,    0,    0,  127,    0,  126,
                                                          0,  128,  129,    0,  130,    0,  131,    0,    0,    0,
                                                          0,    9,    0,    0,   10,   11,    0,  316,    0,   12,
                                                          0,   13,    0,    0,    0,   14,   15,    0,   16,    0,
                                                          17,   18,    0,   19,   87,   21,   22,   23,   24,   25,
                                                          26,   27,  117,   28,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,  132,    0,    0,    0,    0,  127,
                                                          0,  126,    0,  128,  129,    0,  130,    0,    0,   58,
                                                          0,    0,  131,    0,  132,   75,    0,    0,    0,  127,
                                                          0,  126,    0,  128,  129,  131,  130,    0,  458,   61,
                                                          0,    0,    0,    0,  114,  115,    0,    0,    0,    0,
                                                          30,    0,  116,    0,    0,    0,  118,    0,    0,    0,
                                                          0,    0,    0,    0,  327,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,  350,  351,    0,    0,  352,  353,
                                                          354,    0,    0,    0,  355,  356,  357,    0,    0,  358,
                                                          0,  359,  114,  115,  360,    0,  132,  131,    0,    0,
                                                          116,  127,    0,  126,  117,  128,  129,    0,  130,    0,
                                                          119,  120,  121,  122,  123,  124,    0,  131,  132,    0,
                                                          125,    0,    0,  127,    0,  126,    0,  128,  129,    0,
                                                          130,   68,    0,    0,   68,  132,    0,    0,    0,    0,
                                                          127,    0,  126,    0,  128,  129,  361,  130,   68,   68,
                                                          0,    0,  117,   68,    0,    0,    0,    0,  114,  115,
                                                          0,  421,    0,    0,    0,    0,  116,  362,  118,    0,
                                                          0,  114,  115,    0,    0,    0,    0,    0,  404,  116,
                                                          0,    0,    0,   68,   68,    0,  383,    0,  132,  131,
                                                          0,    0,    0,  127,    0,  126,    0,  128,  129,    0,
                                                          130,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,  131,    0,    0,   68,   68,  118,    0,  117,    0,
                                                          0,    0,  363,  120,  121,  122,  123,  124,  131,    0,
                                                          273,  117,  125,  114,  115,  273,    0,  273,    0,  273,
                                                          273,  116,  273,   63,    0,    0,   63,    0,    0,   63,
                                                          274,    0,    0,  114,  115,  274,  273,  274,  274,  274,
                                                          274,  116,  274,   63,   63,    0,    0,    0,   63,    0,
                                                          119,  120,  121,  122,  123,  124,    0,    0,    0,    0,
                                                          125,  131,  118,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  117,    0,  118,    0,    0,   63,   63,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  117,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  273,    0,  114,  115,    0,    0,   63,
                                                          63,    0,    0,  116,    0,    0,  119,  120,  121,  122,
                                                          123,  124,    0,  274,    0,    0,  125,  114,  115,  119,
                                                          120,  121,  122,  123,  124,  116,    0,  118,    0,  125,
                                                          68,   68,    0,    0,  114,  115,    0,    0,    0,    0,
                                                          0,    0,  116,    0,  386,    0,    0,  118,    0,  132,
                                                          0,    0,    0,    0,  127,  117,  126,    0,  128,  129,
                                                          132,  130,    0,    0,    0,  127,    0,  195,    0,  128,
                                                          129,    0,  130,    0,    0,    0,    0,  117,    0,    0,
                                                          0,  119,  120,  121,  122,  123,  124,  114,  115,    0,
                                                          0,  125,    0,    0,  117,  116,    0,    0,    0,    0,
                                                          0,  119,  120,  121,  122,  123,  124,    0,    0,    0,
                                                          0,  125,    0,    0,    0,    0,    0,    0,    0,  118,
                                                          0,    0,    0,    0,    0,    0,  132,    0,    0,  273,
                                                          273,  127,    0,  199,    0,  128,  129,  273,  130,    0,
                                                          0,  118,  131,   63,   63,   63,   63,  117,    0,  274,
                                                          274,    0,    0,  131,    0,    0,    0,  274,  118,    0,
                                                          0,    0,    0,    0,    0,    0,    0,  106,  106,  106,
                                                          0,  106,    0,  119,  120,  121,  122,  123,  124,    0,
                                                          0,    0,    0,  125,    0,  343,  106,    0,  343,  273,
                                                          0,    0,    0,    0,    0,  119,  120,  121,  122,  123,
                                                          124,    0,    0,    0,    0,  125,    0,    0,  461,  274,
                                                          0,  118,  119,  120,  121,  122,  123,  124,  106,  131,
                                                          0,    0,  125,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    9,    0,    0,   10,   11,    0,    0,    0,
                                                          12,    0,   13,    0,    0,    0,   14,   15,    0,   16,
                                                          343,   17,   18,  273,   19,   87,   21,   22,   23,   24,
                                                          25,   26,   27,    0,   28,  119,  120,  121,  122,  123,
                                                          124,    0,    0,  274,    0,  125,    0,    0,  114,  115,
                                                          0,   69,    0,    0,   69,    0,  116,    0,    0,  114,
                                                          115,    0,    0,    0,    0,    0,    0,  116,   69,   69,
                                                          168,  168,  168,   69,  168,    0,    0,  273,  273,  273,
                                                          273,  273,  273,    0,    0,    0,    0,  273,  168,  168,
                                                          0,    0,    0,    0,    0,    0,    0,  274,  274,  274,
                                                          274,  274,  274,   69,   69,    0,    0,  274,  117,    0,
                                                          149,  149,  149,    0,  149,    0,    0,    0,    0,  117,
                                                          0,  168,    0,    0,    0,  114,  115,    0,  149,  149,
                                                          0,    0,    0,  116,   69,   69,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  171,  106,    0,   33,    0,   34,    0,
                                                          0,  149,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,  118,    0,    0,   35,    0,    0,    0,    0,
                                                          0,    0,    0,  118,    0,  117,    0,    0,  106,    0,
                                                          0,  106,  106,  152,    0,    0,  106,    0,  106,    0,
                                                          0,    0,  106,  106,    0,  106,    0,  106,  106,    0,
                                                          106,  106,  106,  106,  106,  106,  106,  106,  106,    0,
                                                          106,    0,    0,    0,    0,    0,  119,  120,  121,  122,
                                                          123,  124,    0,    0,    0,    0,  125,  119,  120,  121,
                                                          122,  123,  124,    0,    0,    0,    0,  125,    0,  118,
                                                          251,  324,   34,    0,    0,    0,    0,    0,    0,    0,
                                                          0,  343,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,  343,    0,    0,
                                                          69,   69,    0,  106,    0,    0,    0,  168,    0,    0,
                                                          0,    0,    0,    0,    0,    0,   95,    0,   95,    0,
                                                          0,  252,    0,  119,  120,  121,  122,  123,  124,    0,
                                                          0,    0,    0,  125,    0,   95,    0,    0,    0,    0,
                                                          0,  168,    0,    0,  168,  168,    0,  149,    0,  168,
                                                          0,  168,    0,    0,    0,  168,  168,  106,  168,    0,
                                                          168,  168,    0,  168,  168,  168,  168,  168,  168,  168,
                                                          168,  168,    0,  168,    0,    0,    0,    0,    0,    0,
                                                          0,  149,    0,    0,  149,  149,    0,    0,    0,  149,
                                                          0,  149,    7,    8,    0,  149,  149,    0,  149,    0,
                                                          149,  149,    0,  149,  149,  149,  149,  149,  149,  149,
                                                          149,  149,    0,  149,  300,    0,  300,    0,   64,    0,
                                                          0,   64,    0,    0,   64,    0,    0,    9,    0,    0,
                                                          10,   11,    0,  300,    0,   12,  168,   13,   64,   64,
                                                          0,   14,   15,   64,   16,    0,   17,   18,    0,   19,
                                                          20,   21,   22,   23,   24,   25,   26,   27,    0,   28,
                                                          0,    0,    0,    0,    0,    0,  129,    0,  129,    0,
                                                          0,    0,    0,   64,   64,    0,  149,    0,    0,    0,
                                                          0,    0,    0,    0,    0,  129,  160,    8,    0,    0,
                                                          168,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          29,    0,    0,    0,   64,   64,    0,  288,  324,   34,
                                                          0,    0,    0,    0,    0,    0,   30,    0,    0,    0,
                                                          0,    9,   31,    0,   10,   11,    0,    0,    0,   12,
                                                          149,   13,   95,   95,    0,   14,   15,    0,   16,    0,
                                                          17,   18,    0,   19,   87,   21,   22,   23,   24,   25,
                                                          26,   27,    0,   28,    0,    0,    0,    0,  252,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   95,    0,    0,
                                                          95,   95,    0,    0,    0,   95,   32,   95,    0,    0,
                                                          0,   95,   95,    0,   95,  182,   95,   95,  182,   95,
                                                          95,   95,   95,   95,   95,   95,   95,   95,    0,   95,
                                                          0,    0,  182,  182,    0,  182,    0,    0,    0,    0,
                                                          30,    0,    0,    0,    0,    0,   31,    0,  183,    0,
                                                          0,  183,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          300,  300,    0,    0,    0,  183,  183,    0,  183,    0,
                                                          95,    0,    0,    0,    0,    0,    0,    0,   64,   64,
                                                          64,   64,    0,    0,    0,    0,   95,    0,    0,    0,
                                                          0,    0,   95,    0,    0,  300,    0,  182,  300,  300,
                                                          32,    0,    0,  300,    0,  300,    0,    0,    0,  300,
                                                          300,    0,  300,  129,  300,  300,  402,  300,  300,  300,
                                                          300,  300,  300,  300,  300,  300,    0,  300,    0,    0,
                                                          183,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,   95,  129,    0,    0,
                                                          129,  129,    0,  160,   86,  129,    0,  129,    0,    0,
                                                          0,  129,  129,    0,  129,    0,  129,  129,  300,  129,
                                                          129,  129,  129,  129,  129,  129,  129,  129,    0,  129,
                                                          0,    0,    0,    0,  300,    0,    0,    0,    9,    0,
                                                          300,   10,   11,    0,    0,    0,   12,    0,   13,    0,
                                                          0,    0,   14,   15,    0,   16,    0,   17,   18,    0,
                                                          19,   87,   21,   22,   23,   24,   25,   26,   27,    0,
                                                          28,    0,    0,    0,  123,    0,    0,    0,    0,    0,
                                                          0,  182,    0,    0,    0,    0,  129,    0,    0,  123,
                                                          0,  123,  129,    0,  300,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,  123,    0,    0,    0,    0,
                                                          0,    0,    0,    0,  183,  182,    0,    0,  182,  182,
                                                          123,    0,  123,  182,    0,  182,    0,   30,    0,  182,
                                                          182,    0,  182,    0,  182,  182,    0,  182,  182,  182,
                                                          182,  182,  182,  182,  182,  182,  129,  182,  183,    0,
                                                          0,  183,  183,  338,    0,    0,  183,    0,  183,    0,
                                                          0,    0,  183,  183,    0,  183,    0,  183,  183,    0,
                                                          183,  183,  183,  183,  183,  183,  183,  183,  183,    0,
                                                          183,  160,   86,    0,  339,    0,    0,    0,  182,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,   65,    0,  182,   65,    0,    0,   65,    0,
                                                          0,    0,    0,    0,    0,    0,    9,    0,    0,   10,
                                                          11,  183,   65,   65,   12,    0,   13,   65,    0,    0,
                                                          14,   15,    0,   16,    0,   17,   18,  183,   19,   87,
                                                          21,   22,   23,   24,   25,   26,   27,    0,   28,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   65,   65,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,   11,   11,    0,   11,
                                                          11,   11,   11,   11,   11,   11,   11,  338,   65,   65,
                                                          0,    0,    0,    0,    0,    0,    0,   11,   11,   11,
                                                          11,   11,   11,    0,    0,   30,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,  339,    0,
                                                          0,  338,    0,    0,  338,  338,    0,    0,    0,  338,
                                                          11,  338,   11,   11,    0,  338,  338,    0,  338,    0,
                                                          338,  338,    0,  338,  338,  338,  338,  338,  338,  338,
                                                          338,  338,  339,  338,    0,  339,  339,    0,    0,    0,
                                                          339,    0,  339,   11,   11,    0,  339,  339,    0,  339,
                                                          0,  339,  339,    0,  339,  339,  339,  339,  339,  339,
                                                          339,  339,  339,    0,  339,    0,    0,    0,    0,    0,
                                                          31,   31,    0,   15,   31,   31,   31,   31,   31,   17,
                                                          31,   86,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          338,   31,   31,   31,   31,   31,   31,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,   65,   65,   65,   65,    0,    0,   10,   11,
                                                          0,  339,    0,   12,    0,   13,   31,   31,    0,   14,
                                                          15,    0,   16,    0,   17,   18,    0,    0,    0,    0,
                                                          0,   23,   24,   25,   26,   27,    0,   28,   10,   11,
                                                          0,    0,    0,   12,    0,   13,    0,   31,   31,   14,
                                                          15,    0,   16,    0,   17,   18,    0,    0,    0,    0,
                                                          0,   23,   24,   25,   26,   27,    0,   28,    0,    0,
                                                          0,   11,   11,   11,   11,   11,   11,   11,   11,   11,
                                                          11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
                                                          11,   11,    1,    1,  342,    1,    0,    1,    1,    1,
                                                          1,    1,    1,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,  342,    1,    1,    1,    1,    1,   44,
                                                          44,    0,    0,   44,   44,   44,   44,   44,    0,   44,
                                                          52,    0,    0,   52,    0,   52,   52,   52,    0,    0,
                                                          44,   44,   44,    0,   44,   44,    1,    0,    0,    1,
                                                          52,   52,   52,    0,   52,   52,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,   44,   44,    0,    0,    1,
                                                          0,    0,    0,    0,    0,   52,   52,   31,   31,   31,
                                                          31,   31,   31,   31,   31,   31,   31,   31,   31,   31,
                                                          31,   31,   31,   31,   31,   19,   44,   44,   53,    0,
                                                          0,   53,    0,   53,   53,   53,   52,   52,   54,    0,
                                                          0,   54,    0,   54,   54,   54,    0,    0,   53,   53,
                                                          53,    0,   53,   53,    0,    0,    0,    0,   54,   54,
                                                          54,    0,   54,   54,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,   56,    0,    0,   56,    0,
                                                          0,   56,    0,   53,   53,    0,    0,    0,    0,    0,
                                                          0,    0,    0,   54,   54,   56,   56,   56,    0,   56,
                                                          56,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,   53,   53,    0,    0,    0,    0,
                                                          0,    0,    0,    0,   54,   54,    0,    0,    0,    0,
                                                          56,   56,    0,    0,    0,    0,    0,    1,    1,    1,
                                                          1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
                                                          1,    1,    1,    1,    1,    1,    1,    1,    0,    0,
                                                          0,   56,   56,    0,    0,    0,   44,   44,   44,   44,
                                                          44,   44,   44,   44,    0,    0,   52,   52,   52,   52,
                                                          52,   52,   52,   52,    0,    0,   57,    0,    0,   57,
                                                          0,    0,   57,   58,    0,    0,   58,    0,    0,   58,
                                                          0,    0,    0,    0,    0,    0,   57,   57,   57,    0,
                                                          57,   57,    0,   58,   58,   58,    0,   58,   58,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,   57,   57,    0,    0,    0,    0,    0,   58,   58,
                                                          0,    0,    0,    0,   53,   53,   53,   53,   53,   53,
                                                          53,   53,    0,    0,   54,   54,   54,   54,   54,   54,
                                                          54,   54,   57,   57,    0,   61,    0,    0,   61,   58,
                                                          58,   61,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,   61,   61,   61,    0,   61,
                                                          61,   56,   56,   56,   56,   56,   56,   56,   56,    0,
                                                          0,    0,   62,    0,    0,   62,    0,    0,   62,   59,
                                                          0,    0,   59,    0,    0,   59,    0,    0,    0,    0,
                                                          61,   61,   62,   62,   62,    0,   62,   62,    0,   59,
                                                          59,   59,    0,   59,   59,   67,    0,    0,   67,    0,
                                                          0,   67,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,   61,   61,    0,    0,   67,   67,   62,   62,    0,
                                                          67,    0,    0,    0,   59,   59,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,   62,   62,
                                                          67,   67,    0,    0,    0,   59,   59,    0,    0,    0,
                                                          0,    0,   57,   57,   57,   57,   57,   57,   57,   57,
                                                          0,   58,   58,   58,   58,   58,   58,   60,    0,    0,
                                                          60,   67,   67,   60,    0,  160,   86,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   60,   60,   60,
                                                          0,   60,   60,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,  332,    0,    0,    0,    0,    0,    0,    0,
                                                          9,    0,    0,   10,   11,    0,    0,    0,   12,    0,
                                                          13,    0,   60,   60,   14,   15,    0,   16,    0,   17,
                                                          18,    0,   19,   87,   21,   22,   23,   24,   25,   26,
                                                          27,    0,   28,   61,   61,   61,   61,   61,   61,    0,
                                                          0,    0,    0,   60,   60,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          62,   62,   62,   62,   62,   62,   86,   59,   59,   59,
                                                          59,   59,   59,    0,    0,    0,    0,    0,    0,   30,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   67,   67,   86,
                                                          9,    0,    0,   10,   11,    0,    0,    0,   12,    0,
                                                          13,    0,    0,    0,   14,   15,    0,   16,    0,   17,
                                                          18,    0,   19,   87,   21,   22,   23,   24,   25,   26,
                                                          27,    0,   28,    9,    0,    0,   10,   11,    0,    0,
                                                          0,   12,    0,   13,   95,    0,    0,   14,   15,    0,
                                                          16,    0,   17,   18,    0,   19,   87,   21,   22,   23,
                                                          24,   25,   26,   27,    0,   28,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,   60,   60,   60,   60,   60,
                                                          60,   95,   95,    0,    0,    0,   95,    0,   95,   88,
                                                          0,    0,   95,   95,    0,   95,    0,   95,   95,    0,
                                                          0,    0,    0,    0,   95,   95,   95,   95,   95,    0,
                                                          95,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,   30,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
                                                          0,    0,    0,    0,    0,    0,    0,   95,
};
short yycheck[] = {                                       2,
                                                          66,   79,   66,   40,  123,   42,   42,   44,    7,   75,
                                                          57,   63,  248,   60,    5,  320,   40,   39,   42,    4,
                                                          257,   58,   59,  257,  256,  257,   58,  257,   34,   27,
                                                          257,   40,   41,   42,   58,   44,   44,  125,    4,   37,
                                                          60,  125,   62,  251,   44,  360,  283,   40,  114,  115,
                                                          59,  117,  253,   40,   57,   42,   44,   60,   40,   40,
                                                          126,   42,  126,  396,   70,   63,   51,   33,   40,   41,
                                                          42,   40,   44,   40,   41,  479,   41,   44,   59,   44,
                                                          288,   47,   91,  257,   44,   48,   49,   59,  289,   48,
                                                          84,  126,  416,   58,   59,  447,   91,   41,  101,   59,
                                                          44,  100,   41,  106,  102,   48,   49,    0,   40,   91,
                                                          42,  256,   40,   41,   58,  467,   44,  125,  116,   91,
                                                          59,  525,   91,   40,   91,  125,   44,   59,   93,  195,
                                                          463,  195,   40,  199,   42,  199,  441,  125,  257,   41,
                                                          440,  126,   44,  281,  210,  445,  210,   40,  382,   42,
                                                          465,   44,  476,  156,  386,  385,   58,   59,  164,  225,
                                                          125,   63,  398,   91,  199,   40,   59,   42,  256,   40,
                                                          123,   42,  256,   44,   91,   93,  268,  269,   40,  245,
                                                          42,  175,  185,   91,    0,  179,  189,   58,   59,  295,
                                                          188,   93,  516,  508,   44,  193,  202,   59,  164,   41,
                                                          191,  124,   44,  440,  445,  311,  440,  381,  440,   59,
                                                          440,   61,  278,  440,  199,    0,   91,  323,   40,  271,
                                                          257,  184,   40,  125,   40,  184,   42,   40,  294,   42,
                                                          61,  253,  125,  257,  364,  192,  159,  284,  376,  271,
                                                          43,  184,   45,   59,  123,  251,  266,  267,  257,   47,
                                                          41,   33,  330,   44,  320,   40,   38,   42,   40,  295,
                                                          42,   43,  260,   45,  257,  384,  440,  262,  263,  256,
                                                          257,   44,   41,   91,   59,  311,  257,  123,  281,  278,
                                                          278,  284,  288,   81,  282,  251,   59,  323,   41,   58,
                                                          257,   44,  358,  278,  358,  252,  125,  295,  296,   44,
                                                          98,   41,   44,  269,   44,   58,   59,  270,  271,   41,
                                                          63,  270,   44,   41,   59,  123,   44,   59,  321,   41,
                                                          41,  440,   44,   44,   41,  257,   58,  270,  271,  257,
                                                          58,   59,   40,   44,   42,   63,   58,   58,   41,  477,
                                                          93,  123,   40,  337,  126,   44,  484,  376,   59,  386,
                                                          416,   59,   44,   41,  420,   58,  420,  423,  356,  423,
                                                          59,  499,  386,  256,  257,   93,  432,   59,  270,  271,
                                                          58,  437,  125,  511,  331,  441,   61,  386,   44,  517,
                                                          383,  338,  257,   41,   41,   44,   44,   44,  454,  455,
                                                          454,  455,  530,  386,  351,  257,  124,  125,  291,  386,
                                                          59,  294,  295,  440,   41,  386,  299,   44,  301,  125,
                                                          476,  445,  305,  306,  386,  308,  440,  310,  311,  386,
                                                          313,  314,  315,  316,  317,  318,  319,  320,  321,   41,
                                                          323,  440,   44,  432,  432,  501,  502,  501,  502,  257,
                                                          256,  257,   41,  409,  257,   44,   41,  440,   80,   44,
                                                          516,  408,   38,  440,  386,  521,  459,  521,  386,  440,
                                                          37,   41,  456,   94,   44,   42,  264,   41,  440,  124,
                                                          47,  364,  257,  440,  256,  291,   61,  471,  294,  295,
                                                          262,  263,   75,  299,  270,  301,   44,  380,  270,  305,
                                                          306,   41,  308,  386,  310,  311,   44,  313,  314,  315,
                                                          316,  317,  318,  319,  320,  321,  291,  323,  440,  294,
                                                          295,  386,  440,  256,  299,  386,  301,  270,  271,   41,
                                                          305,  306,   44,  308,  386,  310,  311,   93,  313,  314,
                                                          315,  316,  317,  318,  319,  320,  321,  125,  323,  376,
                                                          322,   41,  270,  271,   44,   33,  125,  440,  364,  257,
                                                          38,   41,   40,   40,   42,   43,   44,   45,  481,   41,
                                                          192,   46,  264,  265,  380,  440,   59,  365,  386,  440,
                                                          386,   59,  495,  386,  125,  127,  128,  282,  440,  364,
                                                          503,   48,   49,  291,  229,  230,  294,  295,  231,  232,
                                                          41,  299,   41,  301,   41,  380,   41,  305,  306,  151,
                                                          308,  386,  310,  311,  386,  313,  314,  315,  316,  317,
                                                          318,  319,  320,  321,   93,  323,  233,  234,  235,  236,
                                                          252,   58,  440,   59,  440,   41,   59,  440,   44,  237,
                                                          238,  429,  225,   58,   40,  123,   40,  125,  126,   40,
                                                          59,   33,   58,   59,   44,   58,   38,   63,   40,  125,
                                                          42,   43,  245,   45,   44,  440,  364,   41,  440,  441,
                                                          442,  443,  444,  445,   41,   93,   59,   59,  450,   58,
                                                          40,   40,  380,   59,  226,  227,  228,   93,  386,  125,
                                                          377,   59,  300,   59,  316,   40,   40,  272,  273,  274,
                                                          275,  276,  277,  278,  279,  280,  281,   44,   59,  331,
                                                          378,  294,  312,   40,  125,   41,  338,   59,  123,  125,
                                                          41,   34,  123,   41,   41,  125,   59,   41,   40,  351,
                                                          41,   41,   41,  296,  498,   48,   49,  320,  409,  184,
                                                          193,  123,  440,  257,  126,  185,  102,  239,  290,  240,
                                                          243,  383,  241,  281,  242,  503,   33,   70,  244,  495,
                                                          106,   38,   -1,   40,   -1,   42,   43,   -1,   45,   -1,
                                                          -1,   -1,   -1,  395,   -1,   -1,   -1,   -1,  256,  257,
                                                          -1,   -1,   59,   -1,  262,  263,  408,   -1,   -1,   -1,
                                                          -1,   -1,  270,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  291,  292,  293,  294,  295,  296,  297,
                                                          298,  299,   -1,  301,  302,  303,  304,  305,  306,  307,
                                                          308,  309,  310,  311,  312,  313,  314,  315,  316,  317,
                                                          318,  319,  320,  321,  322,  323,  123,   -1,  125,  126,
                                                          -1,   -1,   33,   -1,  437,   -1,   -1,   38,  441,   40,
                                                          -1,   42,   43,   -1,   45,  271,   -1,   -1,   -1,   -1,
                                                          -1,  184,   -1,   -1,  256,  257,   -1,   -1,   59,   -1,
                                                          262,  263,   -1,   -1,   -1,   -1,  364,   -1,  270,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  380,   -1,   -1,   -1,   -1,  385,  386,  291,
                                                          292,  293,  294,  295,  296,  297,  298,  299,   -1,  301,
                                                          302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
                                                          312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
                                                          322,  323,  123,   41,   -1,  126,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,   -1,
                                                          -1,   -1,  440,  441,  442,  443,  444,  445,   -1,   -1,
                                                          -1,   -1,  450,   -1,   -1,   -1,   -1,   -1,   -1,  256,
                                                          257,   -1,  364,   -1,   -1,  262,  263,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  270,  376,   -1,   -1,   -1,  380,   -1,
                                                          -1,   -1,   -1,  385,  386,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,  291,  292,  293,  294,  295,  296,
                                                          297,  298,  299,   -1,  301,  302,  303,  304,  305,  306,
                                                          307,  308,  309,  310,  311,  312,  313,  314,  315,  316,
                                                          317,  318,  319,  320,  321,  322,  323,   -1,  361,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  440,  441,
                                                          442,  443,  444,  445,   -1,   -1,   -1,   -1,  450,   -1,
                                                          -1,   -1,   -1,   -1,   -1,  256,  257,   -1,   -1,   -1,
                                                          -1,  262,  263,   -1,   -1,   -1,   -1,  364,   -1,  270,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  380,   -1,   -1,   -1,   -1,  385,  386,
                                                          291,  292,  293,  294,  295,  296,  297,  298,  299,   -1,
                                                          301,  302,  303,  304,  305,  306,  307,  308,  309,  310,
                                                          311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
                                                          321,  322,  323,   33,   -1,   -1,   -1,   -1,   38,   -1,
                                                          40,   -1,   42,   43,   41,   45,   -1,   44,  256,  257,
                                                          -1,   -1,   -1,  440,  441,  442,  443,  444,  445,   59,
                                                          -1,   58,   59,  450,   -1,   -1,   63,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  364,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  291,   -1,   -1,  294,  295,   -1,  380,
                                                          -1,  299,   -1,  301,  385,  386,   93,  305,  306,   -1,
                                                          308,   -1,  310,  311,   -1,  313,  314,  315,  316,  317,
                                                          318,  319,  320,  321,   -1,  323,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  123,   -1,   -1,  126,  124,  125,   33,
                                                          -1,   -1,   -1,   -1,   38,   -1,   40,   -1,   42,   43,
                                                          -1,   45,   38,   -1,   -1,   41,   -1,   -1,   44,  440,
                                                          441,  442,  443,  444,  445,   59,   -1,   -1,   -1,  450,
                                                          -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,   -1,
                                                          -1,   -1,  380,   -1,   -1,   -1,   -1,   -1,  386,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   38,   -1,   -1,   41,   93,   94,   44,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   58,   59,   -1,   -1,   -1,   63,  123,
                                                          -1,  125,  126,   -1,   -1,   -1,   -1,   -1,  124,  125,
                                                          -1,   -1,  440,   -1,   33,   -1,   -1,   -1,   -1,   38,
                                                          -1,   40,   -1,   42,   43,   -1,   45,   -1,   93,   94,
                                                          -1,   -1,   -1,   -1,   -1,   -1,  256,  257,   -1,   -1,
                                                          -1,   -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          270,   -1,   -1,  270,  271,   -1,   -1,   -1,   -1,  124,
                                                          125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  291,  292,  293,  294,  295,  296,  297,  298,  299,
                                                          -1,  301,  302,  303,  304,  305,  306,  307,  308,  309,
                                                          310,  311,  312,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,  322,  323,  123,   -1,   -1,  126,   -1,   -1,
                                                          33,   -1,   -1,   -1,   -1,   38,   -1,   40,   -1,   42,
                                                          43,   -1,   45,   -1,   -1,   33,   -1,   -1,   -1,   -1,
                                                          38,   -1,   40,  257,   42,   43,   59,   45,  262,  263,
                                                          -1,   -1,   -1,   -1,  364,   -1,  270,   -1,  264,  265,
                                                          266,  267,  268,  269,  270,  271,   -1,   -1,   -1,   -1,
                                                          380,   -1,   -1,   -1,   -1,  385,  386,  291,  292,  293,
                                                          294,  295,  296,  297,  298,  299,   -1,  301,  302,  303,
                                                          304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
                                                          314,  315,  316,  317,  318,  319,  320,  321,  322,  323,
                                                          123,   -1,   -1,  126,  257,  270,  271,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,  123,   -1,   -1,  126,   -1,
                                                          440,  441,  442,  443,  444,  445,   -1,   -1,   -1,   -1,
                                                          450,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,   -1,
                                                          364,  294,  295,  262,  263,   -1,  299,   -1,  301,   -1,
                                                          -1,  270,  305,  306,   -1,  308,  380,  310,  311,   -1,
                                                          -1,  385,  386,   -1,  317,  318,  319,  320,  321,   -1,
                                                          323,   -1,  291,  292,  293,  294,  295,  296,  297,  298,
                                                          299,   -1,  301,  302,  303,  304,  305,  306,  307,  308,
                                                          309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
                                                          319,  320,  321,  322,  323,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,  440,  441,  442,  443,
                                                          444,  445,   -1,   33,   -1,   -1,  450,  380,   38,   -1,
                                                          40,   -1,   42,   43,  257,   45,   -1,   -1,   -1,  262,
                                                          263,   -1,   -1,   -1,   -1,  364,   -1,  270,  256,   -1,
                                                          -1,   -1,   -1,   -1,  262,  263,   -1,   -1,   -1,   -1,
                                                          -1,  380,  270,   -1,   -1,   -1,  385,  386,  291,  292,
                                                          293,  294,  295,  296,  297,  298,  299,   -1,  301,  302,
                                                          303,  304,  305,  306,  307,  308,  309,  310,  311,  312,
                                                          313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
                                                          323,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  123,  322,   41,  126,   -1,   44,   -1,
                                                          -1,  440,  441,  442,  443,  444,  445,   -1,   -1,   -1,
                                                          -1,  450,   58,   59,   -1,   33,   -1,   63,   -1,   -1,
                                                          38,  364,   40,   -1,   42,   43,   -1,   45,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  380,   -1,   -1,
                                                          -1,   -1,  385,  386,   -1,   -1,   -1,   93,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  386,   -1,
                                                          -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,   38,   -1,
                                                          40,   -1,   42,   43,   -1,   45,   -1,   -1,   -1,  125,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  440,  441,  442,
                                                          443,  444,  445,   -1,   -1,  123,   -1,  450,  126,   -1,
                                                          -1,   -1,  440,  441,  442,  443,  444,  445,   -1,   -1,
                                                          -1,   -1,  450,   93,   -1,   -1,   -1,  257,   -1,   33,
                                                          -1,   -1,  262,  263,   38,   -1,   40,   -1,   42,   43,
                                                          270,   45,   33,   -1,   -1,   -1,   -1,   38,   -1,   40,
                                                          -1,   42,   43,   -1,   45,   -1,  126,   -1,   -1,   -1,
                                                          -1,  291,   -1,   -1,  294,  295,   -1,   58,   -1,  299,
                                                          -1,  301,   -1,   -1,   -1,  305,  306,   -1,  308,   -1,
                                                          310,  311,   -1,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,  322,  323,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,   38,
                                                          -1,   40,   -1,   42,   43,   -1,   45,   -1,   -1,  123,
                                                          -1,   -1,  126,   -1,   33,  271,   -1,   -1,   -1,   38,
                                                          -1,   40,   -1,   42,   43,  126,   45,   -1,  256,  257,
                                                          -1,   -1,   -1,   -1,  262,  263,   -1,   -1,   -1,   -1,
                                                          380,   -1,  270,   -1,   -1,   -1,  386,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,  292,  293,   -1,   -1,  296,  297,
                                                          298,   -1,   -1,   -1,  302,  303,  304,   -1,   -1,  307,
                                                          -1,  309,  262,  263,  312,   -1,   33,  126,   -1,   -1,
                                                          270,   38,   -1,   40,  322,   42,   43,   -1,   45,   -1,
                                                          440,  441,  442,  443,  444,  445,   -1,  126,   33,   -1,
                                                          450,   -1,   -1,   38,   -1,   40,   -1,   42,   43,   -1,
                                                          45,   41,   -1,   -1,   44,   33,   -1,   -1,   -1,   -1,
                                                          38,   -1,   40,   -1,   42,   43,  364,   45,   58,   59,
                                                          -1,   -1,  322,   63,   -1,   -1,   -1,   -1,  262,  263,
                                                          -1,   59,   -1,   -1,   -1,   -1,  270,  385,  386,   -1,
                                                          -1,  262,  263,   -1,   -1,   -1,   -1,   -1,   93,  270,
                                                          -1,   -1,   -1,   93,   94,   -1,  123,   -1,   33,  126,
                                                          -1,   -1,   -1,   38,   -1,   40,   -1,   42,   43,   -1,
                                                          45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  126,   -1,   -1,  124,  125,  386,   -1,  322,   -1,
                                                          -1,   -1,  440,  441,  442,  443,  444,  445,  126,   -1,
                                                          33,  322,  450,  262,  263,   38,   -1,   40,   -1,   42,
                                                          43,  270,   45,   38,   -1,   -1,   41,   -1,   -1,   44,
                                                          33,   -1,   -1,  262,  263,   38,   59,   40,   41,   42,
                                                          43,  270,   45,   58,   59,   -1,   -1,   -1,   63,   -1,
                                                          440,  441,  442,  443,  444,  445,   -1,   -1,   -1,   -1,
                                                          450,  126,  386,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  322,   -1,  386,   -1,   -1,   93,   94,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  322,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  126,   -1,  262,  263,   -1,   -1,  124,
                                                          125,   -1,   -1,  270,   -1,   -1,  440,  441,  442,  443,
                                                          444,  445,   -1,  126,   -1,   -1,  450,  262,  263,  440,
                                                          441,  442,  443,  444,  445,  270,   -1,  386,   -1,  450,
                                                          270,  271,   -1,   -1,  262,  263,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  270,   -1,  383,   -1,   -1,  386,   -1,   33,
                                                          -1,   -1,   -1,   -1,   38,  322,   40,   -1,   42,   43,
                                                          33,   45,   -1,   -1,   -1,   38,   -1,   40,   -1,   42,
                                                          43,   -1,   45,   -1,   -1,   -1,   -1,  322,   -1,   -1,
                                                          -1,  440,  441,  442,  443,  444,  445,  262,  263,   -1,
                                                          -1,  450,   -1,   -1,  322,  270,   -1,   -1,   -1,   -1,
                                                          -1,  440,  441,  442,  443,  444,  445,   -1,   -1,   -1,
                                                          -1,  450,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  386,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,  262,
                                                          263,   38,   -1,   40,   -1,   42,   43,  270,   45,   -1,
                                                          -1,  386,  126,  268,  269,  270,  271,  322,   -1,  262,
                                                          263,   -1,   -1,  126,   -1,   -1,   -1,  270,  386,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   40,   41,   42,
                                                          -1,   44,   -1,  440,  441,  442,  443,  444,  445,   -1,
                                                          -1,   -1,   -1,  450,   -1,   58,   59,   -1,   61,  322,
                                                          -1,   -1,   -1,   -1,   -1,  440,  441,  442,  443,  444,
                                                          445,   -1,   -1,   -1,   -1,  450,   -1,   -1,  383,  322,
                                                          -1,  386,  440,  441,  442,  443,  444,  445,   91,  126,
                                                          -1,   -1,  450,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  291,   -1,   -1,  294,  295,   -1,   -1,   -1,
                                                          299,   -1,  301,   -1,   -1,   -1,  305,  306,   -1,  308,
                                                          123,  310,  311,  386,  313,  314,  315,  316,  317,  318,
                                                          319,  320,  321,   -1,  323,  440,  441,  442,  443,  444,
                                                          445,   -1,   -1,  386,   -1,  450,   -1,   -1,  262,  263,
                                                          -1,   41,   -1,   -1,   44,   -1,  270,   -1,   -1,  262,
                                                          263,   -1,   -1,   -1,   -1,   -1,   -1,  270,   58,   59,
                                                          40,   41,   42,   63,   44,   -1,   -1,  440,  441,  442,
                                                          443,  444,  445,   -1,   -1,   -1,   -1,  450,   58,   59,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  440,  441,  442,
                                                          443,  444,  445,   93,   94,   -1,   -1,  450,  322,   -1,
                                                          40,   41,   42,   -1,   44,   -1,   -1,   -1,   -1,  322,
                                                          -1,   91,   -1,   -1,   -1,  262,  263,   -1,   58,   59,
                                                          -1,   -1,   -1,  270,  124,  125,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  123,  257,   -1,   40,   -1,   42,   -1,
                                                          -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  386,   -1,   -1,   59,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,  386,   -1,  322,   -1,   -1,  291,   -1,
                                                          -1,  294,  295,  123,   -1,   -1,  299,   -1,  301,   -1,
                                                          -1,   -1,  305,  306,   -1,  308,   -1,  310,  311,   -1,
                                                          313,  314,  315,  316,  317,  318,  319,  320,  321,   -1,
                                                          323,   -1,   -1,   -1,   -1,   -1,  440,  441,  442,  443,
                                                          444,  445,   -1,   -1,   -1,   -1,  450,  440,  441,  442,
                                                          443,  444,  445,   -1,   -1,   -1,   -1,  450,   -1,  386,
                                                          40,   41,   42,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  364,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  380,   -1,   -1,
                                                          270,  271,   -1,  386,   -1,   -1,   -1,  257,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,   42,   -1,
                                                          -1,   91,   -1,  440,  441,  442,  443,  444,  445,   -1,
                                                          -1,   -1,   -1,  450,   -1,   59,   -1,   -1,   -1,   -1,
                                                          -1,  291,   -1,   -1,  294,  295,   -1,  257,   -1,  299,
                                                          -1,  301,   -1,   -1,   -1,  305,  306,  440,  308,   -1,
                                                          310,  311,   -1,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,   -1,  323,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  291,   -1,   -1,  294,  295,   -1,   -1,   -1,  299,
                                                          -1,  301,  256,  257,   -1,  305,  306,   -1,  308,   -1,
                                                          310,  311,   -1,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,   -1,  323,   40,   -1,   42,   -1,   38,   -1,
                                                          -1,   41,   -1,   -1,   44,   -1,   -1,  291,   -1,   -1,
                                                          294,  295,   -1,   59,   -1,  299,  386,  301,   58,   59,
                                                          -1,  305,  306,   63,  308,   -1,  310,  311,   -1,  313,
                                                          314,  315,  316,  317,  318,  319,  320,  321,   -1,  323,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,   42,   -1,
                                                          -1,   -1,   -1,   93,   94,   -1,  386,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   59,  256,  257,   -1,   -1,
                                                          440,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          364,   -1,   -1,   -1,  124,  125,   -1,   40,   41,   42,
                                                          -1,   -1,   -1,   -1,   -1,   -1,  380,   -1,   -1,   -1,
                                                          -1,  291,  386,   -1,  294,  295,   -1,   -1,   -1,  299,
                                                          440,  301,  256,  257,   -1,  305,  306,   -1,  308,   -1,
                                                          310,  311,   -1,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,   -1,  323,   -1,   -1,   -1,   -1,   91,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  291,   -1,   -1,
                                                          294,  295,   -1,   -1,   -1,  299,  440,  301,   -1,   -1,
                                                          -1,  305,  306,   -1,  308,   41,  310,  311,   44,  313,
                                                          314,  315,  316,  317,  318,  319,  320,  321,   -1,  323,
                                                          -1,   -1,   58,   59,   -1,   61,   -1,   -1,   -1,   -1,
                                                          380,   -1,   -1,   -1,   -1,   -1,  386,   -1,   41,   -1,
                                                          -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          256,  257,   -1,   -1,   -1,   58,   59,   -1,   61,   -1,
                                                          364,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,
                                                          270,  271,   -1,   -1,   -1,   -1,  380,   -1,   -1,   -1,
                                                          -1,   -1,  386,   -1,   -1,  291,   -1,  123,  294,  295,
                                                          440,   -1,   -1,  299,   -1,  301,   -1,   -1,   -1,  305,
                                                          306,   -1,  308,  257,  310,  311,   41,  313,  314,  315,
                                                          316,  317,  318,  319,  320,  321,   -1,  323,   -1,   -1,
                                                          123,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,  440,  291,   -1,   -1,
                                                          294,  295,   -1,  256,  257,  299,   -1,  301,   -1,   -1,
                                                          -1,  305,  306,   -1,  308,   -1,  310,  311,  364,  313,
                                                          314,  315,  316,  317,  318,  319,  320,  321,   -1,  323,
                                                          -1,   -1,   -1,   -1,  380,   -1,   -1,   -1,  291,   -1,
                                                          386,  294,  295,   -1,   -1,   -1,  299,   -1,  301,   -1,
                                                          -1,   -1,  305,  306,   -1,  308,   -1,  310,  311,   -1,
                                                          313,  314,  315,  316,  317,  318,  319,  320,  321,   -1,
                                                          323,   -1,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  257,   -1,   -1,   -1,   -1,  380,   -1,   -1,   59,
                                                          -1,   61,  386,   -1,  440,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   44,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,  257,  291,   -1,   -1,  294,  295,
                                                          59,   -1,   61,  299,   -1,  301,   -1,  380,   -1,  305,
                                                          306,   -1,  308,   -1,  310,  311,   -1,  313,  314,  315,
                                                          316,  317,  318,  319,  320,  321,  440,  323,  291,   -1,
                                                          -1,  294,  295,  123,   -1,   -1,  299,   -1,  301,   -1,
                                                          -1,   -1,  305,  306,   -1,  308,   -1,  310,  311,   -1,
                                                          313,  314,  315,  316,  317,  318,  319,  320,  321,   -1,
                                                          323,  256,  257,   -1,  123,   -1,   -1,   -1,  364,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   38,   -1,  380,   41,   -1,   -1,   44,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,  291,   -1,   -1,  294,
                                                          295,  364,   58,   59,  299,   -1,  301,   63,   -1,   -1,
                                                          305,  306,   -1,  308,   -1,  310,  311,  380,  313,  314,
                                                          315,  316,  317,  318,  319,  320,  321,   -1,  323,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   37,   38,   -1,   40,
                                                          41,   42,   43,   44,   45,   46,   47,  257,  124,  125,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
                                                          61,   62,   63,   -1,   -1,  380,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,   -1,
                                                          -1,  291,   -1,   -1,  294,  295,   -1,   -1,   -1,  299,
                                                          91,  301,   93,   94,   -1,  305,  306,   -1,  308,   -1,
                                                          310,  311,   -1,  313,  314,  315,  316,  317,  318,  319,
                                                          320,  321,  291,  323,   -1,  294,  295,   -1,   -1,   -1,
                                                          299,   -1,  301,  124,  125,   -1,  305,  306,   -1,  308,
                                                          -1,  310,  311,   -1,  313,  314,  315,  316,  317,  318,
                                                          319,  320,  321,   -1,  323,   -1,   -1,   -1,   -1,   -1,
                                                          37,   38,   -1,   40,   41,   42,   43,   44,   45,   46,
                                                          47,  257,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          380,   58,   59,   60,   61,   62,   63,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  268,  269,  270,  271,   -1,   -1,  294,  295,
                                                          -1,  380,   -1,  299,   -1,  301,   93,   94,   -1,  305,
                                                          306,   -1,  308,   -1,  310,  311,   -1,   -1,   -1,   -1,
                                                          -1,  317,  318,  319,  320,  321,   -1,  323,  294,  295,
                                                          -1,   -1,   -1,  299,   -1,  301,   -1,  124,  125,  305,
                                                          306,   -1,  308,   -1,  310,  311,   -1,   -1,   -1,   -1,
                                                          -1,  317,  318,  319,  320,  321,   -1,  323,   -1,   -1,
                                                          -1,  262,  263,  264,  265,  266,  267,  268,  269,  270,
                                                          271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
                                                          281,  282,   37,   38,  380,   40,   -1,   42,   43,   44,
                                                          45,   46,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   58,   59,   60,   61,   62,   63,   37,
                                                          38,   -1,   -1,   41,   42,   43,   44,   45,   -1,   47,
                                                          38,   -1,   -1,   41,   -1,   43,   44,   45,   -1,   -1,
                                                          58,   59,   60,   -1,   62,   63,   91,   -1,   -1,   94,
                                                          58,   59,   60,   -1,   62,   63,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,  124,
                                                          -1,   -1,   -1,   -1,   -1,   93,   94,  264,  265,  266,
                                                          267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
                                                          277,  278,  279,  280,  281,  282,  124,  125,   38,   -1,
                                                          -1,   41,   -1,   43,   44,   45,  124,  125,   38,   -1,
                                                          -1,   41,   -1,   43,   44,   45,   -1,   -1,   58,   59,
                                                          60,   -1,   62,   63,   -1,   -1,   -1,   -1,   58,   59,
                                                          60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   38,   -1,   -1,   41,   -1,
                                                          -1,   44,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   93,   94,   58,   59,   60,   -1,   62,
                                                          63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,
                                                          93,   94,   -1,   -1,   -1,   -1,   -1,  262,  263,  264,
                                                          265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
                                                          275,  276,  277,  278,  279,  280,  281,  282,   -1,   -1,
                                                          -1,  124,  125,   -1,   -1,   -1,  264,  265,  266,  267,
                                                          268,  269,  270,  271,   -1,   -1,  264,  265,  266,  267,
                                                          268,  269,  270,  271,   -1,   -1,   38,   -1,   -1,   41,
                                                          -1,   -1,   44,   38,   -1,   -1,   41,   -1,   -1,   44,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,   -1,
                                                          62,   63,   -1,   58,   59,   60,   -1,   62,   63,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   93,   94,   -1,   -1,   -1,   -1,   -1,   93,   94,
                                                          -1,   -1,   -1,   -1,  264,  265,  266,  267,  268,  269,
                                                          270,  271,   -1,   -1,  264,  265,  266,  267,  268,  269,
                                                          270,  271,  124,  125,   -1,   38,   -1,   -1,   41,  124,
                                                          125,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   58,   59,   60,   -1,   62,
                                                          63,  264,  265,  266,  267,  268,  269,  270,  271,   -1,
                                                          -1,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,   38,
                                                          -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
                                                          93,   94,   58,   59,   60,   -1,   62,   63,   -1,   58,
                                                          59,   60,   -1,   62,   63,   38,   -1,   -1,   41,   -1,
                                                          -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,  124,  125,   -1,   -1,   58,   59,   93,   94,   -1,
                                                          63,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,
                                                          93,   94,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,
                                                          -1,   -1,  264,  265,  266,  267,  268,  269,  270,  271,
                                                          -1,  266,  267,  268,  269,  270,  271,   38,   -1,   -1,
                                                          41,  124,  125,   44,   -1,  256,  257,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
                                                          -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  283,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          291,   -1,   -1,  294,  295,   -1,   -1,   -1,  299,   -1,
                                                          301,   -1,   93,   94,  305,  306,   -1,  308,   -1,  310,
                                                          311,   -1,  313,  314,  315,  316,  317,  318,  319,  320,
                                                          321,   -1,  323,  266,  267,  268,  269,  270,  271,   -1,
                                                          -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          266,  267,  268,  269,  270,  271,  257,  266,  267,  268,
                                                          269,  270,  271,   -1,   -1,   -1,   -1,   -1,   -1,  380,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,  257,
                                                          291,   -1,   -1,  294,  295,   -1,   -1,   -1,  299,   -1,
                                                          301,   -1,   -1,   -1,  305,  306,   -1,  308,   -1,  310,
                                                          311,   -1,  313,  314,  315,  316,  317,  318,  319,  320,
                                                          321,   -1,  323,  291,   -1,   -1,  294,  295,   -1,   -1,
                                                          -1,  299,   -1,  301,  257,   -1,   -1,  305,  306,   -1,
                                                          308,   -1,  310,  311,   -1,  313,  314,  315,  316,  317,
                                                          318,  319,  320,  321,   -1,  323,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,  266,  267,  268,  269,  270,
                                                          271,  294,  295,   -1,   -1,   -1,  299,   -1,  301,  380,
                                                          -1,   -1,  305,  306,   -1,  308,   -1,  310,  311,   -1,
                                                          -1,   -1,   -1,   -1,  317,  318,  319,  320,  321,   -1,
                                                          323,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,  380,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
                                                          -1,   -1,   -1,   -1,   -1,   -1,   -1,  380,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 451
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
#line 1766 "../../src/cgram.y"


static S_completionFunTab spCompletionsTab[]  = {
    {COMPL_FOR_SPECIAL1,    completeForSpecial1},
    {COMPL_FOR_SPECIAL2,    completeForSpecial2},
    {COMPL_UP_FUN_PROFILE,  completeUpFunProfile},
    {0,NULL}
};

static S_completionFunTab completionsTab[]  = {
    {COMPL_TYPE_NAME,       completeTypes},
    {COMPL_STRUCT_NAME,     completeStructs},
    {COMPL_STRUCT_REC_NAME, completeRecNames},
    {COMPL_ENUM_NAME,       completeEnums},
    {COMPL_LABEL_NAME,      completeLabels},
    {COMPL_OTHER_NAME,      completeOthers},
    {0,NULL}
};


void makeCCompletions(char *s, int len, S_position *pos) {
    int tok, yyn, i;
    S_cline compLine;
    /*fprintf(stderr,"completing \"%s\"\n",s);*/
    LICENSE_CHECK();
    strncpy(s_completions.idToProcess, s, MAX_FUN_NAME_SIZE);
    s_completions.idToProcess[MAX_FUN_NAME_SIZE-1] = 0;
    FILL_completions(&s_completions, len, *pos, 0, 0, 0, 0, 0, 0);
    /* special wizard completions */
    for (i=0;(tok=spCompletionsTab[i].token)!=0; i++) {
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            /*fprintf(stderr,"completing %d==%s v stave %d\n",i,yyname[tok],lastyystate);*/
            (*spCompletionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions) return;
        }
    }
    /* If there is a wizard completion, RETURN now */
    if (s_completions.ai != 0 && s_opt.cxrefs != OLO_SEARCH) return;
    /* basic language tokens */
    for (i=0;(tok=completionsTab[i].token)!=0; i++) {
        if (((yyn = yysindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok) ||
            ((yyn = yyrindex[lastyystate]) && (yyn += tok) >= 0 &&
             yyn <= YYTABLESIZE && yycheck[yyn] == tok)) {
            /*&fprintf(stderr,"completing %d==%s v stave %d\n",i,yyname[tok],lastyystate);&*/
            (*completionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions) return;
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
                } else {
                    FILL_cline(&compLine, s_tokenName[tok], NULL, TypeToken,0, 0, NULL,NULL);
                }
                /*&fprintf(stderr,"completing %d==%s(%s) state %d\n",tok,yyname[tok],s_tokenName[tok],lastyystate);&*/
                processName(s_tokenName[tok], &compLine, 0, &s_completions);
            }
        }
    }

    LICENSE_CHECK();
}



#line 2004 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#define ERR_RECOVERY_ON 1
int
yyparse()
{
    register int yym, yyn, yystate;

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
        }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
        {
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
#ifdef lint
    goto yynewerror;
#endif
 yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
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
                            if (yyssp <= yyss) goto yyabort;
                            --yyssp;
                            --yyvsp;
                        }
                }
        }
    else
        {
            if (yychar == 0) goto yyabort;
            yychar = (-1);
            goto yyloop;
        }
 yyreduce:
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
        {
        case 1:
#line 300 "../../src/cgram.y"
            {
                S_symbol *p;
                S_symbol *dd;
                p = yyvsp[0].bbidIdent.d->sd;
                if (p != NULL && p->b.symType == TypeDefault) {
                    assert(p && p);
                    dd = p;
                    assert(dd->b.storage != StorageTypedef);
                    yyval.bbexprType.d.t = dd->u.type;
                    assert(s_opt.taskRegime);
                    if (CX_REGIME()) {
                        yyval.bbexprType.d.r = addCxReference(p, &yyvsp[0].bbidIdent.d->p, UsageUsed,s_noneFileIndex, s_noneFileIndex);
                    } else {
                        yyval.bbexprType.d.r = NULL;
                    }
                } else {
                    /* implicit function declaration */
                    S_typeModifiers *p;
                    S_symbol *d;
                    S_symbol *dd;
                    CrTypeModifier(p, TypeInt);
                    yyval.bbexprType.d.t = StackMemAlloc(S_typeModifiers);
                    FILLF_typeModifiers(yyval.bbexprType.d.t, TypeFunction,f,( NULL,NULL) ,NULL,p);
                    d = StackMemAlloc(S_symbol);
                    FILL_symbolBits(&d->b,0,0,0,0,0,TypeDefault, StorageExtern, 0);
                    FILL_symbol(d,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->p,d->b,type,yyval.bbexprType.d.t,NULL);
                    d->u.type = yyval.bbexprType.d.t;
                    dd = addNewSymbolDef(d, StorageExtern, s_symTab, UsageUsed);
                    if (CX_REGIME()) {
                        yyval.bbexprType.d.r = addCxReference(dd, &yyvsp[0].bbidIdent.d->p, UsageUsed, s_noneFileIndex, s_noneFileIndex);
                    } else {
                        yyval.bbexprType.d.r = NULL;
                    }
                } 
            }
            break;
        case 2:
#line 335 "../../src/cgram.y"
            { CrTypeModifier(yyval.bbexprType.d.t, TypeInt); yyval.bbexprType.d.r = NULL;}
            break;
        case 3:
#line 336 "../../src/cgram.y"
            { CrTypeModifier(yyval.bbexprType.d.t, TypeInt); yyval.bbexprType.d.r = NULL;}
            break;
        case 4:
#line 337 "../../src/cgram.y"
            { CrTypeModifier(yyval.bbexprType.d.t, TypeLong); yyval.bbexprType.d.r = NULL;}
            break;
        case 5:
#line 338 "../../src/cgram.y"
            { CrTypeModifier(yyval.bbexprType.d.t, TypeFloat); yyval.bbexprType.d.r = NULL;}
            break;
        case 6:
#line 339 "../../src/cgram.y"
            { CrTypeModifier(yyval.bbexprType.d.t, TypeDouble); yyval.bbexprType.d.r = NULL;}
            break;
        case 7:
#line 340 "../../src/cgram.y"
            {
                S_typeModifiers *p;
                CrTypeModifier(p, TypeChar);
                yyval.bbexprType.d.t = StackMemAlloc(S_typeModifiers);
                FILLF_typeModifiers(yyval.bbexprType.d.t, TypePointer,f,( NULL,NULL) ,NULL,p);
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 8:
#line 347 "../../src/cgram.y"
            {
                yyval.bbexprType.d = yyvsp[-1].bbexprType.d;
            }
            break;
        case 9:
#line 350 "../../src/cgram.y"
            {       /* GNU's shit */
                yyval.bbexprType.d.t = &s_errorModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 10:
#line 354 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 14:
#line 364 "../../src/cgram.y"
            {
                if (yyvsp[-3].bbexprType.d.t->m==TypePointer || yyvsp[-3].bbexprType.d.t->m==TypeArray) yyval.bbexprType.d.t=yyvsp[-3].bbexprType.d.t->next;
                else if (yyvsp[-1].bbexprType.d.t->m==TypePointer || yyvsp[-1].bbexprType.d.t->m==TypeArray) yyval.bbexprType.d.t=yyvsp[-1].bbexprType.d.t->next;
                else yyval.bbexprType.d.t = &s_errorModifier;
                yyval.bbexprType.d.r = NULL;
                assert(yyval.bbexprType.d.t);
            }
            break;
        case 15:
#line 384 "../../src/cgram.y"
            {
                yyval.typeModif = s_upLevelFunctionCompletionType;
                s_upLevelFunctionCompletionType = yyvsp[0].bbexprType.d.t;
            }
            break;
        case 16:
#line 388 "../../src/cgram.y"
            {
                s_upLevelFunctionCompletionType = yyvsp[-3].typeModif;
                if (yyvsp[-4].bbexprType.d.t->m==TypeFunction) {
                    yyval.bbexprType.d.t=yyvsp[-4].bbexprType.d.t->next;
                    if (yyvsp[-1].bbpositionLst.d==NULL) {
                        handleInvocationParamPositions(yyvsp[-4].bbexprType.d.r, &yyvsp[-2].bbposition.d, NULL, &yyvsp[0].bbposition.d, 0);
                    } else {
                        handleInvocationParamPositions(yyvsp[-4].bbexprType.d.r, &yyvsp[-2].bbposition.d, yyvsp[-1].bbpositionLst.d->next, &yyvsp[0].bbposition.d, 1);
                    }
                } else {
                    yyval.bbexprType.d.t = &s_errorModifier;
                }
                yyval.bbexprType.d.r = NULL;
                assert(yyval.bbexprType.d.t);
            }
            break;
        case 17:
#line 403 "../../src/cgram.y"
            {SetStrCompl1(yyvsp[0].bbexprType.d.t);}
            break;
        case 18:
#line 403 "../../src/cgram.y"
            {
                S_symbol *rec=NULL;
                yyval.bbexprType.d.r = findStrRecordFromType(yyvsp[-3].bbexprType.d.t, yyvsp[0].bbidIdent.d, &rec, CLASS_TO_ANY);
                assert(rec);
                yyval.bbexprType.d.t = rec->u.type;
                assert(yyval.bbexprType.d.t);
            }
            break;
        case 19:
#line 410 "../../src/cgram.y"
            {SetStrCompl2(yyvsp[0].bbexprType.d.t);}
            break;
        case 20:
#line 410 "../../src/cgram.y"
            {
                S_typeModifiers *p;
                S_symbol *rec=NULL;
                yyval.bbexprType.d.r = NULL;
                if (yyvsp[-3].bbexprType.d.t->m==TypePointer || yyvsp[-3].bbexprType.d.t->m==TypeArray) {
                    yyval.bbexprType.d.r = findStrRecordFromType(yyvsp[-3].bbexprType.d.t->next, yyvsp[0].bbidIdent.d, &rec, CLASS_TO_ANY);
                    assert(rec);
                    yyval.bbexprType.d.t = rec->u.type;
                } else yyval.bbexprType.d.t = &s_errorModifier;
                assert(yyval.bbexprType.d.t);
            }
            break;
        case 21:
#line 421 "../../src/cgram.y"
            {
                yyval.bbexprType.d.t = yyvsp[-1].bbexprType.d.t;
                RESET_REFERENCE_USAGE(yyvsp[-1].bbexprType.d.r, UsageAddrUsed);
            }
            break;
        case 22:
#line 425 "../../src/cgram.y"
            {
                yyval.bbexprType.d.t = yyvsp[-1].bbexprType.d.t;
                RESET_REFERENCE_USAGE(yyvsp[-1].bbexprType.d.r, UsageAddrUsed);
            }
            break;
        case 24:
#line 433 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 25:
#line 436 "../../src/cgram.y"
            {
                yyval.bbpositionLst.d = NULL;
            }
            break;
        case 26:
#line 439 "../../src/cgram.y"
            {
                XX_ALLOC(yyval.bbpositionLst.d, S_positionLst);
                FILL_positionLst(yyval.bbpositionLst.d, s_noPos, yyvsp[0].bbpositionLst.d);
            }
            break;
        case 27:
#line 446 "../../src/cgram.y"
            { 
                yyval.bbpositionLst.d = NULL; 
            }
            break;
        case 28:
#line 449 "../../src/cgram.y"
            {
                yyval.bbpositionLst.d = yyvsp[-2].bbpositionLst.d;
                appendPositionToList(&yyval.bbpositionLst.d, &yyvsp[-1].bbposition.d);
            }
            break;
        case 29:
#line 453 "../../src/cgram.y"
            {/* never used */}
            break;
        case 30:
#line 454 "../../src/cgram.y"
            {/* never used */}
            break;
        case 32:
#line 459 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                RESET_REFERENCE_USAGE(yyvsp[0].bbexprType.d.r, UsageAddrUsed);
            }
            break;
        case 33:
#line 463 "../../src/cgram.y"
            {
                yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                RESET_REFERENCE_USAGE(yyvsp[0].bbexprType.d.r, UsageAddrUsed);
            }
            break;
        case 34:
#line 467 "../../src/cgram.y"
            { yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t; yyval.bbexprType.d.r = NULL;}
            break;
        case 35:
#line 468 "../../src/cgram.y"
            {
                yyval.bbexprType.d.t = StackMemAlloc(S_typeModifiers);
                FILLF_typeModifiers(yyval.bbexprType.d.t, TypePointer,f,( NULL,NULL) ,NULL,yyvsp[0].bbexprType.d.t);
                RESET_REFERENCE_USAGE(yyvsp[0].bbexprType.d.r, UsageAddrUsed);
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 36:
#line 474 "../../src/cgram.y"
            {
                if (yyvsp[0].bbexprType.d.t->m==TypePointer || yyvsp[0].bbexprType.d.t->m==TypeArray) yyval.bbexprType.d.t=yyvsp[0].bbexprType.d.t->next;
                else yyval.bbexprType.d.t = &s_errorModifier;
                assert(yyval.bbexprType.d.t);
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 37:
#line 480 "../../src/cgram.y"
            { 
                CrTypeModifier(yyval.bbexprType.d.t, TypeInt);
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 38:
#line 484 "../../src/cgram.y"
            {
                CrTypeModifier(yyval.bbexprType.d.t, TypeInt);
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 39:
#line 489 "../../src/cgram.y"
            {
                labelReference(yyvsp[0].bbidIdent.d, UsageLvalUsed);
            }
            break;
        case 45:
#line 503 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = yyvsp[-2].bbtypeModif.d; 
                yyval.bbexprType.d.r = yyvsp[0].bbexprType.d.r;
            }
            break;
        case 46:
#line 507 "../../src/cgram.y"
            { /* GNU-extension*/
                yyval.bbexprType.d.t = yyvsp[-4].bbtypeModif.d; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 47:
#line 511 "../../src/cgram.y"
            { /* GNU-extension*/
                yyval.bbexprType.d.t = yyvsp[-5].bbtypeModif.d; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 49:
#line 519 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 50:
#line 523 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 51:
#line 527 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 53:
#line 535 "../../src/cgram.y"
            {
                if (yyvsp[0].bbexprType.d.t->m==TypePointer || yyvsp[0].bbexprType.d.t->m==TypeArray) yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                else yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 54:
#line 540 "../../src/cgram.y"
            {
                if (yyvsp[0].bbexprType.d.t->m==TypePointer || yyvsp[0].bbexprType.d.t->m==TypeArray) yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t;
                else yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 56:
#line 549 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 57:
#line 553 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 59:
#line 561 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 60:
#line 565 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 61:
#line 569 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 62:
#line 573 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 64:
#line 581 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 65:
#line 585 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 67:
#line 593 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 69:
#line 601 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 71:
#line 609 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 73:
#line 617 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 75:
#line 625 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = &s_defaultIntModifier;
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 77:
#line 633 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = yyvsp[-2].bbexprType.d.t; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 78:
#line 638 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 80:
#line 646 "../../src/cgram.y"
            {
                if (yyvsp[-2].bbexprType.d.r != NULL && s_opt.cxrefs == OLO_EXTRACT) {
                    S_reference *rr;
                    rr = duplicateReference(yyvsp[-2].bbexprType.d.r);
                    yyvsp[-2].bbexprType.d.r->usg = s_noUsage;
                    if (yyvsp[-1].bbinteger.d == '=') {
                        RESET_REFERENCE_USAGE(rr, UsageLvalUsed);
                    } else {
                        RESET_REFERENCE_USAGE(rr, UsageAddrUsed);
                    }
                } else {
                    if (yyvsp[-1].bbinteger.d == '=') {
                        RESET_REFERENCE_USAGE(yyvsp[-2].bbexprType.d.r, UsageLvalUsed);
                    } else {
                        RESET_REFERENCE_USAGE(yyvsp[-2].bbexprType.d.r, UsageAddrUsed);
                    }
                }
                yyval.bbexprType.d = yyvsp[-2].bbexprType.d;    /* $$.d.r will be used for FOR completions ! */
            }
            break;
        case 81:
#line 668 "../../src/cgram.y"
            {yyval.bbinteger.d = '=';}
            break;
        case 82:
#line 669 "../../src/cgram.y"
            {yyval.bbinteger.d = MUL_ASSIGN;}
            break;
        case 83:
#line 670 "../../src/cgram.y"
            {yyval.bbinteger.d = DIV_ASSIGN;}
            break;
        case 84:
#line 671 "../../src/cgram.y"
            {yyval.bbinteger.d = MOD_ASSIGN;}
            break;
        case 85:
#line 672 "../../src/cgram.y"
            {yyval.bbinteger.d = ADD_ASSIGN;}
            break;
        case 86:
#line 673 "../../src/cgram.y"
            {yyval.bbinteger.d = SUB_ASSIGN;}
            break;
        case 87:
#line 674 "../../src/cgram.y"
            {yyval.bbinteger.d = LEFT_ASSIGN;}
            break;
        case 88:
#line 675 "../../src/cgram.y"
            {yyval.bbinteger.d = RIGHT_ASSIGN;}
            break;
        case 89:
#line 676 "../../src/cgram.y"
            {yyval.bbinteger.d = AND_ASSIGN;}
            break;
        case 90:
#line 677 "../../src/cgram.y"
            {yyval.bbinteger.d = XOR_ASSIGN;}
            break;
        case 91:
#line 678 "../../src/cgram.y"
            {yyval.bbinteger.d = OR_ASSIGN;}
            break;
        case 93:
#line 683 "../../src/cgram.y"
            { 
                yyval.bbexprType.d.t = yyvsp[0].bbexprType.d.t; 
                yyval.bbexprType.d.r = NULL;
            }
            break;
        case 95:
#line 694 "../../src/cgram.y"
            {
                yyval.bbunsign.d = tmpWorkMemoryi;
            }
            break;
        case 96:
#line 700 "../../src/cgram.y"
            { tmpWorkMemoryi = yyvsp[-2].bbunsign.d; }
            break;
        case 97:
#line 701 "../../src/cgram.y"
            { tmpWorkMemoryi = yyvsp[-2].bbunsign.d; }
            break;
        case 99:
#line 706 "../../src/cgram.y"
            {       
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                addNewDeclaration(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d, StorageAuto,s_symTab);
            }
            break;
        case 101:
#line 710 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                addNewDeclaration(yyvsp[-2].bbsymbol.d, yyvsp[0].bbsymbol.d, StorageAuto,s_symTab);
            }
            break;
        case 103:
#line 714 "../../src/cgram.y"
            {
                /* $$.d = &s_errorSymbol; */
                yyval.bbsymbol.d = typeSpecifier2(&s_errorModifier);
            }
            break;
        case 106:
#line 726 "../../src/cgram.y"
            {
                int usage;
                yyval.bbidIdent.d = yyvsp[0].bbidIdent.d;
                assert(s_opt.taskRegime);
                if (CX_REGIME()) {
                    assert(yyvsp[0].bbidIdent.d);
                    assert(yyvsp[0].bbidIdent.d->sd);
                    if (WORK_NEST_LEVEL0()) usage = USAGE_TOP_LEVEL_USED;
                    else usage = UsageUsed;
                    addCxReference(yyvsp[0].bbidIdent.d->sd,&yyvsp[0].bbidIdent.d->p,usage,s_noneFileIndex,s_noneFileIndex);
                }
            }
            break;
        case 107:
#line 741 "../../src/cgram.y"
            { 
                assert(yyvsp[0].bbidIdent.d);
                assert(yyvsp[0].bbidIdent.d->sd);
                yyval.bbsymbol.d = typeSpecifier2(yyvsp[0].bbidIdent.d->sd->u.type);
            }
            break;
        case 108:
#line 746 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier1(yyvsp[0].bbunsign.d);
            }
            break;
        case 109:
#line 749 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier2(yyvsp[0].bbtypeModif.d);
            }
            break;
        case 110:
#line 752 "../../src/cgram.y"
            { 
                assert(yyvsp[0].bbidIdent.d);
                assert(yyvsp[0].bbidIdent.d->sd);
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbidIdent.d->sd->u.type);
            }
            break;
        case 111:
#line 758 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 112:
#line 762 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbtypeModif.d);
            }
            break;
        case 113:
#line 766 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 114:
#line 770 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 115:
#line 774 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbtypeModif.d);
            }
            break;
        case 116:
#line 778 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                yyval.bbsymbol.d->b.storage = yyvsp[0].bbunsign.d; 
            }
            break;
        case 117:
#line 782 "../../src/cgram.y"
            { 
                assert(0);
            }
            break;
        case 118:
#line 785 "../../src/cgram.y"
            { 
                assert(0); /* token never used */ 
            }
            break;
        case 119:
#line 791 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier1(TypeDefault);
                yyval.bbsymbol.d->b.storage = yyvsp[0].bbunsign.d; 
            }
            break;
        case 120:
#line 795 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                yyval.bbsymbol.d->b.storage = yyvsp[0].bbunsign.d; 
            }
            break;
        case 121:
#line 799 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier1(yyvsp[0].bbunsign.d);
            }
            break;
        case 122:
#line 802 "../../src/cgram.y"
            {
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d, yyvsp[0].bbunsign.d);
            }
            break;
        case 128:
#line 849 "../../src/cgram.y"
            { yyval.bbunsign.d = StorageTypedef; }
            break;
        case 129:
#line 850 "../../src/cgram.y"
            { yyval.bbunsign.d = StorageExtern; }
            break;
        case 130:
#line 851 "../../src/cgram.y"
            { yyval.bbunsign.d = StorageStatic; }
            break;
        case 131:
#line 852 "../../src/cgram.y"
            { yyval.bbunsign.d = StorageAuto; }
            break;
        case 132:
#line 853 "../../src/cgram.y"
            { yyval.bbunsign.d = StorageAuto; }
            break;
        case 133:
#line 860 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeDefault; }
            break;
        case 134:
#line 861 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeDefault; }
            break;
        case 135:
#line 862 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeDefault; }
            break;
        case 138:
#line 870 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeChar; }
            break;
        case 139:
#line 871 "../../src/cgram.y"
            { yyval.bbunsign.d = TmodShort; }
            break;
        case 140:
#line 872 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeInt; }
            break;
        case 141:
#line 873 "../../src/cgram.y"
            { yyval.bbunsign.d = TmodLong; }
            break;
        case 142:
#line 874 "../../src/cgram.y"
            { yyval.bbunsign.d = TmodSigned; }
            break;
        case 143:
#line 875 "../../src/cgram.y"
            { yyval.bbunsign.d = TmodUnsigned; }
            break;
        case 144:
#line 876 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeFloat; }
            break;
        case 145:
#line 877 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeDouble; }
            break;
        case 146:
#line 878 "../../src/cgram.y"
            { yyval.bbunsign.d = TypeVoid; }
            break;
        case 149:
#line 887 "../../src/cgram.y"
            {
                int usage;
                if (WORK_NEST_LEVEL0()) usage = USAGE_TOP_LEVEL_USED;
                else usage = UsageUsed;
                yyval.bbtypeModif.d = simpleStrUnionSpecifier(yyvsp[-1].bbidIdent.d, yyvsp[0].bbidIdent.d, usage);
            }
            break;
        case 150:
#line 893 "../../src/cgram.y"
            {
                assert(yyvsp[-3].bbtypeModif.d && yyvsp[-3].bbtypeModif.d->u.t);
                yyval.bbtypeModif.d = yyvsp[-3].bbtypeModif.d;
                specializeStrUnionDef(yyval.bbtypeModif.d->u.t, yyvsp[-1].bbsymbol.d);
            }
            break;
        case 151:
#line 898 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[-2].bbtypeModif.d;
            }
            break;
        case 152:
#line 904 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = simpleStrUnionSpecifier(yyvsp[-1].bbidIdent.d, yyvsp[0].bbidIdent.d, UsageDefined);
            }
            break;
        case 153:
#line 907 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = crNewAnnonymeStrUnion(yyvsp[0].bbidIdent.d);
            }
            break;
        case 155:
#line 914 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 156:
#line 918 "../../src/cgram.y"
            { yyval.bbidIdent.d = yyvsp[0].bbidIdent.d; }
            break;
        case 157:
#line 919 "../../src/cgram.y"
            { yyval.bbidIdent.d = yyvsp[0].bbidIdent.d; }
            break;
        case 159:
#line 924 "../../src/cgram.y"
            {
                if (yyvsp[-1].bbsymbol.d == &s_errorSymbol || yyvsp[-1].bbsymbol.d->b.symType==TypeError) {
                    yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                } else if (yyvsp[0].bbsymbol.d == &s_errorSymbol || yyvsp[-1].bbsymbol.d->b.symType==TypeError)  {
                    yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                } else {
                    yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                    LIST_APPEND(S_symbol, yyval.bbsymbol.d, yyvsp[0].bbsymbol.d);
                }
            }
            break;
        case 160:
#line 937 "../../src/cgram.y"
            {
                S_symbol *p;
                assert(yyvsp[-2].bbsymbol.d && yyvsp[-1].bbsymbol.d);
                for(p=yyvsp[-1].bbsymbol.d; p!=NULL; p=p->next) {
                    completeDeclarator(yyvsp[-2].bbsymbol.d, p);
                }
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                tmpWorkMemoryi = yyvsp[-3].bbunsign.d;
            }
            break;
        case 161:
#line 946 "../../src/cgram.y"
            {
                /* $$.d = &s_errorSymbol; */
                XX_ALLOC(yyval.bbsymbol.d, S_symbol);
                *yyval.bbsymbol.d = s_errorSymbol;
            }
            break;
        case 162:
#line 954 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                assert(yyval.bbsymbol.d->next == NULL);
            }
            break;
        case 163:
#line 958 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                assert(yyvsp[0].bbsymbol.d->next == NULL);
                LIST_APPEND(S_symbol, yyval.bbsymbol.d, yyvsp[0].bbsymbol.d);
            }
            break;
        case 164:
#line 965 "../../src/cgram.y"
            { /* gcc extension allow empty field */
                yyval.bbsymbol.d = crEmptyField();  
            }
            break;
        case 165:
#line 968 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = crEmptyField();
            }
            break;
        case 168:
#line 976 "../../src/cgram.y"
            {
                int usage;
                if (WORK_NEST_LEVEL0()) usage = USAGE_TOP_LEVEL_USED;
                else usage = UsageUsed;
                yyval.bbtypeModif.d = simpleEnumSpecifier(yyvsp[0].bbidIdent.d, usage);
            }
            break;
        case 169:
#line 982 "../../src/cgram.y"
            {
                assert(yyvsp[-3].bbtypeModif.d && yyvsp[-3].bbtypeModif.d->m == TypeEnum && yyvsp[-3].bbtypeModif.d->u.t);
                yyval.bbtypeModif.d = yyvsp[-3].bbtypeModif.d;
                if (yyval.bbtypeModif.d->u.t->u.enums==NULL) {
                    yyval.bbtypeModif.d->u.t->u.enums = yyvsp[-1].bbsymbolList.d;
                    addToTrail(setToNull, & (yyval.bbtypeModif.d->u.t->u.enums) );
                }
            }
            break;
        case 170:
#line 990 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = crNewAnnonymeEnum(yyvsp[-1].bbsymbolList.d);
            }
            break;
        case 171:
#line 996 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = simpleEnumSpecifier(yyvsp[0].bbidIdent.d, UsageDefined);
            }
            break;
        case 173:
#line 1003 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 176:
#line 1012 "../../src/cgram.y"
            {
                yyval.bbsymbolList.d = crDefinitionList(yyvsp[0].bbsymbol.d);
            }
            break;
        case 177:
#line 1015 "../../src/cgram.y"
            {
                yyval.bbsymbolList.d = yyvsp[-2].bbsymbolList.d;
                LIST_APPEND(S_symbolList, yyval.bbsymbolList.d, crDefinitionList(yyvsp[0].bbsymbol.d));
            }
            break;
        case 178:
#line 1022 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = crSimpleDefinition(StorageConstant,TypeInt,yyvsp[0].bbidIdent.d);
                addNewSymbolDef(yyval.bbsymbol.d,StorageConstant, s_symTab, UsageDefined);
            }
            break;
        case 179:
#line 1026 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = crSimpleDefinition(StorageConstant,TypeInt,yyvsp[-2].bbidIdent.d);
                addNewSymbolDef(yyval.bbsymbol.d,StorageConstant, s_symTab, UsageDefined);
            }
            break;
        case 180:
#line 1030 "../../src/cgram.y"
            {
                /* $$.d = &s_errorSymbol; */
                XX_ALLOC(yyval.bbsymbol.d, S_symbol);
                *yyval.bbsymbol.d = s_errorSymbol;
            }
            break;
        case 181:
#line 1035 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 183:
#line 1040 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
                assert(yyval.bbsymbol.d->b.npointers == 0);
                yyval.bbsymbol.d->b.npointers = yyvsp[-1].bbinteger.d;
            }
            break;
        case 184:
#line 1048 "../../src/cgram.y"
            { 
                yyval.bbsymbol.d = StackMemAlloc(S_symbol);
                FILL_symbolBits(&yyval.bbsymbol.d->b,0,0,0,0,0,TypeDefault,StorageDefault,0);
                FILL_symbol(yyval.bbsymbol.d,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->p,yyval.bbsymbol.d->b,type,NULL,NULL);
                yyval.bbsymbol.d->u.type = NULL;
            }
            break;
        case 185:
#line 1054 "../../src/cgram.y"
            { 
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                unpackPointers(yyval.bbsymbol.d);
            }
            break;
        case 186:
#line 1058 "../../src/cgram.y"
            { 
                assert(yyvsp[-2].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                AddComposedType(yyval.bbsymbol.d, TypeArray);
            }
            break;
        case 187:
#line 1063 "../../src/cgram.y"
            { 
                assert(yyvsp[-3].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d; 
                AddComposedType(yyval.bbsymbol.d, TypeArray);
            }
            break;
        case 188:
#line 1068 "../../src/cgram.y"
            { 
                S_typeModifiers *p;
                assert(yyvsp[-2].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d; 
                p = AddComposedType(yyval.bbsymbol.d, TypeFunction);
                FILL_funTypeModif(&p->u.f , NULL, NULL);
                handleDeclaratorParamPositions(yyvsp[-2].bbsymbol.d, &yyvsp[-1].bbposition.d, NULL, &yyvsp[0].bbposition.d, 0);
            }
            break;
        case 189:
#line 1076 "../../src/cgram.y"
            { 
                S_typeModifiers *p;
                assert(yyvsp[-3].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d; 
                p = AddComposedType(yyval.bbsymbol.d, TypeFunction);
                FILL_funTypeModif(&p->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                handleDeclaratorParamPositions(yyvsp[-3].bbsymbol.d, &yyvsp[-2].bbposition.d, yyvsp[-1].bbsymbolPositionLstPair.d.p, &yyvsp[0].bbposition.d, 1);
            }
            break;
        case 190:
#line 1084 "../../src/cgram.y"
            { 
                S_typeModifiers *p;
                assert(yyvsp[-3].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d; 
                p = AddComposedType(yyval.bbsymbol.d, TypeFunction);
                FILL_funTypeModif(&p->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
                handleDeclaratorParamPositions(yyvsp[-3].bbsymbol.d, &yyvsp[-2].bbposition.d, yyvsp[-1].bbsymbolPositionLstPair.d.p, &yyvsp[0].bbposition.d, 1);
            }
            break;
        case 191:
#line 1092 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 192:
#line 1096 "../../src/cgram.y"
            {
                yyval.bbinteger.d = 1;
            }
            break;
        case 193:
#line 1099 "../../src/cgram.y"
            {
                yyval.bbinteger.d = 1;
            }
            break;
        case 194:
#line 1102 "../../src/cgram.y"
            {
                yyval.bbinteger.d = yyvsp[0].bbinteger.d+1;
            }
            break;
        case 195:
#line 1105 "../../src/cgram.y"
            {
                yyval.bbinteger.d = yyvsp[0].bbinteger.d+1;
            }
            break;
        case 196:
#line 1111 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier1(yyvsp[0].bbunsign.d);
            }
            break;
        case 197:
#line 1114 "../../src/cgram.y"
            {
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d, yyvsp[0].bbunsign.d);
            }
            break;
        case 200:
#line 1142 "../../src/cgram.y"
            { 
                assert(yyvsp[0].bbidIdent.d);
                assert(yyvsp[0].bbidIdent.d->sd);
                assert(yyvsp[0].bbidIdent.d->sd);
                yyval.bbsymbol.d = typeSpecifier2(yyvsp[0].bbidIdent.d->sd->u.type);
            }
            break;
        case 201:
#line 1148 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier1(yyvsp[0].bbunsign.d);
            }
            break;
        case 202:
#line 1151 "../../src/cgram.y"
            {
                yyval.bbsymbol.d  = typeSpecifier2(yyvsp[0].bbtypeModif.d);
            }
            break;
        case 203:
#line 1154 "../../src/cgram.y"
            { 
                assert(yyvsp[0].bbidIdent.d);
                assert(yyvsp[0].bbidIdent.d->sd);
                assert(yyvsp[0].bbidIdent.d->sd);
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbidIdent.d->sd->u.type);
            }
            break;
        case 204:
#line 1161 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 205:
#line 1165 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbtypeModif.d);
            }
            break;
        case 206:
#line 1169 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 207:
#line 1173 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier1(yyvsp[-1].bbsymbol.d,yyvsp[0].bbunsign.d);
            }
            break;
        case 208:
#line 1177 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
                declTypeSpecifier2(yyvsp[-1].bbsymbol.d,yyvsp[0].bbtypeModif.d);
            }
            break;
        case 209:
#line 1181 "../../src/cgram.y"
            { 
                assert(0);
            }
            break;
        case 210:
#line 1184 "../../src/cgram.y"
            { 
                assert(0); /* token never used */ 
            }
            break;
        case 212:
#line 1191 "../../src/cgram.y"
            {
                S_symbol *p;
                S_position pp;
                p = StackMemAlloc(S_symbol);
                FILL_position(&pp, -1, 0, 0);
                FILL_symbolBits(&p->b,0,0,0,0,0,TypeElipsis,StorageDefault,0);
                FILL_symbol(p,"","",pp,p->b,type,NULL,NULL);
                yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                LIST_APPEND(S_symbol, yyval.bbsymbolPositionLstPair.d.s, p);                
                appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
            }
            break;
        case 213:
#line 1205 "../../src/cgram.y"
            {
                S_symbol *p;
                p = StackMemAlloc(S_symbol);
                FILL_symbolBits(&p->b,0,0,0,0,0,TypeDefault,StorageDefault,0);
                FILL_symbol(p,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->p,p->b,type,NULL,NULL);
                p->u.type = NULL;
                yyval.bbsymbolPositionLstPair.d.s = p;
                yyval.bbsymbolPositionLstPair.d.p = NULL;
            }
            break;
        case 214:
#line 1214 "../../src/cgram.y"
            {
                S_symbol        *p;
                p = StackMemAlloc(S_symbol);
                FILL_symbolBits(&p->b,0,0,0,0,0,TypeDefault,StorageDefault,0);
                FILL_symbol(p,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->name,yyvsp[0].bbidIdent.d->p,p->b,type,NULL,NULL);
                p->u.type = NULL;
                yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                LIST_APPEND(S_symbol, yyval.bbsymbolPositionLstPair.d.s, p);
                appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
            }
            break;
        case 215:
#line 1224 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 217:
#line 1229 "../../src/cgram.y"
            {
                S_symbol        *p;
                S_position      pp;
                p = StackMemAlloc(S_symbol);
                FILL_position(&pp, -1, 0, 0);
                FILL_symbolBits(&p->b,0,0,0,0,0,TypeElipsis,StorageDefault,0);
                FILL_symbol(p,"","",pp,p->b,type,NULL,NULL);
                yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                LIST_APPEND(S_symbol, yyval.bbsymbolPositionLstPair.d.s, p);
                appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
            }
            break;
        case 218:
#line 1243 "../../src/cgram.y"
            {
                yyval.bbsymbolPositionLstPair.d.s = yyvsp[0].bbsymbol.d;
                yyval.bbsymbolPositionLstPair.d.p = NULL;
            }
            break;
        case 219:
#line 1247 "../../src/cgram.y"
            {
                yyval.bbsymbolPositionLstPair.d = yyvsp[-2].bbsymbolPositionLstPair.d;
                LIST_APPEND(S_symbol, yyvsp[-2].bbsymbolPositionLstPair.d.s, yyvsp[0].bbsymbol.d);
                appendPositionToList(&yyval.bbsymbolPositionLstPair.d.p, &yyvsp[-1].bbposition.d);
            }
            break;
        case 220:
#line 1256 "../../src/cgram.y"
            { 
                completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            }
            break;
        case 221:
#line 1260 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = StackMemAlloc(S_symbol);
                FILL_symbolBits(&yyval.bbsymbol.d->b,0,0,0,0,0,TypeDefault, StorageDefault,0);
                FILL_symbol(yyval.bbsymbol.d, NULL, NULL, s_noPos,yyval.bbsymbol.d->b,type,yyvsp[0].bbtypeModif.d,NULL);
                yyval.bbsymbol.d->u.type = yyvsp[0].bbtypeModif.d;
            }
            break;
        case 222:
#line 1266 "../../src/cgram.y"
            {
                /*
                  this was commented out, because of excess of tmpWorkMemory 
                  but I am putting it in, because in many cases, this helps
                  to index a function with wrong typedefed parameters, like:
                  void toto(Mistype arg) {}
                  In case of problems rather increase the tmpWorkMemory !!!
                */
                XX_ALLOC(yyval.bbsymbol.d, S_symbol);
                *yyval.bbsymbol.d = s_errorSymbol;
            }
            break;
        case 223:
#line 1280 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[0].bbsymbol.d->u.type;
            }
            break;
        case 224:
#line 1283 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[0].bbtypeModif.d;
                LIST_APPEND(S_typeModifiers, yyval.bbtypeModif.d, yyvsp[-1].bbsymbol.d->u.type);
            }
            break;
        case 225:
#line 1290 "../../src/cgram.y"
            {
                int i;
                CrTypeModifier(yyval.bbtypeModif.d,TypePointer);
                for(i=1; i<yyvsp[0].bbinteger.d; i++) appendComposedType(&(yyval.bbtypeModif.d), TypePointer);
            }
            break;
        case 226:
#line 1295 "../../src/cgram.y"
            { 
                yyval.bbtypeModif.d = yyvsp[0].bbtypeModif.d;
            }
            break;
        case 227:
#line 1298 "../../src/cgram.y"
            {
                int i;
                yyval.bbtypeModif.d = yyvsp[0].bbtypeModif.d;
                for(i=0; i<yyvsp[-1].bbinteger.d; i++) appendComposedType(&(yyval.bbtypeModif.d), TypePointer);
            }
            break;
        case 228:
#line 1306 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[-1].bbtypeModif.d; 
            }
            break;
        case 229:
#line 1309 "../../src/cgram.y"
            {
                CrTypeModifier(yyval.bbtypeModif.d,TypeArray);      
            }
            break;
        case 230:
#line 1312 "../../src/cgram.y"
            {
                CrTypeModifier(yyval.bbtypeModif.d,TypeArray);      
            }
            break;
        case 231:
#line 1315 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[-2].bbtypeModif.d;
                appendComposedType(&(yyval.bbtypeModif.d), TypeArray);
            }
            break;
        case 232:
#line 1319 "../../src/cgram.y"
            {
                yyval.bbtypeModif.d = yyvsp[-3].bbtypeModif.d;
                appendComposedType(&(yyval.bbtypeModif.d), TypeArray);
            }
            break;
        case 233:
#line 1323 "../../src/cgram.y"
            {
                CrTypeModifier(yyval.bbtypeModif.d,TypeFunction);
                FILL_funTypeModif(&yyval.bbtypeModif.d->u.f , NULL, NULL);
            }
            break;
        case 234:
#line 1327 "../../src/cgram.y"
            {
                CrTypeModifier(yyval.bbtypeModif.d,TypeFunction);
                FILL_funTypeModif(&yyval.bbtypeModif.d->u.f , yyvsp[-1].bbsymbolPositionLstPair.d.s, NULL);
            }
            break;
        case 235:
#line 1331 "../../src/cgram.y"
            {
                S_typeModifiers *p;
                yyval.bbtypeModif.d = yyvsp[-2].bbtypeModif.d;
                p = appendComposedType(&(yyval.bbtypeModif.d), TypeFunction);
                FILL_funTypeModif(&p->u.f , NULL, NULL);
            }
            break;
        case 236:
#line 1337 "../../src/cgram.y"
            {
                S_typeModifiers *p;
                yyval.bbtypeModif.d = yyvsp[-3].bbtypeModif.d;
                p = appendComposedType(&(yyval.bbtypeModif.d), TypeFunction);
                /* I think there should be the following, but in abstract */
                /* declarator it does not matter*/
                /*& FILL_funTypeModif(&p->u.f , $3.d.s, NULL);*/
                FILL_funTypeModif(&p->u.f , NULL, NULL);
            }
            break;
        case 241:
#line 1357 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-3].bbunsign.d;
            }
            break;
        case 242:
#line 1360 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-3].bbunsign.d;
            }
            break;
        case 243:
#line 1366 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 244:
#line 1369 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 245:
#line 1372 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 246:
#line 1375 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 247:
#line 1378 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 248:
#line 1381 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 249:
#line 1384 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 250:
#line 1387 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 252:
#line 1394 "../../src/cgram.y"
            {
                GenSwitchCaseFork(0);
            }
            break;
        case 253:
#line 1397 "../../src/cgram.y"
            {
                GenSwitchCaseFork(0);
            }
            break;
        case 255:
#line 1407 "../../src/cgram.y"
            {
                labelReference(yyvsp[0].bbidIdent.d,UsageDefined);
            }
            break;
        case 256:
#line 1410 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 257:
#line 1414 "../../src/cgram.y"
            {
                labelReference(yyvsp[0].bbidIdent.d,UsageUsed);
            }
            break;
        case 258:
#line 1417 "../../src/cgram.y"
            { assert(0); /* token never used */ }
            break;
        case 263:
#line 1434 "../../src/cgram.y"
            {
                labelReference(yyvsp[0].bbidIdent.d,UsageDeclared);
            }
            break;
        case 264:
#line 1437 "../../src/cgram.y"
            {
                labelReference(yyvsp[0].bbidIdent.d,UsageDeclared);
            }
            break;
        case 269:
#line 1462 "../../src/cgram.y"
            { yyval.bbexprType.d.t = NULL; yyval.bbexprType.d.r = NULL; }
            break;
        case 270:
#line 1463 "../../src/cgram.y"
            { yyval.bbexprType.d = yyvsp[0].bbexprType.d; }
            break;
        case 272:
#line 1471 "../../src/cgram.y"
            {EXTRACT_COUNTER_SEMACT(yyval.bbinteger.d);}
            break;
        case 273:
#line 1474 "../../src/cgram.y"
            {EXTRACT_LABEL_SEMACT(yyval.bbinteger.d);}
            break;
        case 274:
#line 1477 "../../src/cgram.y"
            {EXTRACT_GOTO_SEMACT(yyval.bbinteger.d);}
            break;
        case 275:
#line 1480 "../../src/cgram.y"
            {EXTRACT_FORK_SEMACT(yyval.bbinteger.d);}
            break;
        case 276:
#line 1484 "../../src/cgram.y"
            {
                GenInternalLabelReference(yyvsp[-1].bbinteger.d, UsageDefined);
            }
            break;
        case 277:
#line 1487 "../../src/cgram.y"
            {
                GenInternalLabelReference(yyvsp[-3].bbinteger.d, UsageDefined);
            }
            break;
        case 278:
#line 1489 "../../src/cgram.y"
            {
                GenInternalLabelReference(yyvsp[-2].bbinteger.d, UsageDefined);
            }
            break;
        case 279:
#line 1492 "../../src/cgram.y"
            {/*6*/
                AddContinueBreakLabelSymbol(1000*yyvsp[0].bbinteger.d, SWITCH_LABEL_NAME, yyval.symbol);
            }
            break;
        case 280:
#line 1494 "../../src/cgram.y"
            {/*7*/
                AddContinueBreakLabelSymbol(yyvsp[-1].bbinteger.d, BREAK_LABEL_NAME, yyval.symbol);
                GenInternalLabelReference(yyvsp[-1].bbinteger.d, UsageFork);
            }
            break;
        case 281:
#line 1497 "../../src/cgram.y"
            {
                GenSwitchCaseFork(1);
                ExtrDeleteContBreakSym(yyvsp[-1].symbol);
                ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                GenInternalLabelReference(yyvsp[-3].bbinteger.d, UsageDefined);
            }
            break;
        case 282:
#line 1506 "../../src/cgram.y"
            {s_forCompletionType=yyvsp[0].bbexprType.d;}
            break;
        case 283:
#line 1511 "../../src/cgram.y"
            {/*7*/
                AddContinueBreakLabelSymbol(yyvsp[-4].bbinteger.d, CONTINUE_LABEL_NAME, yyval.symbol);
            }
            break;
        case 284:
#line 1513 "../../src/cgram.y"
            {/*8*/
                AddContinueBreakLabelSymbol(yyvsp[-1].bbinteger.d, BREAK_LABEL_NAME, yyval.symbol);
            }
            break;
        case 285:
#line 1515 "../../src/cgram.y"
            {
                ExtrDeleteContBreakSym(yyvsp[-1].symbol);
                ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                GenInternalLabelReference(yyvsp[-7].bbinteger.d, UsageUsed);
                GenInternalLabelReference(yyvsp[-3].bbinteger.d, UsageDefined);
            }
            break;
        case 286:
#line 1522 "../../src/cgram.y"
            { /*5*/
                AddContinueBreakLabelSymbol(yyvsp[-1].bbinteger.d, CONTINUE_LABEL_NAME, yyval.symbol);
            }
            break;
        case 287:
#line 1524 "../../src/cgram.y"
            {/*6*/
                AddContinueBreakLabelSymbol(yyvsp[-1].bbinteger.d, BREAK_LABEL_NAME, yyval.symbol);
            }
            break;
        case 288:
#line 1526 "../../src/cgram.y"
            {
                ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                ExtrDeleteContBreakSym(yyvsp[-3].symbol);
                GenInternalLabelReference(yyvsp[-5].bbinteger.d, UsageDefined);
            }
            break;
        case 289:
#line 1530 "../../src/cgram.y"
            {
                GenInternalLabelReference(yyvsp[-11].bbinteger.d, UsageFork);
                GenInternalLabelReference(yyvsp[-9].bbinteger.d, UsageDefined);
            }
            break;
        case 290:
#line 1538 "../../src/cgram.y"
            {
                /*13*/
                GenInternalLabelReference(yyvsp[-7].bbinteger.d, UsageUsed);
                GenInternalLabelReference(yyvsp[-4].bbinteger.d, UsageDefined);
                AddContinueBreakLabelSymbol(yyvsp[-3].bbinteger.d, CONTINUE_LABEL_NAME, yyval.symbol);
            }
            break;
        case 291:
#line 1544 "../../src/cgram.y"
            {/*14*/
                AddContinueBreakLabelSymbol(yyvsp[-1].bbinteger.d, BREAK_LABEL_NAME, yyval.symbol);     
            }
            break;
        case 292:
#line 1548 "../../src/cgram.y"
            { 
                ExtrDeleteContBreakSym(yyvsp[-1].symbol);
                ExtrDeleteContBreakSym(yyvsp[-2].symbol);
                GenInternalLabelReference(yyvsp[-6].bbinteger.d, UsageUsed);
                GenInternalLabelReference(yyvsp[-3].bbinteger.d, UsageDefined);
            }
            break;
        case 296:
#line 1560 "../../src/cgram.y"
            {
                GenContBreakReference(CONTINUE_LABEL_NAME);
            }
            break;
        case 297:
#line 1563 "../../src/cgram.y"
            {
                GenContBreakReference(BREAK_LABEL_NAME);
            }
            break;
        case 298:
#line 1566 "../../src/cgram.y"
            {
                GenInternalLabelReference(-1, UsageUsed);
            }
            break;
        case 299:
#line 1569 "../../src/cgram.y"
            {
                GenInternalLabelReference(-1, UsageUsed);
            }
            break;
        case 300:
#line 1574 "../../src/cgram.y"
            {
                actionsBeforeAfterExternalDefinition();
            }
            break;
        case 314:
#line 1612 "../../src/cgram.y"
            {
                if (inStacki == 0) {
                    poseCachePoint(1);
                }
            }
            break;
        case 315:
#line 1617 "../../src/cgram.y"
            {
                if (inStacki == 0) {
                    poseCachePoint(1);
                }
            }
            break;
        case 317:
#line 1626 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-2].bbunsign.d;
            }
            break;
        case 318:
#line 1629 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-2].bbunsign.d;
            }
            break;
        case 319:
#line 1632 "../../src/cgram.y"
            {
                S_symbol *p,*pa,*pp;
                int i;
                assert(yyvsp[0].bbsymbol.d);
                /* I think that due to the following line sometimes */
                /* storage was not extern, see 'addNewSymbolDef'*/
                /*& if ($2.d->b.storage == StorageDefault) $2.d->b.storage = StorageExtern;*/
                /* TODO!!!, here you should check if there is previous declaration of*/
                /* the function, if yes and is declared static, make it static!*/
                addNewSymbolDef(yyvsp[0].bbsymbol.d, StorageExtern, s_symTab, UsageDefined);
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
                stackMemoryBlockStart();
                s_count.localVar = 0;
                assert(yyvsp[0].bbsymbol.d->u.type && yyvsp[0].bbsymbol.d->u.type->m == TypeFunction);
                s_cp.function = yyvsp[0].bbsymbol.d;
                GenInternalLabelReference(-1, UsageDefined);
                for(p=yyvsp[0].bbsymbol.d->u.type->u.f.args,i=1; p!=NULL; p=p->next,i++) {
                    if (p->b.symType == TypeElipsis) continue;
                    if (p->u.type == NULL) p->u.type = &s_defaultIntModifier;
                    addFunctionParameterToSymTable(yyvsp[0].bbsymbol.d, p, i, s_symTab);
                }
            }
            break;
        case 320:
#line 1653 "../../src/cgram.y"
            {
                stackMemoryBlockFree();
                s_cp.function = NULL;
                LICENSE_CHECK();
                if (s_opt.taskRegime == RegimeHtmlGenerate) {
                    htmlAddFunctionSeparatorReference();
                }
            }
            break;
        case 321:
#line 1661 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-3].bbunsign.d;
            }
            break;
        case 322:
#line 1664 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-5].bbunsign.d;
            }
            break;
        case 323:
#line 1667 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-5].bbunsign.d;
            }
            break;
        case 324:
#line 1670 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-2].bbunsign.d;
            }
            break;
        case 325:
#line 1673 "../../src/cgram.y"
            {
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 326:
#line 1676 "../../src/cgram.y"
            {  /* empty external definition */
                tmpWorkMemoryi = yyvsp[-1].bbunsign.d;
            }
            break;
        case 327:
#line 1682 "../../src/cgram.y"
            {       
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
                addNewDeclaration(yyvsp[-2].bbsymbol.d, yyvsp[-1].bbsymbol.d, StorageExtern,s_symTab);
            }
            break;
        case 328:
#line 1686 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = & s_defaultIntDefinition;
                addNewDeclaration(yyval.bbsymbol.d, yyvsp[-1].bbsymbol.d, StorageExtern,s_symTab);
            }
            break;
        case 329:
#line 1690 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d;
                addNewDeclaration(yyvsp[-3].bbsymbol.d, yyvsp[-1].bbsymbol.d, StorageExtern,s_symTab);
            }
            break;
        case 330:
#line 1694 "../../src/cgram.y"
            {
                /* $$.d = &s_errorSymbol; */
                yyval.bbsymbol.d = typeSpecifier2(&s_errorModifier);
            }
            break;
        case 332:
#line 1702 "../../src/cgram.y"
            {
                int r;
                assert(yyvsp[-1].bbsymbol.d->u.type && yyvsp[-1].bbsymbol.d->u.type->m == TypeFunction);
                r = mergeArguments(yyvsp[-1].bbsymbol.d->u.type->u.f.args, yyvsp[0].bbsymbol.d);
                if (r == RESULT_ERR) YYERROR;
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
            }
            break;
        case 333:
#line 1712 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = NULL;
            }
            break;
        case 334:
#line 1715 "../../src/cgram.y"
            {
                S_symbol *p;
                assert(yyvsp[-2].bbsymbol.d && yyvsp[-1].bbsymbol.d);
                for(p=yyvsp[-1].bbsymbol.d; p!=NULL; p=p->next) {
                    completeDeclarator(yyvsp[-2].bbsymbol.d, p);
                }
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
            }
            break;
        case 335:
#line 1726 "../../src/cgram.y"
            {       
                yyval.bbsymbol.d = yyvsp[-1].bbsymbol.d;
            }
            break;
        case 336:
#line 1729 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-3].bbsymbol.d;
                LIST_APPEND(S_symbol, yyval.bbsymbol.d, yyvsp[-1].bbsymbol.d);
            }
            break;
        case 337:
#line 1733 "../../src/cgram.y"
            {
                yyval.bbsymbol.d = yyvsp[-2].bbsymbol.d;
            }
            break;
        case 338:
#line 1739 "../../src/cgram.y"
            {
                completeDeclarator(&s_defaultIntDefinition, yyvsp[0].bbsymbol.d);
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->u.type);
                if (yyvsp[0].bbsymbol.d->u.type->m != TypeFunction) YYERROR;
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            }
            break;
        case 339:
#line 1745 "../../src/cgram.y"
            {
                completeDeclarator(yyvsp[-1].bbsymbol.d, yyvsp[0].bbsymbol.d);
                assert(yyvsp[0].bbsymbol.d && yyvsp[0].bbsymbol.d->u.type);
                if (yyvsp[0].bbsymbol.d->u.type->m != TypeFunction) YYERROR;
                yyval.bbsymbol.d = yyvsp[0].bbsymbol.d;
            }
            break;
        case 340:
#line 1754 "../../src/cgram.y"
            { stackMemoryBlockStart(); }
            break;
        case 341:
#line 1757 "../../src/cgram.y"
            { stackMemoryBlockFree(); }
            break;
#line 3921 "y.tab.c"
        }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
        {
            yystate = YYFINAL;
            *++yyssp = YYFINAL;
            *++yyvsp = yyval;
            if (yychar < 0)
                {
                    lastyystate = yystate;
                    if ((yychar = yylex()) < 0) yychar = 0;
                }
            if (yychar == 0) goto yyaccept;
            goto yyloop;
        }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
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
