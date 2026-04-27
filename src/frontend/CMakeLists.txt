qt_add_executable(FBDSimulatorGUI MANUAL_FINALIZATION
    main.cpp
    mainwindow.cpp
    simulatorbridge.cpp
    views/canvaspanel.cpp
    views/fbdcanvasview.cpp
    views/propertypanel.cpp
    views/dashboardview.cpp
    mainwindow.ui
    views/canvaspanel.ui
    views/propertypanel.ui
    views/dashboardview.ui
)

target_include_directories(FBDSimulatorGUI
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/views
)

target_link_libraries(FBDSimulatorGUI PRIVATE
    FBDSimulatorCore
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

qt_finalize_executable(FBDSimulatorGUI)

if(WIN32)
    get_target_property(QT_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_QMAKE_EXECUTABLE}" DIRECTORY)

    add_custom_command(TARGET FBDSimulatorGUI POST_BUILD
        COMMAND "${QT_BIN_DIR}/windeployqt.exe"
                --no-translations
                --no-system-d3d-compiler
                --no-opengl-sw
                "$<TARGET_FILE:FBDSimulatorGUI>"
        COMMENT "Running windeployqt for FBDSimulatorGUI"
        VERBATIM
    )
endif()

install(TARGETS FBDSimulatorGUI
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
