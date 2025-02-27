#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED

#include "stdinc.h"
#include <stdbool.h>

#include "zlib.h"

#include "head.h"


typedef unsigned char uchar;

/* ***********************************************************************

   Here follows some enums which were split off a gigantic enum
   Miscellaneus (Duh!). In order to ensure they all have different
   values they are started with a value higher than the last value in
   the previous.

*/

typedef enum addYesNo {
    ADD_DEFAULT = 0,
    ADD_YES,
    ADD_NO
} AddYesNo;

typedef enum accessibilityCheckYesNo {
    ACCESSIBILITY_CHECK_DEFAULT = ADD_NO+1,
    ACCESSIBILITY_CHECK_YES,
    ACCESSIBILITY_CHECK_NO
} AccessibilityCheckYesNo;

typedef enum visibilityCheckYesNo {
    VISIBILITY_CHECK_DEFAULT = ACCESSIBILITY_CHECK_NO+1,
    VISIBILITY_CHECK_YES,
    VISIBILITY_CHECK_NO
} VisibilityCheckYesNo;

typedef enum longjmpReason {
    LONGJMP_REASON_NONE = VISIBILITY_CHECK_NO+1,
    LONGJUMP_REASON_REFERENCE_OVERFLOW,
    LONGJMP_REASON_FILE_ABORT
} LongjmpReason;

typedef enum extractCategory {
    EXTRACT_LOCAL_VAR = LONGJMP_REASON_FILE_ABORT+1,
    EXTRACT_VALUE_ARGUMENT,
    EXTRACT_LOCAL_OUT_ARGUMENT,
    EXTRACT_OUT_ARGUMENT,
    EXTRACT_IN_OUT_ARGUMENT,
    EXTRACT_ADDRESS_ARGUMENT,
    EXTRACT_RESULT_VALUE,
    EXTRACT_IN_RESULT_VALUE,
    EXTRACT_LOCAL_RESULT_VALUE,
    EXTRACT_NONE,
    EXTRACT_ERROR
} ExtractCategory;

typedef enum pushPullDirection {
    PULLING_UP = EXTRACT_ERROR+1,
    PUSHING_DOWN
} PushPullDirection;

typedef enum loadSuperOrNot {
    LOAD_SUPER = PUSHING_DOWN+1,
    DO_NOT_LOAD_SUPER
} LoadSuperOrNot;

