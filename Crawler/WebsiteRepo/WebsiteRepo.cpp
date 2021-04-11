//
// Created by jora on 3/16/21.
//

#include "WebsiteRepo.hpp"

WebsiteRepo::WebsiteRepo()
{
	this->database.emplace_back(Website("bbc.com", "https://www.bbc.com/", WebsiteStatus::WAITING, std::time(nullptr)));
}
std::vector<Website> WebsiteRepo::getBy(WebsiteStatus status, int count)
{
	std::vector<Website> result;
	for (const auto& current : this->database) {
		if (current.getStatus() == status) {
			result.push_back(current);
		}
	}
	std::sort(result.begin(), result.end(),
			[](const Website& first, const Website& second) -> bool {
			  return first.getCrawledTime() < second.getCrawledTime();
			});
	if (result.size() > count) {
		result.erase(result.begin() + count, result.end());
	}
	return result;
}

void WebsiteRepo::save(const Website& website)
{
	for (auto& current : this->database) {
		if (current.getDomain() == website.getDomain()) {
			current = website;
			return;
		}
	}
	this->database.emplace_back(website);
}
