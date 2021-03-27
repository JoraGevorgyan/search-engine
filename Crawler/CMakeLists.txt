CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(crawler)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Crawler)
add_subdirectory(PageLoader)
add_subdirectory(Parser)
add_subdirectory(LinkEntryRepository)
add_subdirectory(WebsiteRepository)
add_subdirectory(tests)

# install crawler_run and crawler_test in bin directory
install(TARGETS crawler_run DESTINATION bin)
install(TARGETS crawler_test DESTINATION bin)

# change default install path if user has not set any directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "../" CACHE PATH "default install path" FORCE )
endif()