//
// Created by jora on 5/14/21.
//

#ifndef SEARCH_SEARCHER_HPP
#define SEARCH_SEARCHER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "mysql++/mysql++.h"

struct SearchResult {
	std::string url;
	std::string title;
	std::string description;
};

class Searcher {
private:
	mysqlpp::Connection connection;
	size_t maxResultCount;

public:
	Searcher(const std::string& DbName, const std::string& DbServer,
			const std::string& DbUsername, const std::string& DbPassword,
			const unsigned long& DbPort, size_t maxResultCount);
	~Searcher() noexcept;
	std::vector<SearchResult> find(const std::string& requiredOffer);

private:
	std::map<std::string, SearchResult> find(const std::string& content, const std::string& rowName);
	void add(std::map<std::pair<int, std::string>, SearchResult>& container,
			const std::map<std::string, SearchResult>& results, int keyValue) const;
	std::vector<SearchResult> toVector(const std::map<std::pair<int, std::string>, SearchResult>& source) const;
};

#endif //SEARCH_SEARCHER_HPP
