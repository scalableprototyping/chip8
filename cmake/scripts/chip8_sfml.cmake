macro(target_add_sfml TARGET_NAME_ARG)

    if (NOT SFML_FOUND)
        find_package(SFML 2.5 COMPONENTS graphics audio window system)
    endif()

    if (NOT SFML_FOUND)
        find_package(SFML 2.3 COMPONENTS graphics audio window system)
    endif()

    if (NOT SFML_FOUND)
        message(FATAL_ERROR "SFML could not be found.")
    endif()

    if (SFML_VERSION VERSION_GREATER_EQUAL 2.5)
        target_link_libraries(${TARGET_NAME_ARG} PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
    elseif(SFML_VERSION VERSION_GREATER_EQUAL 2.3)
        target_include_directories(${TARGET_NAME_ARG} PRIVATE ${SFML_INCLUDE_DIRS})
        target_link_libraries(${TARGET_NAME_ARG} PRIVATE ${SFML_LIBRARIES})
    endif()

endmacro(target_add_sfml)
