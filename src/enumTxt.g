char * taskRegimesEnumName[] = {
    "RegimeUndefined",
    "RegimeXref",
    "RegimeHtmlGenerate",
    "RegimeEditServer",
    "RegimeRefactory",
    "RegimeGenerate"
};

char * fileEncodingsEnumName[] = {
    "MULE_DEFAULT",
    "MULE_EUROPEAN",
    "MULE_EUC",
    "MULE_SJIS",
    "MULE_UTF",
    "MULE_UTF_8",
    "MULE_UTF_16",
    "MULE_UTF_16LE",
    "MULE_UTF_16BE"
};

char * referenceCategoryEnumName[] = {
    "CategoryGlobal",
    "CategoryLocal",
    "MAX_CATEGORIES"
};

char * syntaxPassParsedImportantPositionEnumName[] = {
    "SPP_LAST_TOP_LEVEL_CLASS_POSITION",
    "SPP_ASSIGNMENT_OPERATOR_POSITION",
    "SPP_ASSIGNMENT_END_POSITION",
    "SPP_CLASS_DECLARATION_BEGIN_POSITION",
    "SPP_CLASS_DECLARATION_END_POSITION",
    "SPP_CLASS_DECLARATION_TYPE_BEGIN_POSITION",
    "SPP_CLASS_DECLARATION_TYPE_END_POSITION",
    "SPP_METHOD_DECLARATION_BEGIN_POSITION",
    "SPP_METHOD_DECLARATION_END_POSITION",
    "SPP_METHOD_DECLARATION_TYPE_BEGIN_POSITION",
    "SPP_METHOD_DECLARATION_TYPE_END_POSITION",
    "SPP_FIELD_DECLARATION_BEGIN_POSITION",
    "SPP_FIELD_DECLARATION_END_POSITION",
    "SPP_FIELD_DECLARATION_TYPE_BEGIN_POSITION",
    "SPP_FIELD_DECLARATION_TYPE_END_POSITION",
    "SPP_CAST_LPAR_POSITION",
    "SPP_CAST_RPAR_POSITION",
    "SPP_CAST_TYPE_BEGIN_POSITION",
    "SPP_CAST_TYPE_END_POSITION",
    "SPP_CAST_EXPRESSION_BEGIN_POSITION",
    "SPP_CAST_EXPRESSION_END_POSITION",
    "SPP_PARENTHESED_EXPRESSION_LPAR_POSITION",
    "SPP_PARENTHESED_EXPRESSION_RPAR_POSITION",
    "SPP_PARENTHESED_EXPRESSION_BEGIN_POSITION",
    "SPP_PARENTHESED_EXPRESSION_END_POSITION",
    "SPP_MAX"
};

char * memoryClassEnumName[] = {
    "MEMORY_CF",
    "MEMORY_XX",
    "MEMORY_PP"
};

