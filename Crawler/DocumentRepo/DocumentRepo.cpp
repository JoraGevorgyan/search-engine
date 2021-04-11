//
// Created by jora on 4/11/21.
//

#include <optional>
#include "DocumentRepo.hpp"

std::optional<Document> DocumentRepo::getByUrl(const std::string& url)
{
	for (const auto& current : this->database) {
		if (current.getUrl() == url) {
			return std::optional<Document>(current);
		}
	}
	return std::optional<Document>(std::nullopt);
}

void DocumentRepo::save(const Document& document)
{
	for (Document& current : this->database) {
		if (current.getUrl() == document.getUrl()) {
			current = document;
			return;
		}
	}
	this->database.emplace_back(document);
}
