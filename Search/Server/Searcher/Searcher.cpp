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

Searcher::~Searcher() noexcept
{
	if (this->connection.connected()) {
		this->connection.disconnect();
	}
}

std::vector<SearchResult> Searcher::find(const std::string& requiredOffer)
{
	std::vector<SearchResult> result{};
	auto words = Searcher::divideByWords(requiredOffer);
	while (!words.empty() && this->maxResultCount < result.size()) {
		std::sort(words.begin(), words.end());
		do {
			this->findAdd(result, words);
		}
		while (std::next_permutation(words.begin(), words.end()) && this->maxResultCount < result.size());
		words.pop_back();
	}
	return result;
}

std::vector<std::string> Searcher::divideByWords(const std::string& str)
{
	std::vector<std::string> result{};
	
	for (int i = 0; i < str.size(); ++i) {
		std::string tmp{};
		while (str[i] != ' ') {
			tmp += str[i++];
		}
		result.push_back(tmp);
	}
	return result;
}

void Searcher::findAdd(std::vector<SearchResult>& results, const std::vector<std::string>& content)
{
	mysqlpp::Query query(&this->connection);
	auto result = query.use("SELECT * FROM documents WHERE  ");
}

std::string Searcher::to_string(const std::vector<std::string>& arr)
{
	std::string str{};
	for (const auto& tmp : arr) {
		str += tmp + ' ';
	}
	return str;
}
