#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
public:
    /**
     * @brief Default constructor. Initializes a 1x1 matrix.
     */
    Matrix() : Matrix(1, 1) {}

    /**
     * @brief Constructor that initializes a matrix with given dimensions.
     * 
     * @param rows Number of rows.
     * @param cols Number of columns.
     */
    Matrix(int rows, int cols);

    /**
     * @brief Copy constructor.
     * 
     * @param mat Matrix to copy from.
     */
    Matrix(const Matrix &mat);

    /**
     * @brief Destructor to free allocated memory.
     */
    ~Matrix();

    /**
     * @brief Get the number of rows in the matrix.
     * 
     * @return Number of rows.
     */
    int get_rows() const {
        return _matrixDims.rows;
    }

    /**
     * @brief Get the number of columns in the matrix.
     * 
     * @return Number of columns.
     */
    int get_cols() const {
        return _matrixDims.cols;
    }

    /**
     * @brief Transpose the matrix.
     * 
     * @return Reference to the transposed matrix.
     */
    Matrix &transpose();

    /**
     * @brief Reshape the matrix into a vector.
     * 
     * @return Reference to the vectorized matrix.
     */
    Matrix &vectorize();

    /**
     * @brief Print the matrix elements.
     */
    void plain_print() const;

    /**
     * @brief Compute the element-wise product (Hadamard product) with another matrix.
     * 
     * @param mat Matrix to multiply with.
     * @return Resulting matrix after element-wise multiplication.
     */
    Matrix dot(const Matrix &mat) const;

    /**
     * @brief Compute the Frobenius norm of the matrix.
     * 
     * @return The norm of the matrix.
     */
    float norm() const;

    /**
     * @brief Add another matrix to this matrix.
     * 
     * @param mat Matrix to add.
     * @return Resulting matrix after addition.
     */
    Matrix operator+(const Matrix &mat) const;

    /**
     * @brief Assignment operator.
     * 
     * @param mat Matrix to assign from.
     * @return Reference to this matrix.
     */
    Matrix &operator=(const Matrix &mat);

    /**
     * @brief Multiply this matrix with another matrix.
     * 
     * @param mat Matrix to multiply with.
     * @return Resulting matrix after multiplication.
     */
    Matrix operator*(const Matrix &mat) const;

    /**
     * @brief Add another matrix to this matrix in-place.
     * 
     * @param mat Matrix to add.
     * @return Reference to this matrix after addition.
     */
    Matrix &operator+=(const Matrix &mat);

    /**
     * @brief Element access (const) using row and column indices.
     * 
     * @param row Row index.
     * @param col Column index.
     * @return Element at the specified position.
     */
    float operator()(int row, int col) const;

    /**
     * @brief Element access using row and column indices.
     * 
     * @param row Row index.
     * @param col Column index.
     * @return Reference to the element at the specified position.
     */
    float &operator()(int row, int col);

    /**
     * @brief Element access (const) using a single index (row-major order).
     * 
     * @param index Index.
     * @return Element at the specified position.
     */
    float operator[](int index) const;

    /**
     * @brief Element access using a single index (row-major order).
     * 
     * @param index Index.
     * @return Reference to the element at the specified position.
     */
    float &operator[](int index);

    /**
     * @brief Output stream operator for printing the matrix.
     * 
     * @param os Output stream.
     * @param mat Matrix to print.
     * @return Reference to the output stream.
     */
    friend ostream &operator<<(ostream &os, const Matrix &mat);

    /**
     * @brief Input stream operator for reading matrix elements.
     * 
     * @param is Input stream.
     * @param mat Matrix to read into.
     * @return Reference to the input stream.
     */
    friend istream &operator>>(istream &is, Matrix &mat);

private:
    float **_matrix;         ///< Pointer to the matrix elements.
    matrix_dims _matrixDims; ///< Dimensions of the matrix.
};

/**
 * @brief Scalar multiplication (float * Matrix).
 * 
     * @param scalar The scalar value to multiply.
     * @param mat The matrix to multiply.
     * @return The resulting matrix after scalar multiplication.
     */
Matrix operator*(float scalar, const Matrix &mat);

/**
 * @brief Scalar multiplication (Matrix * float).
 * 
 * @param mat The matrix to multiply.
 * @param scalar The scalar value to multiply.
 * @return The resulting matrix after scalar multiplication.
 */
Matrix operator*(const Matrix &mat, float scalar);

#endif // MATRIX_H

