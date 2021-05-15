CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

project(Search)
set(BINARY ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ConfigParser)
add_subdirectory(Search)
add_subdirectory(Server)

add_executable(${BINARY}_run main.cpp)

set(INCLUDE_DIR Search Server ConfigParser)
include_directories(${INCLUDE_DIR})

target_link_libraries(${BINARY}_run PUBLIC
                      ${BINARY}_server ${BINARY}_search ${BINARY}_configParser)

