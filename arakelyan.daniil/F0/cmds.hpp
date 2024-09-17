#ifndef CMDS_HPP
#define CMDS_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace arakelyan
{
  void addDictionary(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void deleteDictionary(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void addWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void removeWord(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void wordTranslations(std::ostream &, std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void mergeDictionaries(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void moveWords(std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void showAllDictionaries(std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
  void getSizeOfDictionary(std::istream&, const std::map< std::string, std::map< std::string, std::vector< std::string > > >&);
}

#endif
