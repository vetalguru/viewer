#include "json_parser.hpp"

#include <iostream>

#include "boost/json.hpp"
#include "boost/json/src.hpp"

JsonParser::JsonParser(const std::string &json_string) {
  root_ = ParseJsonString(json_string);
}

JsonParser::~JsonParser() {}

bool JsonParser::IsValid() const { return root_ != nullptr; }

void JsonParser::Print() const { PrintJson(std::cout, root_); }

boost::json::value JsonParser::ParseJsonString(const std::string &json_string) {
  boost::json::stream_parser parser;
  parser.write(json_string);
  return parser.release();
}

void JsonParser::PrintJson(std::ostream &os, boost::json::value const &node,
                           std::string indent) const {
  switch (node.kind()) {
  case boost::json::kind::object: {
    os << "{\n";
    indent.append(4, ' ');
    auto const &obj = node.get_object();
    if (!obj.empty()) {
      auto it = obj.begin();
      for (;;) {
        os << indent << boost::json::serialize(it->key()) << " : ";
        PrintJson(os, it->value(), indent);
        if (++it == obj.end()) {
          break;
        }
        os << ",\n";
      }
    }
    os << "\n";
    indent.resize(indent.size() - 4);
    os << indent << "}";
    break;
  }
  case boost::json::kind::array: {
    os << "[\n";
    indent.append(4, ' ');
    auto const &arr = node.get_array();
    if (!arr.empty()) {
      auto it = arr.begin();
      for (;;) {
        os << indent;
        PrintJson(os, *it, indent);
        if (++it == arr.end()) {
          break;
        }
        os << ",\n";
      }
    }
    os << "\n";
    indent.resize(indent.size() - 4);
    os << indent << "]";
    break;
  }
  case boost::json::kind::string: {
    os << boost::json::serialize(node.get_string());
    break;
  }
  case boost::json::kind::uint64: {
    os << node.get_uint64();
    break;
  }
  case boost::json::kind::int64: {
    os << node.get_int64();
    break;
  }
  case boost::json::kind::double_: {
    os << node.get_double();
    break;
  }
  case boost::json::kind::bool_: {
    if (node.get_bool()) {
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
