%{

#define yaccyylex yylex

#include "yacc_parser.x"

#include "globals.h"
#include "misc.h"
#include "commons.h"
#include "complete.h"
#include "caching.h"
#include "yylex.h"
#include "semact.h"
#include "cxref.h"
#include "symbol.h"
#include "list.h"

#include "log.h"
#include "utils.h"

#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define yaccyyerror styyerror
#define yyErrorRecovery styyErrorRecovery


#define SetStrCompl1(xxx) {\
    assert(s_opt.taskRegime);\
    if (s_opt.taskRegime == RegimeEditServer) {\
        s_structRecordCompletionType = xxx;\
    }\
}

#define SetStrCompl2(xxx) {                     \
    assert(s_opt.taskRegime);\
    if (s_opt.taskRegime == RegimeEditServer) {\
        if (xxx->kind==TypePointer || xxx->kind==TypeArray) {\
            s_structRecordCompletionType = xxx->next;\
        } else s_structRecordCompletionType = &s_errorModifier;\
    }\
}

#define AddComposedType(ddd, ttt) appendComposedType(&ddd->u.type, ttt)

#define AddHtmlTrivialReference(pos) {\
    if (s_opt.taskRegime == RegimeHtmlGenerate) {\
        addTrivialCxReference("%",TypeKeyword,StorageDefault,&pos,UsageUsed);\
    }\
}

static Symbol *l_yaccUnion = NULL;
static Symbol *l_currentType = NULL;

static void addRuleLocalVariable(S_id *name, int order);
static void addYaccSymbolReference(S_id *name, int usage);

%}

/*
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         Token definition part must be the same in all grammars
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/* ************************* SPECIALS ****************************** */
/* c+c++ */

%token TYPE_NAME

/* c++-only */
%token CLASS_NAME TEMPLATE_NAME
%token CONVERSION_OP_ID_PREFIX OPERATOR_IDENT

/* ************************* OPERATORS ****************************** */
/* common */
%token INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN

/* c-only */
%token PTR_OP ELIPSIS

/* java -only */
%token URIGHT_OP URIGHT_ASSIGN

/* yacc-only */
%token YACC_PERC YACC_DPERC

/* c++-only */
%token DPOINT POINTM_OP PTRM_OP

/* ************************** KEYWORDS ******************************** */

%token STATIC BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE
%token FLOAT FOR GOTO IF INT LONG RETURN SHORT SWITCH VOID VOLATILE WHILE

/* c-special */
%token TYPEDEF EXTERN AUTO REGISTER SIGNED UNSIGNED STRUCT UNION ENUM
%token SIZEOF RESTRICT _ATOMIC _BOOL _THREADLOCAL _NORETURN
/* hmm */
%token ANONYME_MOD

/* java-special */
%token ABSTRACT BOOLEAN BYTE CATCH CLASS EXTENDS FINAL FINALLY
%token IMPLEMENTS IMPORT INSTANCEOF INTERFACE NATIVE NEW
%token PACKAGE PRIVATE PROTECTED PUBLIC SUPER
%token SYNCHRONIZED THIS THROW THROWS TRANSIENT TRY
%token TRUE_LITERAL FALSE_LITERAL NULL_LITERAL
%token STRICTFP ASSERT

/* c++-special */
%token FRIEND OPERATOR NAMESPACE TEMPLATE DELETE MUTABLE EXPLICIT
%token WCHAR_T BOOL USING ASM_KEYWORD EXPORT VIRTUAL INLINE TYPENAME
%token DYNAMIC_CAST STATIC_CAST REINTERPRET_CAST CONST_CAST TYPEID

/* yacc-special */
%token TOKEN TYPE

/* gcc specials */
%token LABEL

/* ******************** COMPLETION SPECIAL TOKENS ******************** */

%token COMPL_FOR_SPECIAL1 COMPL_FOR_SPECIAL2
%token COMPL_THIS_PACKAGE_SPECIAL

/* c-only */
%token COMPL_TYPE_NAME
%token COMPL_STRUCT_NAME COMPL_STRUCT_REC_NAME COMPL_UP_FUN_PROFILE
%token COMPL_ENUM_NAME COMPL_LABEL_NAME COMPL_OTHER_NAME

/* java-only */
%token COMPL_CLASS_DEF_NAME COMPL_FULL_INHERITED_HEADER
%token COMPL_TYPE_NAME0
%token COMPL_TYPE_NAME1
%token COMPL_PACKAGE_NAME0 COMPL_EXPRESSION_NAME0 COMPL_METHOD_NAME0
%token COMPL_PACKAGE_NAME1 COMPL_EXPRESSION_NAME1 COMPL_METHOD_NAME1
%token COMPL_CONSTRUCTOR_NAME0 COMPL_CONSTRUCTOR_NAME1
%token COMPL_CONSTRUCTOR_NAME2 COMPL_CONSTRUCTOR_NAME3
%token COMPL_STRUCT_REC_PRIM COMPL_STRUCT_REC_SUPER COMPL_QUALIF_SUPER
%token COMPL_SUPER_CONSTRUCTOR1 COMPL_SUPER_CONSTRUCTOR2
%token COMPL_THIS_CONSTRUCTOR COMPL_IMPORT_SPECIAL
%token COMPL_VARIABLE_NAME_HINT COMPL_CONSTRUCTOR_HINT
%token COMPL_METHOD_PARAM1 COMPL_METHOD_PARAM2 COMPL_METHOD_PARAM3


/* yacc-special */
%token COMPL_YACC_LEXEM_NAME

/* ************************** CPP-TOKENS ****************************** */
/* c-only */
%token CPP_TOKENS_START
%token CPP_INCLUDE CPP_DEFINE CPP_IFDEF CPP_IFNDEF CPP_IF CPP_ELSE CPP_ENDIF
%token CPP_ELIF CPP_UNDEF
%token CPP_PRAGMA CPP_LINE
%token CPP_DEFINE0      /* macro with no argument */
%token CPP_TOKENS_END

%token CPP_COLLATION	/* ## in macro body */
%token CPP_DEFINED_OP	/* defined(xxx) in #if */

/* ******************************************************************** */
/* special token signalizing end of program */
%token EOI_TOKEN

/* ******************************************************************** */
/* special tokens used for nontrivial caching !!!! not used */
%token CACHING1_TOKEN

/* ******************************************************************** */
%token OL_MARKER_TOKEN OL_MARKER_TOKEN1 OL_MARKER_TOKEN2

/* ******************************************************************** */
%token TMP_TOKEN1 TMP_TOKEN2
%token CCC_OPER_PARENTHESIS CCC_OPER_BRACKETS

/* ************************ MULTI TOKENS START ************************ */
%token MULTI_TOKENS_START

/* commons */
%token IDENTIFIER CONSTANT LONG_CONSTANT
%token FLOAT_CONSTANT DOUBLE_CONSTANT
%token STRING_LITERAL
%token LINE_TOK
%token IDENT_TO_COMPLETE		/* identifier under cursor */

/* c-only */
%token CPP_MAC_ARG IDENT_NO_CPP_EXPAND

/* java-only */
%token CHAR_LITERAL

/* c++-only */

/* ****************************************************************** */

%token LAST_TOKEN

/* *************************************************************** */

