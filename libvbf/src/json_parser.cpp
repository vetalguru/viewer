#include "json_parser.hpp"

#include <iostream>

#include "boost/json.hpp"
#include "boost/json/src.hpp"

namespace json {

bool JSONNode::IsValid() const noexcept {
  DataType type = Type();
  return type != DataType::NULL_TYPE;
}

JSONNode::DataType JSONNode::Type() const noexcept {
  DataType result{DataType::NULL_TYPE};

  switch (node_.kind()) {
  case boost::json::kind::object: {
    result = DataType::OBJECT_TYPE;
    break;
  }
  case boost::json::kind::array: {
    result = DataType::ARRAY_TYPE;
    break;
  }
  case boost::json::kind::string: {
    result = DataType::STRING_TYPE;
    break;
  }
  case boost::json::kind::uint64: {
    result = DataType::UINT64_TYPE;
    break;
  }
  case boost::json::kind::int64: {
    result = DataType::INT64_TYPE;
    break;
  }
  case boost::json::kind::double_: {
    result = DataType::DOUBLE_TYPE;
    break;
  }
  case boost::json::kind::bool_: {
    result = DataType::BOOL_TYPE;
    break;
  }
  case boost::json::kind::null: {
    result = DataType::NULL_TYPE;
    break;
  }
  default: {
    break;
  }
  }

  return result;
}

bool JSONNode::IsObject() const noexcept { return node_.is_object(); }

bool JSONNode::IsArray() const noexcept { return node_.is_array(); }

bool JSONNode::IsString() const noexcept { return node_.if_string(); }

bool JSONNode::IsUint64() const noexcept { return node_.is_uint64(); }

bool JSONNode::IsInt64() const noexcept { return node_.is_int64(); }

bool JSONNode::IsDouble() const noexcept { return node_.is_double(); }

bool JSONNode::IsBool() const noexcept { return node_.is_bool(); }

bool JSONNode::IsNull() const noexcept { return node_.is_null(); }

bool JSONNode::GetObjectNodes(std::vector<std::pair<std::string, JSONNode>>
                                  &object_value) const noexcept {
  bool result{true};
  object_value.clear();

  if (IsObject()) {
    auto const &obj = node_.get_object();
    if (!obj.empty()) {
      auto it = obj.begin();
      for (;;) {
        std::pair<std::string, boost::json::value> current(
            boost::json::serialize(it->key()), it->value());
        object_value.emplace_back(current);
        if (++it == obj.end()) {
          break;
        }
      }
    }
  } else {
    result = false;
  }

  return result;
}

bool JSONNode::GetArrayNodes(
    std::vector<JSONNode> &array_value) const noexcept {
  bool result{true};
  array_value.clear();

  if (IsArray()) {
    auto const &array = node_.get_array();
    if (!array.empty()) {
      for (auto it = array.begin();;) {
        array_value.emplace_back(*it);
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

bool JSONNode::GetStringValue(std::string &string_value) const noexcept {
  bool result{true};
  string_value.clear();

  if (IsString()) {
    string_value = boost::json::serialize(node_.get_string());
  } else {
    result = false;
  }

  return result;
}

bool JSONNode::GetUInt64Value(uint64_t &uint64_value) const noexcept {
  bool result{true};

  if (IsUint64()) {
    uint64_value = node_.get_uint64();
  } else {
    result = false;
  }

  return result;
}

bool JSONNode::GetInt64Value(int64_t &int64_value) const noexcept {
  bool result{true};

  if (IsInt64()) {
    int64_value = node_.get_int64();
  } else {
    result = false;
  }

  return result;
}

bool JSONNode::GetDoubleValue(double &doulbe_value) const noexcept {
  bool result{true};

  if (IsDouble()) {
    doulbe_value = node_.get_double();
  } else {
    result = false;
  }

  return result;
}

bool JSONNode::GetBoolValue(bool &bool_value) const noexcept {
  bool result{true};

  if (IsBool()) {
    bool_value = node_.get_bool();
  } else {
    result = false;
  }

  return result;
}

void JSONDocument::Parse(const std::string &json_string) noexcept {
  root_ = ParseJsonString(json_string);
}

bool JSONDocument::IsValid() const { return root_.IsValid(); }

void JSONDocument::Print() const {
  if (IsValid())
    PrintJson(std::cout, root_);
}

JSONNode
JSONDocument::ParseJsonString(const std::string &json_string) noexcept {
  JSONNode result;

  if (json_string.empty())
    return result;

  boost::json::error_code ec;
  boost::json::parser parser;

  parser.write(json_string, ec);
  if (!ec) {
    result = parser.release();
  }

  return result;
}

void JSONDocument::PrintJson(std::ostream &os, JSONNode const &node,
                             std::string indent) const {
  switch (node.Type()) {
  case JSONNode::DataType::OBJECT_TYPE: {
    std::vector<std::pair<std::string, JSONNode>> object_value;
    node.GetObjectNodes(object_value);

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
  case JSONNode::DataType::ARRAY_TYPE: {
    std::vector<JSONNode> array_value;
    node.GetArrayNodes(array_value);

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
  case JSONNode::DataType::STRING_TYPE: {
    std::string value;
    node.GetStringValue(value);
    os << value;
    break;
  }
  case JSONNode::DataType::UINT64_TYPE: {
    uint64_t value{};
    node.GetUInt64Value(value);
    os << value;
    break;
  }
  case JSONNode::DataType::INT64_TYPE: {
    int64_t value{};
    node.GetInt64Value(value);
    os << value;
    break;
  }
  case JSONNode::DataType::DOUBLE_TYPE: {
    double value{};
    node.GetDoubleValue(value);
    os << value;
    break;
  }
  case JSONNode::DataType::BOOL_TYPE: {
    bool value{true};
    node.GetBoolValue(value);
    if (value) {
      os << "true";
    } else {
      os << "false";
    }
    break;
  }
  case JSONNode::DataType::NULL_TYPE: {
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

} // namespace json
