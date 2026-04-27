set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(FBDSimulatorGUI
    main.cpp
    mainwindow.cpp
    simulatorbridge.cpp
    views/fbdcanvasview.cpp
    views/propertypanel.cpp
    views/dashboardview.cpp
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

qt_generate_deploy_app_script(
    TARGET FBDSimulatorGUI
    OUTPUT_SCRIPT deploy_gui_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_gui_script})
