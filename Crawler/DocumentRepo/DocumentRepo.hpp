//
// Created by jora on 4/11/21.
//

#ifndef CRAWLER_DOCUMENTREPO_HPP
#define CRAWLER_DOCUMENTREPO_HPP

#include <vector>
#include "Document.hpp"

class DocumentRepo {
private:
	std::vector<Document> database;

public:
	[[nodiscard]] inline const std::vector<Document>& getAll() const
	{
		return this->database;
	}
	[[nodiscard]] std::optional<Document> getByUrl(const std::string& url);
	void save(const Document& document);
};

#endif //CRAWLER_DOCUMENTREPO_HPP
