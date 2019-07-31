# Chip8 Interpreter

[![Build Status](https://travis-ci.org/scalableprototyping/chip8.svg?branch=travis)](https://travis-ci.org/scalableprototyping/chip8)
[![Coverage Status](https://coveralls.io/repos/github/scalableprototyping/chip8/badge.svg?branch=travis)](https://coveralls.io/github/scalableprototyping/chip8?branch=travis)

Welcome to ScalablePrototyping Chip8 Interpreter, developed by:

* Álvaro Páez Guerra
* Juan José Blasco Burguillos

This project show cases the latest C++ cross-platform development best 
practices, making extensive use of C++17 features, the STL, and modern build, 
continuous integration and coverage tools. 

This Chip8 Interpreter allows to run chip8 ROMs and to interact with them. Example ROMs can be found 
[here](https://github.com/dmatlack/chip8/tree/master/roms)

## Requirements ##

ScalablePrototyping Chip8 Interpreter has been designed to have fairly minimal 
requirements to build:

* CMake 3.15 or greater.
* C++17 Compiler.
* SFML version 2.3 or greater. 

## Testing Environment ##

GTest is used as the testing environment. The CMake build system will download and setup the appropriate version, so no additional requirements are needed.

## Coding Standard ## 

This project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)


