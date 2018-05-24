#ifndef MYMATRIX_H
#define MYMATRIX_H

struct matrix {
    int r;
    int c;
    int** data;
};

struct matrix* matrix_mult(struct matrix* matrix1, struct matrix* matrix2);
struct matrix* matrix_add(struct matrix* matrix1, struct matrix* matrix2);

#endif