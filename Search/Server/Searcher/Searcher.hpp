//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SEARCHER_HPP
#define SEARCH_SEARCHER_HPP

#include <string>
#include <vector>
#include "Database/Database.hpp"

struct SearchResult {
    std::string url;
    std::string title;
    std::vector<std::string> foundWords;
};

struct DatabaseInfo;

class Searcher {
private:
    Database database;

public:
    Searcher(const DatabaseInfo& dbInfo, int maxResultCount);

    std::vector<SearchResult> find(const std::string& requiredOffer);

};

#endif //SEARCH_SEARCHER_HPP
