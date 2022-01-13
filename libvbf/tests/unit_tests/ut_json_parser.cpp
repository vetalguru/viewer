#include "gtest/gtest.h"

#include "json_parser.hpp"

TEST(JsonParser, IsValid_Success) {
  std::string test_json_string{"{\"valid\":\"json\"}"};
  JsonParser parser(test_json_string);

  EXPECT_TRUE(parser.IsValid());
}

TEST(JsonParser, IsValid_Fail) {
  std::string test_json_string{"invalid json"};
  JsonParser parser(test_json_string);

  EXPECT_FALSE(parser.IsValid());
}

TEST(JsonParser, Print_Success) {
  std::string test_json_string{"{\"valid\":\"json\"}"};
  std::string expected_json_string{"{\n    \"valid\" : \"json\"\n}\n"};
  JsonParser parser(test_json_string);

  ASSERT_TRUE(parser.IsValid());

  testing::internal::CaptureStdout();
  parser.Print();
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_FALSE(output.empty());
  EXPECT_EQ(expected_json_string, output);
}

TEST(JsonParser, Print_Fail) {
  std::string test_json_string{"invalid json"};
  JsonParser parser(test_json_string);

  ASSERT_FALSE(parser.IsValid());

  testing::internal::CaptureStdout();
  parser.Print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.empty());
}
