#include "Activation.h"
#include <cmath>
using namespace std;

Matrix activation::relu(const Matrix& mat)
{
  Matrix result(mat.get_rows(), mat.get_cols());
  result = mat;
  for (int i = 0 ; i < mat.get_rows() ; i++)
  {
    for (int j = 0 ; j < mat.get_cols() ; j++)
    {
      if (result(i,j) < 0)
      {
        result(i,j) = 0;
      }
    }
  }
  return result;
}

Matrix activation::softmax(const Matrix& mat)
{
  Matrix result(mat.get_rows(), mat.get_cols());
  result = mat;
  float sum = 0;
  for (int i = 0 ; i < mat.get_rows()*mat.get_cols() ; i++)
  {
    sum += exp(mat[i]);
  }
  for (int i = 0 ; i < mat.get_rows()*mat.get_cols() ; i++)
  {
    result[i] = (1/sum)*exp(mat[i]);
  }
  return result;
}
