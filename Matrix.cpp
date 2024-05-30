#include "Matrix.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define INDEX_BOUND 1
#define SPACE " "
#define NEW_LINE "\n"
#define ASTERISKS "**"
#define INVALID_LENGTH throw length_error("either row or column input is invalid.");
#define INVALID_INPUT throw runtime_error("Invalid Input");
#define PROB_FLAG 0.1

/**
 * @brief Checks if the given dimensions are valid (greater than or equal to 1).
 *
 * @param rows Number of rows.
 * @param cols Number of columns.
 * @return 1 if valid, 0 otherwise.
 */
int is_scales_compatible(int rows, int cols) {
    return (rows >= INDEX_BOUND && cols >= INDEX_BOUND) ? 1 : 0;
}

/**
 * @brief Constructor that initializes a matrix with given dimensions.
 *
 * @param rows Number of rows.
 * @param cols Number of columns.
 */
Matrix::Matrix(int rows, int cols) {
    if (!is_scales_compatible(rows, cols)) {
        INVALID_LENGTH
    }
    _matrixDims.rows = rows;
    _matrixDims.cols = cols;
    _matrix = new float *[rows];
    for (int i = 0; i < rows; i++) {
        _matrix[i] = new float[cols]();
    }
}

/**
 * @brief Copy constructor.
 *
 * @param mat Matrix to copy from.
 */
Matrix::Matrix(const Matrix &mat) : Matrix(mat.get_rows(), mat.get_cols()) {
    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            _matrix[i][j] = mat._matrix[i][j];
        }
    }
}

/**
 * @brief Transpose the matrix.
 *
 * @return Reference to the transposed matrix.
 */
Matrix &Matrix::transpose() {
    float **temp_arr = new float *[_matrixDims.cols];
    for (int i = 0; i < _matrixDims.cols; i++) {
        temp_arr[i] = new float[_matrixDims.rows];
        for (int j = 0; j < _matrixDims.rows; j++) {
            temp_arr[i][j] = _matrix[j][i];
        }
    }
    swap(_matrixDims.rows, _matrixDims.cols);
    _matrix = temp_arr;
    return *this;
}

/**
 * @brief Reshape the matrix into a vector.
 *
 * @return Reference to the vectorized matrix.
 */
Matrix &Matrix::vectorize() {
    float **temp_arr = new float *[_matrixDims.rows * _matrixDims.cols];
    for (int i = 0; i < _matrixDims.rows * _matrixDims.cols; i++) {
        temp_arr[i] = new float[1];
        temp_arr[i][0] = (*this)[i];
    }
    _matrixDims.rows = _matrixDims.rows * _matrixDims.cols;
    _matrixDims.cols = 1;
    _matrix = temp_arr;
    return *this;
}

/**
 * @brief Print the matrix elements.
 */
void Matrix::plain_print() const {
    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            cout << _matrix[i][j] << SPACE;
        }
        cout << NEW_LINE;
    }
}

/**
 * @brief Compute the element-wise product (Hadamard product) with another matrix.
 *
 * @param mat Matrix to multiply with.
 * @return Resulting matrix after element-wise multiplication.
 */
Matrix Matrix::dot(const Matrix &mat) const {
    if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols) {
        INVALID_LENGTH
    }
    Matrix result(_matrixDims.rows, _matrixDims.cols);
    for (int i = 0; i < _matrixDims.rows * _matrixDims.cols; i++) {
        result[i] = (*this)[i] * mat[i];
    }
    return result;
}

/**
 * @brief Compute the Frobenius norm of the matrix.
 *
 * @return The norm of the matrix.
 */
float Matrix::norm() const {
    double matrix_sum = 0;
    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            matrix_sum += pow(_matrix[i][j], 2);
        }
    }
    return static_cast<float>(sqrt(matrix_sum));
}

/**
 * @brief Add another matrix to this matrix.
 *
 * @param mat Matrix to add.
 * @return Resulting matrix after addition.
 */
Matrix Matrix::operator+(const Matrix &mat) const {
    if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols) {
        INVALID_LENGTH
    }
    Matrix result(_matrixDims.rows, _matrixDims.cols);
    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            result._matrix[i][j] = _matrix[i][j] + mat._matrix[i][j];
        }
    }
    return result;
}

/**
 * @brief Assignment operator.
 *
 * @param mat Matrix to assign from.
 * @return Reference to this matrix.
 */
Matrix &Matrix::operator=(const Matrix &mat) {
    if (this == &mat) {
        return *this;
    }

    if (_matrixDims.rows != mat.get_rows() || _matrixDims.cols != mat.get_cols()) {
        for (int i = 0; i < _matrixDims.rows; i++) {
            delete[] _matrix[i];
        }
        delete[] _matrix;

        _matrixDims.rows = mat.get_rows();
        _matrixDims.cols = mat.get_cols();
        _matrix = new float *[_matrixDims.rows];
        for (int i = 0; i < _matrixDims.rows; i++) {
            _matrix[i] = new float[_matrixDims.cols];
        }
    }

    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            (*this)(i, j) = mat(i, j);
        }
    }
    return *this;
}

/**
 * @brief Multiply this matrix with another matrix.
 *
 * @param mat Matrix to multiply with.
 * @return Resulting matrix after multiplication.
 */
