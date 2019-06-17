cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip_8_cpp VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(MAIN_TARGET ${PROJECT_NAME}_interpreter)
add_executable(${MAIN_TARGET} src/main.cpp)

set_property(TARGET ${MAIN_TARGET} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${MAIN_TARGET} PROPERTY CXX_STANDARD_REQUIRED TRUE)

target_include_directories(${MAIN_TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/include")

include(compiler-warnings)
target_add_compiler_warnigs(${MAIN_TARGET})

include(sfml)
target_add_sfml(${MAIN_TARGET})

#include(clang-tidy)
#target_add_clang_tidy(${MAIN_TARGET})

include(include-what-you-use)
set(CMAKE_LINK_WHAT_YOU_USE TRUE)

target_sources(${MAIN_TARGET}
)

add_library(PROJECT_SRC
    OBJECT
        src/Interpreter.cpp
        src/io/Speaker.cpp
        src/io/Keypad.cpp
        src/io/KeyMap.cpp
        src/io/display/PixelArray.cpp
        src/io/display/Renderer.cpp
        src/details/memory.cpp
        src/details/audio.cpp
)

include(clang-tidy)
target_add_clang_tidy(${PROJECT_SRC})

# NOTE: Resetting only needed if you have a global CMAKE_CXX_CLANG_TIDY
set_target_properties(
    target_no_static_code_analysis
    PROPERTIES
         CXX_CLANG_TIDY ""
)

...
add_library(target ${other_srcs} $<TARGET_OBJECTS:target_no_static_code_analysis>)



if(BUILD_TESTS)
    set(TESTS_TARGET ${PROJECT_NAME}_tests)

    add_executable(${TESTS_TARGET} test/test_main.cpp)

    add_library(TESTS_SRC
        OBJECT
            test/rom_test.cpp
            test/timer_test.cpp
            test/speaker_test.cpp
            test/keypad_test.cpp
            test/display_test.cpp
    )

    set_property(TARGET ${TESTS_TARGET} PROPERTY CXX_STANDARD 17)
    set_property(TARGET ${TESTS_TARGET} PROPERTY CXX_STANDARD_REQUIRED TRUE)

    target_include_directories(${TESTS_TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/include")

    include(gtest)
    target_add_gtest(${TESTS_TARGET})

    include(sfml)
    target_add_sfml(${TESTS_TARGET})

    include(compiler-warnings)
    target_add_compiler_warnigs(${TESTS_TARGET})

    include(coverage)
    target_add_coverage(${TESTS_TARGET})

    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${TESTS_TARGET})
endif()
