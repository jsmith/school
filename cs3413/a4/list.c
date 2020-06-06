
#include "list.h"
#include <stdlib.h>

StringArray* initStringArray(int initialSize) {
  StringArray *a = malloc(sizeof *a);
  a->array = malloc(initialSize * sizeof(char**));
  a->used = 0;
  a->size = initialSize;
  return a;
}

void appendStringArray(StringArray *a, char* element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char**));
  }
  a->array[a->used++] = element;
}

void freeStringArray(StringArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
