#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix *fromFile(char* path);
int toFile(Matrix *vector, char* path);
void destruct(Matrix *vector);
int add(Matrix *one, Matrix *two);
int sub(Matrix *one, Matrix *two);

#endif
