//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITEREPOSITORY_HPP
#define CRAWLER_WEBSITEREPOSITORY_HPP

#include <vector>
#include "Website.hpp"

class WebsiteRepository {
 private:
  std::vector<Website> database;

 public:
  WebsiteRepository();
  inline const std::vector<Website>& getAll() const;
  void save(const Website &website);
};

#endif //CRAWLER_WEBSITEREPOSITORY_HPP
