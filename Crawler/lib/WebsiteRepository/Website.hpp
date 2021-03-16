//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <string>

class Website {
private:
    int id;
    std::string domain;
    std::string homepage;
    time_t lastCrawledTime;

public:
    Website()
};


#endif //CRAWLER_WEBSITE_HPP
