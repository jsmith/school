#include <stdio.h>

int function() {
  int a = 5;
  return a;
}

int main() {
  printf("helloworld\n");

  // formatting float
  float f = 0.1;
  printf("%f\n", f);

  int d;
  char c;
  while(1) {
    scanf("%d%c", &d, &c);
    printf("Scanned: %d\n", d);
    printf("This is a test @ scanf! %d\n", d);
    if(c == '\n') {
      break;
    }
  }

  // test fgets
  int test[5];
  test[0] = 56;
  int *temp = test;

  printf("Printing pointer value: %d\n", *temp);
  printf("Printing pointer value with index: %d\n", temp[55]);
  printf("Calling function: %d\n", function());
}
