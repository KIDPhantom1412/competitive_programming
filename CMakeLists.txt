cmake_minimum_required(VERSION 3.16)

project(competitive_programming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(competitive_programming main.cpp
    output.txt
    .clang-format
)

target_sources(competitive_programming
    PRIVATE
        input.txt
)

include(GNUInstallDirs)
install(TARGETS competitive_programming
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
