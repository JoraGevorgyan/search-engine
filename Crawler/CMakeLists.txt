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

#set short names for beauty style
set(MAKE +${CMAKE_MAKE_PROGRAM})
set(CXX ${CMAKE_CXX_COMPILER})
set(CXX_FLAGS -lgtest -lpthread -lcurl -lcurlpp -lgumbo)
set(DIR ${CMAKE_HOME_DIRECTORY}/Tests)
set(LOADER ${CMAKE_BINARY_DIR}/PageLoader/libcrawler_loader.a)
set(PARSER ${CMAKE_BINARY_DIR}/Parser/libcrawler_parser.a)

#set commands for running tests
set(RUN mv ./a.out ${DIR} && cd ${DIR} && ./a.out && rm ./a.out && cd -)
set(CHECK_LOADER_COMMAND ${MAKE} crawler_loader && ${CXX} ${DIR}/checkLoader.cc ${LOADER} ${CXX_FLAGS} && ${RUN})
set(CHECK_PARSER_COMMAND ${MAKE} crawler_parser && ${CXX} ${DIR}/checkParser.cc ${PARSER} ${CXX_FLAGS} && ${RUN})

add_custom_command(OUTPUT CHECK_LOADER COMMAND ${CHECK_LOADER_COMMAND})
add_custom_command(OUTPUT CHECK_PARSER COMMAND ${CHECK_PARSER_COMMAND})

add_custom_target(checkLoader DEPENDS CHECK_LOADER)
add_custom_target(checkParser DEPENDS CHECK_PARSER)

