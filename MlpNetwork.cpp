#include "MlpNetwork.h"
#include "Dense.h"
#include "Activation.h"

using namespace activation;

/**
 * @brief Applies the MlpNetwork to the input matrix and returns the identified digit.
 *
 * This function sequentially applies four dense layers with specified activation functions
 * (ReLU for the first three layers and Softmax for the final layer) to the input matrix.
 * It then finds the index of the maximum value in the output matrix, which corresponds to the
 * identified digit, and returns the digit along with its probability.
 *
 * @param X The input matrix.
 * @return The identified digit and its probability.
 */
digit MlpNetwork::operator()(const Matrix& X) {
    // First layer with ReLU activation
    Dense r1(weight_mat[0], bias_mat[0], relu);
    Matrix first_layer = r1(X);

    // Second layer with ReLU activation
    Dense r2(weight_mat[1], bias_mat[1], relu);
    Matrix second_layer = r2(first_layer);

    // Third layer with ReLU activation
    Dense r3(weight_mat[2], bias_mat[2], relu);
    Matrix third_layer = r3(second_layer);

    // Fourth layer with Softmax activation
    Dense r4(weight_mat[3], bias_mat[3], softmax);
    Matrix fourth_layer = r4(third_layer);

    // Find the index of the maximum value in the output matrix
    float max = 0;
    int index_of_max = 0;
    for (int i = 0; i < fourth_layer.get_rows(); i++) {
        if (fourth_layer[i] > max) {
            max = fourth_layer[i];
            index_of_max = i;
        }
    }

    // Create and return the digit result
    digit result;
    result.value = index_of_max;
    result.probability = max;
    return result;
}
