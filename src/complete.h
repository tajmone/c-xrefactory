#ifndef COMPLETE_H
#define COMPLETE_H

#include "proto.h"

extern void processName(char *name, S_cline *t, int orderFlag, void *c);
extern void completeForSpecial1(S_completions*);
extern void completeForSpecial2(S_completions*);
extern void completeUpFunProfile(S_completions* c);
extern void completeTypes(S_completions*);
extern void completeStructs(S_completions*);
extern void completeRecNames(S_completions*);
extern void completeEnums(S_completions*);
extern void completeLabels(S_completions*);
extern void completeMacros(S_completions*c);
extern void completeOthers(S_completions*);
extern void javaCompleteTypeSingleName(S_completions*);
extern void javaHintImportFqt(S_completions*c);
extern void javaHintVariableName(S_completions*c);
extern void javaHintCompleteNonImportedTypes(S_completions*c);
extern void javaHintCompleteMethodParameters(S_completions *c);
extern void javaCompleteTypeCompName(S_completions*);
extern void javaCompleteThisPackageName(S_completions*c);
extern void javaCompletePackageSingleName(S_completions*);
extern void javaCompleteExprSingleName(S_completions*);
extern void javaCompleteUpMethodSingleName(S_completions*);
extern void javaCompleteFullInheritedMethodHeader(S_completions*c);
extern void javaCompletePackageCompName(S_completions*);
extern void javaCompleteExprCompName(S_completions*);
extern void javaCompleteMethodCompName(S_completions*);
extern void javaCompleteHintForConstructSingleName(S_completions *c);
extern void javaCompleteConstructSingleName(S_completions*c);
extern void javaCompleteConstructCompName(S_completions*c);
extern void javaCompleteConstructNestNameName(S_completions*c);
extern void javaCompleteConstructNestPrimName(S_completions*c);
extern void javaCompleteStrRecordPrimary(S_completions*c);
extern void javaCompleteStrRecordSuper(S_completions*c);
extern void javaCompleteStrRecordQualifiedSuper(S_completions*c);
extern void javaCompleteClassDefinitionNameSpecial(S_completions*c);
extern void javaCompleteClassDefinitionName(S_completions*c);
extern void javaCompleteThisConstructor(S_completions*c);
extern void javaCompleteSuperConstructor(S_completions*c);
extern void javaCompleteSuperNestedConstructor(S_completions*c);
extern void completeYaccLexem(S_completions*c);
extern char *javaGetShortClassName( char *inn);
extern char *javaGetShortClassNameFromFileNum_st(int fnum);
extern char *javaGetNudePreTypeName_st( char *inn, int cutMode);

extern void olCompletionListInit(S_position *originalPos);
extern void formatOutputLine(char *tt, int startingColumn);
extern void printCompletionsList(int noFocus);
extern void printCompletions(S_completions*c);

#endif
