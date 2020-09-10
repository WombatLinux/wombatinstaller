project(wombatinstaller)
cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(/usr/local/include)
include_directories(/usr/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Curses)
find_library(LIBMENU menu)

message(STATUS "MENU ${LIBMENU}")

add_executable(installer wombatinstaller/installer.c)

target_link_libraries(installer LINK_PUBLIC Curses ${LIBMENU})