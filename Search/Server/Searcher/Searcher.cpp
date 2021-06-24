//
// Created by jora on 5/14/21.
//

#include "Searcher.hpp"

Searcher::Searcher(const std::string& dbName, const std::string& dbServer,
                   const std::string& dbUsername, const std::string& dbPassword,
                   const unsigned long& dbPort, size_t maxResultCount)
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
	std::map<std::pair<int, std::string>, SearchResult> results{};
	int keyValue = 0;
	const auto foundInTitle = this->find(requiredOffer, "title");
	this->add(results, foundInTitle, ++keyValue);
	const auto foundInDesc = this->find(requiredOffer, "description");
	this->add(results, foundInTitle, ++keyValue);
	const auto foundInContent = this->find(requiredOffer, "content");
	this->add(results, foundInTitle, ++keyValue);
	return Searcher::toVector(results);
}

std::map<std::string, SearchResult> Searcher::find(const std::string& content, const std::string& rowName)
{
	std::cout << "Searcher: start searching for '" << content << "' in " << rowName << "row" << std::endl;
	mysqlpp::Query query(&this->connection);
	std::string pureContent{};
	query.escape_string(&pureContent, content.c_str());
	const std::string& command = "SELECT * FROM documents WHERE MATCH (" + rowName + ") AGAINST ('"
			+ pureContent + "' IN NATURAL MODE)";
	auto queryResult = query.use(command.c_str());
	
	std::map<std::string, SearchResult> results{};
	while (mysqlpp::Row row = queryResult.fetch_row()) {
		const std::string url = row["url"].data();
		results.insert(
				std::pair<std::string, SearchResult>(url, { url, row["title"].data(), row["description"].data() }));
	}
	if (results.empty()) {
		std::cout << "Searcher: there's no result" << std::endl;
	}
	else {
		std::cout << "Searcher: found some results" << std::endl;
	}
	return results;
}

void Searcher::add(std::map<std::pair<int, std::string>, SearchResult>& container,
		const std::map<std::string, SearchResult>& results, int keyValue) const
{
	if (container.size() >= this->maxResultCount) {
		return;
	}
	for (const auto& tmp : results) {
		container.insert(
				std::pair<std::pair<int, std::string>, SearchResult>(std::make_pair(keyValue, tmp.first), tmp.second));
	}
}

std::vector<SearchResult> Searcher::toVector(const std::map<std::pair<int, std::string>, SearchResult>& source) const
{
	const size_t size = std::min(source.size(), this->maxResultCount);
	std::vector<SearchResult> result(size);
	auto srcBegin = source.begin();
	auto destBegin = result.begin();
	auto destEnd = result.end();
	
	while (destBegin != destEnd) {
		*destBegin = srcBegin->second;
		++destBegin;
		++srcBegin;
	}
	return result;
}
