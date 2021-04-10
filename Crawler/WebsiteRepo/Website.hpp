//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITE_HPP
#define CRAWLER_WEBSITE_HPP

#include <ctime>
#include <string>

class Website {
private:
	int id;
	std::string domain;
	std::string homepage;
	time_t crawled;

public:
	Website(int id, std::string domain, std::string homepage);

	[[nodiscard]] inline int getID() const
	{
		return this->id;
	}
	[[nodiscard]] inline const std::string& getDomain() const
	{
		return this->domain;
	}
	[[nodiscard]] inline const std::string& getHomapage() const
	{
		return this->domain;
	}
	[[nodiscard]] inline time_t getCrawledTime() const
	{
		return this->crawled;
	}

	inline void setCrawledTime(time_t crawledTime = time(nullptr))
	{
		this-crawled = crawledTime;
	}
};

#endif //CRAWLER_WEBSITE_HPP
