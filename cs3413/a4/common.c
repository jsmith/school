#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

int str2int(char *s) {
  char *end;
  if (s[0] == '\0' || isspace(s[0])) {
    printf("Unable to convert \"%s\" to a string\n", s);
    exit(1);
  }

  errno = 0;
  long l = strtol(s, &end, 10);
  if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX)) {
    printf("Overflow detected \"%s\"\n", s);
    exit(1);
  } else if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN)) {
    printf("Underflow detected \"%s\"\n", s);
    exit(1);
  } else if (*end != '\0') {
    printf("Unable to convert \"%s\" to a string\n", s);
    exit(1);
  }

  return (int)l;
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

void removeNewline(char* s) {
  s[strcspn(s, "\n")] = 0;
}
