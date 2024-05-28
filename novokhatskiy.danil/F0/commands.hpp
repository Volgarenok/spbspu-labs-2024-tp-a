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
  void random(mainDict& res, size_t count, mainDict& dict1, mainDict& dict2);
  void save(const mainDict& dict, const std::string& name);
  void editTranslation(mainDict& dict, std::istream& in);
  void editExample(mainDict& dict, std::istream& in);
  void merge(mainDict& dict1, mainDict& dict2);
  void deleteWord(mainDict& dict, const std::string& key);
  void find(const mainDict& dict, const std::string& key, std::ostream& out);*/
  void insert(dictionaries& dict, std::istream& in);
  void printHelp();
  void print(const dictionaries& dict, std::istream& in, std::ostream& out);
}

#endif
