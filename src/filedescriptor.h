#ifndef FILEDESCRIPTOR_H_INCLUDED
#define FILEDESCRIPTOR_H_INCLUDED

#include "proto.h"
#include "lexembuffer.h"
#include "stringlist.h"


typedef struct fileDescriptor {
    char *fileName ;
    int lineNumber ;
    int ifDepth;                  /* Depth of #ifs (C only)*/
    struct cppIfStack *ifStack;   /* #if stack (C only) */
    LexemBuffer lexBuffer;
    StringList *includeDirsPosition;
} FileDescriptor;


extern FileDescriptor currentFile;

extern FileDescriptor includeStack[INCLUDE_STACK_SIZE];
extern int includeStackPointer;


extern void fillFileDescriptor(FileDescriptor *fileDescriptor, char *name, char *bbase, int bsize, FILE *ff, unsigned filepos);

#endif
