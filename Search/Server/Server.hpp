//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include <iostream>
#include <cstring>
#include <queue>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include "Request.hpp"
#include "../SearchResult.hpp"

#define MAX_INPUT_SIZE 2048

class Server {
private:
	int description{};
	std::queue<std::string> requestContents{};

public:
	explicit Server(unsigned long lisPort);
	~Server();
	void sendAnswer(const SearchResult& results) const;
	inline Request getRequest()
	{
		Request tmp(this->requestContents.front());
		this->requestContents.pop();
		return tmp;
	}

private:
	void createBindSocket(unsigned long lisPort);
	[[noreturn]] void listen();
	static inline void checkSuccess(int value, const std::string& logMessage)
	{
		if (value == -1) {
			std::cerr << "Got an error from Server" << std::endl;
			exit(errno);
		}
		std::cout << logMessage << std::endl;
	}
};

#endif //SEARCH_SERVER_HPP
