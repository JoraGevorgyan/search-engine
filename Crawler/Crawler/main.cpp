//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "WebsiteRepository.hpp"
#include "LinkEntryRepository.hpp"
#include "PageLoader.hpp"
#include "Parser.hpp"

int main() {
  try {
    auto webisteRepo = WebsiteRepository();
    const auto &websites = webisteRepo.getAll();

    auto linkRepo = LinkEntryRepository();

    for (const auto &website : websites) {
      // test
      auto homepage = website.getHomapage();

      auto homepageEntry = linkRepo.getByUrl(homepage);
      int id = linkRepo.count() + 1;
      if (homepageEntry != nullptr) {
        id = homepageEntry->getId();
      }

      auto newLinkEntry = LinkEntry(id, " ", " ");
      linkRepo.save(newLinkEntry);

      while (true) {
        linkRepo.getFirstNotLoaded("domain");

      }

    }
  }
  catch (const std::exception &exc) {
    std::cout << "thrown exception: "
              << exc.what() << std::endl;
  }
  return 0;
}