enum miscellaneous {						/* misc. constants */
    DEFAULT_VALUE,
    CLASS_TO_TYPE,
    CLASS_TO_EXPR,
    CLASS_TO_METHOD,
    CLASS_TO_ANY,
    CX_FILE_ITEM_GEN,
    NO_CX_FILE_ITEM_GEN,
    CX_GENERATE_OUTPUT,
    CX_JUST_READ,
    CX_FIRST_PASS,
    CX_SECOND_PASS,
    CX_MENU_CREATION,
    CX_BY_PASS,
    MEM_ALLOC_ON_SM,
    MEM_ALLOC_ON_PP,
    MEM_NO_ALLOC,
    INFILES_ENABLED,
    INFILES_DISABLED,
    LOADING_SYMBOL,
    SEARCH_SYMBOL,
    FF_SCHEDULED_TO_PROCESS,
    FF_COMMAND_LINE_ENTERED,
    OL_LOOKING_2_PASS_MACRO_USAGE,
    SHORT_NAME,
    LONG_NAME,
    GEN_JAVA_DOC,
    ONLINE_ONLY,
    ALL_REFS,
    COUNT_ONLY,
    CUT_OUTERS,
    NO_OUTERS_CUT,
    VIRT_ITEM,
    SINGLE_VIRT_ITEM,
    FIRST_PASS,
    SECOND_PASS,
    DO_NOT_CHECK_IF_SELECTED,
    PUSH_AFTER_MENU,
    CHECK_NULL,
    TRAILED_YES,
    TRAILED_NO,
    CPOS_FUNCTION_INNER,
    CPOS_ST,
    DIRECT_ONLY,
    SUPERCLASS_NESTED_TOO,
    DIFF_MISSING_REF,
    DIFF_UNEXPECTED_REF,
    CONSTRUCTOR_INVOCATION,
    REGULAR_METHOD,
    SUPER_METHOD_INVOCATION,
    RESOLVE_DIALOG_ALLWAYS,
    RESOLVE_DIALOG_NEVER,
    GLOBAL_ENV_ONLY,
    NO_ERROR_MESSAGE,
    ADD_CX_REFS,
    NO_CX_REFS,
    ORDER_PREPEND,
    ORDER_APPEND,
    MEMBER_CLASS,
    MEMBER_TYPE,
    GEN_VIRTUALS,
    GEN_NON_VIRTUALS,
    REQ_FIELD,
    REQ_METHOD,
    REQ_STATIC,
    REQ_NONSTATIC,
    REQ_SUPERCLASS,
    REQ_SUBCLASS,
    REQ_CLASS,
    REQ_PACKAGE,
    INSPECT_DEF,
    INSPECT_CLASS,
    DOTIFY_NAME,
    KEEP_SLASHES,
    ADD_MAYBE_THIS_REFERENCE,
    TSS_FULL_SEARCH,
    TSS_SEARCH_DEFS_ONLY,
    TSS_FULL_SEARCH_SHORT,
    TSS_SEARCH_DEFS_ONLY_SHORT,
    GEN_FULL_OUTPUT,
    GEN_PRECHECKS,
    GEN_NO_OUTPUT,
    CHECK_FOR_ADD_PARAM,
    CHECK_FOR_DEL_PARAM,
    GET_PRIMARY_START,
    GET_STATIC_PREFIX_START,
    APPLY_CHECKS,
    NO_CHECKS,
    CONTINUATION_ENABLED,
    CONTINUATION_DISABLED,
    NO_OVERWRITE_CHECK,
    CHECK_OVERWRITE,
    ALLOW_EDITOR_FILES,
    DO_NOT_ALLOW_EDITOR_FILES,
    DEPTH_ONE,
    DEPTH_ANY,
    DEAD_CODE_DETECTION,
    INTERACTIVE_YES,
    INTERACTIVE_NO,
    MARKER_IS_IN_CODE,
    MARKER_IS_IN_SLASH_COMMENT,
    MARKER_IS_IN_STAR_COMMENT,
    PROFILE_NOT_APPLICABLE,
    PROFILE_APPLICABLE,
    PROFILE_PARTIALLY_APPLICABLE,
    USELESS_FQT_REFS_ALLOWED,
    USELESS_FQT_REFS_DISALLOWED,
};

/* *******************      encodings      *************** */

enum fileEncodings {
    MULE_DEFAULT,				// in fact utf-8 or utf-16
    MULE_EUROPEAN,				// byte per char
    MULE_EUC,					// euc
    MULE_SJIS,					// Shift-JIS
    MULE_UTF,					// utf-8 or utf-16
    MULE_UTF_8,					// utf-8
    MULE_UTF_16,				// utf-16
    MULE_UTF_16LE,				// utf-16 little endian
    MULE_UTF_16BE,				// utf-16 big endian
};

/* *******************      comment moving levels for refactoring      *************** */

enum commentMovement {
    CM_NO_COMMENT,
    CM_SINGLE_SLASHED,
    CM_SINGLE_STARED,
    CM_SINGLE_SLASHED_AND_STARED,
    CM_ALL_SLASHED,
    CM_ALL_STARED,
    CM_ALL_SLASHED_AND_STARED,
};

/* *******************      generating imports defaults      *************** */

// do to touch this! order is used, with arithmetics!
enum addImportsDefault {
    NID_IMPORT_ON_DEMAND,
    NID_SINGLE_TYPE_IMPORT,
    NID_KEPP_FQT_NAME,
};

/* *******************      refactoring continuations      *************** */

enum {
    RC_NONE,				// do not continue, keep interactive
    RC_CONTINUE,			// continue, no special info
    RC_IMPORT_SINGLE_TYPE,
    RC_IMPORT_ON_DEMAND,
};

