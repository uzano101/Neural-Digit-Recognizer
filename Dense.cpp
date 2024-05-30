#include "Dense.h"

Dense::Dense (const Matrix & weights,
       const Matrix & bias, Activation ActivationFunction):
weight_mat(weights), bias_mat(bias), activation_func(ActivationFunction){}
