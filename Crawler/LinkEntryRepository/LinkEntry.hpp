//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRY_HPP
#define CRAWLER_LINKENTRY_HPP

#include <string>

class LinkEntry {
private:
    int id;
    std::string url;
    time_t lastLoadedTime;
    time_t addedTime;

};


#endif //CRAWLER_LINKENTRY_HPP