%union {
#include "yystype.h"
}

%type <ast_id> IDENTIFIER identifier struct_identifier enum_identifier
%type <ast_id> str_rec_identifier STRUCT UNION struct_or_union
%type <ast_id> user_defined_type TYPE_NAME lexem
%type <ast_integer> pointer CONSTANT rule_body
%type <ast_unsigned> storage_class_specifier type_specifier1
%type <ast_unsigned> type_modality_specifier Sv_tmp
%type <ast_symbol> init_declarator declarator declarator2 struct_declarator
%type <ast_symbol> type_specifier_list type_mod_specifier_list
%type <ast_symbol> type_specifier_list0
%type <ast_symbol> top_init_declarations
%type <ast_symbol> declaration_specifiers init_declarations
%type <ast_symbol> declaration_modality_specifiers declaration_specifiers0
%type <ast_symbol> enumerator parameter_declaration
%type <ast_symbol> function_head_declaration function_definition_head
%type <ast_symbol> struct_declaration_list struct_declaration
%type <ast_symbol> struct_declarator_list
%type <ast_symbolList> enumerator_list enumerator_list_comma
%type <ast_symbol> fun_arg_init_declarations fun_arg_declaration
%type <ast_symbolPositionListPair> parameter_list parameter_type_list
%type <ast_symbolPositionListPair> parameter_identifier_list identifier_list
%type <ast_positionList> argument_expr_list

%type <ast_typeModifiers> type_specifier2
%type <ast_typeModifiers> struct_or_union_specifier struct_or_union_define_specifier
%type <ast_typeModifiers> enum_specifier enum_define_specifier
%type <ast_typeModifiers> type_name abstract_declarator abstract_declarator2

%type <ast_expressionType> primary_expr postfix_expr unary_expr cast_expr
%type <ast_expressionType> multiplicative_expr additive_expr shift_expr
%type <ast_expressionType> relational_expr equality_expr and_expr exclusive_or_expr
%type <ast_expressionType> inclusive_or_expr logical_and_expr logical_or_expr
%type <ast_expressionType> conditional_expr assignment_expr expr

%type <ast_position> STRING_LITERAL '(' ',' ')'

/* *************************************************************** */
/* *************************************************************** */

%start yaccfile
%%

yaccfile
    : Start_block {
            s_cache.activeCache = 0;    /* no caching in yaccgram */
            // initialize locals
            l_yaccUnion = NULL;
            l_currentType = NULL;
        }
        before_rules '%' '%' {
            placeCachePoint(1);
        }
        rules '%' '%' file
    ;

before_rules
    : before_rules_item
    | before_rules before_rules_item
    ;

before_rules_item
    :
/*
        anytoken_not_yacc

        NOTE: '$<typeModifiers>$' indicates an explict type for the symbol value,
        used here since it is in referring to embedded actions.
*/
        any_token
    |   '%' UNION {
            AddHtmlTrivialReference($2.d->p);
            $<typeModifier>$ = createNewAnonymousStructOrUnion($2.d);
        }
        '{' struct_declaration_list '}' {
            specializeStrUnionDef($<typeModifier>3->u.t, $5.d);
            l_yaccUnion = $<typeModifier>3->u.t;
        }
    |   '%' IDENTIFIER token_seq_opt    {
            AddHtmlTrivialReference($2.d->p);
        }
    |   '%' IDENTIFIER '<' IDENTIFIER '>' {
            Symbol   *res;
            int rr;
            AddHtmlTrivialReference($2.d->p);
            l_currentType = NULL;
            if (l_yaccUnion!=NULL) {
                rr = findStrRecord(l_yaccUnion, $4.d->name, &res, CLASS_TO_ANY);
                if (rr == RESULT_OK) {
                    l_currentType = res;
                }
            }
        } symbol_to_type_seq
    |   '%' '{' file '%' '}'
    |   error
    ;

symbol_to_type_seq
    :
    |   symbol_to_type_seq IDENTIFIER   {
            Symbol *ss;

            ss = newSymbol($2.d->name, $2.d->name, $2.d->p);
            fillSymbolBits(&ss->bits, ACCESS_DEFAULT, TypeDefault, StorageAuto);

            addYaccSymbolReference($2.d,UsageDeclared);
            if (l_currentType!=NULL) {
                addNewDeclaration(l_currentType, ss, NULL, StorageAuto,s_symbolTable);
            }
        }
    ;

token_seq_opt
    :
    |   token_seq
    ;

token_seq
    :   IDENTIFIER              {
            addYaccSymbolReference($1.d, UsageDeclared);
        }
    |   token_seq IDENTIFIER    {
            addYaccSymbolReference($2.d, UsageDeclared);
        }
    ;

rules
    :    Start_block IDENTIFIER ':'                          {
            addYaccSymbolReference($2.d, UsageDefined);
            addRuleLocalVariable($2.d, 0);
        }
        rule_bodies Stop_block ';'
    |   rules Start_block IDENTIFIER ':'                    {
            addYaccSymbolReference($3.d, UsageDefined);
            addRuleLocalVariable($3.d, 0);
        }
        rule_bodies Stop_block ';'
    | COMPL_YACC_LEXEM_NAME             { assert(0); /* token never used */ }
    | rules COMPL_YACC_LEXEM_NAME       { assert(0); /* token never used */ }
    ;

rule_bodies
    :   rule_body_opt
    |   rule_bodies '|' rule_body_opt
    |   error
    ;

rule_body_opt
    :
    |   Start_block rule_body Stop_block
    ;

rule_body
    : lexem                   {
            if ($1.d != NULL) {
                addYaccSymbolReference($1.d, UsageUsed);
                addRuleLocalVariable($1.d, 1);
            }
            $$.d = 2;
        }
    |   compound_statement      {
            $$.d = 2;
        }
    |   precedence              {
            $$.d = 1;
        }
    |   rule_body lexem         {
            if ($2.d != NULL) {
                addYaccSymbolReference($2.d, UsageUsed);
                addRuleLocalVariable($2.d, $1.d);
            }
            $$.d = $1.d + 1;
        }
    |   rule_body compound_statement        {
            $$.d = $1.d + 1;
        }
    |   rule_body precedence        {
            $$.d = $1.d;
        }
    ;

precedence : '%' IDENTIFIER lexem ;

lexem
    : IDENTIFIER              {
            $$.d = $1.d;
        }
    | CHAR_LITERAL            {
            $$.d = NULL;
        }
    | COMPL_YACC_LEXEM_NAME   { assert(0); /* token never used */ }
    ;

any_char_not_perc_par
    :   '!' | '"' | '#' | '$' | '&' | '\'' | '(' | ')' | '*'
    |   '+' | ',' | '-' | '.' | '/' | ':' | ';' | '<' | '=' | '>' | '?'
    |   '@' | '[' | '\\' | ']' | '^' | '`' | '|' | '~'
    ;

anytoken_not_yacc
    :   any_token_not_perc_par
    |   '{'
    |   '}'
    ;

