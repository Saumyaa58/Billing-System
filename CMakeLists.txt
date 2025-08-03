cmake_minimum_required(VERSION 3.16)

project(grocifyy LANGUAGES C)

add_executable(grocifyy
    product.h
    product.c
    main.c)

include(GNUInstallDirs)
install(TARGETS grocifyy
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
