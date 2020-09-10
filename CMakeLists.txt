project(wombatinstaller)
cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(/usr/local/include)
include_directories(/usr/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Curses)
find_library(LIBMENU menu)
find_library(CJSON_LIB cjson)
find_library(USPP uspp)
find_library(ARGP argp)

message(STATUS "MENU ${LIBMENU} ${CJSON_LIB} ${USPP} ${ARGP}")

add_executable(witui wombatinstaller/tui.c)

add_executable(installer wombatinstaller/installer.c)

target_link_libraries(witui LINK_PUBLIC Curses ${LIBMENU})

target_link_libraries(installer LINK_PUBLIC ${CJSON_LIB} ${ARGP})