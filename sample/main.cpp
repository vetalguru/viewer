/**
 *  Copyright 2022
 */

#include <fstream>
#include <iostream>
#include <string>

#include "json_parser.hpp"
#include "testfile.hpp"

int main(int argc, char *argv[]) {

  std::cout << return_42() << std::endl;

  if (argc != 2) {
    std::cerr << "Usage: vbf_viewer <filename>" << std::endl;
    return EXIT_FAILURE;
  }

  try {
    auto const filename = argv[1];
    std::ifstream file(filename, std::ifstream::in);
    std::string input(std::istreambuf_iterator<char>(file), {});
    JsonParser json(input);
    if (json.IsValid())
      json.Print();
  } catch (std::exception const &e) {
    std::cerr << "Ecxeption: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
