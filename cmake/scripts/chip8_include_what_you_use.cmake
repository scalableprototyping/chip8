function(target_add_iwyu TARGET_NAME_ARG)

    if (IWYU)
        if (NOT IWYU_PATH)
            find_program(
                IWYU_PATH
                NAMES "include-what-you-use"
                DOC "Path to IWYU executable"
                )
        endif()

        if(NOT IWYU_PATH)
            message(FATAL_ERROR "IWYU not found.")
        endif()

        set(IWYU_PATH_AND_OPTIONS ${IWYU_PATH} 
            #-Xiwyu --verbose=1
            -Xiwyu --cxx17ns
        )

        set_property(
            TARGET ${TARGET_NAME_ARG} 
            PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH_AND_OPTIONS}
        )
    endif()

endfunction(target_add_iwyu)
