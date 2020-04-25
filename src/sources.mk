SRCS =  main.c globals.c misc.c semact.c commons.c generate.c \
		enumTxt.c complete.c cxref.c cxfile.c lex.c yylex.c options.c \
		caching.c jsemact.c classfilereader.c classcaster.c init.c \
		editor.c refactory.c protocol.c log.c \
		html.c extract.c classhierarchy.c jslsemact.c \
		filetab.c macroargumenttable.c olcxtab.c editorbuffertab.c symboltable.c \
		javafqttab.c jsltypetab.c reftab.c memory.c utils.c characterbuffer.c hash.c \
		symbol.c c_parser.tab.c cexp_parser.tab.c java_parser.tab.c yacc_parser.tab.c \
		fileitem.c filedescriptor.c typemodifier.c position.c id.c

OBJDIR = .objects
OBJS = $(addprefix $(OBJDIR)/,${SRCS:.c=.o})
DEPS = $(addprefix $(OBJDIR)/,${SRCS:.c=.d})

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) -MMD -MP -c $<

$(OBJDIR):
	mkdir $(OBJDIR)

-include $(OBJDIR)/*.d

$(ZLIB_LIB):
	make -C $(ROOTDIR)/lib/zlib libz.a

# If you are using your systems zlib use these
LIBS+=-lz
# Else build the local, included, version and use these
# ZLIB_LIB=$(ROOTDIR)/lib/zlib/libz.a
# ZLIB_INCLUDE=-I$(ROOTDIR)/lib/zlib
