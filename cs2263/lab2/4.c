//
// Jacob Smith 3534295
// Raven-Lee Mills 3564447
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Adds a space if necessary.
 *
 * @param representation
 */
void add_space(char* representation) {
    if(*representation) {
        strcat(representation, " ");
    }
}

int main() {

    char* sing[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char* special[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char* doub[] = {"nothing", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    char representation[1000] = "";

    // Scan into a long, check if out of bounds then cast to an int
    int num;
    long n;
    scanf("%lu", &n);
    if(n > 2000000000 || n < -2000000000) {
        return 1;
    }
    num = (int)n;

    if(num < 0) {
        strcat(representation, "minus");
        num = abs(num);
    }

    // Edge case for 0
    if(num == 0) {
        printf("%s", sing[0]);
    }

    // Split number into its components to easy access
    int nums[15] = {0};
    int count = 0;
    while(num) {
        nums[count] = num % 10;
        num /= 10;
        count++;
    }

    // Initialize char array for sprintf
    char s[10];

    char* names[] = {"", "thousand",  "million", "billion"};
    for(int i = 9; i >= 0; i-=3) {

        // flag variable to see if we should add a name at the end (ex. thousand, million)
        int added_num = 0;

        // Add the hundred (ex. one hundred)
        if (nums[i+2]){
            sprintf(s, "%s", sing[nums[i+2]]);
            add_space(representation);
            strcat(representation, s);
            strcat(representation, " hundred");
            added_num = 1;
        }

        if(nums[i+1] == 1) {
            // This is the special case when the decimal is one (ex. fourteen, eleven)
            add_space(representation);
            sprintf(s, "%s", special[nums[i]]);
            strcat(representation, s);
            added_num = 1;

        } else {
            // Add the decimal (ex. twenty, ninety)
            if(nums[i+1]) {
                add_space(representation);
                sprintf(s, "%s", doub[nums[i+1]]);
                strcat(representation, s);
                added_num = 1;

            }

            // Add the single digit (ex. two, four)
            if(nums[i]) {
                add_space(representation);
                sprintf(s, "%s", sing[nums[i]]);
                strcat(representation, s);
                added_num = 1;
            }
        }

        if(added_num) {
            char* name = names[(i / 3)];

            if(name != "") {
                add_space(representation);
                strcat(representation, name);
            }
        }
    }

    printf("%s", representation);
    return 0;
}

