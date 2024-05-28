#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <utility>
#include <string>
#include <set>
#include <iostream>
#include "dictionary.hpp"

namespace novokhatskiy
{
  using val_t = std::pair< std::string, std::set< std::string > >;
  using mainDict = std::map< std::string, val_t >;
  using dictionaries = std::map< std::string,  Dictionary >;
  /*void unique(dictionaries& dict, std::istream& in);
  void search(mainDict& res, mainDict& dict1, mainDict& dict2, std::istream& in);
  void editTranslation(mainDict& dict, std::istream& in);
  void editExample(mainDict& dict, std::istream& in);
  void merge(mainDict& dict1, mainDict& dict2);*/
  void random(dictionaries& dict, std::istream& in, std::ostream& out);
  void find(const dictionaries& dict, std::istream& in, std::ostream& out);
  void save(const dictionaries& dict, std::istream& in, std::ostream& out);
  void deleteWord(dictionaries& dict, std::istream& in);
  void insert(dictionaries& dict, std::istream& in);
  void printHelp();
  void print(const dictionaries& dict, std::istream& in, std::ostream& out);
}

#endif
