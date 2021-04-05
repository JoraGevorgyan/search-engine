//
// Created by jora on 3/10/21.
//

#include <string>
#include <gtest/gtest.h>
#include "PageLoader.hpp"

TEST(loadingTest, test1) {
  const std::string url = "cplusplus.com";
  PageLoader pageLoader;
  Page page = pageLoader.load(url);
  EXPECT_EQ(page.getStatus(), 200);
}