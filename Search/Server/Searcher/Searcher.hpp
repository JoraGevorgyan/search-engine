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
    std::vector<std::string> foundWords;
};

class Searcher {
private:
    mysqlpp::Connection connection;
    int maxResultCount;

public:
    Searcher(const std::string& DbName, const std::string& DbServer,
            const std::string& DbUsername, const std::string& DbPassword,
            const unsigned long& DbPort, int maxResultCount);
    ~Searcher() noexcept;
    std::vector<SearchResult> find(const std::string& requiredOffer);

private:
	static std::vector<std::string> divideByWords(const std::string& str);
	void findAdd(std::vector<SearchResult>& results, const std::vector<std::string>& content);
	static std::string to_string(const std::vector<std::string>& arr);
	
};

#endif //SEARCH_SEARCHER_HPP
