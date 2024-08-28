#include "commands.hpp"

#include <fstream>
#include <iostream>

void zagrivnyy::help()
{
  std::cout << "Options:\n";
  std::cout << "\t--help\t\tprint this page\n";
  std::cout << "\t--check <file>\tcheck if the given file is correct\n\n";
}

void zagrivnyy::check(const char *fileName)
{
  std::ifstream file(fileName);
  if (file.is_open())
  {
    std::cout << "Check: PASSED\n";
  }
  else
  {
    std::cout << "Check: FAILED\n";
  }
}
