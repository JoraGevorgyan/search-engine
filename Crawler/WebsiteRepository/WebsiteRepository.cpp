//
// Created by jora on 3/16/21.
//

#include "WebsiteRepository.hpp"

void WebsiteRepository::add(const Website &website) {
    this->database.insert(website);
}

std::vector<Website> WebsiteRepository::getAll() const {
    return std::vector<Website>(this->database.begin(), this->database.end());
}

Website WebsiteRepository::getNext() {
    auto it = this->database.begin();
    auto next = *it;
    this->database.erase(it);
    auto tmp = next;
    tmp.update();
    this->database.insert(tmp);
    return next;

}

bool WebsiteRepository::empty() const {
    return this->database.empty();
}