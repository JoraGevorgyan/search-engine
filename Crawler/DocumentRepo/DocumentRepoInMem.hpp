//
// Created by jora on 4/28/21.
//

#ifndef CRAWLER_DOCUMENTREPOINMEM_HPP
#define CRAWLER_DOCUMENTREPOINMEM_HPP

#include <optional>
#include "DocumentRepo.hpp"

class DocumentRepoInMem : public DocumentRepo {
private:
	std::vector<Document> documents;
public:
	void save(const Document& document) override;
	[[nodiscard]] std::optional<Document> getByUrl(const std::string& url) const override;
	[[nodiscard]] size_t getSize() const override;
};

#endif //CRAWLER_DOCUMENTREPOINMEM_HPP
