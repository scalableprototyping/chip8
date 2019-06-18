#!/bin/bash

if [ -z "${CHIP8_ROOT_DIR}" ]; then
    echo "CHIP8_ROOT_DIR is empty. Please set this environment variable."
    echo "If you are at the project root directory, you can use the following command:"
    echo "   export CHIP8_ROOT_DIR=\$(pwd)"
    return
fi

echo "Run configure_chip8 to rebuild and make the project"
alias configure_chip8=". ${CHIP8_ROOT_DIR}/scripts/configure.sh CMAKE"


