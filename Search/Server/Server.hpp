//
// Created by jora on 6/21/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "Searcher/Searcher.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class Server {
private:
	Searcher searcher;
	http_listener listener;

public:
	explicit Server(const DatabaseInfo& dbInfo, unsigned long lisPort = 4554);
	~Server();
	void start();

private:
    void handleGet(const http_request& request);
};

#endif //SEARCH_SERVER_HPP