/* *******************      error messages type      *************** */

enum {
  ERR_ST,				/* standard, no pre-prepared message*/
  ERR_CANT_OPEN,
  ERR_CANT_OPEN_FOR_READ,
  ERR_CANT_OPEN_FOR_WRITE,
  ERR_NO_MEMORY,
  ERR_INTERNAL,
  ERR_INTERNAL_CHECK,
  ERR_CFG,
};


/* ************************** refactorings **************************** */

enum memoryClass {
    MEMORY_CF,
    MEMORY_XX,
    MEMORY_PP,
};

typedef enum referenceCategory {
    CategoryGlobal,
    CategoryLocal,
    MAX_CATEGORIES
} ReferenceCategory;

typedef enum referenceScope {
    ScopeDefault,
    ScopeGlobal,
    ScopeFile,
    ScopeAuto,
    MAX_SCOPES
} ReferenceScope;

#define SCOPES_LN 3


enum menuFilterLevels {
    FilterAllOfSameName,
    FilterSameProfile,
    FilterSameProfileRelatedClass,
//&	FilterVirtualAdequate,
//&	FilterVirtualSameAppl,
    MAX_MENU_FILTER_LEVEL,
};

enum refsFilterLevels {
    RFilterAll,
    RFilterAddrVal,			// also toplevel usage
    RFilterLVal,			// also extend usage
    RFilterDefinitions,
    MAX_REF_LIST_FILTER_LEVEL,
};

#include "storage.h"
#include "type.h"

enum javaPCTIndex {		/* java Primitive Conversion Table Indexes */
    PCTIndexError=0,
    PCTIndexByte,
    PCTIndexShort,
    PCTIndexChar,
    PCTIndexInt,
    PCTIndexLong,
    PCTIndexFloat,
    PCTIndexDouble,
    MAX_PCTIndex
};

enum sFunResult {
    RESULT_OK,
    RESULT_ERR
};

typedef enum inputType {
    INPUT_NORMAL,
    INPUT_MACRO,
    INPUT_MACRO_ARGUMENT,
    INPUT_CACHE,
} InputType;

enum syntaxPassParsedImportantPosition {
    SPP_LAST_TOP_LEVEL_CLASS_POSITION,
    SPP_ASSIGNMENT_OPERATOR_POSITION,
    SPP_ASSIGNMENT_END_POSITION,
    SPP_CLASS_DECLARATION_BEGIN_POSITION,
    SPP_CLASS_DECLARATION_END_POSITION,
    SPP_CLASS_DECLARATION_TYPE_BEGIN_POSITION,
    SPP_CLASS_DECLARATION_TYPE_END_POSITION,
    SPP_METHOD_DECLARATION_BEGIN_POSITION,
    SPP_METHOD_DECLARATION_END_POSITION,
    SPP_METHOD_DECLARATION_TYPE_BEGIN_POSITION,
    SPP_METHOD_DECLARATION_TYPE_END_POSITION,
    SPP_FIELD_DECLARATION_BEGIN_POSITION,
    SPP_FIELD_DECLARATION_END_POSITION,
    SPP_FIELD_DECLARATION_TYPE_BEGIN_POSITION,
    SPP_FIELD_DECLARATION_TYPE_END_POSITION,
    SPP_CAST_LPAR_POSITION,
    SPP_CAST_RPAR_POSITION,
    SPP_CAST_TYPE_BEGIN_POSITION,
    SPP_CAST_TYPE_END_POSITION,
    SPP_CAST_EXPRESSION_BEGIN_POSITION,
    SPP_CAST_EXPRESSION_END_POSITION,
    SPP_PARENTHESED_EXPRESSION_LPAR_POSITION,
    SPP_PARENTHESED_EXPRESSION_RPAR_POSITION,
    SPP_PARENTHESED_EXPRESSION_BEGIN_POSITION,
    SPP_PARENTHESED_EXPRESSION_END_POSITION,
    SPP_MAX,
};

/* ******************************************************************** */
/*                               STRUCTURES                             */
/* ******************************************************************** */

