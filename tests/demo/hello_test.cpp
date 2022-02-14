#include <iostream>

#include "gtest/gtest.h"

TEST(HelloTest, GtestTest) {
  std::cout << "hello googletest!" << std::endl;
  EXPECT_EQ(1, 1);
}