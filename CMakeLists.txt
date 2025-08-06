cmake_minimum_required(VERSION 3.16)

project(Billingapp VERSION 0.1 LANGUAGES C CXX)

# Optional: set architecture (Mac users: arm64 for M1/M2, x86_64 for Intel)
# set(CMAKE_OSX_ARCHITECTURES "arm64")

# Set Qt build settings
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find Qt 6
find_package(QT REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Source files
set(C_SOURCES
    login.c
    product.c
)

set(CPP_SOURCES
    main.cpp
    loginwindow.cpp
    menuwindow.cpp
    billingscreen.cpp
    receiptscreen.cpp
)

set(HEADERS
    login.h
    product.h
    loginwindow.h
    menuwindow.h
    billingscreen.h
    receiptscreen.h
)

set(UIS
    loginwindow.ui
    menuwindow.ui
    billingscreen.ui
    receiptscreen.ui
)

# Create executable with Qt 6
qt_add_executable(Billingapp
    MANUAL_FINALIZATION
    ${C_SOURCES}
    ${CPP_SOURCES}
    ${HEADERS}
    ${UIS}
    billingscreen.h

    receiptscreen.h
    build/Qt_6_9_1_for_macOS-Debug/receiptscreen.cpp


)

# Link Qt 6 widgets
target_link_libraries(Billingapp PRIVATE Qt6::Widgets)

# Finalize for Qt 6
qt_finalize_executable(Billingapp)

# Optional: Show Qt version in build logs
message(STATUS "Using Qt version: ${Qt6_VERSION}")
