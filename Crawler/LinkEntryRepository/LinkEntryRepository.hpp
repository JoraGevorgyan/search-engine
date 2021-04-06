//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRYREPOSITORY_HPP
#define CRAWLER_LINKENTRYREPOSITORY_HPP

#include <vector>
#include <algorithm>
#include "LinkEntry.hpp"

class LinkEntryRepository {
 private:
  std::vector<LinkEntry> links;

 public:
  void save(const LinkEntry &link);
  LinkEntry* getByUrl(const std::string& url);
  LinkEntry* getFirstNotLoaded(const std::string& domainName);
  inline int count() const;
};

#endif //CRAWLER_LINKENTRYREPOSITORY_HPP
