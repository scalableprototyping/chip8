cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip_8_cpp VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(APPEND INTERPRETER_SOURCE_FILES
    src/Interpreter.cpp
    src/utils/rom.cpp
)

set(EXECUTABLE_NAME ${PROJECT_NAME}_interpreter)
add_executable(${EXECUTABLE_NAME} src/main.cpp ${INTERPRETER_SOURCE_FILES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_compile_options(${EXECUTABLE_NAME} PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest)

    if (GTEST_FOUND)
        execute_prcess(COMMAND echo ${GTEST_ROOT})
    endif()

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

    set(${EXECUTABLE_NAME_TEST} ${PROJECT_NAME}_tests)
    add_executable(${EXECUTABLE_NAME_TEST} test/test_main.cpp ${TEST_SOURCE_FILES})
    target_include_directories(${EXECUTABLE_NAME_TEST} PRIVATE include ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME_TEST} PRIVATE ${GTEST_LIBRARIES})
    target_compile_options(${EXECUTABLE_NAME_TEST} PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}_tests)
endif()
