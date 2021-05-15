//
// Created by jora on 5/14/21.
//

#include "Server.hpp"

Server::Server(const std::string& lisAddress, unsigned long lisPort)
		:gotMessage(false)
{

}

Request Server::getRequest() const
{
	if (!this->gotMessage) {
		return std::move(Request{ .got = false, .requiredOffer = {}, .requiredCount = {} });
	}
	return std::move(Request{ .got = false, .requiredOffer = {}, .requiredCount = {} });
}

void Server::sendAnswer(const SearchResult& results) const
{
	std::cout << results.all.size() << std::endl;
}

Server::~Server()
{
	close(this->clientDesc);
	close(this->serverDesc);
}
