//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>

class Website {
 private:
  int id;
  std::string domain;
  std::string homepage;
  time_t crawled;

 public:
  Website(int id, std::string domain, std::string homepage);

  inline int getID() const;
  inline const std::string& getDomain() const;
  inline const std::string& getHomapage() const;
  inline time_t getCrawledTime() const;

  inline void setCrawledTime(time_t crawledTime = time(nullptr));
};

#endif //CRAWLER_WEBSITE_HPP
