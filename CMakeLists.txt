cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(chip_8_cpp VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

list(APPEND INTERPRETER_SOURCE_FILES
    src/Interpreter.cpp
    src/io/Speaker.cpp
    src/io/Display.cpp
    src/details/memory.cpp
    src/details/audio.cpp
)

# TODO: 
# I couldn't make it work, so I'm going to separate between arch and 
# ubuntu. We should clean this up 
if(OS_ARCH)
    set(EXECUTABLE_NAME ${PROJECT_NAME}_interpreter)
    add_executable(${EXECUTABLE_NAME} src/main.cpp ${INTERPRETER_SOURCE_FILES})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
    find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
endif()

if(OS_UBUNTU)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules/")
    find_package(SFML 2.3 COMPONENTS graphics audio window system)
    add_executable(${PROJECT_NAME}_interpreter src/main.cpp ${INTERPRETER_SOURCE_FILES})
    target_include_directories(${PROJECT_NAME}_interpreter PRIVATE include ${SFML_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_interpreter PRIVATE ${SFML_LIBRARIES})
    target_compile_options(${PROJECT_NAME}_interpreter PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
endif()

if(OS_TRAVIS)
    find_package(SFML 2.1 COMPONENTS graphics audio window system)
    add_executable(${PROJECT_NAME}_interpreter src/main.cpp ${INTERPRETER_SOURCE_FILES})
    target_include_directories(${PROJECT_NAME}_interpreter PRIVATE include ${SFML_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_interpreter PRIVATE ${SFML_LIBRARIES})
    target_compile_options(${PROJECT_NAME}_interpreter PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
endif()

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest)

    if (GTEST_FOUND)
        execute_prcess(COMMAND echo ${GTEST_ROOT})
    endif()

    if(NOT GTEST_FOUND)
        message("Could not find gtest library. It will be fetch and compiled..")
        set(EXTERNAL_GTEST_PATH depends/googletest)
        execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        option(INSTALL_GTEST "" OFF)
        option(INSTALL_GMOCK "" OFF)
        add_subdirectory(${EXTERNAL_GTEST_PATH})
        set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)
        set(GTEST_LIBRARIES gtest)
    endif()

    list(APPEND TEST_SOURCE_FILES
        ${INTERPRETER_SOURCE_FILES}
        test/rom_test.cpp
        test/timer_test.cpp
        test/speaker_test.cpp
        test/display_test.cpp
    )

    set(EXECUTABLE_NAME_TEST ${PROJECT_NAME}_tests)

    if(OS_ARCH)
        add_executable(${EXECUTABLE_NAME_TEST} test/test_main.cpp ${TEST_SOURCE_FILES})
        target_include_directories(${EXECUTABLE_NAME_TEST} PRIVATE include ${GTEST_INCLUDE_DIRS})
        find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
        target_link_libraries(${EXECUTABLE_NAME_TEST} PRIVATE 
            ${GTEST_LIBRARIES} 
            sfml-graphics sfml-audio sfml-window sfml-system
            )
        target_compile_options(${EXECUTABLE_NAME_TEST} PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
    endif()

    if(OS_UBUNTU)
        add_executable(${EXECUTABLE_NAME_TEST} test/test_main.cpp ${TEST_SOURCE_FILES})
        target_include_directories(${EXECUTABLE_NAME_TEST} PRIVATE include ${GTEST_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS})
        target_link_libraries(${EXECUTABLE_NAME_TEST} PRIVATE ${GTEST_LIBRARIES} ${SFML_LIBRARIES})
        target_compile_options(${EXECUTABLE_NAME_TEST} PRIVATE --std=c++17 -Wall -Werror -Wfatal-errors -pedantic)
    endif()

    add_test(Chip8TestSuite ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}_tests)
endif()
