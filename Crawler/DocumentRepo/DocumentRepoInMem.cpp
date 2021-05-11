//
// Created by jora on 4/28/21.
//

#include "DocumentRepoInMem.hpp"

std::optional<Document> DocumentRepoInMem::getByUrl(const std::string& url)
{
	for (const auto& document : this->documents) {
		if (document.getUrl() == url) {
			return std::optional<Document>(document);
		}
	}
	return std::optional<Document>(std::nullopt);
}

void DocumentRepoInMem::save(const Document& document)
{
	for (auto& current : this->documents) {
		if (current == document) {
			current = document;
			return;
		}
	}
	this->documents.emplace_back(document);
}
