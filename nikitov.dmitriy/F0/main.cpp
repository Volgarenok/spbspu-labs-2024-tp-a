#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "dictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  std::map< std::string, Dictionary > dictOfDicts;
  for (int i = 1; i != argc + 1; ++i)
  {
    std::ifstream fileInput(argv[i]);
    if (fileInput)
    {
      Dictionary dict;
      fileInput >> dict;
      dictOfDicts.insert({ argv[i], dict });
    }
  }
  dictOfDicts.at("nikitov.dmitriy/F0/input.txt").printDictionary(std::cout);
}
