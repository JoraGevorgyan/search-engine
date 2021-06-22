//
// Created by jora on 6/21/21.
//

#include "Server.hpp"

Server::Server(unsigned long listeningPort)
{
    utility::string_t address = U("http://*:") + std::to_string(listeningPort);
    uri_builder uri(address);
    address = uri.to_uri().to_string();
    this->listener = http_listener(address, http_listener_config());
}

void Server::start()
{
    this->listener.support(methods::GET, &this->)
}