char * olcxOptionsEnumName[] = {
    "OLO_COMPLETION",
    "OLO_SEARCH",
    "OLO_TAG_SEARCH",
    "OLO_RENAME",
    "OLO_ENCAPSULATE",
    "OLO_ARG_MANIP",
    "OLO_VIRTUAL2STATIC_PUSH",
    "OLO_GET_AVAILABLE_REFACTORINGS",
    "OLO_PUSH",
    "OLO_PUSH_NAME",
    "OLO_PUSH_SPECIAL_NAME",
    "OLO_POP",
    "OLO_POP_ONLY",
    "OLO_PLUS",
    "OLO_MINUS",
    "OLO_GOTO_CURRENT",
    "OLO_GET_CURRENT_REFNUM",
    "OLO_GOTO_PARAM_NAME",
    "OLO_GLOBAL_UNUSED",
    "OLO_LOCAL_UNUSED",
    "OLO_LIST",
    "OLO_LIST_TOP",
    "OLO_PUSH_ONLY",
    "OLO_PUSH_AND_CALL_MACRO",
    "OLO_PUSH_ALL_IN_METHOD",
    "OLO_PUSH_FOR_LOCALM",
    "OLO_GOTO",
    "OLO_CGOTO",
    "OLO_TAGGOTO",
    "OLO_TAGSELECT",
    "OLO_CBROWSE",
    "OLO_REF_FILTER_SET",
    "OLO_REF_FILTER_PLUS",
    "OLO_REF_FILTER_MINUS",
    "OLO_CSELECT",
    "OLO_COMPLETION_BACK",
    "OLO_COMPLETION_FORWARD",
    "OLO_EXTRACT",
    "OLO_CT_INSPECT_DEF",
    "OLO_MENU_INSPECT_DEF",
    "OLO_MENU_INSPECT_CLASS",
    "OLO_MENU_SELECT",
    "OLO_MENU_SELECT_ONLY",
    "OLO_MENU_SELECT_ALL",
    "OLO_MENU_SELECT_NONE",
    "OLO_MENU_FILTER_SET",
    "OLO_MENU_FILTER_PLUS",
    "OLO_MENU_FILTER_MINUS",
    "OLO_MENU_GO",
    "OLO_CHECK_VERSION",
    "OLO_RESET_REF_SUFFIX",
    "OLO_TRIVIAL_PRECHECK",
    "OLO_MM_PRE_CHECK",
    "OLO_PP_PRE_CHECK",
    "OLO_SAFETY_CHECK_INIT",
    "OLO_SAFETY_CHECK1",
    "OLO_SAFETY_CHECK2",
    "OLO_INTERSECTION",
    "OLO_REMOVE_WIN",
    "OLO_GOTO_DEF",
    "OLO_GOTO_CALLER",
    "OLO_SHOW_TOP",
    "OLO_SHOW_TOP_APPL_CLASS",
    "OLO_SHOW_TOP_TYPE",
    "OLO_SHOW_CLASS_TREE",
    "OLO_TOP_SYMBOL_RES",
    "OLO_ACTIVE_PROJECT",
    "OLO_JAVA_HOME",
    "OLO_REPUSH",
    "OLO_CLASS_TREE",
    "OLO_USELESS_LONG_NAME",
    "OLO_USELESS_LONG_NAME_IN_CLASS",
    "OLO_MAYBE_THIS",
    "OLO_NOT_FQT_REFS",
    "OLO_NOT_FQT_REFS_IN_CLASS",
    "OLO_GET_ENV_VALUE",
    "OLO_SET_MOVE_TARGET",
    "OLO_SET_MOVE_CLASS_TARGET",
    "OLO_SET_MOVE_METHOD_TARGET",
    "OLO_GET_CURRENT_CLASS",
    "OLO_GET_CURRENT_SUPER_CLASS",
    "OLO_GET_METHOD_COORD",
    "OLO_GET_CLASS_COORD",
    "OLO_GET_SYMBOL_TYPE",
    "OLO_TAG_SEARCH_FORWARD",
    "OLO_TAG_SEARCH_BACK",
    "OLO_PUSH_ENCAPSULATE_SAFETY_CHECK",
    "OLO_ENCAPSULATE_SAFETY_CHECK",
    "OLO_SYNTAX_PASS_ONLY",
    "OLO_GET_PRIMARY_START",
    "OLO_GET_PARAM_COORDINATES",
    "OLO_ABOUT"
};

char * updateTypeEnumName[] = {
    "UP_CREATE",
    "UP_FAST_UPDATE",
    "UP_FULL_UPDATE"
};


char * languageEnumName[] = {
    "LANG_C",
    "LANG_JAVA",
    "LANG_YACC",
    "LANG_JAR",
    "LANG_CLASS"
};

char * addImportsDefaultEnumName[] = {
    "NID_IMPORT_ON_DEMAND",
    "NID_SINGLE_TYPE_IMPORT",
    "NID_KEPP_FQT_NAME"
};

char * javaPCTIndexEnumName[] = {
    "PCTIndexError",
    "PCTIndexByte",
    "PCTIndexShort",
    "PCTIndexChar",
    "PCTIndexInt",
    "PCTIndexLong",
    "PCTIndexFloat",
    "PCTIndexDouble",
    "MAX_PCTIndex"
};

