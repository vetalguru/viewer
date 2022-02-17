#include "gtest/gtest.h"

#include "json_parser.hpp"

TEST(JsonParser, JSONDocument_IsValid_Success) {
  std::string test_json_string{"{\"valid\":\"json\"}"};
  json_parser::JSONDocument doc;
  doc.Parse(test_json_string);

  EXPECT_TRUE(doc.IsValid());
}

TEST(JsonParser, JSONDocument_IsValid_Fail) {
  std::string test_json_string{"invalid json"};
  json_parser::JSONDocument doc;
  doc.Parse(test_json_string);

  EXPECT_FALSE(doc.IsValid());
}

TEST(JsonParser, JSONDocument_Print_Success) {
  std::string test_json_string{"{\"valid\":\"json\"}"};
  std::string expected_json_string{"{\n    \"valid\": \"json\"\n}\n"};
  json_parser::JSONDocument doc;
  doc.Parse(test_json_string);

  ASSERT_TRUE(doc.IsValid());

  testing::internal::CaptureStdout();
  doc.Print();
  std::string output = testing::internal::GetCapturedStdout();
  ASSERT_FALSE(output.empty());
  EXPECT_EQ(expected_json_string, output);
}

TEST(JsonParser, JSONDocument_Print_Fail) {
  std::string test_json_string{"invalid json"};
  json_parser::JSONDocument doc;
  doc.Parse(test_json_string);

  ASSERT_FALSE(doc.IsValid());

  testing::internal::CaptureStdout();
  doc.Print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_TRUE(output.empty());
}
