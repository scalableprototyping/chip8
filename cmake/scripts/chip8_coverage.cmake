function(target_add_coverage TARGET_NAME_ARG)

    if (COVERAGE)
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            set(COVERAGE_EXCLUDES "/usr/include/\\*;" PARENT_SCOPE)
            target_compile_options(${TARGET_NAME_ARG} PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
            target_link_libraries(${TARGET_NAME_ARG} PRIVATE -fprofile-arcs -ftest-coverage)
        endif()
    endif()

endfunction(target_add_coverage)
