//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRY_HPP
#define CRAWLER_LINKENTRY_HPP

#include <ctime>
#include <string>

class LinkEntry {
private:
    size_t id;
    std::string url;
    time_t lastLoadedTime;
    time_t addedTime;

public:
    LinkEntry(std::string url, size_t id);

    void update();
    size_t getID() const;
    std::string getUrl() const;

    bool operator < (const LinkEntry& other) const;
};


#endif //CRAWLER_LINKENTRY_HPP
