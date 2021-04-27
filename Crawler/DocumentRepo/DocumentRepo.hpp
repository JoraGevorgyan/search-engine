//
// Created by jora on 4/11/21.
//

#ifndef CRAWLER_DOCUMENTREPO_HPP
#define CRAWLER_DOCUMENTREPO_HPP

#include <vector>
#include "Document.hpp"

class DocumentRepo {
public:
	virtual void save(const Document& document) = 0;
};

#endif //CRAWLER_DOCUMENTREPO_HPP
