#ifndef OPTIONS_H
#define OPTIONS_H

#include "stdinc.h"
#include "stdbool.h"

extern void addSourcePathsCut(void);
extern void getXrefrcFileName( char *ttt );
extern char *getJavaHome(void);
extern void getJavaClassAndSourcePath(void);
extern int packageOnCommandLine(char *fn);
extern void getStandardOptions(int *nargc, char ***nargv);
extern char *expandSpecialFilePredefinedVariables_st(char *tt);
extern bool readOptionFromFile(FILE *ff, int *nargc, char ***nargv,
                              int memFl, char *sectionFile, char *project, char *resSection);
extern void readOptionFile(char *name, int *nargc, char ***nargv,char *sectionFile, char *project);
extern void readOptionPipe(char *command, int *nargc, char ***nargv,char *sectionFile);
extern void javaSetSourcePath(int defaultCpAllowed);
extern void getOptionsFromMessage(char *qnxMsgBuff, int *nargc, char ***nargv);
extern int changeRefNumOption(int newRefNum);

#endif
