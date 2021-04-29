//
// Created by jora on 3/24/21.
//

#include <string>
#include <fstream>
#include <gtest/gtest.h>
#include "Parser.hpp"

std::string readFile(const std::string& path)
{
	std::string result;
	std::ifstream file(path);
	if (!file.is_open()) {
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
TEST(parsingTest, test1)
{
	const std::string html = readFile("../parserTest.html");
	Parser parser(html, "https://example.am/");
	EXPECT_EQ(parser.invalid(), true);
}
