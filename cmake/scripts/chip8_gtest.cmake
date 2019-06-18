macro(target_add_gtest TARGET_NAME_ARG)

    if (NOT GTEST_FOUND)
        find_package(GTest)
    endif()

    if (NOT GTEST_FOUND)
        message("Could not find GTest library. It will be fetch and compiled.")
        set(EXTERNAL_GTEST_PATH depends/googletest)
        execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        option(INSTALL_GTEST "" OFF)
        option(INSTALL_GMOCK "" OFF)
        add_subdirectory(${EXTERNAL_GTEST_PATH})

        set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include)
        set(GTEST_LIBRARIES gtest)
        set(GTEST_FOUND TRUE)
    endif()

    target_include_directories(${TARGET_NAME_ARG} PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME_ARG} PRIVATE ${GTEST_LIBRARIES})

endmacro(target_add_gtest)
