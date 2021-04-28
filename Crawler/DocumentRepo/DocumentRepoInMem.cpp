//
// Created by jora on 4/28/21.
//

#include "DocumentRepoInMem.hpp"

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

std::optional<Document> DocumentRepoInMem::getByUrl(const std::string& url) const
{
	for (const auto& document : this->documents) {
		if (document.getUrl() == url) {
			return std::optional<Document>(document);
		}
	}
	return std::optional<Document>(std::nullopt);
}

size_t DocumentRepoInMem::getSize() const
{
	return this->documents.size();
}
