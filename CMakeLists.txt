cmake_minimum_required(VERSION 3.1)

project(chip8-interpreter)

set(EXECUTABLE_NAME "chip8-interpreter")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
