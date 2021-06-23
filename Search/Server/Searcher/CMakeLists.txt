set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

add_library(${BINARY}_server_searcher STATIC ${SOURCES})

target_link_libraries(${BINARY}_server_searcher -lmysqlclient -lmysqlpp)
target_compile_options(${BINARY}_server_searcher PUBLIC -I/usr/include/mysql)

