//
// Jacob Smith 47118500
//

#include <stdio.h>
#include <stdlib.h>
#include "mymatrix.h"


struct Matrix* matrix_mult(struct Matrix* matrix1, struct Matrix* matrix2) {
    struct Matrix *result = malloc(sizeof(struct Matrix));
    result->r = matrix1->r;
    result->c = matrix2->c;
    initializeMatrix(result);

    for(int i = 0; i < matrix1->r; i++) {
        for(int j = 0; j < matrix2->c; j++) {
            result->data[i][j] = 0;
            for(int index = 0; index < matrix1->c; index++) {
                result->data[i][j] += matrix1->data[i][index] * matrix2->data[index][j];
            }
        }
    }

    return result;
}

struct Matrix* matrix_add(struct Matrix* matrix1, struct Matrix* matrix2) {
    struct Matrix *result = malloc(sizeof(struct Matrix));
    result->r = matrix1->r;
    result->c = matrix1->c;
    initializeMatrix(result);

    for(int i = 0; i < matrix1->r; i++) {
        for(int j = 0; j < matrix1->c; j++) {
            result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
        }
    }

    return result;
}

void initializeMatrix(struct Matrix* matrix) {
    matrix->data = (int**)malloc(sizeof(int*) * matrix->r);
    for(int i = 0; i < matrix->r; i++) {
        matrix->data[i] = (int*)malloc(sizeof(int) * matrix->c);
    }
}

void deconstructMatrix(struct Matrix* matrix) {
    for(int i = 0; i < matrix->r; i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);
}