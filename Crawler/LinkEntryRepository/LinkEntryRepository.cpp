//
// Created by jora on 3/16/21.
//

#include "LinkEntryRepository.hpp"

void LinkEntryRepository::add(const std::vector<std::string>& urls) {
    for(const auto& current : urls) {
        this->links.insert(LinkEntry(current, this->links.size() + 1));
    }
}

bool LinkEntryRepository::empty() const {
    return this->links.empty();
}

std::string LinkEntryRepository::getNext() {
    if(this->links.empty()) {
        return std::string("");
    }
    auto it = this->links.begin();
    auto tmp = *it;
    this->links.erase(it);
    tmp.update();
    this->links.insert(tmp);

    return tmp.getUrl();
}