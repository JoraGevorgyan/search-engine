CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
project(crawler)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Crawler)
add_subdirectory(ConfigParser)
add_subdirectory(PageLoader)
add_subdirectory(Parser)
add_subdirectory(LinkEntryRepo)
add_subdirectory(WebsiteRepo)
add_subdirectory(DocumentRepo)
add_subdirectory(Tests)

# install crawler_run and crawler_test in bin directory
install(TARGETS crawler_run DESTINATION bin)
install(TARGETS crawler_test DESTINATION bin)

# change default install path if user has not set any directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "../" CACHE PATH "default install path" FORCE)
endif ()

