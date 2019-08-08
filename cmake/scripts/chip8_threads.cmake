macro(target_link_threads TARGET_NAME_ARG)

    find_package(Threads REQUIRED)
    target_link_libraries(${TARGET_NAME_ARG} PUBLIC Threads::Threads)

endmacro(target_link_threads)


