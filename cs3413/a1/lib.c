#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "lib.h"
#include "list.h"

bool file_exist(char *fileName) {
  if (access(fileName, F_OK ) != -1) {
    return true;
  } else {
    return false;
  }
}

ReadResult *readFile(char* fileName) {
  ReadResult *s = malloc(sizeof *s);
  if (!file_exist(fileName)) {
    s->status = READ_RESULT_NOT_FOUND;
    return s;
  }

  FILE* file = fopen(fileName, "r");
  if (!file) {
    s->status = READ_RESULT_ERROR;
    return s;
  }

  s->status = READ_RESULT_SUCCESS;

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = malloc(length);
  fread(buffer, 1, length, file);
  fclose(file);

  s->contents = buffer;

  return s;
}

void freeReadResult(ReadResult* readResult) {
  free(readResult->contents);
  // free(readResult->result);
  free(readResult);
}

StringArray* split(char* target, char c) {
  StringArray* a = initStringArray(10);
  char* pch = strtok(target, &c);
  while (pch != NULL) {
    appendStringArray(a, pch);
    pch = strtok(NULL, &c);
  }

  return a;
}

CharArray* readFromStdin() {
  char ch;
  CharArray *a = initCharArray(10);
  while(read(STDIN_FILENO, &ch, 1) > 0) {
    appendCharArray(a, ch);
  }

  // Not sure if a null terminator is added by default
  appendCharArray(a, '\0');

  return a;
}

StringToIntError str2int(int *out, char *s, int base) {
  char *end;
  if (s[0] == '\0' || isspace(s[0])) {
    return STR2INT_INCONVERTIBLE;
  }

  errno = 0;
  long l = strtol(s, &end, base);
  /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
  if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX)) {
    return STR2INT_OVERFLOW;
  } else if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN)) {
    return STR2INT_UNDERFLOW;
  } else if (*end != '\0') {
    return STR2INT_INCONVERTIBLE;
  }

  *out = l;
  return STR2INT_SUCCESS;
}

int min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}
