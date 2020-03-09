#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "lib.h"
#include "list.h"

void testReadFileNonExistentFile() {
  ReadResult *s = readFile("assets/sdkfldskjflskd.txt");
  assert(!strcmp(s->result, "not-found"));
  freeReadResult(s);
}

void testReadFileCorrectlyReadsContents() {
  ReadResult *s = readFile("assets/lib.txt");
  assert(!strcmp(s->result, "success"));
  assert(!strcmp(s->contents, "My \nName\nIs\nJacob"));
  freeReadResult(s);
}

void testSplit() {
  char s[] = "My  Name IS       Jacob";
  StringArray* a = split(s, ' ');
  assert(a->used == 4);
  assert(!strcmp(a->array[0], "My"));
  assert(!strcmp(a->array[1], "Name"));
  assert(!strcmp(a->array[2], "IS"));
  assert(!strcmp(a->array[3], "Jacob"));
  freeStringArray(a);
}

int main() {
  testReadFileNonExistentFile();
  testReadFileCorrectlyReadsContents();
  testSplit();
}
