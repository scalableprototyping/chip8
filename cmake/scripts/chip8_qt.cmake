macro(target_add_qt TARGET_NAME_ARG)

    find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
    target_link_libraries(${TARGET_NAME_ARG} PRIVATE Qt5::Widgets Qt5::Qml Qt5::Quick)

endmacro(target_add_qt)

macro(target_add_qt_resources TARGET_NAME_ARG QT_RESOURCES_ARG)

    qt5_add_resources(QT_RESOURCES ${QT_RESOURCES_ARG})
    target_sources(${TARGET_NAME_ARG} PUBLIC ${QT_RESOURCES})

endmacro(target_add_qt_resources)

macro(target_add_qt_headers TARGET_NAME_ARG QT_HEADERS_ARG)

    qt5_wrap_cpp(QT_HEADERS ${QT_HEADERS_ARG})
    target_sources(${TARGET_NAME_ARG} PUBLIC ${QT_HEADERS})

endmacro(target_add_qt_headers)
