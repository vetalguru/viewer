#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <array>
#include <string>
#include <utility>

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
  enum class DataType : unsigned char {
    UNKNOWN_TYPE,
    NULL_TYPE,
    BOOL_TYPE,
    INT64_TYPE,
    UINT64_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    ARRAY_TYPE,
    OBJECT_TYPE,
  };

private:
  boost::json::value ParseJsonString(const std::string &json_string);

  void PrintJson(std::ostream &os, boost::json::value const &node,
                 std::string indent = std::string()) const;

  bool IsBool(boost::json::value const &node) const noexcept;
  bool GetBoolValue(boost::json::value const &node,
                    bool &bool_value) const noexcept;

  bool IsDouble(boost::json::value const &node) const noexcept;
  bool GetDoubleValue(boost::json::value const &node,
                      double &doulbe_value) const noexcept;

  bool IsInt64(boost::json::value const &node) const noexcept;
  bool GetInt64Value(boost::json::value const &node,
                     int64_t &int64_value) const noexcept;

  bool IsUInt64(boost::json::value const &node) const noexcept;
  bool GetUInt64Value(boost::json::value const &node,
                      uint64_t &uint64_value) const noexcept;

  bool IsString(boost::json::value const &node) const noexcept;
  bool GetStringValue(boost::json::value const &node,
                      std::string &string_value) const noexcept;

  bool IsArray(boost::json::value const &node) const noexcept;
  bool
  GetArrayNodes(boost::json::value const &node,
                std::vector<boost::json::value> &array_value) const noexcept;

  bool IsObject(boost::json::value const &node) const noexcept;
  bool GetObjectNodes(boost::json::value const &node,
                      std::vector<std::pair<std::string, boost::json::value>>
                          &object_value) const noexcept;

  bool IsNull(boost::json::value const &node) const noexcept;

  DataType NodeType(boost::json::value const &node) const noexcept;

private:
  boost::json::value root_{nullptr};
};

} // namespace json

#endif // JSONPARSER_HPP
