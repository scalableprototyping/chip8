#!/bin/bash

if [ -z "${CHIP8_ROOT_DIR}" ]; then
    echo "CHIP8_ROOT_DIR is empty. Please set this environment variable."
    echo "If you are at the project root directory, you can use the following command:"
    echo "   export CHIP8_ROOT_DIR=\$(pwd)"
    return
fi

cd "${CHIP8_ROOT_DIR}"
rm -rf build
mkdir build
cd build
cmake -DBUILD_TESTS=TRUE -DCMAKE_BUILD_TYPE=Debug ..

make -j8
