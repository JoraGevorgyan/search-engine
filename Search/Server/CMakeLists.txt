set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.hpp *.cpp)
find_package(cpprestsdk REQUIRED)

add_library(${BINARY}_server STATIC ${SOURCES})

target_link_libraries(${BINARY}_server PRIVATE cpprestsdk::cpprest)

