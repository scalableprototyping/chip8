cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip_8_cpp VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(APPEND INTERPRETER_SOURCE_FILES
    src/Interpreter.cpp
    src/utils/rom.cpp
)

add_executable(${PROJECT_NAME}_interpreter src/main.cpp ${INTERPRETER_SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_interpreter PRIVATE include)
target_compile_options(${PROJECT_NAME}_interpreter PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest)

    if(NOT GTEST_FOUND)
        message("Could not find gtest library. It will be fetch and compiled..")
        set(EXTERNAL_GTEST_PATH depends/googletest)
        execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        option(INSTALL_GTEST "" OFF)
        option(INSTALL_GMOCK "" OFF)
        add_subdirectory(${EXTERNAL_GTEST_PATH})
        set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)
        set(GTEST_LIBRARIES gtest)
    endif()

    list(APPEND TEST_SOURCE_FILES
        ${INTERPRETER_SOURCE_FILES}
        test/rom_test.cpp
    )

    add_executable(${PROJECT_NAME}_tests test/test_main.cpp ${TEST_SOURCE_FILES})
    target_include_directories(${PROJECT_NAME}_tests PRIVATE include ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${GTEST_LIBRARIES})
    target_compile_options(${PROJECT_NAME}_tests PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}_tests)
endif()

# Compilation options for SFML. TODO: Merge with the rest of the cmakefile.
#cmake_minimum_required(VERSION 3.1)
#project(chip8-interpreter)
#set(EXECUTABLE_NAME "chip8-interpreter")
#include_directories(include)
#file(GLOB SOURCES "src/*.cpp")
#find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
#add_executable(${EXECUTABLE_NAME} ${SOURCES})
#target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
