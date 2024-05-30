#include "Activation.h"
#include <cmath>

namespace activation {

/**
 * @brief Applies the ReLU (Rectified Linear Unit) activation function to each element of the matrix.
 *
 * The ReLU function is defined as:
 *      f(x) = max(0, x)
 *
 * @param mat The input matrix to apply the ReLU function on.
 * @return A matrix with the ReLU function applied element-wise.
 */
    Matrix relu(const Matrix &mat) {
        Matrix result(mat.get_rows(), mat.get_cols());
        result = mat;
        for (int i = 0; i < mat.get_rows(); i++) {
            for (int j = 0; j < mat.get_cols(); j++) {
                if (result(i, j) < 0) {
                    result(i, j) = 0;
                }
            }
        }
        return result;
    }

/**
 * @brief Applies the softmax activation function to the input matrix.
 *
 * The softmax function is defined as:
 *      f(x_i) = exp(x_i) / sum(exp(x_j)) for all j
 *
 * This function is typically used in the output layer of a neural network
 * to represent a probability distribution.
 *
 * @param mat The input matrix to apply the softmax function on.
 * @return A matrix with the softmax function applied.
 */
    Matrix softmax(const Matrix &mat) {
        Matrix result(mat.get_rows(), mat.get_cols());
        result = mat;
        float sum = 0;
        for (int i = 0; i < mat.get_rows() * mat.get_cols(); i++) {
            sum += std::exp(mat[i]);
        }
        for (int i = 0; i < mat.get_rows() * mat.get_cols(); i++) {
            result[i] = (1 / sum) * std::exp(mat[i]);
        }
        return result;
    }

} // namespace activation
