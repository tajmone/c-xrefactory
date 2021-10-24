#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>

#include "misc.h"

#include "memory.h"

#include "globals.mock"
#include "options.mock"
#include "caching.mock"
#include "filetable.mock"
#include "jsemact.mock"
#include "classfilereader.mock"
#include "cxref.mock"
#include "cxfile.mock"
#include "yylex.mock"
#include "commons.mock"
#include "editor.mock"
#include "ppc.mock"
#include "fileio.mock"


Describe(Misc);
BeforeEach(Misc) {}
AfterEach(Misc) {}


Ensure(Misc, can_run_an_empty_test) {
}
