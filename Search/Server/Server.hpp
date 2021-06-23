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
	explicit Server(const DatabaseInfo& dbInfo, unsigned long listeningPort, int maxResultCount);
	~Server();
	void start();

private:
    void handleGet(const http_request& request);
    static json::value makeJson(const std::vector<SearchResult>& results);
    static inline void handleOtherMethods(const http_request& request)
    {
        request.reply(status_codes::MethodNotAllowed);
    }
};

#endif //SEARCH_SERVER_HPP
