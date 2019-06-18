add_library(CHIP8_TESTS_LIB
    OBJECT
        test/rom_test.cpp
        test/timer_test.cpp
        test/speaker_test.cpp
        test/keypad_test.cpp
        test/display_test.cpp
)

target_include_directories(CHIP8_TESTS_LIB PRIVATE include)

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
