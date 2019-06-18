function(target_add_compiler_warnigs TARGET_NAME_ARG)

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
            message(FATAL_ERROR "Insufficient Clang version")
        endif()

        message(STATUS "Setting Clang warnings")

        set(COMPILE_WARNINGS 
            -Wall 
            -Wextra 
            -Wpedantic
            -Wfatal-errors
        )

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0.0")
            message(FATAL_ERROR "Insufficient GCC version")
        endif()

        message(STATUS "Setting GCC warnings")

        set(COMPILE_WARNINGS
            -Wall 
            -Wextra 
            -Wpedantic
            -Wfatal-errors
        )

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        message(STATUS "Setting Intel C++ warnings")

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        message(STATUS "Setting Visual Studio C++ warnings")

    endif()

    target_compile_options(${TARGET_NAME_ARG} PRIVATE ${COMPILE_WARNINGS})

endfunction(target_add_compiler_warnigs)
