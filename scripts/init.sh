#!/bin/bash

if [ -z "${CHIP8_ROOT_DIR}" ]
then
    echo "\${CHIP8_ROOT_DIR} is empty. Please set this environment variable."
    exit
fi

alias configure_chip8=". ${CHIP8_ROOT_DIR}/scripts/configure.sh CMAKE"


