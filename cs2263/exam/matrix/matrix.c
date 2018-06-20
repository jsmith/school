#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix *fromFile(char* path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    int rows, cols;
    if(fscanf(file, "%d %d", &rows, &cols) != 2) { // NOLINT
        return NULL;
    }

    int **data = malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        data[i] = malloc(sizeof(int) * cols);
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%d", &data[i][j]) == 0) { // NOLINT
                for (;i >= 0; i--) {
                    free(data[i]);
                }
                free(data);
                return NULL;
            }
        }
    }

    fclose(file);

    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = data;

    return matrix;
}

int toFile(Matrix *vector, char* path) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "%d %d\n", vector->rows, vector->cols);

    for (int i = 0; i < vector->rows; i++) {
        for (int j = 0; j < vector->cols - 1; j++) {
            fprintf(file, "%d ", vector->data[i][j]);
        }
        fprintf(file, "%d\n", vector->data[i][vector->cols - 1]);
    }
    fclose(file);

    return 1;
}

void destruct(Matrix *vector) {
    for (int i = 0; i < vector->rows; i++) {
        free(vector->data[i]);
    }
    free(vector->data);
    free(vector);
}

int compatible(Matrix *one, Matrix *two) {
    return one->rows == two->rows && one->cols == two->cols;
}

int add(Matrix *one, Matrix *two) {
    if(!compatible(one, two)) {
        return 0;
    }

    for (int i = 0; i < one->rows; i++) {
        for (int j = 0; j < one->cols; j++) {
            one->data[i][j] += two->data[i][j];
        }
    }

    return 1;
}

int sub(Matrix *one, Matrix *two) {
    if(!compatible(one, two)) {
        return 0;
    }

    for (int i = 0; i < one->rows; i++) {
        for (int j = 0; j < one->cols; j++) {
            one->data[i][j] -= two->data[i][j];
        }
    }

    return 1;
}