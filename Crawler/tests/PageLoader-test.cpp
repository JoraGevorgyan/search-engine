//
// Created by jora on 3/10/21.
//

#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include "PageLoader.hpp"

TEST(loadingTest, test1) {
    EXPECT_EQ("ping", "ping");

    /*
    std::string url;
    std::cout << "enter the url for loading from there: ";
    std::cin >> url;

    PageLoader loader;
    Page news = loader.load(url);

    std::cout << "status: " << news.getStatus() << std::endl
        << "effecitve url found: " << news.getUrl() << std::endl
        << "html: " << news.getData() << std::endl;
    */
}