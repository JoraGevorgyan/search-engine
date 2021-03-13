//
// Created by jora on 3/13/21.
//

#include <iostream>
#include "../lib/PageLoader/PageLoader.hpp"

int main(int argc, char** argv) {
    std::cout << "arguments count: " << argc << std::endl;
    std::cout << "first argument: " << argv[argc - 1] << std::endl;

    return 0;
}
