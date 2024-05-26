#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <vector>
#include <string>

namespace kuzmina
{
  using Dict = std::map< std::string, std::vector< std::string > >;
  using allDicts = std::map< std::string, Dict >;

  void addWord(std::istream&, Dict&);
  void addTranslation(std::istream&, Dict&);
  void searchWord(std::istream&, std::ostream&, const Dict&);
  void searchTranslation(std::istream&, std::ostream&, const Dict&);
  void deleteWord(std::istream&, Dict&);
  void deleteTranslation(std::istream&, Dict&);
  void findSynonyms(std::istream&, std::ostream&, const Dict&);
  //void countWords(std::istream&, std::ostream&, const Dict&);
  //void intersect(std::istream&, allDicts&);
  //void subtract(std::istream&, allDicts&);
  //void merge(std::istream&, allDicts&);
}

#endif
