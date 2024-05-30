cmake_minimum_required(VERSION 3.22)
project(ex4_alon_uzan)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_alon_uzan
        Activation.h
        Activation.cpp
        Dense.h
        Dense.cpp
        main.cpp
        Matrix.h
        Matrix.cpp
        MlpNetwork.h
        MlpNetwork.cpp
        #test.cpp
        test.h
        test_activation.cpp
        test_activation.h
        test_dense.cpp
        test_dense.h
        test_matrix.cpp
        test_matrix.h
        Makefile)
