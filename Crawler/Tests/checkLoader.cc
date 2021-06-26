//
// Created by jora on 6/24/21.
//

#include "testRunner.h"

#define IMAGE "https://www.thengfq.com/site/wp-content/uploads/2018/01/Q_Top100_Logos_Ping-1.jpg"
#define PDF "http://www-f9.ijs.si/~studen/literatura/Stroustrup_book.pdf"

TEST(checkLoader, okay)
{
	const auto page = PageLoader::load("google.com");
	EXPECT_EQ(page.valid(), true);
}

TEST(checkLoader, ignoreAnImage)
{
	const auto page = PageLoader::load(IMAGE);
	EXPECT_EQ(page.valid(), false);
}

TEST(checkLoader, ignorePDF)
{
	const auto page = PageLoader::load(PDF);
	EXPECT_EQ(page.valid(), false);
}

TEST(checkLoader, effectiveUrl)
{
	const auto page = PageLoader::load("cppreference.com");
	EXPECT_EQ(page.getEffUrl(), "https://en.cppreference.com/w/");
}

int main(int argc, char** argv)
{
	run(argc, argv);
}
