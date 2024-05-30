#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#include "MlpNetwork.h"
#include <fstream>

#define QUIT "q"
#define INSERT_IMAGE_PATH "Please insert image path:"
#define ERROR_INVALID_PARAMETER "Error: invalid Parameters file for layer: "
#define ERROR_INVALID_INPUT "Error: Failed to retrieve input. Exiting.."
#define ERROR_INVALID_IMG "Error: invalid image path or size: "
#define USAGE_MSG "Usage:\n" \
                  "\t./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4\n" \
                  "\twi - the i'th layer's weights\n" \
                  "\tbi - the i'th layer's biases"
#define USAGE_ERR "Error: wrong number of arguments."
#define ARGS_START_IDX 1
#define ARGS_COUNT (ARGS_START_IDX + (MLP_SIZE * 2))
#define WEIGHTS_START_IDX ARGS_START_IDX
#define BIAS_START_IDX (ARGS_START_IDX + MLP_SIZE)

/**
 * @brief Prints program usage to stdout.
 *
 * @param argc Number of arguments given in the program.
 * @throw std::domain_error In case of wrong number of arguments.
 */
void usage(int argc) noexcept(false) {
    if (argc != ARGS_COUNT) {
        throw std::domain_error(USAGE_ERR);
    }
    std::cout << USAGE_MSG << std::endl;
}

/**
 * @brief Reads the content of a binary file into the given matrix.
 *
 * The file must match the matrix in size to read successfully.
 *
 * @param filePath Path of the binary file to read.
 * @param mat Matrix to read the file into.
 * @return True if the file was read successfully, false otherwise.
 */
bool readFileToMatrix(const std::string &filePath, Matrix &mat) {
    std::ifstream s(filePath, std::ifstream::binary);
    if (!s.is_open() || !(s >> mat)) {
        return false;
    }
    return true;
}

/**
 * @brief Loads MLP parameters from weights & biases paths into the arrays.
 *
 * Throws an exception upon failures.
 *
 * @param paths Array of program arguments, expected to be MLP parameters path.
 * @param weights Array of matrices, weights[i] is the i'th layer weights matrix.
 * @param biases Array of matrices, biases[i] is the i'th layer bias matrix.
 * @throw std::invalid_argument In case of a problem with a certain argument.
 */
void loadParameters(char *paths[ARGS_COUNT], Matrix weights[MLP_SIZE],
                    Matrix biases[MLP_SIZE]) noexcept(false) {
    for (int i = 0; i < MLP_SIZE; i++) {
        weights[i] = Matrix(weights_dims[i].rows, weights_dims[i].cols);
        biases[i] = Matrix(bias_dims[i].rows, bias_dims[i].cols);

        std::string weightsPath(paths[WEIGHTS_START_IDX + i]);
        std::string biasPath(paths[BIAS_START_IDX + i]);

        if (!readFileToMatrix(weightsPath, weights[i]) ||
            !readFileToMatrix(biasPath, biases[i])) {
            auto msg = ERROR_INVALID_PARAMETER + std::to_string(i + 1);
            throw std::invalid_argument(msg);
        }
    }
}

/**
 * @brief Command line interface for the MLP network.
 *
 * This function loops to retrieve user input, feed input to MlpNetwork,
 * print image and network prediction.
 *
 * Throws an exception on fatal errors: unable to read user input path.
 *
 * @param mlp MlpNetwork to use in order to predict the image.
 * @throw std::invalid_argument In case of a problem with the user input path.
 */
void mlpCli(MlpNetwork &mlp) noexcept(false) {
    Matrix img(img_dims.rows, img_dims.cols);
    std::string imgPath;

    std::cout << INSERT_IMAGE_PATH << std::endl;
    std::cin >> imgPath;
    if (!std::cin.good()) {
        throw std::invalid_argument(ERROR_INVALID_INPUT);
    }

    while (imgPath != QUIT) {
        if (readFileToMatrix(imgPath, img)) {
            Matrix imgVec = img.vectorize();
            digit output = mlp(imgVec);
            std::cout << "Image processed:" << std::endl
                      << img << std::endl;
            std::cout << "Mlp result: " << output.value <<
                      " at probability: " << output.probability << std::endl;
        } else {
            throw std::invalid_argument(ERROR_INVALID_IMG + imgPath);
        }

        std::cout << INSERT_IMAGE_PATH << std::endl;
        std::cin >> imgPath;
        if (!std::cin.good()) {
            throw std::invalid_argument(ERROR_INVALID_INPUT);
        }
    }
}

/**
 * @brief Program's main function.
 *
 * @param argc Count of arguments.
 * @param argv Array of arguments.
 * @return Program exit status code.
 */
int main(int argc, char **argv) {
    try {
        usage(argc);
    } catch (const std::domain_error &domainError) {
        std::cerr << domainError.what() << std::endl;
        return EXIT_FAILURE;
    }

    Matrix weights[MLP_SIZE];
    Matrix biases[MLP_SIZE];

    try {
        loadParameters(argv, weights, biases);
    } catch (const std::invalid_argument &invalidArgument) {
        std::cerr << invalidArgument.what() << std::endl;
        return EXIT_FAILURE;
    }

    MlpNetwork mlp(weights, biases);

    try {
        mlpCli(mlp);
    } catch (const std::invalid_argument &invalidArgument) {
        std::cerr << invalidArgument.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
