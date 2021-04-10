//
// Created by jora on 4/6/21.
//

#ifndef CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_
#define CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_

#include <vector>
#include "Document.hpp"

class DocumentRepository {
 private:
  std::vector<Document> database;

 public:
  void save(const Document& index);
  inline const std::vector<Document>& getAll() const;
};

#endif //CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_
