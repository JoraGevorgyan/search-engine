//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "Parser.hpp"
#include "PageLoader.hpp"
#include "WebsiteRepository.hpp"
#include "LinkEntryRepository.hpp"
#include "DocumentRepository.hpp"

int main() {
  try {
    auto websiteRepo = WebsiteRepository();
    const auto &websites = websiteRepo.getAll();

    auto linkRepo = LinkEntryRepository();
    auto indexRepo = DocumentRepository(); // document
    PageLoader pageLoader;

    for (const auto &website : websites) {
      if (website.getCrawledTime() != 0) {
        continue;
      }

      const auto &homepage = website.getHomapage();

      auto homepageEntry = LinkEntry(homepage, website.getDomain(), LinkStatus::WAITING, time(nullptr));
      linkRepo.save(homepageEntry);

      while (true) {
        auto links = linkRepo.getBy(website.getDomain(), LinkStatus::WAITING, 10);
        if (links.empty()) {
          break;
        }

        for (const auto &link : links) {
          auto page = pageLoader.load(link.getUrl());
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

          auto urls = parser.getUrls();
          for (const auto &url : urls) {
            if (linkRepo.getByUrl(url).has_value()) {
              continue;
            }
            linkRepo.save(LinkEntry(url, website.getDomain(), LinkStatus::WAITING, time(nullptr)));
          }

          // indexRepo.save(Document())

        }
      }
    // websiteRepo.save() // set updated
    }
  }
  catch (const std::exception &exc) {
    std::cout << "thrown exception: "
              << exc.what() << std::endl;
  }
  return 0;
}
