set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_library(${BINARY}_server STATIC ${SOURCES})

add_subdirectory(Searcher)

target_link_libraries(${BINARY}_server ${BINARY}_server_searcher)

