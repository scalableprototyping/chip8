add_library(CHIP8_TESTS_LIB
    OBJECT
        ${PROJECT_SOURCE_DIR}/test/rom_test.cpp
        ${PROJECT_SOURCE_DIR}/test/timer_test.cpp
        ${PROJECT_SOURCE_DIR}/test/speaker_test.cpp
        ${PROJECT_SOURCE_DIR}/test/keypad_test.cpp
        ${PROJECT_SOURCE_DIR}/test/display_test.cpp
)

target_include_directories(CHIP8_TESTS_LIB PUBLIC "${PROJECT_SOURCE_DIR}/include")

set_property(TARGET CHIP8_TESTS_LIB PROPERTY CXX_STANDARD 17)
set_property(TARGET CHIP8_TESTS_LIB PROPERTY CXX_STANDARD_REQUIRED TRUE)

include(chip8_gtest)
target_add_gtest(CHIP8_TESTS_LIB)
include(chip8_sfml)
target_add_sfml(CHIP8_TESTS_LIB)
include(chip8_include_what_you_use)
target_add_iwyu(CHIP8_TESTS_LIB)
include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_TESTS_LIB)
