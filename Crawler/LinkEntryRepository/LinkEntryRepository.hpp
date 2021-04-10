//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRYREPOSITORY_HPP
#define CRAWLER_LINKENTRYREPOSITORY_HPP

#include <vector>
#include <algorithm>
#include <optional>
#include "LinkEntry.hpp"

class LinkEntryRepository {
 private:
  std::vector<LinkEntry> links;

 public:
  const std::vector<LinkEntry>& getAll() const;
  std::optional<LinkEntry> getByUrl(const std::string& url);
  std::vector<LinkEntry> getBy(const std::string& domain, LinkStatus status, int count) const;
  void save(const LinkEntry& link);
};

#endif //CRAWLER_LINKENTRYREPOSITORY_HPP
