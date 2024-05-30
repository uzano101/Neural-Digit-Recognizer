#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef Matrix (*Activation)(const Matrix&);

namespace activation{
  Matrix relu(const Matrix&);
  Matrix softmax(const Matrix&);
}

#endif //ACTIVATION_H
