# ***Search Engine***

__by [Jora Gevorgyan](https://www.linkedin.com/in/jora-gevorgyan-b8b0151b9)__

_This is a simple project which allows You to search something and find some links containing the words you're looking
for, and shows the results sorted by count of words found._

### Design

___There're three subprojects___

- [Crawler](./Crawler) - Recursively goes from given websites, and their containing links, and saves the found data in
  database.
- [Search](./Search) - Creates a server listening HTTP requests, finds all links contain required content from client
  and sends an answer.
- [UI (User Interface)](./UI) - Reads from user texts to search and sends the HTTP request to the server, then shows an
  answer.

### Tech
- Operating System - UNIX/Linux (or other UNIX/Linux based operating systems)
- Compiler - g++ 5.0+/clang++ 5.0+
- Build system - [CMake](https://cmake.org/)
- Database - [MySQL](https://www.mysql.com/)

__Used libraries with their references are shown below.__

- [curlpp](https://github.com/jpbarrette/curlpp/blob/master/doc/guide.pdf)
- [gumbo](https://github.com/google/gumbo-parser)
- [mysqlpp](https://github.com/rpetrich/mysqlpp)
- [cpprestsdk](https://github.com/microsoft/cpprestsdk)
- [googletest](https://github.com/google/googletest)
- [nlohmann JSON](https://github.com/nlohmann/json)

### How to use

- Build stage - do following steps in order in your bash terminal
  - ``sudo ./build.sh`` - this will install all packages You need, create the database and compile all components 
    of the program 
  - ``./bin/crawler_run &``
  - ``./bin/search_run &``
  - ``./bin/UI_run``
  - If You would like to use this project on non Linux machine - look
  on [how to do it](https://preshing.com/20170511/how-to-build-a-cmake-based-project/), but there's no warranty that it
  will work successfully!

