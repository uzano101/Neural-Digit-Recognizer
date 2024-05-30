#include "Matrix.h"
#include <iostream>
#include <string>
using namespace std;

#define INDEX_BOUND 1
#define SPACE " "
#define NEW_LINE "\n"
#define ASTERISKS "**"
#define INVALID_LENGTH throw length_error ("either row or "\
"column input is invalid.");
#define INVALID_INPUT throw runtime_error("Invalid Input");
#define PROB_FLAG 0.1

int is_scales_compatible (int rows, int cols)
{
  if (rows < INDEX_BOUND || cols < INDEX_BOUND)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

Matrix::Matrix (int rows, int cols)
{
  if (!is_scales_compatible (rows, cols))
  {
    INVALID_LENGTH
  }
  _matrixDims.rows = rows;
  _matrixDims.cols = cols;
  _matrix = nullptr;
  _matrix = new float *[rows];
  if (!_matrix)
  {
    throw bad_alloc ();
  }
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    _matrix[i] = nullptr;
    _matrix[i] = new float[cols];
    if (!_matrix[i])
    {
      throw bad_alloc ();
    }
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      _matrix[i][j] = 0;
    }
  }
}

Matrix::Matrix (const Matrix &mat) : Matrix (mat.get_rows (), mat.get_cols ())
{
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      _matrix[i][j] = mat._matrix[i][j];
    }
  }
}

Matrix& Matrix::transpose ()
{
  float ** temp_arr= nullptr;
  temp_arr = new float*[_matrixDims.cols];
  for (int i = 0; i < _matrixDims.cols; i++)
  {
    temp_arr[i] = new float[_matrixDims.rows];
    for (int j = 0; j < _matrixDims.rows; j++)
    {
      temp_arr[i][j] = _matrix[j][i];
    }
  }
  swap (_matrixDims.rows, _matrixDims.cols);
  _matrix = temp_arr;
  return *this;
}

Matrix& Matrix::vectorize ()
{
  float ** temp_arr= nullptr;
  temp_arr = new float*[_matrixDims.rows * _matrixDims.cols];
  for (int i = 0 ; i < _matrixDims.rows*_matrixDims.cols ; i++)
  {
    temp_arr[i] = new float[1];
  }
  for (int i = 0 ; i < _matrixDims.rows*_matrixDims.cols; i++)
  {
    temp_arr[i][0] = (*this)[i];
  }
  _matrixDims.rows = _matrixDims.rows*_matrixDims.cols;
  _matrixDims.cols = 1;
  _matrix = temp_arr;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      cout << _matrix[i][j] << SPACE;
    }
    cout << NEW_LINE;
  }
}

Matrix Matrix::dot (const Matrix &mat) const
{
  if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols)
  {
    INVALID_LENGTH
  }
  Matrix result (_matrixDims.rows, _matrixDims.cols);
  for (int i = 0; i < _matrixDims.rows*_matrixDims.cols; i++)
  {
    result[i] = (*this)[i]*mat[i];
  }
  return result;
}

float Matrix::norm () const
{
  double matrix_sum = 0;
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      matrix_sum += pow (_matrix[i][j], 2);
    }
  }
  double matrix_norm = sqrt (matrix_sum);
  return (float) matrix_norm;
}

Matrix Matrix::operator+ (const Matrix &mat) const
{
  if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols)
  {
    INVALID_LENGTH
  }
  Matrix result (_matrixDims.rows, _matrixDims.cols);
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      result._matrix[i][j] = _matrix[i][j] + mat._matrix[i][j];
    }
  }
  return result;
}

Matrix &Matrix::operator= (const Matrix &mat)
{
  {
    if (this == &mat)
    {
      return *this;
    }

    if (_matrixDims.rows != mat.get_rows ()
        || _matrixDims.cols != mat.get_cols ())
    {
      for (int i = 0; i < _matrixDims.rows; i++)
      {
        delete[] _matrix[i];
      }
      delete[] _matrix;

      _matrixDims.rows = mat.get_rows ();
      _matrixDims.cols = mat.get_cols ();
      _matrix = new float*[_matrixDims.rows];
      for (int i = 0; i < _matrixDims.rows; i++)
      {
       _matrix[i] = new float[_matrixDims.cols];
      }

    }

    for (int i = 0; i < _matrixDims.rows; i++)
    {
      for (int j = 0; j < _matrixDims.cols; j++)
      {
        (*this)(i,j) = mat(i,j);
      }
    }
    return *this;
  }
}

