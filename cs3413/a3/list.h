#ifndef LIST_H_
#define LIST_H_

/**
 * Nice utility array types for strings, chars and ints. These all use techniques
 * to dynamically resize while maintaining a O(1) append time.
 */

typedef struct {
  int* array;
  int used;
  int size;
} IntArray;

IntArray* initIntArray(int initialSize);
void appendIntArray(IntArray *a, int element);
void freeIntArray(IntArray *a);

typedef struct {
  char** array;
  int used;
  int size;
} StringArray;

StringArray* initStringArray(int initialSize);
void appendStringArray(StringArray *a, char* element);
void freeStringArray(StringArray *a);

typedef struct {
  char* array;
  int used;
  int size;
} CharArray;

CharArray* initCharArray(int initialSize);
void appendCharArray(CharArray *a, char element);
void freeCharArray(CharArray *a);

#endif
