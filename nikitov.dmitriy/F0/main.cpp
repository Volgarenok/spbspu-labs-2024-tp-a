#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "dictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  std::map< std::string, Dictionary > dictOfDicts;
  for (int i = 1; i != argc; ++i)
  {
    std::ifstream fileInput(argv[i]);
    if (fileInput)
    {
    }
  }
}
