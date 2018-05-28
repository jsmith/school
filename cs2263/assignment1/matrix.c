//
// Jacob Smith 47118500
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymatrix.h"
#define MULTIPLY "multiplication"
#define ADD "addition"

/**
 * Allocates and reads in a matrix.
 *
 * @param m The matrix.
 */
void readMatrix(struct Matrix *m) {
    scanf("%d %d", &m->r, &m->c);
    initializeMatrix(m);
    for(int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            scanf("%d", &(m->data[i][j]));
        }
    }
}

/**
 * Writes a matrix in the specified format.
 *
 * @param m The matrix.
 */
void writeMatrix(struct Matrix* m) {
    printf("%d %d\n", m->r, m->c);
    for (int i = 0; i < m->r; i++) {
        for (int j = 0; j < (m->c - 1); j++) {
            printf("%d ", m->data[i][j]);
        }
        printf("%d\n", m->data[i][m->c - 1]); // write a newline at the end of the columns
    }
}

int main(int argc, char *argv[]) {
    char command[20];
    scanf("%s", command);
    if(strcmp(command, MULTIPLY) != 0 && strcmp(command, ADD) != 0) {
        printf("The command must be either %s or %s. %s is invalid!\n", MULTIPLY, ADD, command);
        exit(1);
    }

    struct Matrix m1;
    readMatrix(&m1);

    struct Matrix m2;
    readMatrix(&m2);


    // Here we check the command and validate the input data. I would usually do that in a function; however, c does
    // not support error handling so it's easiest to validate the data before it is given to the function. This way
    // we can still free the other memory we've allocated.
    struct Matrix* result;
    int result_initialized = 0;
    if(!strcmp(command, MULTIPLY)) {
        if(m1.c != m2.r) {
            printf("The column count of the first should equal the row count of the second: %d vs %d\n", m1.c, m2.r);
        } else {
            result = matrix_mult(&m1, &m2);
            result_initialized = 1;
        }
    } else {
        if(m1.r != m2.r) {
            printf("The row count of the first should equal the row count of the second: %d vs %d\n", m1.r, m2.r);
        } else if(m1.c != m2.c) {
            printf("The column count of the first should equal the column count of the second: %d vs %d\n", m1.c, m2.c);
        } else {
            result = matrix_add(&m1, &m2);
            result_initialized = 1;
        }
    }

    deconstructMatrix(&m1);
    deconstructMatrix(&m2);

    // Only free if we've actually allocated memory!
    if(result_initialized) {
        writeMatrix(result);

        deconstructMatrix(result);
        free(result);
    }
}