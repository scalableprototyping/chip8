function(target_add_iwyu TARGET_NAME_ARG)

    if (NOT INCLUDE_WHAT_YOU_USE_EXE)
        find_program(
            INCLUDE_WHAT_YOU_USE_EXE
            NAMES "include-what-you-use"
            DOC "Path to include-what-you-use executable"
            )
    endif()

    if(NOT INCLUDE_WHAT_YOU_USE_EXE)
        message(FATAL_ERROR "include-what-you-use not found.")
    endif()

    if(INLCUDE_WHAT_YOU_USE_EXE)
        set_property(
            TARGET ${TARGET_NAME_ARG} 
            PROPERTY CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use"
        )
    endif()

endfunction(target_add_iwyu)
