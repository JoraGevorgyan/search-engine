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
	std::string domain;
	std::string homepage;
	WebsiteStatus status;
	time_t crawled;

public:
	Website(std::string domain, std::string homepage, WebsiteStatus status, time_t crawled);

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
