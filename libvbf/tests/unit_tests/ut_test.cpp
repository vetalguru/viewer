#include "gtest/gtest.h"

#include "testfile.hpp"

TEST(Foo, return_42_SUCCESS) { EXPECT_EQ(42, return_42()); }

TEST(Foo, return_42_FAIL) { EXPECT_NE(!42, return_42()); }
