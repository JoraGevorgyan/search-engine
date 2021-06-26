//
// Created by jora on 6/24/21.
//

#include "testRunner.h"


#define EXPECTED_TITLE "JoraGevorgyan/search-engine"
#define EXPECTED_DESCRIPTION "Contribute to JoraGevorgyan/search-engine development by creating an account on GitHub."
#define EXPECTED_CONTENT_SIZE 15069
#define EXPECTED_URLS_COUNT 6

#define VALID_URL "https://github.com/JoraGevorgyan/search-engine"
#define INVALID_URL ""

TEST(checkParser, fail_1)
{
	const auto html = readFile("./parser/valid");
	Parser parser(html, INVALID_URL);
	EXPECT_EQ(parser.invalid(), true);
}

TEST(checkParser, fail_2)
{
	const auto html = readFile("./parser/invalid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getDescription().empty(), true);
}

TEST(checkParser, fail_3)
{
	const auto html = readFile("./parser/invalid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getTitle().empty(), true);
}

TEST(checkParser, fail_4)
{
	const auto html = readFile("./parser/invalid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getUrls().empty(), true);
}

TEST(checkParser, title)
{
	const auto html = readFile("./parser/valid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getTitle(), EXPECTED_TITLE);
}

TEST(checkParser, desctiption)
{
	const auto html = readFile("./parser/valid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getDescription(), EXPECTED_DESCRIPTION);
}

TEST(checkParser, content)
{
	const auto html = readFile("./parser/valid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getContent().size(), EXPECTED_CONTENT_SIZE);
}

TEST(checkParser, urls)
{
	const auto html = readFile("./parser/valid");
	Parser parser(html, VALID_URL);
	EXPECT_EQ(parser.getUrls().size(), EXPECTED_URLS_COUNT);
}

int main(int argc, char** argv)
{
	return run(argc, argv);
}