#include "position.h"

/* return value for IDENTIFIER token from yylex */

#include "id.h"

#include "typemodifier.h"

typedef struct recFindStr {
    struct symbol			*baseClass;	/* class, application on which is looked*/
    struct symbol			*currClass;	/* current class, NULL for loc vars. */
    struct symbol           *nextRecord;
    unsigned                recsClassCounter;
    int                     sti;
    struct symbolList		*st[MAX_INHERITANCE_DEEP];	/* super classes stack */
    int                     aui;
    struct symbol			*au[MAX_ANONYMOUS_FIELDS];	/* anonymous unions */
} S_recFindStr;

typedef struct extRecFindStr {
    struct recFindStr			s;
    struct symbol				*memb;
    struct typeModifierList	*params;
} S_extRecFindStr;

typedef struct nestedSpec {
    struct symbol		*cl;
    bool membFlag;		/* flag whether it is nested in class */
    short unsigned  accFlags;
} S_nestedSpec;

#include "classcaster.h"

typedef struct symStructSpec {
    struct symbolList		*super;			/* list of super classes & interfaces */
    struct symbol			*records;		/* str. records, should be a table of   */
    struct cctNode			casts;			/* possible casts                       */
    short int				nestedCount;		/* # of java nested classes     */
    struct nestedSpec		*nest;			/* array of nested classes		*/
    struct typeModifier	stype;              /* this structure type */
    struct typeModifier	sptrtype;           /* this structure pointer type */
    int						classFile;		/* in java, my class file index
                                               == -1 for none, TODO to change
                                               it to s_noneFileIndex !!!
                                            */
    unsigned				recSearchCounter; /* tmp counter when looking for a record
                                                it flags searched classes
                                             */
} S_symStructSpec;


typedef struct jslSymbolList {
    struct symbol           *d;
    struct position			position;
    bool					isExplicitlyImported;
    struct jslSymbolList	*next;
} JslSymbolList;


/* ****************************************************************** */
/*          symbol definition item in cross-reference table           */

typedef struct usageBits {
    unsigned base:8;								// 0 - 128, it should not grow anymore
    unsigned requiredAccess:MAX_REQUIRED_ACCESS_LN;	// required accessibility of the reference
} UsageBits;

// !!! if you add a pointer to this structure, then update olcxCopyRefList
typedef struct reference {
    struct usageBits			usage;
    struct position				position;
    struct reference            *next;
} Reference;

typedef struct symbolReferenceItemBits {
    Type					symType		: SYMTYPES_LN;
    Storage					storage		: STORAGES_LN;
    ReferenceScope			scope		: SCOPES_LN;
    Access					accessFlags	: 12; /* java access bits */
    ReferenceCategory		category	: 2;  /* local/global */
} SymbolReferenceItemBits;

// !!! if you add a pointer to this structure, then update olcxCopyRefItem!
typedef struct symbolReferenceItem {
    char						*name;
    unsigned					fileHash;
    int							vApplClass;	/* appl class for java virtuals */
    int							vFunClass;	/* fun class for java virtuals */
    struct symbolReferenceItemBits b;
    struct reference			*refs;
    struct symbolReferenceItem  *next;
} SymbolReferenceItem;

typedef struct symbolReferenceItemList {
    struct symbolReferenceItem		*d;
    struct symbolReferenceItemList	*next;
} SymbolReferenceItemList;

/* ***************** on - line cross referencing ***************** */

typedef struct olCompletion {
    char					*name;
    char					*fullName;
    char					*vclass;
    short int				jindent;
    short int				lineCount;
    char					category;       /* Global/Local */
    char					csymType;		/* symtype of completion */
    struct reference		ref;
    struct symbolReferenceItem	sym;
    struct olCompletion		*next;
} S_olCompletion;

typedef struct SymbolFoundInformation {
    struct symbolReferenceItem	*symrefs;		/* this is valid */
    struct symbolReferenceItem	*symRefsInfo;	/* additional for error message */
    struct reference		*currentRef;
} SymbolFoundInformation;

