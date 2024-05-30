#include "Dense.h"

/**
 * @brief Constructs a Dense layer.
 *
 * @param weights The weight matrix for the Dense layer.
 * @param bias The bias matrix for the Dense layer.
 * @param activationFunction The activation function to be used in this layer.
 */
Dense::Dense(const Matrix &weights, const Matrix &bias, Activation activationFunction)
        : weight_mat(weights), bias_mat(bias), activation_func(activationFunction) {}
