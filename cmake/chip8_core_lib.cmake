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

target_include_directories(CHIP8_CORE_LIB PRIVATE include)

set_property(TARGET CHIP8_CORE_LIB PROPERTY CXX_STANDARD 17)
set_property(TARGET CHIP8_CORE_LIB PROPERTY CXX_STANDARD_REQUIRED TRUE)

include(chip8_sfml)
target_add_sfml(CHIP8_CORE_LIB)
include(chip8_include_what_you_use)
target_add_iwyu(CHIP8_CORE_LIB)
include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_CORE_LIB)
