//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITEREPO_HPP
#define CRAWLER_WEBSITEREPO_HPP

#include <vector>
#include "Website.hpp"

class WebsiteRepo {
 private:
  std::vector<Website> database;

 public:
  WebsiteRepo();
  inline const std::vector<Website>& getAll() const;
  void save(const Website &website);
};

#endif //CRAWLER_WEBSITEREPO_HPP
