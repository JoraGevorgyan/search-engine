//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRY_HPP
#define CRAWLER_LINKENTRY_HPP

#include <ctime>
#include <string>
#include "LinkStatus.hpp"

class LinkEntry {
 private:
  std::string url;
  std::string domain;
  LinkStatus status;
  time_t updated;

 public:
  LinkEntry(std::string url, std::string domain, LinkStatus status, time_t updated);

  inline const std::string& getUrl() const;
  inline const std::string& getDomain() const;
  inline LinkStatus getStatus() const;
  inline time_t getUpdatedTime() const;
};

#endif //CRAWLER_LINKENTRY_HPP
