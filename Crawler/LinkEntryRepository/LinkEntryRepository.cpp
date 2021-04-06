//
// Created by jora on 3/16/21.
//

#include "LinkEntryRepository.hpp"

// if that link already exists, then update it, otherwise add it into the base
void LinkEntryRepository::save(const LinkEntry& link) {
  for (auto& curLink : this->links) {
    if (curLink.getId() == link.getId()) {
      curLink = link;
      return;
    }
  }
  this->links.emplace_back(link);
}

LinkEntry* LinkEntryRepository::getByUrl(const std::string& url) {
  for (auto& curLink : this->links) {
    if (curLink.getUrl() == url) {
      return &curLink;
    }
  }
  return nullptr;
}

inline int LinkEntryRepository::count() const {
  return this->links.size();
}

LinkEntry* LinkEntryRepository::getFirstNotLoaded(const std::string& domainName) {
  for (auto& curLink : this->links) {
    if (curLink.getLoadedTime() == 0 && curLink.getDomain() == domainName) {
      return &curLink;
    }
  }
  return nullptr;
}
