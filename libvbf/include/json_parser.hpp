#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <string>

#include "boost/json/value.hpp"

namespace json {

class JSONDocument {
public:
  JSONDocument();
  virtual ~JSONDocument();

  void Parse(const std::string &json_string) noexcept;

  bool IsValid() const;
  void Print() const;

private:
  boost::json::value ParseJsonString(const std::string &json_string);

  void PrintJson(std::ostream &os, boost::json::value const &node,
                 std::string indent = std::string()) const;

private:
  boost::json::value root_{nullptr};
};

} // namespace json

#endif // JSONPARSER_HPP
