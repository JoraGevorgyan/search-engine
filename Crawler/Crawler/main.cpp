//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "PageLoader.hpp"
#include "Parser.hpp"

int main() {
    PageLoader pageLoader;
    Page rau = pageLoader.load("rau.am");
    Parser parser(rau.getData(), rau.getEffUrl());

    parser.parse();

    std::cout << parser.getTitle() << std::endl;

    return 0;
}
