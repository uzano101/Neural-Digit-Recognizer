#ifndef DENSE_H
#define DENSE_H

#include <iostream>
#include <string>
#include "Activation.h"
#include "Matrix.h"

using namespace activation;

class Dense {
public:
    /**
     * @brief Constructs a Dense layer.
     *
     * @param weights The weight matrix for the Dense layer.
     * @param bias The bias matrix for the Dense layer.
     * @param activation The activation function to be used in this layer.
     */
    Dense(const Matrix &weights, const Matrix &bias, Activation activation)
            : weight_mat(weights), bias_mat(bias), activation_func(activation) {}

    /**
     * @brief Retrieves the weight matrix of the Dense layer.
     *
     * @return The weight matrix.
     */
    Matrix get_weights() const {
        return weight_mat;
    }

    /**
     * @brief Retrieves the bias matrix of the Dense layer.
     *
     * @return The bias matrix.
     */
    Matrix get_bias() const {
        return bias_mat;
    }

    /**
     * @brief Retrieves the activation function used in the Dense layer.
     *
     * @return The activation function.
     */
    Activation get_activation() const {
        return activation_func;
    }

    /**
     * @brief Applies the Dense layer transformation to the input matrix.
     *
     * The transformation is defined as:
     *      output = activation(weights * input + bias)
     *
     * @param mat The input matrix.
     * @return The transformed matrix after applying weights, bias, and activation.
     */
    Matrix operator()(const Matrix &mat) {
        return activation_func((weight_mat * mat) + bias_mat);
    }

private:
    Matrix weight_mat;        ///< The weight matrix for the Dense layer
    Matrix bias_mat;          ///< The bias matrix for the Dense layer
    Activation activation_func; ///< The activation function for the Dense layer
};

#endif // DENSE_H
