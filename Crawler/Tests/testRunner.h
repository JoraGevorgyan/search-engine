//
// Created by jora on 6/24/21.
//

#ifndef CRAWLER_TESTRUNNER_H
#define CRAWLER_TESTRUNNER_H

#include <string>
#include <fstream>
#include "gtest/gtest.h"
#include "../PageLoader/PageLoader.hpp"
#include "../Parser/Parser.hpp"

#define TEST_DIR

std::string readFile(const std::string& path)
{
	std::string result;
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Can't open file!!" << std::endl;
		return result;
	}
	std::string current;
	while (getline(file, current)) {
		result += current;
		result += '\n';
	}
	file.close();
	return result;
}

int run(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif //CRAWLER_TESTRUNNER_H
