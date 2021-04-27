//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_LINKENTRY_HPP
#define CRAWLER_LINKENTRY_HPP

#include <ctime>
#include <string>
#include "LinkStatus.hpp"

class LinkEntry {
private:
	int id;
	int websiteId;
	std::string url;
	LinkStatus status;
	time_t updated;

public:
	LinkEntry(int id, int websiteId, std::string url, LinkStatus status, time_t updated);

	[[nodiscard]] inline int getId() const
	{
		return this->id;
	}
	[[nodiscard]] inline int getWebsiteId() const
	{
		return this->websiteId;
	}
	[[nodiscard]] inline const std::string& getUrl() const
	{
		return this->url;
	}
	[[nodiscard]]  inline LinkStatus getStatus() const
	{
		return this->status;
	}
	[[nodiscard]]   inline time_t getUpdatedTime() const
	{
		return this->updated;
	}
};

#endif //CRAWLER_LINKENTRY_HPP
