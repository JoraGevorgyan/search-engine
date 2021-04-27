//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "Parser.hpp"
#include "PageLoader.hpp"
#include "WebsiteRepo.hpp"
#include "LinkEntryRepo.hpp"
#include "DocumentRepo.hpp"

int main()
{
	try {
		WebsiteRepo* websiteRepo = new WebsiteRepoDb();
		const auto& websites = websiteRepo.getAll();

		auto linkRepo = LinkEntryRepo();
		auto documentRepo = DocumentRepo();

		for (const auto& website : websites) {
			if (website.getStatus() == WebsiteStatus::CRAWLED || website.getStatus() == WebsiteStatus::INVALID) {
				continue;
			}
			const auto& homepage = website.getHomapage();

			auto homepageEntry = LinkEntry(homepage, website.getDomain(), LinkStatus::WAITING, time(nullptr));
			linkRepo.save(homepageEntry);

			while (true) {
				auto links = linkRepo.getBy(website.getDomain(), LinkStatus::WAITING, 10);
				if (links.empty()) {
					break;
				}

				for (const auto& link : links) {
					auto page = PageLoader::load(link.getUrl());
					if (!page.valid()) {
						linkRepo.save(LinkEntry(link.getUrl(), link.getDomain(), LinkStatus::INVALID, time(nullptr)));
						continue;
					}

					Parser parser(page.getData(), page.getEffUrl());
					int err = parser.parse();
					if (err != 0) {
						linkRepo.save(LinkEntry(link.getUrl(), link.getDomain(), LinkStatus::INVALID, time(nullptr)));
						continue;
					}
					linkRepo.save(LinkEntry(link.getUrl(), link.getDomain(), LinkStatus::LOADED, time(nullptr)));
					std::cout << "one link loaded: " << link.getUrl() << std::endl;

					auto urls = parser.getUrls();
					for (const auto& url : urls) {
						if (linkRepo.getByUrl(url).has_value()) {
							continue;
						}
						linkRepo.save(LinkEntry(url, website.getDomain(), LinkStatus::WAITING, time(nullptr)));
					}

					documentRepo.save(Document(
							page.getEffUrl(), parser.getTitle(),
							parser.getDescription(),
							parser.getContent(), time(nullptr)));

				}
			}
			websiteRepo.save(Website(website.getDomain(), website.getHomapage(), WebsiteStatus::CRAWLED, time(nullptr)));
			std::cout << "\tone website crawled: " << website.getDomain() << std::endl;
		}
	}
	catch (const std::exception& exc) {
		std::cout << "thrown exception: "
				  << exc.what() << std::endl;
	}
	return 0;
}
