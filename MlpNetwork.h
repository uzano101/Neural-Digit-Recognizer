#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include <iostream>
#include <string>
#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by MlpNetwork) digit with the associated probability.
 * 
 * @var value - Identified digit value.
 * @var probability - Identification probability.
 */
typedef struct digit {
    unsigned int value;
    float probability;
} digit;

// Dimensions for input image and layer weights/biases
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {
        {128, 784},
        {64,  128},
        {20,  64},
        {10,  20}
};
const matrix_dims bias_dims[] = {
        {128, 1},
        {64,  1},
        {20,  1},
        {10,  1}
};

class MlpNetwork {
public:
    /**
     * @brief Constructs an MlpNetwork with given weights and biases.
     * 
     * @param weights Array of weight matrices.
     * @param biases Array of bias matrices.
     */
    MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
            : weight_mat(weights), bias_mat(biases) {}

    /**
     * @brief Applies the MlpNetwork to the input matrix and returns the identified digit.
     * 
     * @param input Input matrix.
     * @return Identified digit and its probability.
     */
    digit operator()(const Matrix &input);

private:
    Matrix *weight_mat; ///< Array of weight matrices.
    Matrix *bias_mat;   ///< Array of bias matrices.
};

#endif // MLPNETWORK_H
