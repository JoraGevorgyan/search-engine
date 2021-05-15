//
// Created by jora on 5/15/21.
//

#ifndef SEARCH_SEARCHRESULT_HPP
#define SEARCH_SEARCHRESULT_HPP

#include <vector>
#include <string>

struct Info {
	std::string url;
	std::string title;
	std::string foundWords;
};

struct SearchResult {
	bool found;
	std::vector<Info> all;
};

#endif //SEARCH_SEARCHRESULT_HPP
