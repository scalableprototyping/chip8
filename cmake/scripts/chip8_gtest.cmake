macro(target_add_gtest TARGET_NAME_ARG)

    if (NOT GTEST_FOUND)
        message("Fetching GTest.")
        set(EXTERNAL_GTEST_PATH depends/googletest)
        execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        option(INSTALL_GTEST "" OFF)
        option(INSTALL_GMOCK "" OFF)
        add_subdirectory(${EXTERNAL_GTEST_PATH})

        set(GTEST_INCLUDE_DIRS ${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)
        set(GTEST_LIBRARIES gtest gmock)
        set(GTEST_FOUND TRUE)

        target_include_directories(${TARGET_NAME_ARG} PRIVATE ${GTEST_INCLUDE_DIRS})
        target_link_libraries(${TARGET_NAME_ARG} PRIVATE ${GTEST_LIBRARIES})
    endif()

endmacro(target_add_gtest)
