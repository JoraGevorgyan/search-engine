//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "Parser.hpp"
#include "PageLoader.hpp"
#include "WebsiteRepository.hpp"
#include "LinkEntryRepository.hpp"

int main() {
  try {
    auto webisteRepo = WebsiteRepository();
    const auto& websites = webisteRepo.getAll();

    auto linkRepo = LinkEntryRepository();

    for (const auto& website : websites) {
      if (website.getCrawledTime() != 0) {
        continue;
      }

      const auto& homepage = website.getHomapage();

      auto homepageEntry = linkRepo.getByUrl(homepage);
      int id = linkRepo.count() + 1;
      if (homepageEntry != nullptr) {
        id = homepageEntry->getId();
      }

      auto newLinkEntry = LinkEntry(id, homepage, website.getDomain()); // ????
      linkRepo.save(newLinkEntry);

      while (true) {
        auto* link = linkRepo.getFirstNotLoaded(website.getDomain());
        PageLoader pageLoader;
        auto page = pageLoader.load(link->getUrl());
        if (page.valid()) {
          link->setLoadedTime();

          Parser parser(page.getData(), page.getEffUrl());
          int err = parser.parse();
          if (err == 0) {
            parser.getUrls();
          } else {
            // in the future this can be changed as log file
            std::cerr << "can't parse the following html code ( error code: " << err << " ): " <<  std::endl;
            std::cerr << page.getData() << std::endl;
          }
        } else {
          std::cerr << "the following page can't load with exit status: " << page.getStatus() << std::endl;
          std::cerr << "\t" << link->getUrl() << std::endl;
        }
      }

    }
  }
  catch (const std::exception &exc) {
    std::cout << "thrown exception: "
              << exc.what() << std::endl;
  }
  return 0;
}
