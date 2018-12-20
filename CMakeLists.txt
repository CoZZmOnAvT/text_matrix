cmake_minimum_required(VERSION "3.2")
project(text_matrix LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall -Wextra -Werror")

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(${PROJECT_NAME}_core ${SOURCES})
target_link_libraries(${PROJECT_NAME}_core ncurses ncursesw)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core ncurses ncursesw)
