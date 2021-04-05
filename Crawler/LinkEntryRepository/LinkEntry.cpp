//
// Created by jora on 3/16/21.
//

#include "LinkEntry.hpp"

LinkEntry::LinkEntry(int id, std::string url, std::string domain)
    : id{id}, domain{std::move(domain)}, url{std::move(url)}, created{time(nullptr)}, loaded{0} {

}

const std::string &LinkEntry::getUrl() const {
  return this->url;
}

const std::string &LinkEntry::getDomain() const {
  return this->domain;
}

int LinkEntry::getId() const {
  return this->id;
}
