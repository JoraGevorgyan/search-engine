//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "PageLoader.hpp"
#include "Parser.hpp"

int main() {
    PageLoader pageLoader;
    Page rau = pageLoader.load("docker.com");
    Parser parser(rau.getData(), rau.getEffUrl());

    int err = parser.parse();
    if(err != 0) {
        return err;
    }
    std::cout << parser.getTitle() << std::endl;
    std::cout << parser.getDescription() << std::endl;

    auto urls = parser.getUrls();
    for(auto cur : urls) {
        std::cout << cur << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
