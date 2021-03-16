//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITEREPOSITORY_HPP
#define CRAWLER_WEBSITEREPOSITORY_HPP

#include <vector>
#include <map>

#include "Website.hpp"

class WebsiteRepository {
private:
    std::map<int, Website> database;

public:
    /*
     *
     */
    std::vector<Website> getAll() const;
    void add(const Website& website);

};


#endif //CRAWLER_WEBSITEREPOSITORY_HPP
