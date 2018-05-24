#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymatrix.h"
#define MULTIPLY "multiplication"
#define ADD "addition"

void initializeArray(struct matrix* m, FILE* fp) {
    fscanf(fp, "%d %d", &m->r, &m->c);
    m->data = (int**)malloc(sizeof(int*) * m->r);

    for(int i = 0; i < m->r; i++) {
        m->data[i] = (int*)malloc(sizeof(int) * m->c);

        for(int j = 0; j < m->c; j++) {
            fscanf(fp, "%d", &(m->data[i][j]));
        }
    }
}

void deconstructMatrix(struct matrix* m) {
    for(int i = 0; i < m->r; i++) {
        free(m->data[i]);
    }

    free(m->data);
}

void writeMatrix(struct matrix* m, FILE* fp) {
    fprintf(fp, "%d %d\n", m->r, m->c);
    for(int i = 0; i < m->r; i++) {
        for(int j = 0; j < (m->c-1); j++) {
            fprintf(fp, "%d ", m->data[i][j]);
        }
        fprintf(fp, "%d\n", m->data[i][m->c-1]); // don't write a space at the end of the columns
    }
}

void open(FILE** fp, char* file, char* code) {
    if(((*fp) = fopen(file, code)) == NULL) {
        printf("Input file %s does not exist\n", file);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Expected three arguments from the command line. Ex. `matrix multiplication input.txt output.txt`");
        exit(1);
    }

    char *command = argv[1];
    if(strcmp(command, MULTIPLY) != 0 && strcmp(command, ADD) != 0) {
        printf("The first command must be either %s or %s. %s is invalid!\n", MULTIPLY, ADD, command);
        exit(1);
    }

    char *input = argv[2];
    char *output = argv[3];
    printf("Reading from %s and outputting results to %s\n", input, output);

    FILE *fp;
    open(&fp, input, "r");

    struct matrix m1;
    initializeArray(&m1, fp);

    struct matrix m2;
    initializeArray(&m2, fp);
    fclose(fp);


    int end_r, end_c;
    struct matrix* result;
    if(!strcmp(command, MULTIPLY)) {
        result = matrix_mult(&m1, &m2);
    } else {
        result = matrix_add(&m1, &m2);
    }


    open(&fp, output, "w+"); // overwrite file with w+
    writeMatrix(result, fp);
    fclose(fp);

    deconstructMatrix(&m1);
    deconstructMatrix(&m2);
    deconstructMatrix(result);
    free(result);
}