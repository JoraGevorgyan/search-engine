CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(crawler)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(crawler)

add_link_options(-lcurlpp -lcurl)

install(TARGETS crawler_run DESTINATION bin)
install(TARGETS crawler_test DESTINATION bin)
