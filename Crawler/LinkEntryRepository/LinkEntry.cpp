//
// Created by jora on 3/16/21.
//

#include "LinkEntry.hpp"

LinkEntry::LinkEntry(std::string url, size_t id)
    : url{std::move(url)}
    , id{id}
    , addedTime{time(nullptr)}
    , lastLoadedTime{0} {
}

void LinkEntry::update() {
    this->lastLoadedTime = time(nullptr);
}

bool LinkEntry::operator < (const LinkEntry &other) const {
    if(this->lastLoadedTime == other.lastLoadedTime) {
        return this->addedTime < other.addedTime;
    }
    return this->lastLoadedTime < other.lastLoadedTime;
}

std::string LinkEntry::getUrl() const {
    return this->url;
}

size_t LinkEntry::getID() const {
    return this->id;
}