function(target_add_clang_tidy TARGET_NAME_ARG CLANG_TIDY_CHECKS)

    if(${CLANG_TIDY})
        find_program(
            CLANG_TIDY_PATH
            NAMES "clang-tidy"
            DOC "Path to clang-tidy executable"
            )

        if(NOT CLANG_TIDY_PATH)
            message(FATAL_ERROR "Clang-tidy not found.")
        endif()
        
        execute_process (
            COMMAND ${CLANG_TIDY_PATH} --version
            OUTPUT_VARIABLE CLANG_TIDY_VERSION
        )

        # if clang-tidy version > 8.0.0
        if(${CLANG_TIDY_VERSION} MATCHES "([1-9]+[0-9]|[8-9])\.([0-9]+)\.([0-9]+)")
            message(STATUS "Clang-tidy found: ${CLANG_TIDY_PATH}")
            set(CLANG_TIDY_PATH_AND_OPTIONS "${CLANG_TIDY_PATH}" "${CLANG_TIDY_CHECKS}")

            set_target_properties(
                ${TARGET_NAME_ARG} PROPERTIES
                CXX_CLANG_TIDY "${CLANG_TIDY_PATH_AND_OPTIONS}"
                )
        else()
            message(FATAL_ERROR 
                "Minimum clang-tidy version is 8.0.0\n
                Current version:\n ${CLANG_TIDY_VERSION}\n
                Please upgrade."
            )
        endif()
    endif()

endfunction(target_add_clang_tidy)
