//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include "Request.hpp"
#include "../SearchResult.hpp"

class Server {
private:
	int serverDesc{};
	int clientDesc{};
	bool gotMessage;

public:
	Server(const std::string& lisAddress, unsigned long lisPort);
	~Server();
	[[nodiscard]] Request getRequest() const;
	void sendAnswer(const SearchResult& results) const;

};

#endif //SEARCH_SERVER_HPP
