macro(target_add_gtest TARGET_NAME_ARG)

    if (NOT GTEST_FOUND)
        message("Fetching GTest.")
        set(EXTERNAL_GTEST_PATH depends/googletest)
        execute_process(COMMAND git submodule update --init -- ${EXTERNAL_GTEST_PATH}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        option(INSTALL_GTEST "" OFF)
        option(INSTALL_GMOCK "" OFF)
        add_subdirectory(${EXTERNAL_GTEST_PATH})

        target_include_directories(${TARGET_NAME_ARG} 
            PRIVATE 
                ${gtest_SOURCE_DIR}/include 
            )
        target_link_libraries(${TARGET_NAME_ARG} PRIVATE gtest)

        set(GTEST_FOUND TRUE)

    endif()

endmacro(target_add_gtest)
