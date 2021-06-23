//
// Created by jora on 5/14/21.
//

#include "Searcher.hpp"

Searcher::Searcher(const std::string& dbName, const std::string& dbServer,
                  const std::string& dbUsername, const std::string& dbPassword,
                  const unsigned long& dbPort, int maxResultCount)
        : connection(true), maxResultCount(maxResultCount)
{
    this->connection.connect(dbName.c_str(), dbServer.c_str(), dbUsername.c_str(), dbPassword.c_str(), dbPort);
}