any_token_not_perc_par
    :   any_char_not_perc_par
    |   TYPE_NAME
    |   FLOAT_CONSTANT | DOUBLE_CONSTANT
    |   IDENTIFIER | CONSTANT | LONG_CONSTANT
    |   STRING_LITERAL
    |   CHAR_LITERAL
    | INC_OP | DEC_OP | LEFT_OP | RIGHT_OP | LE_OP | GE_OP | EQ_OP | NE_OP
    | AND_OP | OR_OP | MUL_ASSIGN | DIV_ASSIGN | MOD_ASSIGN | ADD_ASSIGN
    | SUB_ASSIGN | LEFT_ASSIGN | RIGHT_ASSIGN | AND_ASSIGN
    | XOR_ASSIGN | OR_ASSIGN
    | PTR_OP | ELIPSIS
    | URIGHT_OP | URIGHT_ASSIGN
    | DPOINT | POINTM_OP | PTRM_OP
    | STATIC | BREAK | CASE | CHAR | CONST | CONTINUE | DEFAULT | DO
    | DOUBLE | ELSE | FLOAT | FOR | GOTO | IF | INT | LONG | RETURN | SHORT
    | SWITCH | VOID | VOLATILE | WHILE
    | TYPEDEF | EXTERN | AUTO | REGISTER | SIGNED | UNSIGNED | STRUCT | UNION
    | ENUM | SIZEOF
    | ANONYME_MOD | TOKEN
    | ABSTRACT | BOOLEAN | BYTE | CATCH | CLASS | EXTENDS | FINAL | FINALLY
    | IMPLEMENTS | IMPORT | INSTANCEOF | INTERFACE | NATIVE | NEW
    | PACKAGE | PRIVATE | PROTECTED | PUBLIC | SUPER
    | SYNCHRONIZED | THIS | THROW | THROWS | TRANSIENT | TRY
    | TRUE_LITERAL | FALSE_LITERAL | NULL_LITERAL
    | FRIEND | OPERATOR | NAMESPACE | TEMPLATE | DELETE | MUTABLE | EXPLICIT
    | WCHAR_T | BOOL | USING | ASM_KEYWORD | EXPORT | VIRTUAL | INLINE | TYPENAME
    | DYNAMIC_CAST | STATIC_CAST | REINTERPRET_CAST | CONST_CAST | TYPEID
    ;

any_token
    :   anytoken_not_yacc
    |   '%'
    ;


/* *************************************************************** */
/* *************************************************************** */
/*                  NOW FOLLOWS THE COMPLETE C GRAMMAR             */
/* TODO: check if this is exactly the same as c_parser.y and if so */
/* extract the common parts and include the same code to avoid dup */
/* *************************************************************** */
/* *************************************************************** */

primary_expr
    : IDENTIFIER            {
        Symbol *p;
        Symbol *dd;
        p = $1.d->sd;
        if (p != NULL && p->bits.symType == TypeDefault) {
            assert(p && p);
            dd = p;
            assert(dd->bits.storage != StorageTypedef);
            $$.d.typeModifier = dd->u.type;
            assert(s_opt.taskRegime);
            if (CX_REGIME()) {
                $$.d.reference = addCxReference(p, &$1.d->p, UsageUsed,s_noneFileIndex, s_noneFileIndex);
            }
        } else {
            /* implicit function declaration */
            TypeModifier *p;
            Symbol *d;
            Symbol *dd __attribute__((unused));

            p = newSimpleTypeModifier(TypeInt);
            $$.d.typeModifier = newFunctionTypeModifier(NULL, NULL, NULL, p);

            d = newSymbolAsType($1.d->name, $1.d->name, $1.d->p,$$.d.typeModifier);
            fillSymbolBits(&d->bits, ACCESS_DEFAULT, TypeDefault, StorageExtern);

            dd = addNewSymbolDef(d, StorageExtern, s_symbolTable, UsageUsed);
            $$.d.reference = NULL;
        }
    }
    | CHAR_LITERAL          { $$.d.typeModifier = newSimpleTypeModifier(TypeInt); $$.d.reference = NULL;}
    | CONSTANT              { $$.d.typeModifier = newSimpleTypeModifier(TypeInt); $$.d.reference = NULL;}
    | LONG_CONSTANT         { $$.d.typeModifier = newSimpleTypeModifier(TypeLong); $$.d.reference = NULL;}
    | FLOAT_CONSTANT        { $$.d.typeModifier = newSimpleTypeModifier(TypeFloat); $$.d.reference = NULL;}
    | DOUBLE_CONSTANT       { $$.d.typeModifier = newSimpleTypeModifier(TypeDouble); $$.d.reference = NULL;}
    | STRING_LITERAL        {
        TypeModifier *p;
        p = newSimpleTypeModifier(TypeChar);
        $$.d.typeModifier = newPointerTypeModifier(p);
        $$.d.reference = NULL;
    }
    | '(' expr ')'          {
        $$.d = $2.d;
    }
    | '(' compound_statement ')'            {       /* GNU's shit */
        $$.d.typeModifier = &s_errorModifier;
        $$.d.reference = NULL;
    }
    | COMPL_OTHER_NAME      { assert(0); /* token never used */ }
    ;

postfix_expr
    : primary_expr                              /*& { $$.d = $1.d; } */
    | postfix_expr '[' expr ']'                 {
        if ($1.d.typeModifier->kind==TypePointer || $1.d.typeModifier->kind==TypeArray) $$.d.typeModifier=$1.d.typeModifier->next;
        else if ($3.d.typeModifier->kind==TypePointer || $3.d.typeModifier->kind==TypeArray) $$.d.typeModifier=$3.d.typeModifier->next;
        else $$.d.typeModifier = &s_errorModifier;
        $$.d.reference = NULL;
        assert($$.d.typeModifier);
    }
    | postfix_expr '(' ')'                      {
        if ($1.d.typeModifier->kind==TypeFunction) {
            $$.d.typeModifier=$1.d.typeModifier->next;
            handleInvocationParamPositions($1.d.reference, &$2.d, NULL, &$3.d, 0);
        } else {
            $$.d.typeModifier = &s_errorModifier;
        }
        $$.d.reference = NULL;
        assert($$.d.typeModifier);
    }
    | postfix_expr '(' argument_expr_list ')'   {
        if ($1.d.typeModifier->kind==TypeFunction) {
            $$.d.typeModifier=$1.d.typeModifier->next;
            handleInvocationParamPositions($1.d.reference, &$2.d, $3.d, &$4.d, 1);
        } else {
            $$.d.typeModifier = &s_errorModifier;
        }
        $$.d.reference = NULL;
        assert($$.d.typeModifier);
    }
    | postfix_expr {SetStrCompl1($1.d.typeModifier);} '.' str_rec_identifier       {
        Symbol *rec=NULL;
        $$.d.reference = findStrRecordFromType($1.d.typeModifier, $4.d, &rec, CLASS_TO_ANY);
        assert(rec);
        $$.d.typeModifier = rec->u.type;
        assert($$.d.typeModifier);
    }
    | postfix_expr {SetStrCompl2($1.d.typeModifier);} PTR_OP str_rec_identifier    {
        Symbol *rec=NULL;

        $$.d.reference = NULL;
        if ($1.d.typeModifier->kind==TypePointer || $1.d.typeModifier->kind==TypeArray) {
            $$.d.reference = findStrRecordFromType($1.d.typeModifier->next, $4.d, &rec, CLASS_TO_ANY);
            assert(rec);
            $$.d.typeModifier = rec->u.type;
        } else $$.d.typeModifier = &s_errorModifier;
        assert($$.d.typeModifier);
    }
    | postfix_expr INC_OP                       { $$.d.typeModifier = $1.d.typeModifier; $$.d.reference = NULL;}
    | postfix_expr DEC_OP                       { $$.d.typeModifier = $1.d.typeModifier; $$.d.reference = NULL;}
    ;

