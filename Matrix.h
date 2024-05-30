// Matrix.h
#include <iostream>
#include <string>
#include <cmath>
#ifndef MATRIX_H
#define MATRIX_H
using namespace std;
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

class Matrix{
 public:
  /// ~ constructors:
  Matrix() : Matrix (1,1){}
  Matrix(int rows, int cols);
  Matrix(const Matrix& mat);

  /// ~ destructor:
  ~Matrix()
  {
    for (int i = 0; i < _matrixDims.rows ; i++)
    {
      delete[] _matrix[i];
    }
    delete _matrix;
  }

  /// ~ getter functions:
  int get_rows() const
  {
    return _matrixDims.rows;
  }
  int get_cols() const
  {
    return _matrixDims.cols;
  }

  /// ~ member functions:
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& mat) const;
  float norm() const;

  /// ~ class operators:
  Matrix operator+(const Matrix&) const;
  Matrix& operator=(const Matrix&);
  Matrix operator*(const Matrix&) const;
  Matrix& operator+=(const Matrix&);
  float operator()(int, int) const;
  float& operator()(int, int);
  float operator[](int) const;
  float& operator[](int);

  /// ~ input/output streams:
  friend ostream& operator<<(ostream&, const Matrix&);
  friend istream& operator>>(istream&, const Matrix&);

 private:
  float ** _matrix;
  matrix_dims _matrixDims{};
};

Matrix operator* (float, const Matrix&);
Matrix operator* (const Matrix&, float);

#endif //MATRIX_H