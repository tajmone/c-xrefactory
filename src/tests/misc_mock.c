#include "../misc.h"

#include <cgreen/mocks.h>

void ppcGenSynchroRecord() {
  mock();
}

void ppcIndentOffset() {
  mock();
}

void ppcGenGotoOffsetPosition(char *fname, int offset) {
  mock(fname, offset);
}

void ppcGenRecordBegin(char *kind) {
  mock(kind);
}

void ppcGenRecordWithAttributeBegin(char *kind, char *attr, char *val) {
  mock(kind, attr, val);
}

void ppcGenRecordWithNumAttributeBegin(char *kind, char *attr, int val) {
  mock(kind, attr, val);
}

void ppcGenRecordEnd(char *kind) {
  mock(kind);
}

void ppcGenNumericRecordBegin(char *kind, int val) {
  mock(kind, val);
}

void ppcGenTwoNumericAndRecordBegin(char *kind, char *attr1, int val1, char *attr2, int val2) {
  mock(kind, attr1, val1, attr2, val2);
}

void ppcGenWithNumericAndRecordBegin(char *kind, int val, char *attr, char *attrVal) {
  mock(kind, val, attr, attrVal);
}

void ppcGenAllCompletionsRecordBegin(int nofocus, int len) {
  mock(nofocus, len);
}

void ppcGenTwoNumericsAndrecord(char *kind, char *attr1, int val1, char *attr2, int val2, char *message, char *suff) {
  mock(kind, attr1, val1, attr2, val2, message, suff);
}

void ppcGenRecordWithNumeric(char *kind, char *attr, int val, char *message, char *suff) {
  mock(kind, attr, val, message, suff);
}

void ppcGenNumericRecord(char *kind, int val, char *message, char *suff) {
  mock(kind, val, message, suff);
}

void ppcGenRecord(char *kind, char *message, char *suffix) {
  mock(kind, message, suffix);
}

void ppcGenTmpBuff() {
  mock();
}

void ppcGenDisplaySelectionRecord(char *message, int messageType, int continuation) {
  mock(message, messageType, continuation);
}

void ppcGenGotoMarkerRecord(S_editorMarker *pos) {
  mock(pos);
}

void ppcGenPosition(S_position *p) {
  mock(p);
}

void ppcGenDefinitionNotFoundWarning() {
  mock();
}

void ppcGenDefinitionNotFoundWarningAtBottom() {
  mock();
}

void ppcGenReplaceRecord(char *file, int offset, char *oldName, int oldNameLen, char *newName) {
  mock(file, offset, oldName, oldNameLen, newName);
}

void ppcGenPreCheckRecord(S_editorMarker *pos, int oldLen) {
  mock(pos, oldLen);
}

void ppcGenReferencePreCheckRecord(S_reference *r, char *text) {
  mock(r, text);
}

void ppcGenGotoPositionRecord(S_position *p) {
  mock(p);
}

void ppcGenOffsetPosition(char *fn, int offset) {
  mock(fn, offset);
}

void ppcGenMarker(S_editorMarker *m) {
  mock(m);
}

void jarFileParse() {
  mock();
}

void scanJarFilesForTagSearch() {
  mock();
}

void classFileParse() {
  mock();
}

void fillTrivialSpecialRefItem(S_symbolRefItem *ddd, char *name) {
  mock(ddd, name);
}

int optionsOverflowHandler(int n) {
  return (int) mock(n);
}

int cxMemoryOverflowHandler(int n) {
  return (int) mock(n);
}

void noSuchRecordError(char *rec) {
  mock(rec);
}

void methodAppliedOnNonClass(char *rec) {
  mock(rec);
}

void methodNameNotRecognized(char *rec) {
  mock(rec);
}

void dumpOptions(int nargc, char **nargv) {
  mock(nargc, nargv);
}

void stackMemoryInit() {
  mock();
}

void *stackMemoryAlloc(int size) {
  return (void *) mock(size);
}

void *stackMemoryPush(void *p, int size) {
  return (void *) mock(p, size);
}

int *stackMemoryPushInt(int x) {
  return (int *) mock(x);
}

char *stackMemoryPushString(char *s) {
  return (char *) mock(s);
}

void stackMemoryPop(void *p, int size) {
    mock(p, size);
}

void stackMemoryBlockStart() {
  mock();
}

void stackMemoryBlockFree() {
  mock();
}

void stackMemoryDump() {
  mock();
}

void addToTrail(void (*action)(void *), void *p) {
  mock(action, p);
}

void removeFromTrailUntil(S_freeTrail *untilP) {
  mock(untilP);
}

void symDump(S_symbol *s) {
  mock(s);
}

void symbolRefItemDump(S_symbolRefItem *ss) {
  mock(ss);
}

int javaTypeStringSPrint(char *buff, char *str, int nameStyle, int *oNamePos) {
  return (int) mock(buff, str, nameStyle, oNamePos);
}

void typeSPrint(char *buff, int *size, S_typeModifiers *t, char *name, int dclSepChar, int maxDeep, int typedefexp, int longOrShortName, int *oNamePos) {
  mock(buff, size, t, name, dclSepChar, maxDeep, typedefexp, longOrShortName, oNamePos);
}

void throwsSprintf(char *out, int outsize, S_symbolList *exceptions) {
  mock(out, outsize, exceptions);
}

void macDefSPrintf(char *buff, int *size, char *name1, char *name2, int argn, char **args, int *oNamePos) {
  mock(buff, size, name1, name2, argn, args, oNamePos);
}

