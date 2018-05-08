//
// Jacob Smith 3534295
//

#include <stdio.h>

int main() {
    int num, base;
    scanf("%d %d", &num, &base);

    // Calculate the size of the integer array for the converted number first
    int div = num;
    int size = 0;
    while(1) {
        div = div / base;
        size++;

        if(div == 0) {
            break;
        }
    }


    int converted[size];  // The converted number stored in a base 10 array
    int found = 0;
    div = num;
    for(int i = 0; i < size; i++) {
        converted[i] = div % base;
        div = div / base;

        // Check all the previous converted numbers for a duplicate. Unsure if this is the most optimal solution for speed.
        for(int j = 0; j < i; j++) {
            if(converted[i] == converted[j]) {
                found = 1;
                break;
            }
        }

        if(found) {
            break;
        }
    }

    if(found) {
        printf("%d base %d has repeated digits", num, base);
    } else {
        printf("%d base %d does not have repeated digits", num, base);
    }

    return 0;
}