Matrix Matrix::operator* (const Matrix &mat) const
{
  if (mat.get_rows() != _matrixDims.cols)
  {
    INVALID_LENGTH
  }
  Matrix temp(_matrixDims.rows, mat.get_cols());
    for (int i = 0; i < temp.get_rows(); ++i) {
      for (int j = 0; j < temp.get_cols(); ++j) {
        for (int k = 0; k < _matrixDims.cols; ++k) {
          temp._matrix[i][j] += (_matrix[i][k] * mat._matrix[k][j]);
        }
      }
    }
    return temp;
}

Matrix operator* (const Matrix &mat, float scalar)
{
  Matrix result (mat.get_rows (), mat.get_cols ());
  for (int i = 0; i < mat.get_rows (); i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      result(i,j) = scalar * mat(i, j);
    }
  }
  return result;
}

Matrix operator* (float scalar, const Matrix &mat)
{
  Matrix result (mat.get_rows (), mat.get_cols ());
  for (int i = 0; i < mat.get_rows (); i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      result(i,j) = scalar * mat(i, j);
    }
  }
  return result;
}

Matrix &Matrix::operator+= (const Matrix &mat)
{
  if (mat.get_rows() != _matrixDims.rows || mat.get_cols() != _matrixDims.cols)
  {
    INVALID_LENGTH
  }
  for (int i = 0; i < _matrixDims.rows; i++)
  {
    for (int j = 0; j < _matrixDims.cols; j++)
    {
      _matrix[i][j] += mat._matrix[i][j];
    }
  }
  return *this;
}

float Matrix::operator() (int row, int col) const
{
  if ((row < 0 || col < 0) ||
      (row >= _matrixDims.rows || col >= _matrixDims.cols))
  {
    throw out_of_range ("Index out of range");
  }
  return _matrix[row][col];
}

float &Matrix::operator() (int row, int col)
{
  if ((row < 0 || col < 0) ||
      (row >= _matrixDims.rows || col >= _matrixDims.cols))
  {
    throw out_of_range ("Index out of range");
  }
  return _matrix[row][col];
}

float Matrix::operator[] (int index) const
{
  if (index < 0 || index >= (_matrixDims.rows * _matrixDims.cols))
  {
    throw out_of_range ("Index out of range");
  }
  return _matrix[(int) index / _matrixDims.cols][index % (_matrixDims.cols)];
}

float &Matrix::operator[] (int index)
{
  if (index < 0 || index >= (_matrixDims.rows * _matrixDims.cols))
  {
    throw out_of_range ("Index out of range");
  }
  return _matrix[(int) index / _matrixDims.cols][index % (_matrixDims.cols)];
}

ostream &operator<< (ostream &output_stream, const Matrix &mat)
{
  for (int i = 0; i < mat.get_rows (); i++)
  {
    for (int j = 0; j < mat.get_cols (); j++)
    {
      if (mat (i, j) > PROB_FLAG)
      {
        output_stream << ASTERISKS;
      }
      else
      {
        output_stream << SPACE;
      }
    }
    output_stream << NEW_LINE;
  }
  return output_stream;
}

istream &operator>> (istream &input_stream, const Matrix &mat)
{
  int chars_to_read = sizeof(float) * mat.get_cols() * mat.get_rows();
  input_stream.seekg (0, std::istream::end);
  int length_of_file = input_stream.tellg();
  input_stream.seekg (0, std::istream::beg);
  if(chars_to_read != length_of_file)
  {
    throw std::runtime_error("Invalid Input!");
  }
  for(int i=0;i<mat.get_rows();i++)
  {
    if(!input_stream.read((char*)mat._matrix[i], mat.get_cols()*sizeof(float)))
    {
      throw std::runtime_error("Invalid Input!");
    }
  }
  return input_stream;
}
