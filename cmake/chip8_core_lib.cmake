add_library(CHIP8_CORE_LIB
    OBJECT
        ${PROJECT_SOURCE_DIR}/src/Interpreter.cpp
        ${PROJECT_SOURCE_DIR}/src/io/Speaker.cpp
        ${PROJECT_SOURCE_DIR}/src/io/Keypad.cpp
        ${PROJECT_SOURCE_DIR}/src/io/KeyMap.cpp
        ${PROJECT_SOURCE_DIR}/src/io/display/PixelArray.cpp
        ${PROJECT_SOURCE_DIR}/src/io/display/Renderer.cpp
        ${PROJECT_SOURCE_DIR}/src/details/memory.cpp
        ${PROJECT_SOURCE_DIR}/src/details/audio.cpp
)

target_include_directories(CHIP8_CORE_LIB PUBLIC "${PROJECT_SOURCE_DIR}/include")

set_property(TARGET CHIP8_CORE_LIB PROPERTY CXX_STANDARD 17)
set_property(TARGET CHIP8_CORE_LIB PROPERTY CXX_STANDARD_REQUIRED TRUE)

include(chip8_sfml)
target_add_sfml(CHIP8_CORE_LIB)
include(chip8_include_what_you_use)
target_add_iwyu(CHIP8_CORE_LIB)
include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_CORE_LIB)
