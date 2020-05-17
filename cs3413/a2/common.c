//
// Created by Jacob Smith on 2020-05-16.
//
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

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