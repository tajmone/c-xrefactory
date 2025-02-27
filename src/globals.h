#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "constants.h"
#include "symboltable.h"
#include "filetable.h"
#include "stringlist.h"


typedef struct int2StringTable {
    int     i;
    char    *string;
} Int2StringDictionary;

/* ***************** unique counters  *********************** */
typedef struct counters {
    int localSym;
    int localVar;
    int anonymousClassCounter;
} Counters;


extern char cwd[MAX_FILE_NAME_SIZE]; /* current working directory */
extern char s_base[MAX_FILE_NAME_SIZE];
extern char ppcTmpBuff[MAX_PPC_RECORD_SIZE];

extern int s_fileAbortionEnabled;

extern bool s_wildcardSearch;
extern int s_lastReturnedLexem;
extern Position s_spp[SPP_MAX];
extern UsageBits s_noUsage;

extern int s_progressFactor;
extern int s_progressOffset;

extern int s_cxResizingBlocked;
extern Counters counters;
extern unsigned s_recFindCl;

extern FILE *errOut;
extern FILE *dumpOut;

extern char s_olSymbolType[COMPLETION_STRING_SIZE];
extern char s_olSymbolClassType[COMPLETION_STRING_SIZE];
extern Position s_paramPosition;
extern Position s_paramBeginPosition;
extern Position s_paramEndPosition;
extern Position s_primaryStartPosition;
extern Position s_staticPrefixStartPosition;
extern Id s_yyIdentBuf[YYBUFFERED_ID_INDEX];
extern int s_yyIdentBufi;

extern char *s_cppVarArgsName;
extern char defaultClassPath[];
extern Id s_javaAnonymousClassName;
extern Id s_javaConstructorName;
extern StringList *javaClassPaths;
extern char *javaSourcePaths;
extern IdList *s_javaDefaultPackageName;
extern IdList *s_javaLangName;
extern IdList *s_javaLangStringName;
extern IdList *s_javaLangCloneableName;
extern IdList *s_javaIoSerializableName;
extern IdList *s_javaLangClassName;
extern IdList *s_javaLangObjectName;
extern char *s_javaLangObjectLinkName;

extern Symbol s_javaArrayObjectSymbol;
extern Symbol *s_javaStringSymbol;
extern Symbol *s_javaObjectSymbol;
extern Symbol *s_javaCloneableSymbol;
extern Symbol *s_javaIoSerializableSymbol;
extern TypeModifier s_javaStringModifier;
extern TypeModifier s_javaClassModifier;
extern TypeModifier s_javaObjectModifier;

extern FILE *cxOut;
extern FILE *communicationChannel;

extern int s_javaPreScanOnly;

extern S_currentlyParsedCl s_cp;
extern S_currentlyParsedCl s_cpInit;
extern S_currentlyParsedStatics s_cps;
extern S_currentlyParsedStatics s_cpsInit;

extern TypeModifier defaultIntModifier;
extern Symbol s_defaultIntDefinition;
extern TypeModifier s_defaultPackedTypeModifier;
extern TypeModifier s_defaultVoidModifier;
extern Symbol s_defaultVoidDefinition;
extern TypeModifier s_errorModifier;
extern Symbol s_errorSymbol;
extern Position s_noPos;
extern Reference s_noRef;

extern uchar typeLongChange[MAX_TYPE];
extern uchar typeShortChange[MAX_TYPE];
extern uchar typeSignedChange[MAX_TYPE];
extern uchar typeUnsignedChange[MAX_TYPE];

extern TypeModifier *s_structRecordCompletionType;
extern TypeModifier *s_upLevelFunctionCompletionType;
extern S_exprTokenType s_forCompletionType;
extern TypeModifier *s_javaCompletionLastPrimary;
extern char *tokenNamesTable[];
extern int tokenNameLengthsTable[];
extern TypeModifier * s_preCreatedTypesTable[MAX_TYPE];
extern TypeModifier * s_preCrPtr1TypesTab[MAX_TYPE];
extern TypeModifier * s_preCrPtr2TypesTab[MAX_TYPE];

extern char s_javaBaseTypeCharCodes[MAX_TYPE];
extern int s_javaCharCodeBaseTypes[MAX_CHARS];
extern char s_javaTypePCTIConvert[MAX_TYPE];
extern char s_javaPrimitiveWideningConversions[MAX_PCTIndex-1][MAX_PCTIndex-1];

extern Position s_olcxByPassPos;
extern Position s_cxRefPos;
extern int s_cxRefFlag;

extern FILE *inputFile;

extern int s_input_file_number;
extern int s_olStringSecondProcessing;  /* am I in macro body pass ? */
extern int s_olOriginalFileNumber;      /* original file name */
extern int s_olOriginalComFileNumber;	/* original communication file */

extern char *storageNamesTable[MAX_STORAGE_NAMES];

extern char *s_editCommunicationString;

extern time_t s_expiration;

extern jmp_buf cxmemOverflow;

extern char *inputFilename;

extern time_t fileProcessingStartTime;

extern Language s_language;
extern int currentPass;
extern int maxPasses;

extern Completions s_completions;
extern unsigned s_menuFilterOoBits[MAX_MENU_FILTER_LEVEL];
extern int s_refListFilters[MAX_REF_LIST_FILTER_LEVEL];

/* ********* vars for on-line additions after EOF ****** */

extern char s_olstring[MAX_FUN_NAME_SIZE];
extern int s_olstringFound;
extern int s_olstringServed;
extern int s_olstringUsage;
extern char *s_olstringInMbody;
extern int s_olMacro2PassFile;

/* **************** variables due to cpp **************** */

extern bool s_ifEvaluation;		/* flag for yylex, to not filter '\n' */

extern int s_javaRequiredeAccessibilitiesTable[MAX_REQUIRED_ACCESS+1];

extern char *s_javaThisPackageName;

#endif
