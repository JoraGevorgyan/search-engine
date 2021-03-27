//
// Created by jora on 3/16/21.
//

#include "Website.hpp"

Website::Website(std::string domain, std::string homepage, size_t id)
    : domain{std::move(domain)}
    , homepage{std::move(homepage)}
    , id{id}
    , lastCrawledTime{time(nullptr)} {

}

bool Website::operator < (const Website &other) const {
    return this->lastCrawledTime < other.lastCrawledTime;
}
void Website::update() {
    this->lastCrawledTime = time(nullptr);
}

std::string Website::getDomain() const {
    return this->domain;
}

std::string Website::getHomapage() const {
    return this->homepage;
}

size_t Website::getID() const {
    return this->id;
}