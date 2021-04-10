set(BINARY ${CMAKE_PROJECT_NAME}_test)
set(INCLUDE_DIR
    ../PageLoader/ ../Parser/
    ../WebsiteRepo/ ../LinkEntryRepo)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

include_directories(${INCLUDE_DIR})
target_link_libraries(
		${BINARY} PUBLIC
		${CMAKE_PROJECT_NAME}_loader
		${CMAKE_PROJECT_NAME}_parser
		gtest pthread)

