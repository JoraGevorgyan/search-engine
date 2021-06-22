//
// Created by jora on 6/21/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "Request.hpp"
#include "Searcher.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

using Answer = std::tuple<std::string, std::string, std::vector<std::string>>; /// url, title, found words

class Server {
private:
    http_listener listener;
    Searcher searcher;

public:
	explicit Server(unsigned long listeningPort = 4554);
	void start();

private:
    void
};

#endif //SEARCH_SERVER_HPP
