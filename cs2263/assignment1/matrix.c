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
 * @param fp The file object.
 */
void readMatrix(struct Matrix *m, FILE *fp) {
    fscanf(fp, "%d %d", &m->r, &m->c);
    initializeMatrix(m);
    for(int i = 0; i < m->r; i++) {
        for (int j = 0; j < m->c; j++) {
            fscanf(fp, "%d", &(m->data[i][j]));
        }
    }
}

/**
 * Writes a matrix to a file in the specified format.
 *
 * @param m The matrix.
 * @param fp The file object.
 */
void writeMatrix(struct Matrix* m, FILE* fp) {
    fprintf(fp, "%d %d\n", m->r, m->c);
    for(int i = 0; i < m->r; i++) {
        for(int j = 0; j < (m->c-1); j++) {
            fprintf(fp, "%d ", m->data[i][j]);
        }
        fprintf(fp, "%d\n", m->data[i][m->c-1]); // don't write a space at the end of the columns
    }
}

/**
 * Opens a file and exits if an error occurs.
 *
 * @param fp The file pointer to place the file.
 * @param file The file name to read in.
 * @param code The code to use when opening the file.
 */
void open(FILE** fp, char* file, char* code) {
    if(((*fp) = fopen(file, code)) == NULL) {
        printf("Input file %s does not exist\n", file);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Expected three arguments from the command line. Ex. `matrix multiplication input0.txt output.txt`");
        exit(1);
    }

    char *command = argv[1];
    if(strcmp(command, MULTIPLY) != 0 && strcmp(command, ADD) != 0) {
        printf("The first command must be either %s or %s. %s is invalid!\n", MULTIPLY, ADD, command);
        exit(1);
    } else {
        printf("Running the %s command!\n", command);
    }

    char *input = argv[2];
    char *output = argv[3];
    printf("Reading from %s and outputting results to %s\n", input, output);

    FILE *fp;
    open(&fp, input, "r");

    struct Matrix m1;
    readMatrix(&m1, fp);

    struct Matrix m2;
    readMatrix(&m2, fp);
    fclose(fp);


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
        open(&fp, output, "w+"); // overwrite file with w+
        writeMatrix(result, fp);
        fclose(fp);

        deconstructMatrix(result);
        free(result);
    }
}