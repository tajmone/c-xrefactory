# This should become the golden standard for creating an edit_server test:
#
# 1. generate CXrefs if they don't exist by running c-xref
# 2. use ../../utils/server_driver to feed the edit_server what's in commands.input
# 3. normalize the output and compare
#
# N.B. You can create a good starting point for your commands.input by running emacs
# from ../sandboxed_emacs.

include ../Makefile.boilerplate

CXREF = ../../src/c-xref
ARGUMENTS = -xrefactory-II -refactory -xrefrc $(CURDIR)/.c-xrefrc -p $(CURDIR) -user 1 -rfct-add-param -olcxparnum=2 -rfct-param1=int\ arg -rfct-param2=42 -olcursor=36 $(CURDIR)/test_source/hello-extracted.c

$(TEST): clean
	@# First do the extract
	$(CXREF) $(ARGUMENTS) -log=log $(EXTRA) > output.tmp
	@$(NORMALIZE) output.tmp | grep -v progress > output
	@diff -B output expected > /dev/null ; \
	if [ $$? -ne 0 ] ; then \
		$(FAIL) ; \
		echo "diff output expected" ; \
		diff output expected ; \
		exit 1 ; \
	else \
		$(OK) ; \
		exit 0 ; \
	fi

trace: EXTRA=-trace
trace: $(TEST)

clean:
	@-rm -rf CXrefs output.log output.tmp output log

debug: DEBUGGER=gdb
debug:
	echo run $(ARGUMENTS)
	$(DEBUGGER) $(CXREF)
