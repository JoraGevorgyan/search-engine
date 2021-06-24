//
// Created by jora on 6/21/21.
//

#include "Server.hpp"

Server::Server(const std::string& dbName, const std::string& dbServer,
               const std::string& dbUsername, const std::string& dbPassword,
               const unsigned long& dbPort, unsigned long listeningPort, size_t maxResultCount)
        : searcher{ Searcher(dbName, dbServer, dbUsername, dbPassword, dbPort, maxResultCount) }
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
    this->listener.support(methods::GET, [this](auto&& arg) { handleGet(std::forward<decltype(arg)>(arg)); });
    this->listener.support(methods::POST, &Server::handleOtherMethods);
    this->listener.support(methods::PUT, &Server::handleOtherMethods);
    this->listener.support(methods::DEL, &Server::handleOtherMethods);
    this->listener.open().wait();
}

void Server::handleGet(const http_request& request)
{
	std::cout << "Server: got a request of GET type." << std::endl;
    const auto requiredOffer = request.to_string();
    const auto result = this->searcher.find(requiredOffer);
    if (result.empty()) {
	    std::cout << "Server: reply to client with NO content" << std::endl;
	    request.reply(status_codes::NoContent);
        return;
    }
    std::cout << "Server: found some results for required offer" << std::endl;;
    std::cout << "Server: reply to client" << std::endl;
    request.reply(status_codes::OK, Server::makeJson(result));
}

json::value Server::makeJson(const std::vector<SearchResult>& results)
{
    std::vector<json::value> arr(results.size());

    for (int i = 0; i < arr.size(); ++i) {
        const auto& tmp = results[i];
        arr[i]["url"] = json::value::string(tmp.url);
        arr[i]["title"] = json::value::string(tmp.title);
        arr[i]["description"] = json::value::string(tmp.description);
    }
    return json::value::array(arr);
}
