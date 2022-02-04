#include "json_parser.hpp"

#include <iostream>

#include "boost/json.hpp"
#include "boost/json/src.hpp"

namespace json {

JSONDocument::JSONDocument() {}

JSONDocument::~JSONDocument() {}

void JSONDocument::Parse(const std::string &json_string) noexcept {
  try {
    root_ = ParseJsonString(json_string);
  } catch (...) {
    root_ = nullptr;
  }
}

bool JSONDocument::IsValid() const { return root_ != nullptr; }

void JSONDocument::Print() const {
  if (IsValid())
    PrintJson(std::cout, root_);
}

boost::json::value
JSONDocument::ParseJsonString(const std::string &json_string) {
  boost::json::value result = nullptr;

  try {
    boost::json::stream_parser parser;
    parser.write(json_string);
    result = parser.release();
  } catch (...) {
    result = nullptr;
  }

  return result;
}

void JSONDocument::PrintJson(std::ostream &os, boost::json::value const &node,
                             std::string indent) const {
  switch (node.kind()) {
  case boost::json::kind::object: {
    std::vector<std::pair<std::string, boost::json::value>> object_value;
    GetObjectNodes(node, object_value);

    os << "{\n";
    indent.append(4, ' ');
    for (size_t i = 0;;) {
      os << indent << object_value[i].first << ": ";
      PrintJson(os, object_value[i].second, indent);
      if (++i == object_value.size()) {
        os << "\n";
        break;
      }

      os << ",\n";
    }
    indent.resize(indent.size() - 4);
    os << indent << "}";

    break;
  }
  case boost::json::kind::array: {
    std::vector<boost::json::value> array_value;
    GetArrayNodes(node, array_value);

    os << "[\n";
    indent.append(4, ' ');

    for (size_t i = 0;;) {
      os << indent;
      PrintJson(os, array_value[i], indent);
      if (++i == array_value.size()) {
        os << "\n";
        break;
      }

      os << ",\n";
    }
    indent.resize(indent.size() - 4);
    os << indent << "]";

    break;
  }
  case boost::json::kind::string: {
    std::string value;
    GetStringValue(node, value);
    os << value;
    break;
  }
  case boost::json::kind::uint64: {
    uint64_t value{};
    GetUInt64Value(node, value);
    os << value;
    break;
  }
  case boost::json::kind::int64: {
    int64_t value{};
    GetInt64Value(node, value);
    os << value;
    break;
  }
  case boost::json::kind::double_: {
    double value{};
    GetDoubleValue(node, value);
    os << value;
    break;
  }
  case boost::json::kind::bool_: {
    bool value{true};
    GetBoolValue(node, value);
    if (value) {
      os << "true";
    } else {
      os << "false";
    }
    break;
  }
  case boost::json::kind::null: {
    os << "null";
    break;
  }
  default:
    std::cerr << "Unknown json type" << std::endl;
  }

  if (indent.empty()) {
    os << "\n";
  }
}

bool JSONDocument::IsBool(boost::json::value const &node) const noexcept {
  return node.is_bool();
}

bool JSONDocument::GetBoolValue(boost::json::value const &node,
                                bool &bool_value) const noexcept {
  bool result{true};

  if (IsBool(node)) {
    bool_value = node.get_bool();
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsDouble(boost::json::value const &node) const noexcept {
  return node.is_double();
}

bool JSONDocument::GetDoubleValue(boost::json::value const &node,
                                  double &doulbe_value) const noexcept {
  bool result{true};

  if (IsDouble(node)) {
    doulbe_value = node.get_double();
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsInt64(boost::json::value const &node) const noexcept {
  return node.is_int64();
}

bool JSONDocument::GetInt64Value(boost::json::value const &node,
                                 int64_t &int64_value) const noexcept {
  bool result{true};

  if (IsInt64(node)) {
    int64_value = node.get_int64();
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsUInt64(boost::json::value const &node) const noexcept {
  return node.is_uint64();
}

bool JSONDocument::GetUInt64Value(boost::json::value const &node,
                                  uint64_t &uint64_value) const noexcept {
  bool result{true};

  if (IsUInt64(node)) {
    uint64_value = node.get_uint64();
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsString(boost::json::value const &node) const noexcept {
  return node.if_string();
}

bool JSONDocument::GetStringValue(boost::json::value const &node,
                                  std::string &string_value) const noexcept {
  bool result{true};
  string_value.clear();

  if (IsString(node)) {
    string_value = boost::json::serialize(node.get_string());
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsArray(boost::json::value const &node) const noexcept {
  return node.is_array();
}

bool JSONDocument::GetArrayNodes(
    boost::json::value const &node,
    std::vector<boost::json::value> &array_value) const noexcept {
  bool result{true};
  array_value.clear();

  if (IsArray(node)) {
    auto const &array = node.get_array();
    if (!array.empty()) {
      for (auto it = array.begin();;) {
        array_value.push_back(*it);
        if (++it == array.end()) {
          break;
        }
      }
    }
  } else {
    result = false;
  }

  return result;
}

bool JSONDocument::IsObject(boost::json::value const &node) const noexcept {
  return node.is_object();
}

bool JSONDocument::GetObjectNodes(
    boost::json::value const &node,
    std::vector<std::pair<std::string, boost::json::value>> &object_value)
    const noexcept {
  bool result{true};
  object_value.clear();

  if (IsObject(node)) {
    auto const &obj = node.get_object();
    if (!obj.empty()) {
      auto it = obj.begin();
      for (;;) {
        std::pair<std::string, boost::json::value> current(
            boost::json::serialize(it->key()), it->value());
        object_value.push_back(current);
        if (++it == obj.end()) {
          break;
        }
      }
    }
  } else {
    result = true;
  }

  return result;
}

bool JSONDocument::IsNull(boost::json::value const &node) const noexcept {
  return node.is_null();
}

JSONDocument::DataType
JSONDocument::NodeType(boost::json::value const &node) const noexcept {
  JSONDocument::DataType result{JSONDocument::DataType::UNKNOWN_TYPE};

  switch (node.kind()) {
  case boost::json::kind::object: {
    result = JSONDocument::DataType::OBJECT_TYPE;
    break;
  }
  case boost::json::kind::array: {
    result = JSONDocument::DataType::ARRAY_TYPE;
    break;
  }
  case boost::json::kind::string: {
    result = JSONDocument::DataType::STRING_TYPE;
    break;
  }
  case boost::json::kind::uint64: {
    result = JSONDocument::DataType::UINT64_TYPE;
    break;
  }
  case boost::json::kind::int64: {
    result = JSONDocument::DataType::INT64_TYPE;
    break;
  }
  case boost::json::kind::double_: {
    result = JSONDocument::DataType::DOUBLE_TYPE;
    break;
  }
  case boost::json::kind::bool_: {
    result = JSONDocument::DataType::BOOL_TYPE;
    break;
  }
  case boost::json::kind::null: {
    result = JSONDocument::DataType::NULL_TYPE;
    break;
  }
  }

  return result;
}

} // namespace json
