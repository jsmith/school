#include <stdio.h>

/**
 * Reads all characters!
 *
 * @param string The location to place the scanned characters.
 * @return The amount of scanned characters!
 */
int scan(char* string) {
    int i = 0;
    while(scanf("%c", &string[i]) == 1) {
        i++;
    }

    return i;
}


int main() {
    char string[100];
    int size = scan(string);
    printf("%d", size);
    return 0;
}
