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
target_add_clang_tidy(CHIP8_CORE_LIB)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})
install(DIRECTORY src/assets DESTINATION bin)
