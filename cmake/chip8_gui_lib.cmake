add_library(CHIP8_GUI_LIB
    OBJECT
        gui/QInterpreter.cpp
        gui/liveReload/liveReloadQmlApplicationEngine.cpp
)

target_include_directories(CHIP8_GUI_LIB PRIVATE include)
target_compile_features(CHIP8_GUI_LIB PRIVATE cxx_std_17)

include(chip8_qt)
target_add_qt(CHIP8_GUI_LIB)

target_add_qt_resources(CHIP8_GUI_LIB 
    gui/qml/qml.qrc
)
target_add_qt_headers(CHIP8_GUI_LIB 
    gui/QInterpreter.hpp
    gui/liveReload/liveReloadQmlApplicationEngine.hpp
)

include(chip8_sfml)
target_add_sfml(CHIP8_GUI_LIB)

include(chip8_compiler_warnings)
target_add_compiler_warnigs(CHIP8_GUI_LIB)

include(chip8_clang_tidy)
string(CONCAT CHIP8_GUI_LIB_CLANG_TIDY_CHECKS "-checks=*,"
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
target_add_clang_tidy(CHIP8_GUI_LIB ${CHIP8_GUI_LIB_CLANG_TIDY_CHECKS})