str_rec_identifier
    : identifier                /*& { $$.d = $1.d; } */
    | COMPL_STRUCT_REC_NAME     { assert(0); /* token never used */ }
    ;

argument_expr_list
    : assignment_expr                           {
        $$.d = NULL;
    }
    | argument_expr_list ',' assignment_expr    {
        $$.d = $1.d;
        appendPositionToList(&$$.d, &$2.d);
    }
    ;

unary_expr
    : postfix_expr                  /*& { $$.d = $1.d; } */
    | INC_OP unary_expr             { $$.d.typeModifier = $2.d.typeModifier; $$.d.reference = NULL;}
    | DEC_OP unary_expr             { $$.d.typeModifier = $2.d.typeModifier; $$.d.reference = NULL;}
    | unary_operator cast_expr      { $$.d.typeModifier = $2.d.typeModifier; $$.d.reference = NULL;}
    | '&' cast_expr                 {
        $$.d.typeModifier = newPointerTypeModifier($2.d.typeModifier);
        RESET_REFERENCE_USAGE($2.d.reference, UsageAddrUsed);
        $$.d.reference = NULL;
    }
    | '*' cast_expr                 {
        if ($2.d.typeModifier->kind==TypePointer || $2.d.typeModifier->kind==TypeArray) $$.d.typeModifier=$2.d.typeModifier->next;
        else $$.d.typeModifier = &s_errorModifier;
        assert($$.d.typeModifier);
        $$.d.reference = NULL;
    }
    | SIZEOF unary_expr             {
        $$.d.typeModifier = newSimpleTypeModifier(TypeInt);
        $$.d.reference = NULL;
    }
    | SIZEOF '(' type_name ')'      {
        $$.d.typeModifier = newSimpleTypeModifier(TypeInt);
        $$.d.reference = NULL;
    }
    ;

unary_operator
    : '+'
    | '-'
    | '~'
    | '!'
    ;

cast_expr
    : unary_expr                        /*& { $$.d = $1.d; } */
    | '(' type_name ')' cast_expr       {
        $$.d.typeModifier = $2.d;
        $$.d.reference = $4.d.reference;
    }
    | '(' type_name ')' '{' initializer_list '}'        { /* GNU-extension*/
        $$.d.typeModifier = $2.d;
        $$.d.reference = NULL;
    }
    | '(' type_name ')' '{' initializer_list ',' '}'    { /* GNU-extension*/
        $$.d.typeModifier = $2.d;
        $$.d.reference = NULL;
    }
    ;

