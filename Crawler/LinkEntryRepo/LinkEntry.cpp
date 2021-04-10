//
// Created by jora on 3/16/21.
//

#include "LinkEntry.hpp"

LinkEntry::LinkEntry(int id, std::string url, std::string domain)
    : id{id}, domain{std::move(domain)}, url{std::move(url)}, created{time(nullptr)}, loaded{0} {

}

inline int LinkEntry::getId() const {
  return this->id;
}

inline const std::string& LinkEntry::getUrl() const {
  return this->url;
}

inline const std::string& LinkEntry::getDomain() const {
  return this->domain;
}

inline time_t LinkEntry::getLoadedTime() const {
  return this->loaded;
}

inline time_t LinkEntry::getCreatedTime() const {
  return this->created;
}

inline void LinkEntry::setLoadedTime(time_t loadTime) {
  this->loaded = loadTime;
}