#!/bin/bash

if [ -z "${CHIP8_ROOT_DIR}" ]
then
    echo "\${CHIP8_ROOT_DIR} is empty. Please set this environment variable."
    exit
fi

cd "${CHIP8_ROOT_DIR}"
rm -rf build
mkdir build
cd build
cmake -DBUILD_TESTS=1 -DCMAKE_BUILD_TYPE=Debug ..

make
