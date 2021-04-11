//
// Created by jora on 3/16/21.
//

#ifndef CRAWLER_WEBSITEREPO_HPP
#define CRAWLER_WEBSITEREPO_HPP

#include <vector>
#include <algorithm>
#include "Website.hpp"

class WebsiteRepo {
private:
	std::vector<Website> database;

public:
	WebsiteRepo();
	[[nodiscard]] inline const std::vector<Website>& getAll() const
	{
		return this->database;
	}
	[[nodiscard]] std::vector<Website> getBy(WebsiteStatus status, int count);
	void save(const Website& website);
};

#endif //CRAWLER_WEBSITEREPO_HPP
