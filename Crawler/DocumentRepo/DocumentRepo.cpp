//
// Created by jora on 4/11/21.
//

#include "DocumentRepo.hpp"


void DocumentRepo::save(const Document& index) {
	for (Document &curIndex : this->database) {
		if (curIndex.getId() == index.getId()) {
			curIndex = index;
			return;
		}
	}
	this->database.emplace_back(index);
}

inline const std::vector<Document>& DocumentRepo::getAll() const {
	return this->database;
}