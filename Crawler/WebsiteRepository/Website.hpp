//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>

class Website {
 private:
  size_t id;
  std::string domain;
  std::string homepage;
  time_t lastCrawledTime;

 public:
  Website(std::string domain, std::string homepage, size_t id);

  bool operator<(const Website &other) const;
  void update();

  std::string getDomain() const;
  std::string getHomapage() const;
  size_t getID() const;
};

#endif //CRAWLER_WEBSITE_HPP
