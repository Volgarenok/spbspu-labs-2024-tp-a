#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <utility>
#include <string>
#include <list>
#include <iostream>

namespace novokhatskiy
{
  using val_t = std::pair< std::string, std::list< std::string > >;
  using mainDict = std::map< std::string, val_t >;
  mainDict unique(mainDict& dict1, mainDict& dict2);
  mainDict search(mainDict& res, mainDict& dict1, mainDict& dict2, std::istream& in);
  void random(mainDict& res, size_t count, mainDict& dict1, mainDict& dict2);
  void save(const mainDict& dict, const std::string& name);
  void editTranslation(mainDict& dict, std::istream& in);
  void editExample(mainDict& dict, std::istream& in);
  mainDict merge(mainDict& dict1, mainDict& dict2);
  void printHelp();
  void deleteWord(mainDict& dict, const std::string& key);
  void find(const mainDict& dict, const std::string& key, std::ostream& out);
  void insert(mainDict& dict, std::istream& in);
  void print(const mainDict& dict, std::ostream& out);
}

#endif
