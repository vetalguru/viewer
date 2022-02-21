/**
 *  Copyright 2022
 */

#include "application.hpp"

#include <fstream>

#include "json_parser.hpp"

Application::Application(int &argc, char **argv) : is_args_valid_{false} {
  is_args_valid_ = ParseArguments(argc, argv);
}

int Application::Run() {
  if (file_path_.empty()) {
    return EXIT_FAILURE;
  }

  std::ifstream file(file_path_, std::ifstream::in);
  std::string input(std::istreambuf_iterator<char>(file), {});
  json_parser::JSONDocument json;
  json.Parse(input);
  if (!json.IsValid()) {
    return EXIT_FAILURE;
  }

  json.Print();

  return EXIT_SUCCESS;
}

bool Application::ParseArguments(int &argc, char **argv) {
  if (argc != 2 || !argv) {
    return false;
  }

  file_path_ = (std::string{argv[1]});

  return true;
}
