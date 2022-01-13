#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <string>

#include "boost/json/value.hpp"

class JsonParser {
public:
  explicit JsonParser(const std::string &json_string);
  virtual ~JsonParser();

  bool IsValid() const;
  void Print() const;

private:
  boost::json::value ParseJsonString(const std::string &json_string);

  void PrintJson(std::ostream &os, boost::json::value const &node,
                 std::string indent = std::string()) const;

private:
  boost::json::value root_{nullptr};
};

#endif // JSONPARSER_HPP