char *string3ConcatInStackMem(char *str1, char *str2, char *str3) {
  return (char *) mock(str1, str2, str3);
}

unsigned hashFun(char *s) {
  return (unsigned) mock(s);
}

void javaSignatureSPrint(char *buff, int *size, char *sig, int classstyle) {
  mock(buff, size, sig, classstyle);
}

void fPutDecimal(FILE *f, int n) {
  mock(f, n);
}

char *strmcpy(char *dest, char *src) {
  return (char *) mock(dest, src);
}

char *simpleFileName(char *fullFileName) {
  return (char *) mock(fullFileName);
}

char *directoryName_st(char *fullFileName) {
  return (char *) mock(fullFileName);
}

char *simpleFileNameWithoutSuffix_st(char *fullFileName) {
  return (char *) mock(fullFileName);
}

int containsWildcard(char *ss) {
  return (int) mock(ss);
}

int shellMatch(char *string, int stringLen, char *pattern, int caseSensitive) {
  return (int) mock(string, stringLen, pattern, caseSensitive);
}

void expandWildCharactersInOnePathRec(char *fn, char **outpaths, int *freeolen) {
  mock(fn, outpaths, freeolen);
}

void expandWildCharactersInOnePath(char *fn, char *outpaths, int olen) {
  mock(fn, outpaths, olen);
}

void expandWildCharactersInPaths(char *paths, char *outpaths, int freeolen) {
  mock(paths, outpaths, freeolen);
}

char *getRealFileNameStatic(char *fn) {
  return (char *) mock(fn);
}

int substringIndexWithLimit(char *s, int limit, char *subs) {
  return (int) mock(s, limit, subs);
}

int stringContainsSubstring(char *s, char *subs) {
  return (int) mock(s, subs);
}

void javaGetPackageNameFromSourceFileName(char *src, char *opack) {
  mock(src, opack);
}

void javaGetClassNameFromFileNum(int nn, char *tmpOut, int dotify) {
  mock(nn, tmpOut, dotify);
}

void javaSlashifyDotName(char *ss) {
  mock(ss);
}

void javaDotifyClassName(char *ss) {
  mock(ss);
}

void javaDotifyFileName(char *ss) {
  mock(ss);
}

char *javaGetNudePreTypeName_st(char *inn, int cutMode) {
  return (char *) mock(inn, cutMode);
}

char *javaGetShortClassNameFromFileNum_st(int fnum) {
  return (char *) mock(fnum);
}

int substringIndex(char *s, char *subs) {
  return (int) mock(s, subs);
}

int stringEndsBySuffix(char *s, char *suffix) {
  return (int) mock(s, suffix);
}

int fileNameHasOneOfSuffixes(char *fname, char *suffs) {
  return (int) mock(fname, suffs);
}

int mapPatternFiles(char *pattern, void (*fun)(char *file, char *a1, char *a2, S_completions *a3, void *a4, int *a5), char *a1, char *a2, S_completions *a3, void *a4, int *a5) {
  return (int) mock(pattern, fun, a1, a2, a3, a4, a5);
}

int mapDirectoryFiles(char *dirname, void (*fun)(char *file, char *a1, char *a2, S_completions *a3, void *a4, int *a5), int allowEditorFilesFlag, char *a1, char *a2, S_completions *a3, void *a4, int *a5) {
  return (int) mock(dirname, fun, allowEditorFilesFlag, a1, a2, a3, a4, a5);
}

void javaMapDirectoryFiles1(char *packfile, void (*fun)(char *file, char *a1, char *a2, S_completions *a3, void *a4, int *a5), S_completions *a1, void *a2, int *a3) {
  mock(packfile, fun, a1, a2, a3);
}

void javaMapDirectoryFiles2(S_idIdentList *packid, void (*fun)(char *file, char *a1, char *a2, S_completions *a3, void *a4, int *a5), S_completions *a1, void *a2, int *a3) {
  mock(packid, fun, a1, a2, a3);
}

char *lastOccurenceInString(char *ss, int ch) {
  return (char *) mock(ss, ch);
}

char *lastOccurenceOfSlashOrAntiSlash(char *ss) {
  return (char *) mock(ss);
}

char *getFileSuffix(char *fn) {
  return (char *) mock(fn);
}

char *javaCutClassPathFromFileName(char *fname) {
  return (char *) mock(fname);
}

char *javaCutSourcePathFromFileName(char *fname) {
  return (char *) mock(fname);
}

int pathncmp(char *ss1, char *ss2, int n, int caseSensitive) {
  return (int) mock(ss1, ss2, n, caseSensitive);
}

int fnCmp(char *ss1, char *ss2) {
  return (int) mock(ss1, ss2);
}

int fnnCmp(char *ss1, char *ss2, int n) {
  return (int) mock(ss1, ss2, n);
}

void linkNamePrettyPrint(char *ff, char *javaLinkName, int maxlen, int argsStyle) {
  mock(ff, javaLinkName, maxlen, argsStyle);
}

char *simpleFileNameFromFileNum(int fnum) {
  return (char *) mock(fnum);
}

char *getShortClassNameFromClassNum_st(int fnum) {
  return (char *) mock(fnum);
}

void printSymbolLinkNameString(FILE *ff, char *linkName) {
  mock(ff, linkName);
}

void printClassFqtNameFromClassNum(FILE *ff, int fnum) {
  mock(ff, fnum);
}

void sprintfSymbolLinkName(char *ttt, S_olSymbolsMenu *ss) {
  mock(ttt, ss);
}

void printSymbolLinkName(FILE *ff, S_olSymbolsMenu *ss) {
  mock(ff, ss);
}
