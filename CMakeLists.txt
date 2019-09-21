cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip8_cpp VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH 
    "${PROJECT_SOURCE_DIR}/cmake"
    "${PROJECT_SOURCE_DIR}/cmake/modules"
    "${PROJECT_SOURCE_DIR}/cmake/scripts"    
)

include(chip8_core_lib)

if(BUILD_INTERPRETER)
    set(INTERPRETER_EXECUTABLE ${PROJECT_NAME}_interpreter)
    add_executable(${INTERPRETER_EXECUTABLE} src/main.cpp
        $<TARGET_OBJECTS:CHIP8_CORE_LIB>
    )
    target_include_directories(${INTERPRETER_EXECUTABLE} PRIVATE include)
    target_compile_features(${INTERPRETER_EXECUTABLE} PRIVATE cxx_std_17)
    set_property(TARGET ${INTERPRETER_EXECUTABLE} PROPERTY LINK_WHAT_YOU_USE TRUE)

    include(chip8_threads)
    target_link_threads(${INTERPRETER_EXECUTABLE})

    include(chip8_sfml)
    target_add_sfml(${INTERPRETER_EXECUTABLE})

    include(chip8_include_what_you_use)
    target_add_iwyu(${INTERPRETER_EXECUTABLE})

    include(chip8_compiler_warnings)
    target_add_compiler_warnigs(${INTERPRETER_EXECUTABLE})

    include(chip8_clang_tidy)
    target_add_clang_tidy(${INTERPRETER_EXECUTABLE} ${CHIP8_CORE_CLANG_TIDY_CHECKS})
endif()

if(BUILD_GUI)
    include(chip8_gui_lib)

    set(GUI_EXECUTABLE ${PROJECT_NAME}_gui)
    add_executable(${GUI_EXECUTABLE} gui/gui_main.cpp 
        $<TARGET_OBJECTS:CHIP8_CORE_LIB> 
        $<TARGET_OBJECTS:CHIP8_GUI_LIB>
    )
    target_include_directories(${GUI_EXECUTABLE} PRIVATE include)
    target_compile_features(${GUI_EXECUTABLE} PRIVATE cxx_std_17)
    set_property(TARGET ${GUI_EXECUTABLE} PROPERTY LINK_WHAT_YOU_USE TRUE)

    include(chip8_threads)
    target_link_threads(${GUI_EXECUTABLE})

    include(chip8_qt)
    target_add_qt(${GUI_EXECUTABLE})

    include(chip8_sfml)
    target_add_sfml(${GUI_EXECUTABLE})

    include(chip8_compiler_warnings)
    target_add_compiler_warnigs(${GUI_EXECUTABLE})
endif()

if(BUILD_TESTS)
    enable_testing()

    include(chip8_tests_lib)

    set(TESTS_EXECUTABLE ${PROJECT_NAME}_tests)
    add_executable(${TESTS_EXECUTABLE} test/test_main.cpp 
        $<TARGET_OBJECTS:CHIP8_CORE_LIB> 
        $<TARGET_OBJECTS:CHIP8_TESTS_LIB>
    )
    target_include_directories(${TESTS_EXECUTABLE} PRIVATE include)
    target_compile_features(${TESTS_EXECUTABLE} PRIVATE cxx_std_17)
    set_property(TARGET ${TESTS_EXECUTABLE} PROPERTY LINK_WHAT_YOU_USE TRUE)

    include(chip8_gtest)
    target_add_gtest(${TESTS_EXECUTABLE})

    include(chip8_sfml)
    target_add_sfml(${TESTS_EXECUTABLE})

    include(chip8_compiler_warnings)
    target_add_compiler_warnigs(${TESTS_EXECUTABLE})

    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${TESTS_EXECUTABLE})
endif()

install(TARGETS ${INTERPRETER_EXECUTABLE}  DESTINATION bin)
install(TARGETS ${TESTS_EXECUTABLE}        DESTINATION bin)
install(TARGETS ${GUI_EXECUTABLE}          DESTINATION bin)

include(chip8_uninstall)
