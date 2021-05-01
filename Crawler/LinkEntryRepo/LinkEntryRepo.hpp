//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRYREPO_HPP
#define CRAWLER_LINKENTRYREPO_HPP

#include <vector>
#include <optional>
#include "LinkEntry.hpp"

class LinkEntryRepo {
public:
	virtual ~LinkEntryRepo() = default;
	virtual std::vector<LinkEntry> getAll() = 0;
	[[nodiscard]] virtual size_t getSize() const = 0;
	virtual std::optional<LinkEntry> getByUrl(const std::string& url) = 0;
	virtual std::vector<LinkEntry> getBy(int websiteId, LinkStatus status, int count) = 0;
	virtual void save(const LinkEntry& link) = 0;
};

#endif //CRAWLER_LINKENTRYREPO_HPP
