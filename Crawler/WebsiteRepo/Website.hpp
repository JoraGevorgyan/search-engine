//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>
#include "WebsiteStatus.hpp"

class Website {
private:
	int id;
	std::string domain;
	std::string homepage;
	WebsiteStatus status;
	time_t crawled;

public:
	Website(int id, std::string domain, std::string homepage, WebsiteStatus status, time_t crawled);

	[[nodixcard]] inline int getId() const
	{
		return this->id;
	}
	[[nodiscard]] inline const std::string& getDomain() const
	{
		return this->domain;
	}
	[[nodiscard]] inline const std::string& getHomapage() const
	{
		return this->homepage;
	}
	[[nodiscard]] inline WebsiteStatus getStatus() const
	{
		return this->status;
	}
	[[nodiscard]] inline time_t getCrawledTime() const
	{
		return this->crawled;
	}

};

#endif //CRAWLER_WEBSITE_HPP
