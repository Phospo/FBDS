cmake_minimum_required(VERSION 3.31)

project(FBDSimulator LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(FBDSimulatorCore STATIC
    cinput.cpp
    coutput.cpp
    cfunctionblock.cpp
    cconnection.cpp
    sdatasample.cpp
    stimestamp.cpp
    csimulatorfbd.cpp
    ccontainerfbd.cpp
    csimengine.cpp
    cfbdbuilder.cpp
    csiggen.cpp
)

target_include_directories(FBDSimulatorCore
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(FBDSimulator main.cpp)

target_link_libraries(FBDSimulator PRIVATE
    FBDSimulatorCore
)

add_executable(FBDSimulatorTests
    tests/cfunctionblock_tests.cpp
    tests/csiggen_tests.cpp
)

target_link_libraries(FBDSimulatorTests PRIVATE
    FBDSimulatorCore
    GTest::gtest_main
)

target_include_directories(FBDSimulatorTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(FBDSimulatorTests)

include(GNUInstallDirs)
install(TARGETS FBDSimulator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
