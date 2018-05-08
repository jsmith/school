//
// Jacob Smith 3534295
//


#include <stdio.h>

/**
 * Swaps two int pointers.
 *
 * @param a The first number!
 * @param b The second number!
 */
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    swap(&a, &b);
    printf("%d %d", a, b);
    return 0;
}
