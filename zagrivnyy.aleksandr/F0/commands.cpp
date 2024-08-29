#include "commands.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void zagrivnyy::help()
{
  std::cout << "Options:\n";
  std::cout << "\t--help\t\tprint this page\n";
  std::cout << "\t--check <file>\tcheck if the given file is correct\n\n";
  std::cout << "Commands:\n";
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
  file.close();
}

void zagrivnyy::read(dict &dictionaries, std::istream &in)
{
  std::string file = "";
  std::string name = "";
  in >> file >> name;

  zagrivnyy::Dictionary dictionary;

  std::fstream input(file);
  int row = 0;
  while (!input.eof())
  {
    std::string line = "";
    std::getline(input, line);
    row += 1;

    std::stringstream ss(line);
    std::string word;
    int col = 0;
    while (ss >> word)
    {
      col += 1;
      dictionary.add(word, {row, col});
    }
  }

  dictionaries[name] = dictionary;
}
