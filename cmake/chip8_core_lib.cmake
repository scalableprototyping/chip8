add_library(CHIP8_CORE_LIB
    OBJECT
        src/Interpreter.cpp
        src/io/Speaker.cpp
        src/io/Keypad.cpp
        src/io/KeyMap.cpp
        src/io/display/PixelArray.cpp
        src/io/display/Renderer.cpp
        src/details/memory.cpp
        src/details/audio.cpp
        src/details/opcodes.cpp
        src/registers/DataRegister.cpp
        src/registers/IRegister.cpp
)

target_include_directories(CHIP8_CORE_LIB 
    PUBLIC 
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_compile_features(CHIP8_CORE_LIB PRIVATE cxx_std_17)

include(chip8_sfml)
target_add_sfml(CHIP8_CORE_LIB)

include(chip8_include_what_you_use)
target_add_iwyu(CHIP8_CORE_LIB)

include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_CORE_LIB)

include(chip8_clang_tidy)
string(CONCAT CHIP8_CORE_CLANG_TIDY_CHECKS "-checks=*,"
    # Disabled checks must be marked with a slash prefix
    "-fuchsia-*" "," 
    "-google-readability-namespace-comments" ","
    "-google-readability-todo" ","
    "-llvm-namespace-comment" ","
    "-hicpp-uppercase-literal-suffix" ","
    "-readability-uppercase-literal-suffix"
    )
target_add_clang_tidy(CHIP8_CORE_LIB ${CHIP8_CORE_CLANG_TIDY_CHECKS})

include(chip8_coverage)
target_add_coverage(CHIP8_CORE_LIB)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})
install(DIRECTORY src/assets DESTINATION bin)
