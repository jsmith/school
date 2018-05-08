//
// Jacob Smith 3534295
//

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // Read in the previous number first! This assumes that n is > 0.
    double prev;
    scanf("%lf", &prev);

    // Read in the current number, check if the current < prev, then update the previous value if still in order.
    double curr;
    int sorted = 1;
    for(int i = 1; i < n; i++) {
        scanf("%lf", &curr);
        if(curr < prev) {
            sorted = 0;
            break;
        }
        prev = curr;
    }

    if(sorted) {
        printf("The numbers are sorted");
    } else {
        printf("The numbers are not sorted");
    }

    return 0;
}