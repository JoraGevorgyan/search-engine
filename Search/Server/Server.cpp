//
// Created by jora on 5/14/21.
//

#include "Server.hpp"

Server::Server(unsigned long lisPort)
{
	this->createBindSocket(lisPort);
	this->listen();
}

void Server::createBindSocket(unsigned long lisPort)
{
	this->description = socket(AF_INET, SOCK_STREAM, 0);
	Server::checkSuccess(this->description, "Server socket created successfully.");

	struct sockaddr_in server{};
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(lisPort);
	int success = bind(this->description, (const sockaddr*)&server, sizeof(server));
	Server::checkSuccess(success, "Bind: done successfully.");
}

[[noreturn]] void Server::listen()
{
	int success = ::listen(this->description, MAX_INPUT_SIZE);
	Server::checkSuccess(success, "Server is ready to listen.");

	while (true) {
		sockaddr_in clientAddr{};
		unsigned addrSize = 0;
		int clientDesc = accept(this->description, (sockaddr*)&clientAddr, &addrSize);
		Server::checkSuccess(clientDesc, "Connected from '" + std::string(inet_ntoa(clientAddr.sin_addr)));
		char message[MAX_INPUT_SIZE];
		memset(&message, '\0', MAX_INPUT_SIZE);

		auto readSize = recv(clientDesc, message, MAX_INPUT_SIZE - 1, 0);
		if (readSize == -1) {
			std::cerr << "Error while listening!!" << std::endl;
			close(clientDesc);
			continue;
		}
		if (readSize > 0) {
			this->requestContents.push(std::move(std::string(message)));
		}
		close(clientDesc);
	}
}

void Server::sendAnswer(const SearchResult& results) const
{
	std::cout << results.all.size() << std::endl;
}

Server::~Server()
{
	close(this->description);
}
