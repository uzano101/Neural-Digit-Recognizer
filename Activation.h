#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// Define a function pointer type for activation functions
typedef Matrix (*Activation)(const Matrix &);

namespace activation {
    /**
     * @brief Applies the ReLU (Rectified Linear Unit) activation function.
     *
     * The ReLU function is defined as:
     *      f(x) = max(0, x)
     *
     * @param matrix The input matrix to apply the ReLU function on.
     * @return A matrix with the ReLU function applied element-wise.
     */
    Matrix relu(const Matrix &matrix);

    /**
     * @brief Applies the softmax activation function.
     *
     * The softmax function is defined as:
     *      f(x_i) = exp(x_i) / sum(exp(x_j)) for all j
     *
     * This function is typically used in the output layer of a neural network
     * to represent a probability distribution.
     *
     * @param matrix The input matrix to apply the softmax function on.
     * @return A matrix with the softmax function applied.
     */
    Matrix softmax(const Matrix &matrix);
}

#endif //ACTIVATION_H
