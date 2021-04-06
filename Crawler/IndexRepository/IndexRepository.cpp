//
// Created by jora on 4/6/21.
//

#include "IndexRepository.hpp"

void IndexRepository::save(const Index& index) {
  for (Index &curIndex : this->database) {
    if (curIndex.getId() == index.getId()) {
      curIndex = index;
      return;
    }
  }
  this->database.emplace_back(index);
}

inline const std::vector<Index>& IndexRepository::getAll() const {
  return this->database;
}