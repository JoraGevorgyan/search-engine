//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>

class Website {
private:
    size_t id;
    std::string domain;
    std::string homepage;
    time_t lastCrawledTime;

public:
    Website();
};


#endif //CRAWLER_WEBSITE_HPP
