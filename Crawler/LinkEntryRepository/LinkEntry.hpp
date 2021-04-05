//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRY_HPP
#define CRAWLER_LINKENTRY_HPP

#include <ctime>
#include <string>

class LinkEntry {
 private:
  int id;
  std::string url;
  std::string domain;
  time_t loaded;
  time_t created;

 public:
  LinkEntry(int id, std::string url, std::string domain);

  int getId() const;
  const std::string &getUrl() const;
  const std::string &getDomain() const;

};

#endif //CRAWLER_LINKENTRY_HPP
