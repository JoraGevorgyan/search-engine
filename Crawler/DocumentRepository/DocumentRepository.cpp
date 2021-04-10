//
// Created by jora on 4/6/21.
//

#include "DocumentRepository.hpp"

void DocumentRepository::save(const Document& index) {
  for (Document &curIndex : this->database) {
    if (curIndex.getId() == index.getId()) {
      curIndex = index;
      return;
    }
  }
  this->database.emplace_back(index);
}

inline const std::vector<Document>& DocumentRepository::getAll() const {
  return this->database;
}