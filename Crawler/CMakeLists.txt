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

# install crawler_run and crawler_test in bin directory
install(TARGETS crawler_run DESTINATION bin)

# change default install path if user has not set any directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "../" CACHE PATH "default install path" FORCE)
endif ()

#set commands for checking program components
set(CHECK_LOADER_COMMAND make crawler_loader && ${CMAKE_CXX_COMPILER} ${CMAKE_HOME_DIRECTORY}/Tests/checkLoader.cc)
set(CHECK_PARSER_COMMAND make crawler_parser && ${CMAKE_CXX_COMPILER} ${CMAKE_HOME_DIRECTORY}/Tests/checkParser.cc)

add_custom_command(OUTPUT CHECK_LOADER COMMAND ${CHECK_LOADER_COMMAND})
add_custom_command(OUTPUT CHECK_PARSER COMMAND ${CHECK_PARSER_COMMAND})

add_custom_target(checkLoader DEPENDS CHECK_LOADER)
add_custom_target(checkParser DEPENDS CHECK_PARSER)

