add_library(CHIP8_TESTS_LIB
    OBJECT
        test/rom_test.cpp
        test/timer_test.cpp
        test/speaker_test.cpp
        test/keypad_test.cpp
        test/display_test.cpp
        test/register_test.cpp
        test/random_test.cpp
        test/opcodes.cpp
)

target_include_directories(CHIP8_TESTS_LIB PRIVATE include)

target_compile_features(CHIP8_TESTS_LIB PRIVATE cxx_std_17)

include(chip8_gtest)
target_add_gtest(CHIP8_TESTS_LIB)

include(chip8_sfml)
target_add_sfml(CHIP8_TESTS_LIB)

include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_TESTS_LIB)

include(chip8_clang_tidy)
string(CONCAT CHIP8_TESTS_LIB_CLANG_TIDY_CHECKS "-checks=*,"
    # Disabled checks must be marked with a slash prefix
    "-fuchsia-*" ","
    "-google-readability-namespace-comments" ","
    "-google-readability-todo" ","
    "-llvm-namespace-comment" ","
    "-hicpp-uppercase-literal-suffix" ","
    "-readability-uppercase-literal-suffix" ","
    "-cppcoreguidelines-special-member-functions" ","
    "-hicpp-special-member-functions" ","
    "-cert-err58-cpp" ","
    "-cppcoreguidelines-owning-memory" ","
    "-cppcoreguidelines-avoid-goto" ","
    "-hicpp-avoid-goto" ","
    "-cppcoreguidelines-avoid-magic-numbers" ","
    "-readability-magic-numbers" ","
    "-cppcoreguidelines-pro-type-vararg" ","
    "-hicpp-vararg"
    )
target_add_clang_tidy(CHIP8_TESTS_LIB ${CHIP8_TESTS_LIB_CLANG_TIDY_CHECKS})

include(chip8_coverage)
target_add_coverage(${MAIN_EXECUTABLE})
