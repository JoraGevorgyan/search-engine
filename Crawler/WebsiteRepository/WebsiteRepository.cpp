//
// Created by jora on 3/16/21.
//

#include "WebsiteRepository.hpp"

WebsiteRepository::WebsiteRepository() {
  this->database.emplace_back(Website(1, "bbc.com", "https://www.bbc.com/"));
}

inline const std::vector<Website>& WebsiteRepository::getAll() const {
  return this->database;
}

void WebsiteRepository::save(const Website& website) {
  for (auto& curWebsite : this->database) {
    if (curWebsite.getID() == website.getID()) {
      curWebsite = website;
      return;
    }
  }
  this->database.emplace_back(website);
}
