//
// Created by jora on 3/16/21.
//

#include "Website.hpp"

Website::Website(int id, std::string domain, std::string homepage)
    : id{id}, domain{std::move(domain)}, homepage{std::move(homepage)}, crawled{0} {

}

inline int Website::getID() const {
  return this->id;
}

inline const std::string& Website::getDomain() const {
  return this->domain;
}

inline const std::string& Website::getHomapage() const {
  return this->homepage;
}

inline time_t Website::getCrawledTime() const {
  return this->crawled;
}

inline void Website::setCrawledTime(time_t crawledTime) {
  this->crawled = crawledTime;
}
