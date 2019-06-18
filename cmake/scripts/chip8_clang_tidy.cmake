function(target_add_clang_tidy TARGET_NAME_ARG)

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        find_program(
            CLANG_TIDY_EXE
            NAMES "clang-tidy"
            DOC "Path to clang-tidy executable"
            )

        if(NOT CLANG_TIDY_EXE)
            message(FATAL_ERROR "Clang-tidy not found.")
        else()
            message(STATUS "Clang-tidy found: ${CLANG_TIDY_EXE}")
            set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*")
        endif()

        if(CLANG_TIDY_EXE)
            set_target_properties(
                ${TARGET_NAME_ARG} PROPERTIES
                CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
                )
        endif()

    endif()

endfunction(target_add_clang_tidy)
