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
	std::string url;
	std::string domain;
	LinkStatus status;
	time_t updated;

public:
	LinkEntry(std::string url, std::string domain, LinkStatus status, time_t updated);

	[[nodiscard]] inline const std::string& getUrl() const
	{
		return this->url;
	}
	[[nodiscard]] inline const std::string& getDomain() const
	{
		return this->domain;
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
