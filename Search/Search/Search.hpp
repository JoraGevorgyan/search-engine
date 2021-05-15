//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SEARCH_HPP
#define SEARCH_SEARCH_HPP

#include "Database/Database.hpp"
#include "../SearchResult.hpp"

class Search {
private:
	Database database;

public:
	Search(const std::string& dbName, const std::string& server, const std::string& username,
			const std::string& password, unsigned long port);
	SearchResult find(const std::string& requiredOffer, int requiredCount);

};

#endif //SEARCH_SEARCH_HPP
