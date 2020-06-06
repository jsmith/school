#ifndef LIST_H_
#define LIST_H_

typedef struct {
  char** array;
  int used;
  int size;
} StringArray;

StringArray* initStringArray(int initialSize);
void appendStringArray(StringArray *a, char* element);
void freeStringArray(StringArray *a);

#endif
