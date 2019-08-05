cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip8_cpp VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH 
    "${PROJECT_SOURCE_DIR}/cmake"
    "${PROJECT_SOURCE_DIR}/cmake/modules"
    "${PROJECT_SOURCE_DIR}/cmake/scripts"    
)

set(MAIN_EXECUTABLE ${PROJECT_NAME}_interpreter)

include(chip8_core_lib)
add_executable(${MAIN_EXECUTABLE} src/main.cpp
    $<TARGET_OBJECTS:CHIP8_CORE_LIB>
)

target_include_directories(${MAIN_EXECUTABLE} PRIVATE include)

target_compile_features(${MAIN_EXECUTABLE} PRIVATE cxx_std_17)

set_property(TARGET ${MAIN_EXECUTABLE} PROPERTY LINK_WHAT_YOU_USE TRUE)

include(chip8_sfml)
target_add_sfml(${MAIN_EXECUTABLE})

include(chip8_include_what_you_use)
target_add_iwyu(${MAIN_EXECUTABLE})

include(chip8_compiler_warnings)
target_add_compiler_warnigs(${MAIN_EXECUTABLE})

include(chip8_clang_tidy)
target_add_clang_tidy(${MAIN_EXECUTABLE} ${CHIP8_CORE_CLANG_TIDY_CHECKS})

include(chip8_coverage)
target_add_coverage(${MAIN_EXECUTABLE})

if(BUILD_GUI)
    set(GUI_EXECUTABLE ${PROJECT_NAME}_gui)

    include(chip8_gui_lib)
    add_executable(${GUI_EXECUTABLE} gui/gui_main.cpp 
        $<TARGET_OBJECTS:CHIP8_CORE_LIB> 
        $<TARGET_OBJECTS:CHIP8_GUI_LIB>
    )

    target_include_directories(${GUI_EXECUTABLE} PRIVATE include)

    target_compile_features(${GUI_EXECUTABLE} PRIVATE cxx_std_17)

    set_property(TARGET ${GUI_EXECUTABLE} PROPERTY LINK_WHAT_YOU_USE TRUE)

    include(chip8_qt)
    target_add_qt(${GUI_EXECUTABLE})

    include(chip8_sfml)
    target_add_sfml(${GUI_EXECUTABLE})

    include(chip8_coverage)
    target_add_coverage(${GUI_EXECUTABLE})

    include(chip8_compiler_warnings)
    target_add_compiler_warnigs(${GUI_EXECUTABLE})
endif()

if(BUILD_TESTS)
    enable_testing()

    set(TESTS_EXECUTABLE ${PROJECT_NAME}_tests)

    include(chip8_tests_lib)
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

    include(chip8_coverage)
    target_add_coverage(${TESTS_EXECUTABLE})

    include(chip8_compiler_warnings)
    target_add_compiler_warnigs(${TESTS_EXECUTABLE})

    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${TESTS_EXECUTABLE})
endif()

install(TARGETS ${MAIN_EXECUTABLE} DESTINATION bin)
install(TARGETS ${TESTS_EXECUTABLE}      DESTINATION bin)
install(TARGETS ${GUI_EXECUTABLE}        DESTINATION bin)

include(chip8_uninstall)
