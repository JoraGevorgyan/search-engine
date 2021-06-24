cmake_minimum_required(VERSION 3.1)
project(CLI)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${BINARY}_run main.cpp)

add_subdirectory(UI)

include_directories(UI)

target_link_libraries(${BINARY}_run PUBLIC
                      ${BINARY}_ui)

