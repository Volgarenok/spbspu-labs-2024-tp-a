#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <utility>
#include <string>
#include <set>
#include <random>
#include <iostream>
#include "dictionary.hpp"

namespace novokhatskiy
{
  using dictionaries = std::map< std::string, Dictionary >;
  void search(dictionaries &dict, std::istream &in);
  void merge(dictionaries &dict, std::istream &in);
  void unique(dictionaries &dict, std::istream &in);
  void editTranslation(dictionaries &dict, std::istream &in);
  void randomDict(dictionaries &dict, std::istream &in, std::random_device &randomDevice);
  void find(const dictionaries &dict, std::istream &in, std::ostream &out);
  void save(const dictionaries &dict, std::istream &in);
  void deleteWord(dictionaries &dict, std::istream &in);
  void insert(dictionaries &dict, std::istream &in);
  void printHelp();
  void print(const dictionaries &dict, std::istream &in, std::ostream &out);
}

#endif
