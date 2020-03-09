#ifndef LIB_H_
#define LIB_H_
#include "list.h"

typedef enum {
  STR2INT_SUCCESS,
  STR2INT_OVERFLOW,
  STR2INT_UNDERFLOW,
  STR2INT_INCONVERTIBLE
} StrintToIntError;

typedef struct ReadResult {
  // "success" | "error" | "not-found"
  char* result;
  // Only defined when result == "succes"
  char* contents;
} ReadResult;

ReadResult *readFile(char* fileName);
void freeReadResult(ReadResult* readResult);
StringArray* split(char* target, char c);
CharArray* readFromStdin();
StrintToIntError str2int(int *out, char *s, int base);
int min(int a, int b);
int max(int a, int b);

#endif
