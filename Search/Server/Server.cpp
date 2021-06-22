//
// Created by jora on 6/21/21.
//

#include "Server.hpp"

Server::Server(const DatabaseInfo& dbInfo, unsigned long listeningPort)
        : searcher(Searcher(dbInfo))
{
    utility::string_t address = U("http://*:") + std::to_string(listeningPort);
    uri_builder uri(address);
    address = uri.to_uri().to_string();
    this->listener = http_listener(address, http_listener_config());
}

Server::~Server()
{
    this->listener.close().wait();
}

void Server::start()
{
    this->listener.support(methods::GET, std::bind(&Server::handleGet, this, std::placeholders::_1));
    this->listener.open().wait();
}

void Server::handleGet(const http_request& request)
{

}