Matrix Matrix::operator*(const Matrix &mat) const {
    if (mat.get_rows() != _matrixDims.cols) {
        INVALID_LENGTH
    }
    Matrix result(_matrixDims.rows, mat.get_cols());
    for (int i = 0; i < result.get_rows(); ++i) {
        for (int j = 0; j < result.get_cols(); ++j) {
            for (int k = 0; k < _matrixDims.cols; ++k) {
                result._matrix[i][j] += (_matrix[i][k] * mat._matrix[k][j]);
            }
        }
    }
    return result;
}

/**
 * @brief Add another matrix to this matrix in-place.
 *
 * @param mat Matrix to add.
 * @return Reference to this matrix after addition.
 */
Matrix &Matrix::operator+=(const Matrix &mat) {
    if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols) {
        INVALID_LENGTH
    }
    for (int i = 0; i < _matrixDims.rows; i++) {
        for (int j = 0; j < _matrixDims.cols; j++) {
            _matrix[i][j] += mat._matrix[i][j];
        }
    }
    return *this;
}

/**
 * @brief Element access (const) using row and column indices.
 *
 * @param row Row index.
 * @param col Column index.
 * @return Element at the specified position.
 */
float Matrix::operator()(int row, int col) const {
    if ((row < 0 || col < 0) || (row >= _matrixDims.rows || col >= _matrixDims.cols)) {
        throw out_of_range("Index out of range");
    }
    return _matrix[row][col];
}

/**
 * @brief Element access using row and column indices.
 *
 * @param row Row index.
 * @param col Column index.
 * @return Reference to the element at the specified position.
 */
float &Matrix::operator()(int row, int col) {
    if ((row < 0 || col < 0) || (row >= _matrixDims.rows || col >= _matrixDims.cols)) {
        throw out_of_range("Index out of range");
    }
    return _matrix[row][col];
}

/**
 * @brief Element access (const) using a single index (row-major order).
 *
 * @param index Index.
 * @return Element at the specified position.
 */
float Matrix::operator[](int index) const {
    if (index < 0 || index >= (_matrixDims.rows * _matrixDims.cols)) {
        throw out_of_range("Index out of range");
    }
    return _matrix[index / _matrixDims.cols][index % _matrixDims.cols];
}

/**
 * @brief Element access using a single index (row-major order).
 *
 * @param index Index.
 * @return Reference to the element at the specified position.
 */
float &Matrix::operator[](int index) {
    if (index < 0 || index >= (_matrixDims.rows * _matrixDims.cols)) {
        throw out_of_range("Index out of range");
    }
    return _matrix[index / _matrixDims.cols][index % _matrixDims.cols];
}

/**
 * @brief Scalar multiplication (Matrix * float).
 *
 * @param mat The matrix to multiply.
 * @param scalar The scalar value to multiply.
 * @return The resulting matrix after scalar multiplication.
 */
Matrix operator*(const Matrix &mat, float scalar) {
    Matrix result(mat.get_rows(), mat.get_cols());
    for (int i = 0; i < mat.get_rows(); i++) {
        for (int j = 0; j < mat.get_cols(); j++) {
            result(i, j) = scalar * mat(i, j);
        }
    }
    return result;
}

/**
 * @brief Scalar multiplication (float * Matrix).
 *
 * @param scalar The scalar value to multiply.
 * @param mat The matrix to multiply.
 * @return The resulting matrix after scalar multiplication.
 */
Matrix operator*(float scalar, const Matrix &mat) {
    Matrix result(mat.get_rows(), mat.get_cols());
    for (int i = 0; i < mat.get_rows(); i++) {
        for (int j = 0; j < mat.get_cols(); j++) {
            result(i, j) = scalar * mat(i, j);
        }
    }
    return result;
}

/**
 * @brief Output stream operator for printing the matrix.
 *
 * @param output_stream Output stream.
 * @param mat Matrix to print.
 * @return Reference to the output stream.
 */
ostream &operator<<(ostream &output_stream, const Matrix &mat) {
    for (int i = 0; i < mat.get_rows(); i++) {
        for (int j = 0; j < mat.get_cols(); j++) {
            if (mat(i, j) > PROB_FLAG) {
                output_stream << ASTERISKS;
            } else {
                output_stream << SPACE;
            }
        }
        output_stream << NEW_LINE;
    }
    return output_stream;
}

/**
 * @brief Input stream operator for reading matrix elements.
 *
 * @param input_stream Input stream.
 * @param mat Matrix to read into.
 * @return Reference to the input stream.
 */
istream &operator>>(istream &input_stream, Matrix &mat) {
    int chars_to_read = sizeof(float) * mat.get_cols() * mat.get_rows();
    input_stream.seekg(0, std::istream::end);
    int length_of_file = input_stream.tellg();
    input_stream.seekg(0, std::istream::beg);
    if (chars_to_read != length_of_file) {
        throw std::runtime_error("Invalid Input!");
    }
    for (int i = 0; i < mat.get_rows(); i++) {
        if (!input_stream.read((char *) mat._matrix[i], mat.get_cols() * sizeof(float))) {
            throw std::runtime_error("Invalid Input!");
        }
    }
    return input_stream;
}
