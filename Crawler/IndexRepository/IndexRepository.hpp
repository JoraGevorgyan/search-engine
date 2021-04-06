//
// Created by jora on 4/6/21.
//

#ifndef CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_
#define CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_

#include <vector>
#include "Index.hpp"

class IndexRepository {
 private:
  std::vector<Index> database;

 public:
  void save(const Index& index);
  inline const std::vector<Index>& getAll() const;
};

#endif //CRAWLER_INDEXREPOSITORY_INDEXREPOSITORY_HPP_
