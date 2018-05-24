//
// Jacob Smith 47118500
//

#ifndef MYMATRIX_H
#define MYMATRIX_H

/**
 * The matrix structure to simplify logic.
 */
struct Matrix {
    int r;
    int c;
    int** data;
};

/**
 * Preforms a matrix multiplication on two given matrices and returns the result. The column count of the first matrix
 * should match the row count of the second matrix.
 *
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 * @return The resulting matrix.
 */
struct Matrix* matrix_mult(struct Matrix* matrix1, struct Matrix* matrix2);

/**
 * Adds the values of two matrices and returns the result in a new matrix. The shapes must match.
 *
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 * @return The resulting matrix.
 */
struct Matrix* matrix_add(struct Matrix* matrix1, struct Matrix* matrix2);

/**
 * Allocates the neccessary memory to the matrix. The row and column values should be initialized.
 *
 * @param matrix The matrix to initialize.
 */
void initializeMatrix(struct Matrix* matrix);

/**
 * Deconstructs a matrix my freeing its memory.
 *
 * @param matrix The matrix to deconstruct.
 */
void deconstructMatrix(struct Matrix* matrix);

#endif