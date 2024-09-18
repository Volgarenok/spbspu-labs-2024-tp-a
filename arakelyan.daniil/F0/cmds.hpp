#ifndef CMDS_HPP
#define CMDS_HPP

#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace arakelyan
{
  void addDictionary(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void deleteDictionary(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void addWord(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void removeWord(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void wordTranslations(std::istream &, std::ostream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void mergeDictionaries(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void moveWords(std::istream&, std::ostream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void showAllDictionariesNames(std::istream &, std::ostream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void getSizeOfDictionary(std::istream&, std::ostream &, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void printTranslations(std::istream&, std::ostream &, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
}

#endif
