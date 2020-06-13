#include <cgreen/cgreen.h>

#include "cxref.h"

/* Dependencies: */
#include "filedescriptor.mock"
#include "filetable.mock"
#include "olcxtab.mock"
#include "globals.mock"
#include "cxfile.mock"
#include "editor.mock"
#include "refactory.mock"
#include "misc.mock"
#include "classhierarchy.mock"
#include "html.mock"
#include "complete.mock"
#include "caching.mock"
#include "options.mock"
#include "symbol.mock"
#include "main.mock"
#include "commons.mock"
#include "characterreader.mock"
#include "jsemact.mock"
#include "memory.mock"
#include "utils.mock"
#include "reftab.mock"
#include "fileio.mock"


Describe(CxRef);
BeforeEach(CxRef) {}
AfterEach(CxRef) {}


Ensure(CxRef, get_class_num_from_class_linkname_will_return_default_value_if_not_member) {
    int defaultValue = 14;

    expect(fileTableExists,
           when(fileName, is_equal_to_string(";name.class")),
           will_return(false));

    assert_that(getClassNumFromClassLinkName("name", defaultValue), is_equal_to(defaultValue));
}

Ensure(CxRef, get_class_num_from_class_linkname_will_return_filenumber_if_member) {
    int defaultValue = 14;
    int position = 42;

    expect(fileTableExists,
           when(fileName, is_equal_to_string(";name.class")),
           will_return(true));
    expect(fileTableLookup, will_return(position));

    assert_that(getClassNumFromClassLinkName("name", defaultValue), is_equal_to(position));
}
