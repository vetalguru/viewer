/**
 *  Copyright 2022
 */

#include <fstream>
#include <iostream>
#include <string>

#include "json_parser.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: vbf_viewer <filename>" << std::endl;
    return EXIT_FAILURE;
  }

  auto const filename = argv[1];
  std::ifstream file(filename, std::ifstream::in);
  std::string input(std::istreambuf_iterator<char>(file), {});
  json_parser::JSONDocument json;
  json.Parse(input);
  if (json.IsValid()) {
    json.Print();
  }

  return EXIT_SUCCESS;
}
