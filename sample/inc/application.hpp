/**
 *  Copyright 2022
 */

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>

class Application {
public:
  Application(int &argc, char **argv);
  virtual ~Application() = default;

  int Run();

private:
  bool ParseArguments(int &argc, char **argv);

private:
  bool is_args_valid_;
  std::string file_path_;
};

#endif // APPLICATION_HPP
