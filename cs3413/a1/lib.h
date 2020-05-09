#ifndef LIB_H_
#define LIB_H_
#include "list.h"

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
 * Convert string s to int out. Exits if it fails to convert.
 *
 * @param s Input string to be converted.
 * @return The int.
 */
int str2int(char *s);

int min(int a, int b);
int max(int a, int b);

#endif
