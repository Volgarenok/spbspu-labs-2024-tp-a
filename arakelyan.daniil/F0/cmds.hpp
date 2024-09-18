#ifndef CMDS_HPP
#define CMDS_HPP

#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace arakelyan
{
  using dictionaries_t = std::map< std::string, std::map< std::string, 
                          std::vector< std::string > > >;
  void addDictionary(std::istream&, std::ostream&, dictionaries_t&);
  void deleteDictionary(std::istream&, std::ostream&, dictionaries_t&);
  void addWord(std::istream&, std::ostream&, dictionaries_t&);
  void removeWord(std::istream&, std::ostream&, dictionaries_t&);
  void wordTranslations(std::istream &, std::ostream&, const dictionaries_t&);
  void mergeDictionaries(std::istream&, std::ostream&, dictionaries_t&);
  void moveWords(std::istream&, std::ostream&, dictionaries_t&);
  void showAllDictionariesNames(std::istream &, std::ostream&, const dictionaries_t&);
  void getSizeOfDictionary(std::istream&, std::ostream &, const dictionaries_t&);
  void printTranslations(std::istream&, std::ostream &, const dictionaries_t&);
}

#endif
