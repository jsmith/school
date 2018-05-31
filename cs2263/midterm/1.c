#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int function() {
  int a = 5;
  return a;
}

int length(char *s){
  char *p = s; //warning if p not const
  for(; *p ;p++);
  return p - s;
}

void print(int* arr, int n) {
  for(int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  printf("helloworld\n");

  // formatting float
  float f = 0.1;
  printf("%f\n", f);

  // int d;
  // char c;
  // while(1) {
  //   scanf("%d%c", &d, &c);
  //   printf("Scanned: %d\n", d);
  //   printf("This is a test @ scanf! %d\n", d);
  //   if(c == '\n') {
  //     break;
  //   }
  // }

  // test fgets
  int test[5];
  test[0] = 56;
  int *temp = test;

  printf("Printing pointer value: %d\n", *temp);
  printf("Printing pointer value with index: %d\n", temp[55]);
  printf("Calling function: %d\n", function());

  char *a ="One", *b="Two";
  printf("%s vs %s: %s\n", a, b, strcmp(a, b) ? "False" : "True");

  a = "0123456789 \t\na";
  printf("The length of %s is %d\n", a, length(a));
  int index = strstr(a, "8") - a;
  printf("8 can be found in the %dth index\n", index);

  int *malloced = malloc(sizeof(int)*5);
  malloced[0] = 0;
  malloced[1] = 1;
  malloced[2] = 2;
  malloced[3] = 3;
  malloced[4] = 666;
  print(malloced, 10);
  free(malloced);
}
