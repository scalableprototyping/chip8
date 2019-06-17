find_program(
    INCLUDE_WHAT_YOU_USE_EXE
    NAMES "include-what-you-use"
    DOC "Path to include-what-you-use executable"
    )
if(NOT INCLUDE_WHAT_YOU_USE_EXE)
    message(STATUS "include-what-you-use not found.")
else()
    message(STATUS "include-what-you-use found: ${INCLUDE_WHAT_YOU_USE_EXE}")
endif()

if(INLCUDE_WHAT_YOU_USE_EXE)
    set(CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use")
endif()
