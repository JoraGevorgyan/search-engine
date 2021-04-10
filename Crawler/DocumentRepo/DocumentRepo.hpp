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
	void save(const Document& index);
	inline const std::vector<Document>& getAll() const;
};

#endif //CRAWLER_DOCUMENTREPO_HPP
