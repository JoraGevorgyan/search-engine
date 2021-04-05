//
// Created by jora on 3/16/21.
//

#include "WebsiteRepository.hpp"

WebsiteRepository::WebsiteRepository() {
  this->database.emplace_back(Website("rau.am", "http://rau.am/", 1));
}

void WebsiteRepository::add(const Website &website) {
  this->database.push_back(website);
}

std::vector<Website> WebsiteRepository::getAll() const {
  return std::vector<Website>(this->database.begin(), this->database.end());
}
