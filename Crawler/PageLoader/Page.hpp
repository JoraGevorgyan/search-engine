//
// Created by jora on 3/12/21.
//

#ifndef CRAWLER_PAGE_HPP
#define CRAWLER_PAGE_HPP

#include <string>

class Page {
private:
	std::string data;
	std::string effUrl;
	long status;

public:
	Page(std::string effUrl, std::string data, long status);

	[[nodiscard]] inline const std::string& getEffUrl() const
	{
		return this->effUrl;
	}
	[[nodiscard]] inline const std::string& getData() const
	{
		return this->data;
	};
	[[nodiscard]] inline long getStatus() const
	{
		return this->status;
	}
	[[nodiscard]] inline bool valid() const
	{
		return this->status >= 200 && this->status < 300;
	}
};

#endif //CRAWLER_PAGE_HPP