typedef struct SymbolsMenu {
    struct symbolReferenceItem	s;
    char					selected;
    char					visible;
    unsigned				ooBits;
    char					olUsage;	/* usage of symbol under cursor */
    short int				vlevel;		/* virt. level of applClass <-> olsymbol*/
    short int				refn;
    short int				defRefn;
    char					defUsage;   /* usage of definition reference */
    struct position         defpos;
    int                     outOnLine;
    struct editorMarkerList	*markers;	/* for refactory only */
    struct SymbolsMenu	*next;
} SymbolsMenu;

// if you add something to this structure, update olcxMoveTopFromAnotherUser()
// !!!!!
typedef struct olcxReferences {
    struct reference        *references; /* list of references */
    struct reference        *actual;     /* actual reference */
    char					command;     /* OLO_PUSH/OLO_LIST/OLO_COMPLETION */
    char					language;    /* C/JAVA/YACC */
    time_t					accessTime;	 /* last access time */
    struct position			callerPosition; /* caller position */
    struct olCompletion		*completions;       /* completions list for OLO_COMPLETION */
    // following two lists should be probably split into hashed tables of lists
    // because of bad performances for class tree and global unused symbols
    struct SymbolsMenu      *hkSelectedSym; /* resolved symbols under the cursor */
    struct SymbolsMenu      *menuSym;		/* hkSelectedSyms plus same name */
    int						menuFilterLevel;
    int						refsFilterLevel;
    struct olcxReferences	*previous;
} OlcxReferences;

typedef struct classTreeData {
    int						baseClassFileIndex;
    struct SymbolsMenu	*tree;
} S_classTreeData;

typedef struct olcxReferencesStack {
    struct olcxReferences	*top;
    struct olcxReferences	*root;
} OlcxReferencesStack;



/* ***************** COMPLETION STRUCTURES ********************** */


typedef struct completionLine {
    char            *string;
    struct symbol   *symbol;
    Type			symbolType;
    short int		virtLevel;
    short int		margn;
    char			**margs;
    struct symbol	*vFunClass;
} CompletionLine;

typedef struct completions {
    char            idToProcess[MAX_FUN_NAME_SIZE];
    int				idToProcessLen;
    struct position	idToProcessPos;
    bool fullMatchFlag;
    bool isCompleteFlag;
    bool noFocusOnCompletions;
    bool abortFurtherCompletions;
    char            comPrefix[TMP_STRING_SIZE];
    int				maxLen;
    struct completionLine    alternatives[MAX_COMPLETIONS];
    int             alternativeIndex;
} Completions;


/* ************************** INIT STRUCTURES ********************* */

typedef struct typeCharCodeIni {
    int         symType;
    char		code;
} S_typeCharCodeIni;

typedef struct javaTypePCTIConvertIni {
    int		symType;
    int		PCTIndex;
} S_javaTypePCTIConvertIni;

typedef struct currentlyParsedCl {		// class local, nested for classes
    struct symbol			*function;
    struct extRecFindStr	*erfsForParamsComplet;			// curently parsed method for param completion
    unsigned				funBegPosition;
    int                     cxMemoryIndexAtFunctionBegin;
    int						cxMemoryIndexAtFunctionEnd;
    int                     cxMemoryIndexdiAtClassBegin;
    int						cxMemoryIndexAtClassEnd;
    int						thisMethodMemoriesStored;
    int						thisClassMemoriesStored;
    int						parserPassedMarker;
} S_currentlyParsedCl;

typedef struct currentlyParsedStatics {
    int             extractProcessedFlag;
    int				marker1Flag;
    int				marker2Flag;
    char			setTargetAnswerClass[TMP_STRING_SIZE];	// useless for xref2
    int				moveTargetApproved;
    char			currentPackageAnswer[TMP_STRING_SIZE];
    char			currentClassAnswer[TMP_STRING_SIZE];
    char			currentSuperClassAnswer[TMP_STRING_SIZE];
    int				methodCoordEndLine;        // to be removed
    int				classCoordEndLine;
    struct codeBlock *workMemoryIndexAtBlockBegin;
    struct codeBlock *workMemiAtBlockEnd;
    int             cxMemoryIndexAtBlockBegin;
    int             cxMemoryIndexAtBlockEnd;
    int				cxMemoryIndexAtMethodBegin;
    int				cxMemoryIndexAtMethodEnd;
    int				cxMemoryIndexAtClassBeginning;
    int				cxMemoryIndexAtClassEnd;
    int				lastImportLine;
    struct symbol	*lastDeclaratorType;
    struct symbol	*lastAssignementStruct;
} S_currentlyParsedStatics;