char * refsFilterLevelsEnumName[] = {
    "RFilterAll",
    "RFilterAddrVal",
    "RFilterLVal",
    "RFilterDefinitions",
    "MAX_REF_LIST_FILTER_LEVEL"
};

char * sFunResultEnumName[] = {
    "RESULT_OK",
    "RESULT_ERR"
};

char * menuFilterLevelsEnumName[] = {
    "FilterAllOfSameName",
    "FilterSameProfile",
    "FilterSameProfileRelatedClass",
    "FilterVirtualAdequate",
    "FilterVirtualSameAppl",
    "MAX_MENU_FILTER_LEVEL"
};

char * miscellaneousEnumName[] = {
    "DEFAULT_VALUE",
    "TYPE_ADD_YES",
    "TYPE_ADD_NO",
    "ADD_YES",
    "ADD_NO",
    "CLASS_TO_TYPE",
    "CLASS_TO_EXPR",
    "CLASS_TO_METHOD",
    "CLASS_TO_ANY",
    "ACC_CHECK_YES",
    "ACC_CHECK_NO",
    "VISIB_CHECK_YES",
    "VISIB_CHECK_NO",
    "CUT_OVERRIDEN_YES",
    "CUT_OVERRIDEN_NO",
    "CX_FILE_ITEM_GEN",
    "NO_CX_FILE_ITEM_GEN",
    "CX_GENERATE_OUTPUT",
    "CX_JUST_READ",
    "CX_HTML_FIRST_PASS",
    "CX_HTML_SECOND_PASS",
    "CX_MENU_CREATION",
    "CX_BY_PASS",
    "HTML_GEN",
    "HTML_NO_GEN",
    "MEM_ALLOC_ON_SM",
    "MEM_ALLOC_ON_PP",
    "MEM_NO_ALLOC",
    "MESS_REFERENCE_OVERFLOW",
    "MESS_FILE_ABORT",
    "MESS_NONE",
    "INFILES_ENABLED",
    "INFILES_DISABLED",
    "BEFORE_BLOCK",
    "INSIDE_BLOCK",
    "AFTER_BLOCK",
    "EXTRACT_LOCAL_VAR",
    "EXTRACT_VALUE_ARGUMENT",
    "EXTRACT_LOCAL_OUT_ARGUMENT",
    "EXTRACT_OUT_ARGUMENT",
    "EXTRACT_IN_OUT_ARGUMENT",
    "EXTRACT_ADDRESS_ARGUMENT",
    "EXTRACT_RESULT_VALUE",
    "EXTRACT_IN_RESULT_VALUE",
    "EXTRACT_LOCAL_RESULT_VALUE",
    "EXTRACT_NONE",
    "EXTRACT_ERROR",
    "INVOCATION_XREF",
    "INVOCATION_SETUP",
    "INVOCATION_SPELLER",
    "LOADING_SYMBOL",
    "SEARCH_SYMBOL",
    "FF_SCHEDULED_TO_PROCESS",
    "FF_COMMAND_LINE_ENTERED",
    "OL_LOOKING_2_PASS_MACRO_USAGE",
    "SHORT_NAME",
    "LONG_NAME",
    "GEN_HTML",
    "GEN_JAVA_DOC",
    "ONLINE_ONLY",
    "ALL_REFS",
    "COUNT_ONLY",
    "CUT_OUTERS",
    "NO_OUTERS_CUT",
    "VIRT_ITEM",
    "SINGLE_VIRT_ITEM",
    "FIRST_PASS",
    "SECOND_PASS",
    "DO_NOT_CHECK_IF_SELECTED",
    "PUSH_AFTER_MENU",
    "CHECK_NULL",
    "RESULT_IS_CLASS_FILE",
    "RESULT_IS_JAVA_FILE",
    "RESULT_NO_FILE_FOUND",
    "TRAILED_YES",
    "TRAILED_NO",
    "CPOS_FUNCTION_INNER",
    "CPOS_ST",
    "DIRECT_ONLY",
    "SUPERCLASS_NESTED_TOO",
    "DIFF_MISSING_REF",
    "DIFF_UNEXPECTED_REF",
    "CONSTRUCTOR_INVOCATION",
    "REGULAR_METHOD",
    "SUPER_METHOD_INVOCATION",
    "RESOLVE_DIALOG_ALLWAYS",
    "RESOLVE_DIALOG_NEVER",
    "GLOBAL_ENV_ONLY",
    "NO_ERROR_MESSAGE",
    "ADD_CX_REFS",
    "NO_CX_REFS",
    "ORDER_PREPEND",
    "ORDER_APPEND",
    "MEMBER_CLASS",
    "MEMBER_TYPE",
    "GEN_VIRTUALS",
    "GEN_NON_VIRTUALS",
    "REQ_FIELD",
    "REQ_METHOD",
    "REQ_STATIC",
    "REQ_NONSTATIC",
    "REQ_SUPERCLASS",
    "REQ_SUBCLASS",
    "REQ_CLASS",
    "REQ_PACKAGE",
    "INSPECT_DEF",
    "INSPECT_CLASS",
    "DOTIFY_NAME",
    "KEEP_SLASHES",
    "LOAD_SUPER",
    "DO_NOT_LOAD_SUPER",
    "ADD_MAYBE_THIS_REFERENCE",
    "TSS_FULL_SEARCH",
    "TSS_SEARCH_DEFS_ONLY",
    "TSS_FULL_SEARCH_SHORT",
    "TSS_SEARCH_DEFS_ONLY_SHORT",
    "GEN_FULL_OUTPUT",
    "GEN_PRECHECKS",
    "GEN_NO_OUTPUT",
    "CHECK_FOR_ADD_PARAM",
    "CHECK_FOR_DEL_PARAM",
    "GET_PRIMARY_START",
    "GET_STATIC_PREFIX_START",
    "APPLY_CHECKS",
    "NO_CHECKS",
    "CONTINUATION_ENABLED",
    "CONTINUATION_DISABLED",
    "NO_OVERWRITE_CHECK",
    "CHECK_OVERWRITE",
    "ALLOW_EDITOR_FILES",
    "DO_NOT_ALLOW_EDITOR_FILES",
    "DEPTH_ONE",
    "DEPTH_ANY",
    "DEAD_CODE_DETECTION",
    "INTERACTIVE_YES",
    "INTERACTIVE_NO",
    "MARKER_IS_IN_CODE",
    "MARKER_IS_IN_SLASH_COMMENT",
    "MARKER_IS_IN_STAR_COMMENT",
    "PROFILE_NOT_APPLICABLE",
    "PROFILE_APPLICABLE",
    "PROFILE_PARTIALLY_APPLICABLE",
    "USELESS_FQT_REFS_ALLOWED",
    "USELESS_FQT_REFS_DISALLOWED",
    "PULLING_UP",
    "PUSHING_DOWN"
};

