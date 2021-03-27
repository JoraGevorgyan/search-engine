//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITEREPOSITORY_HPP
#define CRAWLER_WEBSITEREPOSITORY_HPP

#include <vector>
#include <set>

#include "Website.hpp"

class WebsiteRepository {
private:
    std::set<Website> database;

public:
    /*
     *
     */
    std::vector<Website> getAll() const;
    Website getNext();
    void add(const Website& website);
    bool empty() const;

};


#endif //CRAWLER_WEBSITEREPOSITORY_HPP
