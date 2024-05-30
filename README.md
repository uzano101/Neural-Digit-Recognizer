Sure, here's a comprehensive README file for your GitHub repository:

---

# Neural Digit Recognizer

![Neural Network](https://img.icons8.com/ios-filled/50/000000/artificial-intelligence.png)

## Overview

**Neural Digit Recognizer** is a C++ project that implements a multi-layer perceptron (MLP) neural network to recognize handwritten digits. The network is capable of achieving approximately 96% accuracy in digit recognition. The project demonstrates the use of matrix operations, activation functions, and multi-threaded programming for efficient data processing.

## Features

- **Multi-layer Perceptron (MLP)**: Implements a 4-layer neural network.
- **Custom Activation Functions**: Supports ReLU and Softmax activation functions.
- **Matrix Operations**: Provides comprehensive matrix operations for neural network computations.
- **User Interface**: Command-line interface for loading and recognizing digit images.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Examples](#examples)
- [Contributing](#contributing)

## Installation

### Prerequisites

- C++ Compiler (g++ recommended)
- POSIX Threads Library
- CMake (optional, for building the project)

### Building the Project

To build the project, you can use the provided Makefile or CMake. Here’s how to do it using CMake:

```sh
mkdir build
cd build
cmake ..
make
```

## Usage

### Running the Program

To run the program, execute the following command:

```sh
./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4
```

Where:
- `wi` are the paths to the binary files containing the weights for the i-th layer.
- `bi` are the paths to the binary files containing the biases for the i-th layer.

### Example Command

```sh
./mlpnetwork weights1.bin weights2.bin weights3.bin weights4.bin biases1.bin biases2.bin biases3.bin biases4.bin
```

### User Interaction

1. The program will prompt you to insert the image path for the digit to recognize.
2. Enter the path to the image file and press Enter.
3. The program will display the processed image and the recognized digit along with the probability.
4. To quit, type `q` and press Enter.

## Project Structure

```
.
├── src
│   ├── Activation.cpp
│   ├── Dense.cpp
│   ├── MlpNetwork.cpp
│   ├── Matrix.cpp
│   ├── main.cpp
│   ├── Activation.h
│   ├── Dense.h
│   ├── MlpNetwork.h
│   └── Matrix.h
├── CMakeLists.txt
├── Makefile
└── README.md
```

### Description of Key Files

- **Matrix.h / Matrix.cpp**: Implementation of matrix operations.
- **Activation.h / Activation.cpp**: Implementation of activation functions (ReLU and Softmax).
- **Dense.h / Dense.cpp**: Implementation of a dense (fully connected) layer.
- **MlpNetwork.h / MlpNetwork.cpp**: Implementation of the multi-layer perceptron network.
- **main.cpp**: The main entry point of the program, including command-line interface handling.

## Examples

### Example Output

```sh
Please insert image path:
/path/to/digit_image.bin
Image processed:
**  * *   *   
*   **   *    
...

Mlp result: 7 at probability: 0.96
```

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, feel free to create a pull request or open an issue.

---

### Authors

- **Your Name** - [GitHub](https://github.com/uzano101)

---

Thank you for visiting the **Neural Digit Recognizer** project. We hope you find it useful and educational. Happy coding!


---

Replace the placeholders with your actual details and links to provide a complete and engaging README for your GitHub project.