char * refScopesEnumName[] = {
    "ScopeDefault",
    "ScopeGlobal",
    "ScopeFile",
    "ScopeAuto",
    "MAX_SCOPES"
};

char * commentMovementEnumName[] = {
    "CM_NO_COMMENT",
    "CM_SINGLE_SLASHED",
    "CM_SINGLE_STARED",
    "CM_SINGLE_SLASHED_AND_STARED",
    "CM_ALL_SLASHED",
    "CM_ALL_STARED",
    "CM_ALL_SLASHED_AND_STARED"
};

char * inputTypeEnumName[] = {
    "INPUT_NORMAL",
    "INPUT_MACRO",
    "INPUT_MACRO_ARGUMENT",
    "INPUT_CACHE"
};

char * accessEnumName[] = {
    "ACCESS_DEFAULT",
    "ACCESS_PUBLIC",
    "ACCESS_PRIVATE",
    "ACCESS_PROTECTED",
    "ACCESS_STATIC",
    "ACCESS_FINAL",
    "ACCESS_SYNCHRONIZED",
    "ACCESS_THREADSAFE",
    "ACCESS_TRANSIENT",
    "ACCESS_NATIVE",
    "ACCESS_INTERFACE",
    "ACCESS_ABSTRACT",
    "ACCESS_ALL"
};