/* ************************ PRE-PROCESSOR **************************** */

typedef struct cppIfStack {
    struct position position;
    struct cppIfStack *next;
} S_cppIfStack;


/* *********************************************************** */

typedef struct expressionTokenType {
    struct typeModifier  *typeModifier;
    struct reference     *reference;
    struct position      *position;
} S_exprTokenType;

typedef struct nestedConstrTokenType {
    struct typeModifier	*typeModifier;
    struct idList *idList;
    struct position *position;
} S_nestedConstrTokenType;

typedef struct unsignedPositionPair {
    unsigned		u;
    struct position	*position;
} S_unsignedPositionPair;

typedef struct symbolPositionPair {
    struct symbol	*symbol;
    struct position	*position;
} S_symbolPositionPair;

typedef struct symbolPositionListPair {
    struct symbol		*symbol;
    struct positionList	*p;
} S_symbolPositionListPair;

typedef struct intPair {
    int i1;
    int i2;
} S_intPair;

typedef struct typeModifiersListPositionListPair {
    struct typeModifierList	*t;
    struct positionList			*p;
} S_typeModifiersListPositionListPair;

typedef struct pushAllInBetweenData {
    int			minMemi;
    int			maxMemi;
} S_pushAllInBetweenData;



/* *********************************************************** */

/* **************     parse tree with positions    *********** */

// following structures are used in yacc parser, they always
// contain 'b','e' records for begin and end position of parse tree
// node and additional data 'd' for parsing.

typedef struct {
    struct position  b, e;
    int d;
} Ast_int;
typedef struct {
    struct position b, e;
    unsigned d;
} Ast_unsigned;
typedef struct {
    struct position b, e;
    struct symbol *d;
} Ast_symbol;
typedef struct {
    struct position b, e;
    struct symbolList *d;
} Ast_symbolList;
typedef struct {
    struct position          b, e;
    struct typeModifier		*d;
} Ast_typeModifiers;
typedef struct {
    struct position              b, e;
    struct typeModifierList		*d;
} Ast_typeModifiersList;
typedef struct {
    struct position      b, e;
    struct freeTrail		*d;
} Ast_freeTrail;
typedef struct {
    struct position      b, e;
    struct id		*d;
} Ast_id;
typedef struct {
    struct position          b, e;
    struct idList		*d;
} Ast_idList;
typedef struct {
    struct position          b, e;
    struct expressionTokenType		d;
} Ast_exprTokenType;
typedef struct {
    struct position                  b, e;
    struct nestedConstrTokenType		d;
} Ast_nestedConstrTokenType;
typedef struct {
    struct position      b, e;
    struct intPair		d;
} Ast_intPair;
typedef struct {
    struct position              b, e;
    struct whileExtractData		*d;
} Ast_whileExtractData;
typedef struct {
    struct position      b, e;
    struct position		d;
} Ast_position;
typedef struct {
    struct position              b, e;
    struct unsignedPositionPair		d;
} Ast_unsPositionPair;
typedef struct {
    struct position                  b, e;
    struct symbolPositionPair		d;
} Ast_symbolPositionPair;
typedef struct {
    struct position                  b, e;
    struct symbolPositionListPair		d;
} Ast_symbolPositionListPair;
typedef struct {
    struct position          b, e;
    struct positionList		*d;
} Ast_positionList;
typedef struct {
    struct position                                  b, e;
    struct typeModifiersListPositionListPair			d;
} Ast_typeModifiersListPositionListPair;


#include "refactorings.h"

#endif
