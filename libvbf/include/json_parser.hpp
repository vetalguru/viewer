#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <array>
#include <string>
#include <utility>

#include "boost/json/value.hpp"

namespace json {

class JSONDocument;

class JSONNode {
public:
  enum class DataType : unsigned char {
    NULL_TYPE = 0,
    OBJECT_TYPE,
    ARRAY_TYPE,
    STRING_TYPE,
    UINT64_TYPE,
    INT64_TYPE,
    DOUBLE_TYPE,
    BOOL_TYPE,
  };

public:
  JSONNode() = default;
  JSONNode(const JSONNode &) = default;
  JSONNode(JSONNode &&) = default;
  JSONNode(const boost::json::value &value) noexcept : node_(value) {}

  JSONNode &operator=(const JSONNode &) = default;
  JSONNode &operator=(JSONNode &&) = default;

  ~JSONNode() = default;

public:
  bool IsValid() const noexcept;

  DataType Type() const noexcept;

  bool IsObject() const noexcept;
  bool IsArray() const noexcept;
  bool IsString() const noexcept;
  bool IsUint64() const noexcept;
  bool IsInt64() const noexcept;
  bool IsDouble() const noexcept;
  bool IsBool() const noexcept;
  bool IsNull() const noexcept;

  bool GetObjectNodes(std::vector<std::pair<std::string, JSONNode>>
                          &object_value) const noexcept;
  bool GetArrayNodes(std::vector<JSONNode> &array_value) const noexcept;
  bool GetStringValue(std::string &string_value) const noexcept;
  bool GetUInt64Value(uint64_t &uint64_value) const noexcept;
  bool GetInt64Value(int64_t &int64_value) const noexcept;
  bool GetDoubleValue(double &doulbe_value) const noexcept;
  bool GetBoolValue(bool &bool_value) const noexcept;

private:
  boost::json::value node_;
};

class JSONDocument {
public:
  JSONDocument() = default;
  ~JSONDocument() = default;

public:
  void Parse(const std::string &json_string) noexcept;

  bool IsValid() const;
  void Print() const;

private:
  JSONNode ParseJsonString(const std::string &json_string) noexcept;

  void PrintJson(std::ostream &os, const JSONNode &node,
                 std::string indent = std::string()) const;

private:
  JSONNode root_;
};

} // namespace json

#endif // JSONPARSER_HPP
