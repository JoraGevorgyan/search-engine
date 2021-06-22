//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SEARCH_HPP
#define SEARCH_SEARCH_HPP

#include <string>
#include <vector>
#include "Database/Database.hpp"

using SearchResult = std::tuple<std::string, std::string, std::vector<std::string>>; /// url, title, found words

class Searcher {
private:
	Database database;

public:
	Searcher(const std::string& dbName, const std::string& server, const std::string& username,
			const std::string& password, unsigned long port);

	std::vector<SearchResult> find(const std::string& requiredOffer, int requiredCount);

};

#endif //SEARCH_SEARCH_HPP
