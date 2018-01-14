#include "../commons.h"

#include <cgreen/mocks.h>

void initCwd(void) {
  mock();
}

void reInitCwd(char *dffname, char *dffsect) {
  mock(dffname, dffsect);
}

void emergencyExit(int exitStatus) {
  mock(exitStatus);
}

void warning(int kod, char *sprava) {
  mock(kod, sprava);
}

void error(int kod, char *sprava) {
  mock(kod, sprava);
}

void fatalError(int kod, char *sprava, int exitCode) {
  mock(kod, sprava, exitCode);
}

void internalCheckFail(char *expr, char *file, int line) {
  mock(expr, file, line);
}

char *create_temporary_filename() {
  return (char *) mock();
}

char *normalizeFileName(char *name, char *relativeto) {
  return (char *) mock(name, relativeto);
}

void copyFile(char *src, char *dest) {
  mock(src, dest);
}

void createDir(char *dirname) {
  mock(dirname);
}

void copyDir(char *dest, char *s, int *i) {
  mock(dest, s, i);
}

void removeFile(char *dirname) {
  mock(dirname);
}
