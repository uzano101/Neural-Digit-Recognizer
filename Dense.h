#ifndef DENSE_H
#define DENSE_H
#include <iostream>
#include <string>
#include "Activation.h"
#include "Matrix.h"
using namespace activation;
using namespace std;


class Dense{
 public:
  Dense(const Matrix&, const Matrix&, Activation);
  Matrix get_weights() const
  {
    return weight_mat;
  }
  Matrix get_bias() const
  {
    return bias_mat;
  }
  Activation get_activation() const
  {
    return activation_func;
  }
  Matrix operator () (const Matrix& mat)
  {
    return activation_func((weight_mat * mat) + bias_mat);
  }
 private:
  Matrix weight_mat;
  Matrix bias_mat;
  Activation activation_func;
};

#endif //DENSE_H
