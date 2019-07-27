#!/bin/bash

if [ -z "${CHIP8_ROOT_DIR}" ]; then
    echo "CHIP8_ROOT_DIR is empty. Please set this environment variable."
    echo "If you are at the project root directory, you can use the following command:"
    echo "   export CHIP8_ROOT_DIR=\$(pwd)"
    return
fi

function build_project()
{
    cd "${CHIP8_ROOT_DIR}"
    rm -rf build
    mkdir build
    cd build
    cmake -DBUILD_TESTS=TRUE -DCLANG_TIDY=TRUE -DIWYU=TRUE -DCMAKE_BUILD_TYPE=Debug ..
    make -j8
}

if [[ "$1" == "gcc" ]]; then
    export CXX=g++
    export CC=gcc
    build_project

elif [[ "$1" == "clang" ]]; then
    export CXX=clang++
    export CC=clang
    build_project

else
    echo "Error: Provide gcc or clang argument"
    return
fi

