set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

add_library(${BINARY}_loader STATIC ${SOURCES})
target_link_libraries(${BINARY}_loader -lcurl -lcurlpp)

