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

void zagrivnyy::read(dict_t &dictionaries, std::istream &in)
{
  std::string file = "";
  std::string dict_name = "";
  in >> file >> dict_name;

  zagrivnyy::Dictionary dictionary;

  std::fstream input(file);
  int row = 0;
  while (!input.eof())
  {
    std::string line = "";
    std::getline(input, line);
    row++;

    std::stringstream ss(line);
    std::string word;
    int col = 0;
    while (ss >> word)
    {
      col++;
      dictionary.add(word, {row, col});
    }
  }

  dictionaries[dict_name] = dictionary;
}

void zagrivnyy::list(const dict_t &dictionaries, std::istream &in, std::ostream &out)
{
  std::string dict_name = "";
  in >> dict_name;
  zagrivnyy::Dictionary dictionary;
  try
  {
    dictionary = dictionaries.at(dict_name);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }

  for (auto dict : dictionary.get_dict())
  {
    out << dict.first << ": \n";
    int count = 0;
    for (auto position : dict.second)
    {
      if (count == 0)
      {
        out << '\t';
      }

      out << position << ' ';
      count++;
      if (count == 20)
      {
        out << '\n';
        count = 0;
      }
    }
    out << '\n';
  }
}

void zagrivnyy::deleteDict(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  in >> dict_name;
  dictionaries.erase(dict_name);
}

void zagrivnyy::deleteWord(dict_t &dictionaries, std::istream &in)
{
  std::string dict_name = "";
  std::string word = "";
  in >> dict_name >> word;

  try
  {
    zagrivnyy::Dictionary &dictionary = dictionaries.at(dict_name);
    dictionary.remove(word);
  }
  catch (const std::out_of_range &)
  {
    throw std::invalid_argument("warn: no dictionary with given name");
  }
}
