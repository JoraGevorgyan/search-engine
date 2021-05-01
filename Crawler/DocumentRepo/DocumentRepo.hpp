//
// Created by jora on 4/11/21.
//

#ifndef CRAWLER_DOCUMENTREPO_HPP
#define CRAWLER_DOCUMENTREPO_HPP

#include <vector>
#include <optional>
#include "Document.hpp"

class DocumentRepo {
public:
	virtual ~DocumentRepo() = default;
	virtual void save(const Document& document) = 0;
	[[nodiscard]] virtual std::optional<Document> getByUrl(const std::string& url) const = 0;
	[[nodiscard]] virtual size_t getSize() const = 0;
};

#endif //CRAWLER_DOCUMENTREPO_HPP
