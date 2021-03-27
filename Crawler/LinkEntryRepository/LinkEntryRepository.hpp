//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRYREPOSITORY_HPP
#define CRAWLER_LINKENTRYREPOSITORY_HPP

#include <set>
#include <vector>
#include "LinkEntry.hpp"

class LinkEntryRepository {
private:
    std::set<LinkEntry> links;

public:
    void add(const std::vector<std::string>& urls);
    std::string getNext();
    bool empty() const;
};

#endif //CRAWLER_LINKENTRYREPOSITORY_HPP
