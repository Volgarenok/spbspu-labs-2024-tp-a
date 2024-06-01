#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>

namespace kuzmina
{
  void showHelp(std::ostream&);

  using Dict = std::map< std::string, std::vector< std::string > >;
  using allDicts = std::map< std::string, Dict >;
  using Record = std::pair< std::string, std::vector< std::string > >;

  void addWord(std::istream&, allDicts&);
  void addTranslation(std::istream&, allDicts&);
  void searchWord(std::istream&, std::ostream&, const allDicts&);
  void searchTranslation(std::istream&, std::ostream&, const allDicts&);
  void deleteWord(std::istream&, allDicts&);
  void deleteTranslation(std::istream&, allDicts&);
  void findSynonyms(std::istream&, std::ostream&, const allDicts&);
  void countWords(std::istream&, std::ostream&, const allDicts&);
  void intersect(std::istream&, allDicts&);
  void subtract(std::istream&, allDicts&);
  void merge(std::istream&, allDicts&);
  void print(std::istream&, std::ostream&, const allDicts&);
}

#endif
