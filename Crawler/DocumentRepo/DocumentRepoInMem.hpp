//
// Created by jora on 4/28/21.
//

#ifndef CRAWLER_DOCUMENTREPOINMEM_HPP
#define CRAWLER_DOCUMENTREPOINMEM_HPP

#include <map>
#include <optional>
#include "DocumentRepo.hpp"

class DocumentRepoInMem : public DocumentRepo {
private:
	std::vector<Document> documents;

public:
	std::optional<Document> getByUrl(const std::string& url) override;
	void save(const Document& document) override;
};

#endif //CRAWLER_DOCUMENTREPOINMEM_HPP
