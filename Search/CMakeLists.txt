CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(search)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable(${BINARY}_run main.cpp)

add_subdirectory(ConfigParser)
add_subdirectory(Server)

include_directories(Server ConfigParser)

target_link_libraries(${BINARY}_run PUBLIC
                      ${BINARY}_server ${BINARY}_configParser)

