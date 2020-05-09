#ifndef LIB_H_
#define LIB_H_
#include "list.h"

typedef enum {
  STR2INT_SUCCESS,
  STR2INT_OVERFLOW,
  STR2INT_UNDERFLOW,
  STR2INT_INCONVERTIBLE
} StringToIntError;

typedef enum {
  READ_RESULT_SUCCESS,
  READ_RESULT_ERROR,
  READ_RESULT_NOT_FOUND,
} ReadResultStatus;

typedef struct ReadResult {
  ReadResultStatus status;
  // Only defined when result == "succes"
  char* contents;
} ReadResult;

ReadResult *readFile(char* fileName);
void freeReadResult(ReadResult* readResult);
StringArray* split(char* target, char c);
CharArray* readFromStdin();

/*
 * Convert string s to int out.
 *
 * @param out The converted int. Cannot be NULL.
 * @param s Input string to be converted.
 * @param base Base to interpret string in. Same range as strtol (2 to 36).
 * @return Indicates if the operation succeeded, or why it failed.
 */
StringToIntError str2int(int *out, char *s, int base);

int min(int a, int b);
int max(int a, int b);

#endif
