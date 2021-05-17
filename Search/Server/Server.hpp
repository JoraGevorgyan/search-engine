//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SERVER_HPP
#define SEARCH_SERVER_HPP

#include <iostream>
#include <cstring>
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
	bool gotMessage;

public:
	explicit Server(unsigned long lisPort);
	~Server();
	[[nodiscard]] Request getRequest() const;
	void sendAnswer(const SearchResult& results) const;

private:
	void createBindSocket(unsigned long lisPort);
	void listen();
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
