macro(target_add_clang_tidy TARGET_NAME_ARG)

    find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
        )
    if(NOT CLANG_TIDY_EXE)
        message(STATUS "clang-tidy not found.")
    else()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CLANG_TIDY_FLAGS "${CLANG_TIDY_EXE}" "-checks=*")
    endif()

    if(CLANG_TIDY_EXE)
        set_target_properties(
            ${TARGET_NAME_ARG} PROPERTIES
            CXX_CLANG_TIDY "${CLANG_TIDY_FLAGS}"
            )
    endif()

endmacro(target_add_clang_tidy)
