//
// Created by jora on 6/21/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include "Request.hpp"

using Answer = std::tuple<std::string, std::string, std::vector<std::string>>; /// url, title, found words


class Server {
public:
	Server(unsigned long listeningPort = 4554);
	Request getRequest();
	void sendAnswer(const std::vector<Answer>& answers);
};

#endif //SEARCH_SERVER_HPP
