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

  inline int getId() const;
  inline const std::string& getUrl() const;
  inline const std::string& getDomain() const;
  inline time_t getLoadedTime() const;
  inline time_t getCreatedTime() const;

  inline void setLoadedTime(time_t loadTime = time(nullptr));
};

#endif //CRAWLER_LINKENTRY_HPP
