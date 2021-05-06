//
// Created by jora on 3/13/21.
//

#include <iostream>
#include <memory>
#include "Parser.hpp"
#include "PageLoader.hpp"
#include "WebsiteRepoInMem.hpp"
#include "WebsiteRepoDb.hpp"
#include "LinkEntryRepoInMem.hpp"
#include "LinkEntryRepoDb.hpp"
#include "DocumentRepoInMem.hpp"
#include "DocumentRepoDb.hpp"

void saveInvalidLink(const LinkEntry& link, std::unique_ptr<LinkEntryRepo>& linkEntryRepo)
{
	std::cout << "found invalid link: " << link.getUrl() << std::endl
			  << "from the website with < " << link.getWebsiteId() << " > id: " << std::endl;
	linkEntryRepo->save(LinkEntry(link.getId(), link.getWebsiteId(),
			link.getUrl(), LinkStatus::INVALID, time(nullptr)));
}

void saveDocument(const std::string& url, const Parser& parser,
		std::unique_ptr<DocumentRepo>& documentRepo)
{
	auto documentOpt = documentRepo->getByUrl(url);
	if (documentOpt.has_value()) {
		documentRepo->save(Document(documentOpt->getId(), url, parser.getTitle(),
				parser.getDescription(), parser.getContent(), time(nullptr)));
		return;
	}
	documentRepo->save(Document((int)documentRepo->getSize(), url, parser.getTitle(),
			parser.getDescription(), parser.getContent(), time(nullptr)));
}

void saveLinks(const Parser& parser, const LinkEntry& link, std::unique_ptr<LinkEntryRepo>& linkEntryRepo)
{
	for (const auto& url : parser.getUrls()) {
		if (linkEntryRepo->getByUrl(url).has_value()) {
			continue;
		}
		linkEntryRepo->save(LinkEntry((int)linkEntryRepo->getSize(), link.getWebsiteId(),
				url, LinkStatus::WAITING, time(nullptr)));
	}
}

void crawlLink(const LinkEntry& link,
		std::unique_ptr<LinkEntryRepo>& linkEntryRepo,
		std::unique_ptr<DocumentRepo>& documentRepo)
{
	auto page = PageLoader::load(link.getUrl());
	if (!page.valid()) {
		saveInvalidLink(link, linkEntryRepo);
		return;
	}
	Parser parser(page.getData(), page.getEffUrl());
	if (parser.invalid()) {
		saveInvalidLink(link, linkEntryRepo);
		return;
	}
	linkEntryRepo->save(LinkEntry(link.getId(), link.getWebsiteId(),
			link.getUrl(), LinkStatus::LOADED, time(nullptr)));
	std::cout << "link loaded successfully: " << link.getUrl() << std::endl;

	saveDocument(link.getUrl(), parser, documentRepo);
	saveLinks(parser, link, linkEntryRepo);
}

void crawlWebsite(const Website& website,
		std::unique_ptr<LinkEntryRepo>& linkEntryRepo,
		std::unique_ptr<DocumentRepo>& documentRepo)
{
	auto homepageOpt = linkEntryRepo->getByUrl(website.getHomepage());
	if (homepageOpt.has_value()) {
		linkEntryRepo->save(LinkEntry(homepageOpt->getId(), homepageOpt->getWebsiteId(),
				homepageOpt->getUrl(), LinkStatus::WAITING, time(nullptr)));
	}
	else {
		linkEntryRepo->save(LinkEntry((int)linkEntryRepo->getSize(), website.getId(),
				website.getHomepage(), LinkStatus::WAITING, time(nullptr)));
	}

	while (true) {
		constexpr int expectedLinksCount = 14;
		auto links = linkEntryRepo->getBy(website.getId(), LinkStatus::WAITING, expectedLinksCount);
		if (links.empty()) {
			break;
		}
		for (const auto& link : links) {
			crawlLink(link, linkEntryRepo, documentRepo);
		}
	}
}

int main()
{
	std::unique_ptr<WebsiteRepo> websiteRepo = std::make_unique<WebsiteRepoDb>("crawler", "localhost", "root", "pass", 3306);
	std::unique_ptr<LinkEntryRepo> linkEntryRepo = std::make_unique<LinkEntryRepoInMem>();
	std::unique_ptr<DocumentRepo> documentRepo = std::make_unique<DocumentRepoInMem>();

	websiteRepo->save(Website(0, "cppreference.com", "https://en.cppreference.com/w/", time(nullptr)));
	websiteRepo->save(Website(1, "cplusplus.com", "https://www.cplusplus.com/", time(nullptr)));
	websiteRepo->save(Website(2, "bbc.com", "https://bbc.com/", time(nullptr)));
	const auto& websites = websiteRepo->getAll();
	for (const auto& website : websites) {
		crawlWebsite(website, linkEntryRepo, documentRepo);
		websiteRepo->save(Website(website.getId(), website.getDomain(), website.getHomepage(), time(nullptr)));
		std::cout << "\tone website crawled: " << website.getDomain() << std::endl;
	}
	return 0;
}
