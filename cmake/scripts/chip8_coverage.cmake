function(target_add_coverage TARGET_NAME_ARG)

    set(COVERAGE_EXCLUDES "/usr/include/\\*;" PARENT_SCOPE)
    target_compile_options(${TARGET_NAME_ARG} PRIVATE --coverage)
    target_link_libraries(${TARGET_NAME_ARG} PRIVATE --coverage)

endfunction(target_add_coverage)
