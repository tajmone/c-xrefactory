#include <cgreen/cgreen.h>

#include "yylex.h"
/* Declare semi-private function */
void processDefineDirective(bool hasArguments);
void processLineDirective(void);
void processIncludeDirective(Position *ipos);

#include "filedescriptor.h"
#include "filetable.h"
#include "symboltable.h"
#include "macroargumenttable.h"
#include "symbol.h"

#include "globals.mock"
#include "caching.mock"
#include "parsers.mock"
#include "cexp_parser.mock"
#include "jslsemact.mock"
#include "jsemact.mock"
#include "reftab.mock"
#include "editor.mock"
#include "commons.mock"
#include "misc.mock"
#include "cxfile.mock"
#include "characterreader.mock"
#include "lexer.mock"
#include "semact.mock"
#include "java_parser.mock"
#include "cxref.mock"
#include "extract.mock"
#include "c_parser.mock"
#include "yacc_parser.mock"
#include "fileio.mock"
#include "memory.mock"


Describe(Yylex);
BeforeEach(Yylex) {
    options.taskRegime = RegimeEditServer;
    ppMemInit();
    initFileTable(&fileTable);
    s_symbolTable = StackMemoryAlloc(SymbolTable);
    symbolTableInit(s_symbolTable, 10);
}
AfterEach(Yylex) {}

static void setup_lexBuffer_for_reading_identifier(void *data) {
    char *lexemStreamP = currentFile.lexBuffer.lexemStream;
    putLexToken(IDENTIFIER, &lexemStreamP);
    strcpy(lexemStreamP, currentFile.lexBuffer.buffer.chars);
    /* TODO: WTF This is mostly guesswork, no idea if this is how they are connected... */
    *strchr(&currentFile.lexBuffer.lexemStream[2], ' ') = '\0';
    currentFile.lexBuffer.next = currentFile.lexBuffer.lexemStream;
    currentFile.lexBuffer.end = strchr(currentFile.lexBuffer.lexemStream, '\0');
    currentFile.lexBuffer.index = 2;
}

Ensure(Yylex, add_a_cpp_definition_to_the_symbol_table) {
#   define DEFINE "__x86_64__"
    char *definition = (char *)malloc(strlen(DEFINE)+1);
    strcpy(definition, DEFINE);

    expect(getLexemFromLexer, when(buffer, is_equal_to(&currentFile.lexBuffer)),
           will_return(true), with_side_effect(setup_lexBuffer_for_reading_identifier, NULL));
    expect(setGlobalFileDepNames, when(iname, is_equal_to_string(definition)),
           will_set_contents_of_parameter(pp_name, &definition, sizeof(char *)));
    expect(getLexemFromLexer, when(buffer, is_equal_to(&currentFile.lexBuffer)),
           will_return(false));

    /* This is the confirmation that there is a symbol p with a
     * field with name equal to DEFINE
     */
    expect(addCxReference, when(symbol_name, is_equal_to_string(DEFINE)));

    /* If the define does not have a body, add the value of "1" */
    initInput(NULL, NULL, "__x86_64__ 1", NULL);
    currentFile.lineNumber = 1;
    processDefineDirective(false);
}

Ensure(Yylex, can_handle_a_line_directive_without_number) {
    expect(getLexemFromLexer, when(buffer, is_equal_to(&currentFile.lexBuffer)),
           will_return(false));

    initInput(NULL, NULL, "", NULL);
    currentFile.lineNumber = 1;
    processLineDirective();
    /* No asserts, only for execution of END_OF_FILE_EXCEPTION in #line directive */
}

Ensure(Yylex, can_process_include_directive) {
    Position ipos = (Position){1,2,3};
    char *lexem_stream = "\303\001\"include.h";
    FILE file;

    strcpy(cwd, "cwd");

    strcpy(currentFile.lexBuffer.lexemStream, lexem_stream);
    currentFile.lexBuffer.next = currentFile.lexBuffer.lexemStream;
    currentFile.lexBuffer.end = currentFile.lexBuffer.lexemStream + strlen(lexem_stream);

    initInput(NULL, NULL, "", NULL);
    currentInput.endOfBuffer = currentInput.beginningOfBuffer + strlen(lexem_stream);

    expect(extractPathInto, will_set_contents_of_parameter(dest, "some/path", 10));
    always_expect(normalizeFileName,
                  will_return("some/path/include.h"));
    expect(editorFindFile, will_return(NULL));
    expect(openFile, when(fileName, is_equal_to_string("some/path/include.h")), will_return(&file));

    /* Always  */
    always_expect(checkFileModifiedTime);
    always_expect(cacheInclude);

    /* Finally ensure that the include file is added as a reference */
    expect(addCxReference, when(symbol_name, is_equal_to_string(LINK_NAME_INCLUDE_REFS)));
    expect(addCxReference, when(symbol_name, is_equal_to_string(LINK_NAME_INCLUDE_REFS)));

    processIncludeDirective(&ipos);
}
