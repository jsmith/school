
#include "list.h"
#include <stdlib.h>

IntArray* initIntArray(int initialSize) {
  IntArray *a = malloc(sizeof *a);
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
  return a;
}

void appendIntArray(IntArray *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int*)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeIntArray(IntArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

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

CharArray* initCharArray(int initialSize) {
  CharArray *a = malloc(sizeof *a);
  a->array = malloc(initialSize * sizeof(char*));
  a->used = 0;
  a->size = initialSize;
  return a;
}

void appendCharArray(CharArray *a, char element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char*));
  }
  a->array[a->used++] = element;
}

void freeCharArray(CharArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
