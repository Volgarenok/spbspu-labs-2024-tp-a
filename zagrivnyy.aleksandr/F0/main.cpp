#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "commands.hpp"

int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    if (strcmp(argv[1], "--help") == 0)
    {
      zagrivnyy::help();
    }
    else if (strcmp(argv[1], "--check") == 0)
    {
      zagrivnyy::check(argv[2]);
    }
    else
    {
      std::cerr << "unknown option: " << argv[1] << "\n";
      std::cerr << "possible options: [--help] [--check <file>]\n";
      return 1;
    }
    return 0;
  }

  return 0;
}
