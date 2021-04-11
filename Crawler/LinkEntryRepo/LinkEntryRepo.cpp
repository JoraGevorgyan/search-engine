//
// Created by jora on 3/16/21.
//

#include "LinkEntryRepo.hpp"

std::optional<LinkEntry> LinkEntryRepo::getByUrl(const std::string& url)
{
	for (auto& current : this->links) {
		if (current.getUrl() == url) {
			return std::optional<LinkEntry>(current);
		}
	}
	return std::optional<LinkEntry>(std::nullopt);
}

std::vector<LinkEntry> LinkEntryRepo::getBy(const std::string& domain, LinkStatus status, int count) const
{
	std::vector<LinkEntry> result;
	for (const auto& current : this->links) {
		if (current.getDomain() == domain && current.getStatus() == status) {
			result.push_back(current);
		}
	}

	std::sort(result.begin(), result.end(),
			[](const LinkEntry& first, const LinkEntry& second) -> bool {
			  return first.getUpdatedTime() < second.getUpdatedTime();
			});

	if (count < result.size()) {
		result.erase(result.begin() + count, result.end());
	}
	return result;
}

// if that link already exists, then update it, otherwise add it into the base
void LinkEntryRepo::save(const LinkEntry& link)
{
	for (auto& current : this->links) {
		if (current.getUrl() == link.getUrl()) {
			current = link;
			return;
		}
	}
	this->links.emplace_back(link);
}