multiplicative_expr
    : cast_expr                         /*& { $$.d = $1.d; } */
    | multiplicative_expr '*' cast_expr {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | multiplicative_expr '/' cast_expr {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | multiplicative_expr '%' cast_expr {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

additive_expr
    : multiplicative_expr                       /*& { $$.d = $1.d; } */
    | additive_expr '+' multiplicative_expr     {
        if ($3.d.typeModifier->kind==TypePointer || $3.d.typeModifier->kind==TypeArray) $$.d.typeModifier = $3.d.typeModifier;
        else $$.d.typeModifier = $1.d.typeModifier;
        $$.d.reference = NULL;
    }
    | additive_expr '-' multiplicative_expr     {
        if ($3.d.typeModifier->kind==TypePointer || $3.d.typeModifier->kind==TypeArray) $$.d.typeModifier = $3.d.typeModifier;
        else $$.d.typeModifier = $1.d.typeModifier;
        $$.d.reference = NULL;
    }
    ;

shift_expr
    : additive_expr                             /*& { $$.d = $1.d; } */
    | shift_expr LEFT_OP additive_expr          {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | shift_expr RIGHT_OP additive_expr         {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

relational_expr
    : shift_expr                                /*& { $$.d = $1.d; } */
    | relational_expr '<' shift_expr            {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | relational_expr '>' shift_expr            {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | relational_expr LE_OP shift_expr          {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | relational_expr GE_OP shift_expr          {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

equality_expr
    : relational_expr                           /*& { $$.d = $1.d; } */
    | equality_expr EQ_OP relational_expr       {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    | equality_expr NE_OP relational_expr       {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

and_expr
    : equality_expr                             /*& { $$.d = $1.d; } */
    | and_expr '&' equality_expr                {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

exclusive_or_expr
    : and_expr                                  /*& { $$.d = $1.d; } */
    | exclusive_or_expr '^' and_expr            {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

inclusive_or_expr
    : exclusive_or_expr                         /*& { $$.d = $1.d; } */
    | inclusive_or_expr '|' exclusive_or_expr   {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

logical_and_expr
    : inclusive_or_expr                         /*& { $$.d = $1.d; } */
    | logical_and_expr AND_OP inclusive_or_expr {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

logical_or_expr
    : logical_and_expr                          /*& { $$.d = $1.d; } */
    | logical_or_expr OR_OP logical_and_expr    {
        $$.d.typeModifier = &s_defaultIntModifier;
        $$.d.reference = NULL;
    }
    ;

conditional_expr
    : logical_or_expr                                           /*& { $$.d = $1.d; } */
    | logical_or_expr '?' logical_or_expr ':' conditional_expr  {
        $$.d.typeModifier = $3.d.typeModifier;
        $$.d.reference = NULL;
    }
    ;

assignment_expr
    : conditional_expr                                  /*& { $$.d = $1.d; } */
    | unary_expr assignment_operator assignment_expr    {
        RESET_REFERENCE_USAGE($1.d.reference, UsageLvalUsed);
        $$.d.typeModifier = $1.d.typeModifier;
        $$.d.reference = NULL;
    }
    ;

assignment_operator
    : '='
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;

expr
    : assignment_expr                           /*& { $$.d = $1.d; } */
    | expr ',' assignment_expr                  {
        $$.d.typeModifier = $3.d.typeModifier;
        $$.d.reference = NULL;
    }
    ;

constant_expr
    : conditional_expr
    ;

Sv_tmp:
    {
        $$.d = tmpWorkMemoryi;
    }
    ;

declaration
    : Sv_tmp declaration_specifiers ';'     { tmpWorkMemoryi = $1.d; }
    | Sv_tmp init_declarations ';'          { tmpWorkMemoryi = $1.d; }
    | error
    ;

init_declarations
    : declaration_specifiers init_declarator            {
        $$.d = $1.d;
        addNewDeclaration($1.d, $2.d, NULL, StorageAuto,s_symbolTable);
    }
    | init_declarations ',' init_declarator             {
        $$.d = $1.d;
        addNewDeclaration($1.d, $3.d, NULL, StorageAuto,s_symbolTable);
    }
    | error                                             {
        $$.d = newSymbolAsCopyOf(s_errorSymbol);
    }
    ;

declaration_specifiers
    : declaration_modality_specifiers                       /*& { $$.d = $1.d; } */
    | declaration_specifiers0                               /*& { $$.d = $1.d; } */
    ;

user_defined_type
    : TYPE_NAME                                             {
        $$.d = $1.d;
        assert(s_opt.taskRegime);
        if (CX_REGIME()) {
            assert($1.d);
            assert($1.d->sd);
            addCxReference($1.d->sd, &$1.d->p, UsageUsed,s_noneFileIndex, s_noneFileIndex);
        }
    }
    ;

declaration_specifiers0
    : user_defined_type                                     {
        assert($1.d);
        assert($1.d->sd);
        assert($1.d->sd);
        $$.d = typeSpecifier2($1.d->sd->u.type);
    }
    | type_specifier1                                       {
        $$.d  = typeSpecifier1($1.d);
    }
    | type_specifier2                                       {
        $$.d  = typeSpecifier2($1.d);
    }
    | declaration_modality_specifiers  user_defined_type    {
        assert($2.d);
        assert($2.d->sd);
        assert($2.d->sd);
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d->sd->u.type);
    }
    | declaration_modality_specifiers type_specifier1       {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | declaration_modality_specifiers type_specifier2       {
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d);
    }
    | declaration_specifiers0 type_modality_specifier       {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | declaration_specifiers0 type_specifier1               {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | declaration_specifiers0 type_specifier2               {
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d);
    }
    | declaration_specifiers0 storage_class_specifier       {
        $$.d = $1.d;
        $$.d->bits.storage = $2.d;
    }
    | declaration_specifiers0 function_specifier			{
        $$.d = $1.d;
    }
    | COMPL_TYPE_NAME                                       {
        assert(0);
    }
    | declaration_modality_specifiers COMPL_TYPE_NAME       {
        assert(0); /* token never used */
    }
    ;

declaration_modality_specifiers
    : storage_class_specifier                               {
        $$.d  = typeSpecifier1(TypeDefault);
        $$.d->bits.storage = $1.d;
    }
    | declaration_modality_specifiers storage_class_specifier       {
        $$.d = $1.d;
        $$.d->bits.storage = $2.d;
    }
    | type_modality_specifier                               {
        $$.d  = typeSpecifier1($1.d);
    }
    | declaration_modality_specifiers type_modality_specifier       {
        declTypeSpecifier1($1.d, $2.d);
    }
    | function_specifier									{
        $$.d = typeSpecifier1(TypeDefault);
    }
    | declaration_modality_specifiers function_specifier			{
        $$.d = $1.d;
    }
    ;

init_declarator
    : declarator                    /*& { $$.d = $1.d; } */
    | declarator '=' initializer    /*& { $$.d = $1.d; } */
    ;

storage_class_specifier
    : TYPEDEF		{ $$.d = StorageTypedef; }
    | EXTERN		{ $$.d = StorageExtern; }
    | STATIC		{ $$.d = StorageStatic; }
    | _THREADLOCAL	{ $$.d = StorageThreadLocal; }
    | AUTO			{ $$.d = StorageAuto; }
    | REGISTER		{ $$.d = StorageAuto; }
    ;

type_modality_specifier
    : CONST         { $$.d = TypeDefault; }
    | RESTRICT		{ $$.d = TypeDefault; }
    | VOLATILE      { $$.d = TypeDefault; }
    | _ATOMIC		{ $$.d = TypeDefault; }
    | ANONYME_MOD   { $$.d = TypeDefault; }
    ;

type_specifier1
    : CHAR      { $$.d = TypeChar; }
    | SHORT     { $$.d = TmodShort; }
    | INT       { $$.d = TypeInt; }
    | LONG      { $$.d = TmodLong; }
    | SIGNED    { $$.d = TmodSigned; }
    | UNSIGNED  { $$.d = TmodUnsigned; }
    | FLOAT     { $$.d = TypeFloat; }
    | DOUBLE    { $$.d = TypeDouble; }
    | VOID      { $$.d = TypeVoid; }
    | _BOOL		{ $$.d = TypeBoolean; }
    ;

type_specifier2
    : struct_or_union_specifier     /*& { $$.d = $1.d; } */
    | enum_specifier                /*& { $$.d = $1.d; } */
    ;

function_specifier
    : INLINE
    | _NORETURN
    ;

struct_or_union_specifier
    : struct_or_union struct_identifier                             {
        $$.d = simpleStrUnionSpecifier($1.d, $2.d, UsageUsed);
    }
    | struct_or_union_define_specifier '{' struct_declaration_list '}'{
        assert($1.d && $1.d->u.t);
        $$.d = $1.d;
        specializeStrUnionDef($$.d->u.t, $3.d);
    }
    ;

struct_or_union_define_specifier
    : struct_or_union struct_identifier                             {
        $$.d = simpleStrUnionSpecifier($1.d, $2.d, UsageDefined);
    }
    | struct_or_union                                               {
        $$.d = createNewAnonymousStructOrUnion($1.d);
    }
    ;

struct_identifier
    : identifier            /*& { $$.d = $1.d; } */
    | COMPL_STRUCT_NAME     { assert(0); /* token never used */ }
    ;

struct_or_union
    : STRUCT        { $$.d = $1.d; }
    | UNION         { $$.d = $1.d; }
    ;

struct_declaration_list
    : struct_declaration                                /*& { $$.d = $1.d; } */
    | struct_declaration_list struct_declaration        {
        if ($1.d == &s_errorSymbol || $1.d->bits.symType==TypeError) {
            $$.d = $2.d;
        } else if ($2.d == &s_errorSymbol || $1.d->bits.symType==TypeError) {
            $$.d = $1.d;
        } else {
            $$.d = $1.d;
            LIST_APPEND(Symbol, $$.d, $2.d);
        }
    }
    ;

struct_declaration
    : Sv_tmp type_specifier_list struct_declarator_list ';'     {
        Symbol *p;
        assert($2.d && $3.d);
        for(p=$3.d; p!=NULL; p=p->next) {
            completeDeclarator($2.d, p);
        }
        $$.d = $3.d;
        tmpWorkMemoryi = $1.d;
    }
    | error                                             {
        $$.d = newSymbolAsCopyOf(s_errorSymbol);
    }
    ;

struct_declarator_list
    : struct_declarator                                 {
        $$.d = $1.d;
        assert($$.d->next == NULL);
    }
    | struct_declarator_list ',' struct_declarator      {
        $$.d = $1.d;
        assert($3.d->next == NULL);
        LIST_APPEND(Symbol, $$.d, $3.d);
    }
    ;

struct_declarator
    : declarator                    /*& { $$.d = $1.d; } */
    | ':' constant_expr             {
        TypeModifier *p;
        p = newSimpleTypeModifier(TypeAnonymousField);
        $$.d = newSymbolAsType(NULL, NULL, s_noPos, p);

    }
    | declarator ':' constant_expr  /*& { $$.d = $1.d; } */
    ;

enum_specifier
    : ENUM enum_identifier                                  {
        $$.d = simpleEnumSpecifier($2.d, UsageUsed);
    }
    | enum_define_specifier '{' enumerator_list_comma '}'       {
        assert($1.d && $1.d->kind == TypeEnum && $1.d->u.t);
        $$.d = $1.d;
        if ($$.d->u.t->u.enums==NULL) {
            $$.d->u.t->u.enums = $3.d;
            addToTrail(setToNull, & ($$.d->u.t->u.enums) );
        }
    }
    | ENUM '{' enumerator_list_comma '}'                        {
        $$.d = createNewAnonymousEnum($3.d);
    }
    ;

enum_define_specifier
    : ENUM enum_identifier                                  {
        $$.d = simpleEnumSpecifier($2.d, UsageDefined);
    }
    ;

enum_identifier
    : identifier            /*& { $$.d = $1.d; } */
    | COMPL_ENUM_NAME       { assert(0); /* token never used */ }
    ;

enumerator_list_comma
    : enumerator_list               /*& { $$.d = $1.d; } */
    | enumerator_list ','           /*& { $$.d = $1.d; } */
    ;

enumerator_list
    : enumerator                            {
        $$.d = createDefinitionList($1.d);
    }
    | enumerator_list ',' enumerator        {
        $$.d = $1.d;
        LIST_APPEND(SymbolList, $$.d, createDefinitionList($3.d));
    }
    ;

enumerator
    : identifier                            {
        $$.d = createSimpleDefinition(StorageConstant,TypeInt,$1.d);
        addNewSymbolDef($$.d,StorageConstant, s_symbolTable, UsageDefined);
    }
    | identifier '=' constant_expr          {
        $$.d = createSimpleDefinition(StorageConstant,TypeInt,$1.d);
        addNewSymbolDef($$.d,StorageConstant, s_symbolTable, UsageDefined);
    }
    | error                                 {
        $$.d = newSymbolAsCopyOf(s_errorSymbol);
    }
    | COMPL_OTHER_NAME      { assert(0); /* token never used */ }
    ;

declarator
    : declarator2                                       /*& { $$.d = $1.d; } */
    | pointer declarator2                               {
        int i;
        $$.d = $2.d;
        for (i=0; i<$1.d; i++) AddComposedType($$.d,TypePointer);
    }
    ;

declarator2
    : IDENTIFIER                                        {
        $$.d = newSymbol($1.d->name, $1.d->name, $1.d->p);
    }
    | '(' declarator ')'                                {
        $$.d = $2.d;
    }
    | declarator2 '[' ']'                               {
        assert($1.d);
        $$.d = $1.d;
        AddComposedType($$.d, TypeArray);
    }
    | declarator2 '[' constant_expr ']'                 {
        assert($1.d);
        $$.d = $1.d;
        AddComposedType($$.d, TypeArray);
    }
    | declarator2 '(' ')'                               {
        TypeModifier *p;
        assert($1.d);
        $$.d = $1.d;
        p = AddComposedType($$.d, TypeFunction);
        initFunctionTypeModifier(&p->u.f , NULL);
    }
    | declarator2 '(' parameter_type_list ')'           {
        TypeModifier *p;
        assert($1.d);
        $$.d = $1.d;
        p = AddComposedType($$.d, TypeFunction);
        initFunctionTypeModifier(&p->u.f , $3.d.s);
        handleDeclaratorParamPositions($1.d, &$2.d, $3.d.p, &$4.d, 1);
    }
    | declarator2 '(' parameter_identifier_list ')'     {
        TypeModifier *p;
        assert($1.d);
        $$.d = $1.d;
        p = AddComposedType($$.d, TypeFunction);
        initFunctionTypeModifier(&p->u.f , $3.d.s);
        handleDeclaratorParamPositions($1.d, &$2.d, $3.d.p, &$4.d, 1);
    }
    | COMPL_OTHER_NAME      { assert(0); /* token never used */ }
    ;

pointer
    : '*'                                   {
        $$.d = 1;
    }
    | '*' type_mod_specifier_list               {
        $$.d = 1;
    }
    | '*' pointer                           {
        $$.d = $2.d+1;
    }
    | '*' type_mod_specifier_list pointer       {
        $$.d = $3.d+1;
    }
    ;

type_mod_specifier_list
    : type_modality_specifier                                   {
        $$.d  = typeSpecifier1($1.d);
    }
    | type_mod_specifier_list type_modality_specifier           {
        declTypeSpecifier1($1.d, $2.d);
    }
    ;

/*
type_specifier_list
    : type_specifier1                                   {
        $$.d  = typeSpecifier1($1.d);
    }
    | type_specifier2                                   {
        $$.d  = typeSpecifier2($1.d);
    }
    | type_specifier_list type_specifier1               {
        declTypeSpecifier1($1.d, $2.d);
    }
    | type_specifier_list type_specifier2               {
        declTypeSpecifier2($1.d, $2.d);
    }
    ;
*/

type_specifier_list
    : type_mod_specifier_list                       /*& { $$.d = $1.d; } */
    | type_specifier_list0                          /*& { $$.d = $1.d; } */
    ;

type_specifier_list0
    : user_defined_type                                     {
        assert($1.d);
        assert($1.d->sd);
        assert($1.d->sd);
        $$.d = typeSpecifier2($1.d->sd->u.type);
    }
    | type_specifier1                                       {
        $$.d  = typeSpecifier1($1.d);
    }
    | type_specifier2                                       {
        $$.d  = typeSpecifier2($1.d);
    }
    | type_mod_specifier_list user_defined_type             {
        assert($2.d);
        assert($2.d->sd);
        assert($2.d->sd);
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d->sd->u.type);
    }
    | type_mod_specifier_list type_specifier1       {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | type_mod_specifier_list type_specifier2       {
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d);
    }
    | type_specifier_list0 type_modality_specifier      {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | type_specifier_list0 type_specifier1              {
        $$.d = $1.d;
        declTypeSpecifier1($1.d,$2.d);
    }
    | type_specifier_list0 type_specifier2              {
        $$.d = $1.d;
        declTypeSpecifier2($1.d,$2.d);
    }
    | COMPL_TYPE_NAME                                       {
        assert(0);
    }
    | type_mod_specifier_list COMPL_TYPE_NAME       {
        assert(0); /* token never used */
    }
    ;

parameter_identifier_list
    : identifier_list                           /*& { $$.d = $1.d; } */
    | identifier_list ',' ELIPSIS               {
        Symbol *p;
        Position pp;
        fillPosition(&pp, -1, 0, 0);

        p = newSymbol("", "", pp);
        fillSymbolBits(&p->bits, ACCESS_DEFAULT, TypeElipsis, StorageDefault);

        $$.d = $1.d;

        LIST_APPEND(Symbol, $$.d.s, p);
        appendPositionToList(&$$.d.p, &$2.d);
    }
    ;

identifier_list
    : IDENTIFIER                                {
        Symbol *p;

        p = newSymbol($1.d->name, $1.d->name, $1.d->p);

        $$.d.s = p;
        $$.d.p = NULL;
    }
    | identifier_list ',' identifier            {
        Symbol        *p;

        p = newSymbol($3.d->name, $3.d->name, $3.d->p);

        $$.d = $1.d;

        LIST_APPEND(Symbol, $$.d.s, p);
        appendPositionToList(&$$.d.p, &$2.d);
    }
    | COMPL_OTHER_NAME      { assert(0); /* token never used */ }
    ;

parameter_type_list
    : parameter_list                    /*& { $$.d = $1.d; } */
    | parameter_list ',' ELIPSIS                {
        Symbol        *p;
        Position      pp;
        fillPosition(&pp, -1, 0, 0);

        p = newSymbol("", "", pp);
        fillSymbolBits(&p->bits, ACCESS_DEFAULT, TypeElipsis, StorageDefault);

        $$.d = $1.d;
        LIST_APPEND(Symbol, $$.d.s, p);
        appendPositionToList(&$$.d.p, &$2.d);
    }
    ;

parameter_list
    : parameter_declaration                         {
        $$.d.s = $1.d;
        $$.d.p = NULL;
    }
    | parameter_list ',' parameter_declaration      {
        $$.d = $1.d;
        LIST_APPEND(Symbol, $1.d.s, $3.d);
        appendPositionToList(&$$.d.p, &$2.d);
    }
    ;

parameter_declaration
    : declaration_specifiers declarator         {
        completeDeclarator($1.d, $2.d);
        $$.d = $2.d;
    }
    | type_name                                 {
        $$.d = newSymbolAsType(NULL, NULL, s_noPos, $1.d);
    }
    | error                                     {
        $$.d = newSymbolAsCopyOf(s_errorSymbol);
    }
    ;

type_name
    : declaration_specifiers                        {
        $$.d = $1.d->u.type;
    }
    | declaration_specifiers abstract_declarator    {
        $$.d = $2.d;
        LIST_APPEND(TypeModifier, $$.d, $1.d->u.type);
    }
    ;

abstract_declarator
    : pointer                               {
        int i;
        $$.d = newPointerTypeModifier(NULL);
        for(i=1; i<$1.d; i++) appendComposedType(&($$.d), TypePointer);
    }
    | abstract_declarator2                  {
        $$.d = $1.d;
    }
    | pointer abstract_declarator2          {
        int i;
        $$.d = $2.d;
        for(i=0; i<$1.d; i++) appendComposedType(&($$.d), TypePointer);
    }
    ;

abstract_declarator2
    : '(' abstract_declarator ')'           {
        $$.d = $2.d;
    }
    | '[' ']'                               {
        $$.d = newArrayTypeModifier();
    }
    | '[' constant_expr ']'                 {
        $$.d = newArrayTypeModifier();
    }
    | abstract_declarator2 '[' ']'          {
        $$.d = $1.d;
        appendComposedType(&($$.d), TypeArray);
    }
    | abstract_declarator2 '[' constant_expr ']'    {
        $$.d = $1.d;
        appendComposedType(&($$.d), TypeArray);
    }
    | '(' ')'                                       {
        $$.d = newFunctionTypeModifier(NULL, NULL, NULL, NULL);
        initFunctionTypeModifier(&$$.d->u.f , NULL);
    }
    | '(' parameter_type_list ')'                   {
        $$.d = newFunctionTypeModifier(NULL, NULL, NULL, NULL);
        initFunctionTypeModifier(&$$.d->u.f , $2.d.s);
    }
    | abstract_declarator2 '(' ')'                  {
        TypeModifier *p;
        $$.d = $1.d;
        p = appendComposedType(&($$.d), TypeFunction);
        initFunctionTypeModifier(&p->u.f , NULL);
    }
    | abstract_declarator2 '(' parameter_type_list ')'          {
        TypeModifier *p;
        $$.d = $1.d;
        p = appendComposedType(&($$.d), TypeFunction);
        // why there was the following ?????
        // initFunctionTypeModifier(&p->u.f , NULL);
        initFunctionTypeModifier(&p->u.f , $3.d.s);
    }
    ;

initializer
    : assignment_expr
    | '{' Start_block initializer_list Stop_block '}'
    | '{' Start_block initializer_list ',' Stop_block '}'
    ;

initializer_list
    : Sv_tmp initializer    {
        tmpWorkMemoryi = $1.d;
    }
    | initializer_list ',' Sv_tmp initializer   {
        tmpWorkMemoryi = $3.d;
    }
    | error
    ;

statement
    : Sv_tmp labeled_statement      {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp compound_statement     {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp expression_statement       {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp selection_statement        {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp iteration_statement        {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp jump_statement     {
        tmpWorkMemoryi = $1.d;
    }
    | error
    ;

labeled_statement
    : label_def_name ':' statement
    | CASE constant_expr ':' statement
    | CASE constant_expr ELIPSIS constant_expr ':' statement
    | DEFAULT ':' statement
    ;

label_def_name
    : identifier            {
        labelReference($1.d,UsageDefined);
    }
    | COMPL_LABEL_NAME      { assert(0); /* token never used */ }
    ;

label_name
    : identifier            {
        labelReference($1.d,UsageUsed);
    }
    | COMPL_LABEL_NAME      { assert(0); /* token never used */ }
    ;

compound_statement
    : '{' '}'
    | '{' Start_block statement_list Stop_block '}'
    | '{' Start_block declaration_list Stop_block '}'
    | '{' Start_block declaration_list statement_list Stop_block '}'
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

statement_list
    : statement
    | statement_list statement
/*
    | declaration
    | statement_list declaration
*/
    ;

maybe_expr
    :
    | expr
    ;

expression_statement
    : maybe_expr ';'
    ;

selection_statement
    : IF '(' expr ')' statement
    | IF '(' expr ')' statement ELSE statement
    | SWITCH '(' expr ')' statement
    ;

iteration_statement
    : WHILE '(' expr ')' statement
    | DO statement WHILE '(' expr ')' ';'
    | FOR '(' maybe_expr ';' maybe_expr ';' maybe_expr ')' statement
    ;

jump_statement
    : GOTO label_name ';'
    | CONTINUE ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN expr ';'
    ;

file
    : cached_external_definition_list
    |
    | cached_external_definition_list EOI_TOKEN
        Start_block statement_list Stop_block
    | EOI_TOKEN Start_block statement_list Stop_block
    ;

cached_external_definition_list
    : external_definition       {
        /* poseCachePoint(1); no caching in yacc files */
    }
    | cached_external_definition_list external_definition {
        /* poseCachePoint(1); no caching in yacc files */
    }
    ;

external_definition
    : Sv_tmp declaration_specifiers ';'     {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp top_init_declarations ';'      {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp function_definition_head {
        Symbol *p,*pa;
        int i;
        assert($2.d);
        //&if ($2.d->bits.storage == StorageDefault) $2.d->bits.storage = StorageExtern;
        addNewSymbolDef($2.d, StorageExtern, s_symbolTable, UsageDefined);
        tmpWorkMemoryi = $1.d;
        stackMemoryBlockStart();
        assert($2.d->u.type && $2.d->u.type->kind == TypeFunction);
        s_cp.function = $2.d;
        for(p=$2.d->u.type->u.f.args,i=1; p!=NULL; p=p->next,i++) {
            if (p->bits.symType == TypeElipsis) continue;
            if (p->u.type == NULL) p->u.type = &s_defaultIntModifier;
            if (p->name != NULL) {
                XX_ALLOC(pa,Symbol);
                *pa = *p;
                addNewSymbolDef(pa, StorageAuto, s_symbolTable, UsageDefined);
            }
            if (s_opt.server_operation == OLO_GOTO_PARAM_NAME
                && i == s_opt.olcxGotoVal
                && POSITION_EQ($2.d->pos, s_cxRefPos)) {
                s_paramPosition = p->pos;
            }

        }
    } compound_statement {
        stackMemoryBlockFree();
        s_cp.function = NULL;
    }
    | Sv_tmp EXTERN STRING_LITERAL  external_definition {
        tmpWorkMemoryi = $1.d;
    }
    | Sv_tmp EXTERN STRING_LITERAL  '{' cached_external_definition_list '}' {
        tmpWorkMemoryi = $1.d;
    }
    | error compound_statement
    | error ';'
    ;

top_init_declarations
    : declaration_specifiers init_declarator            {
        $$.d = $1.d;
        addNewDeclaration($1.d, $2.d, NULL, StorageExtern,s_symbolTable);
    }
    | init_declarator                                   {
        $$.d = & s_defaultIntDefinition;
        addNewDeclaration($$.d, $1.d, NULL, StorageExtern,s_symbolTable);
    }
    | top_init_declarations ',' init_declarator         {
        $$.d = $1.d;
        addNewDeclaration($1.d, $3.d, NULL, StorageExtern,s_symbolTable);
    }
    | error                                             {
        $$.d = newSymbolAsCopyOf(s_errorSymbol);
    }
    ;

function_definition_head
    : function_head_declaration                         /*& { $$.d = $1.d; } */
    | function_definition_head fun_arg_declaration      {
        int r;
        assert($1.d->u.type && $1.d->u.type->kind == TypeFunction);
        r = mergeArguments($1.d->u.type->u.f.args, $2.d);
        if (r == RESULT_ERR) YYERROR;
        $$.d = $1.d;
    }
    ;

fun_arg_declaration
    : declaration_specifiers ';'                                {
        $$.d = NULL;
    }
    | declaration_specifiers fun_arg_init_declarations ';'      {
        Symbol *p;
        assert($1.d && $2.d);
        for(p=$2.d; p!=NULL; p=p->next) {
            completeDeclarator($1.d, p);
        }
        $$.d = $2.d;
    }
    ;

fun_arg_init_declarations
    : init_declarator           {
        $$.d = $1.d;
    }
    | fun_arg_init_declarations ',' init_declarator             {
        $$.d = $1.d;
        LIST_APPEND(Symbol, $$.d, $3.d);
    }
    | fun_arg_init_declarations ',' error                       {
        $$.d = $1.d;
    }
    ;

function_head_declaration
    : declarator                            {
        completeDeclarator(&s_defaultIntDefinition, $1.d);
        assert($1.d && $1.d->u.type);
        if ($1.d->u.type->kind != TypeFunction) YYERROR;
        $$.d = $1.d;
    }
    | declaration_specifiers declarator     {
        completeDeclarator($1.d, $2.d);
        assert($2.d && $2.d->u.type);
        if ($2.d->u.type->kind != TypeFunction) YYERROR;
        $$.d = $2.d;
    }
    ;


Start_block:    { stackMemoryBlockStart(); }
    ;

Stop_block:     { stackMemoryBlockFree(); }
    ;

identifier
    : IDENTIFIER    /*& { $$.d = $1.d; } */
    | TYPE_NAME     /*& { $$.d = $1.d; } */
    ;

%%

static void addYaccSymbolReference(S_id *name, int usage) {
    Symbol sss;

    fillSymbol(&sss, name->name, name->name, name->p);
    fillSymbolBits(&sss.bits, ACCESS_DEFAULT, TypeYaccSymbol, StorageNone);
    addCxReference(&sss, &name->p, usage,s_noneFileIndex, s_noneFileIndex);
}

static void addRuleLocalVariable(S_id *name, int order) {
    Symbol *p,*ss;
    char	*nn;

    if (l_yaccUnion!=NULL) {
        p = name->sd;
        if (p != NULL && p->bits.symType == TypeDefault) {
            nn = stackMemoryAlloc(10*sizeof(char));
            assert(order>=0 && order < 10000);
            sprintf(nn,"$%d",order);
            if (order == 0) nn[1] = '$';

            ss = newSymbol(nn, nn, name->p);
            fillSymbolBits(&ss->bits, ACCESS_DEFAULT, TypeDefault, StorageAuto);

            ss->pos.col ++ ; // to avoid ambiguity of NonTerminal <-> $$.d
            addNewDeclaration(p, ss, NULL, StorageAuto, s_symbolTable);
        }
    }
}

static S_completionFunTab completionsTab[]  = {
    {COMPL_TYPE_NAME,		completeTypes},
    {COMPL_STRUCT_NAME,		completeStructs},
    {COMPL_STRUCT_REC_NAME,	completeRecNames},
    {COMPL_ENUM_NAME,		completeEnums},
    {COMPL_LABEL_NAME,		completeLabels},
    {COMPL_OTHER_NAME,		completeOthers},
    {COMPL_YACC_LEXEM_NAME,	completeYaccLexem},
    {0,NULL}
};


static bool exists_valid_parser_action_on(int token) {
    int yyn1, yyn2;
    bool shift_action = (yyn1 = yysindex[lastyystate]) && (yyn1 += token) >= 0 &&
        yyn1 <= YYTABLESIZE && yycheck[yyn1] == token;
    bool reduce_action = (yyn2 = yyrindex[lastyystate]) && (yyn2 += token) >= 0 &&
        yyn2 <= YYTABLESIZE && yycheck[yyn2] == token;
    bool valid = shift_action || reduce_action;

    return valid;
}

/* These are similar in the three parsers, except that we have macro
   replacement of YACC variables so that we can have multiple parsers
   linked together. Therefore it is not straight forward to refactor
   out commonalities. */
void makeYaccCompletions(char *s, int len, Position *pos) {
    int token, i;
    CompletionLine compLine;

    log_trace("completing \"%s\"", s);
    strncpy(s_completions.idToProcess, s, MAX_FUN_NAME_SIZE);
    s_completions.idToProcess[MAX_FUN_NAME_SIZE-1] = 0;
    initCompletions(&s_completions, len, *pos);

    for (i=0; (token=completionsTab[i].token) != 0; i++) {
        log_trace("trying token %d", s_tokenName[token]);
        if (exists_valid_parser_action_on(token)) {
            log_trace("completing %d==%s in state %d", i, s_tokenName[token], lastyystate);
            (*completionsTab[i].fun)(&s_completions);
            if (s_completions.abortFurtherCompletions)
                return;
        }
    }

    /* basic language tokens */
    for (token=0; token<LAST_TOKEN; token++) {
        if (token == IDENTIFIER)
            continue;
        if (exists_valid_parser_action_on(token)) {
                if (s_tokenName[token] != NULL) {
                    if (isalpha(*s_tokenName[token]) || *s_tokenName[token]=='_') {
                        fillCompletionLine(&compLine, s_tokenName[token], NULL, TypeKeyword, 0, 0, NULL, NULL);
                    } else {
                        fillCompletionLine(&compLine, s_tokenName[token], NULL, TypeToken, 0, 0, NULL, NULL);
                    }
                    log_trace("completing %d==%s(%s) in state %d", token, s_tokenName[token], s_tokenName[token], lastyystate);
                    processName(s_tokenName[token], &compLine, 0, &s_completions);
                }
        }
    }
}
