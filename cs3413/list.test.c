#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include <assert.h>

void testIntArray() {
  IntArray *a = initIntArray(10);
  assert(a->size == 10);
  appendIntArray(a, 5);
  assert(a->array[0] == 5);
  freeIntArray(a);
}

void testStringArray() {
  StringArray *a = initStringArray(10);
  assert(a->size == 10);
  appendStringArray(a, "JACOB");
  assert(!strcmp(a->array[0], "JACOB"));
  freeStringArray(a);
}

int main() {
  testIntArray();
  testStringArray();
}
