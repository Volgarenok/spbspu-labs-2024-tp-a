#ifndef DICT_FUNCTIONS
#define DICT_FUNCTIONS
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  using pair_t = std::pair< std::string, size_t >;
  void extendDict(dict_t & dict, std::istream & in);
  void printElement(const pair_t & item, std::ostream & out);
  pair_t getCount(const std::pair< std::string, dict_t > & namedDict, const std::string & word);
  size_t getWordCount(const dict_t & dict, const std::string & word);
  bool countComparator(const pair_t & lhs, const pair_t & rhs);
  bool isContains(const dict_t & dict, const pair_t & item);
  void joinWord(const pair_t & item, dict_t & dict);
  pair_t addWordCount(const pair_t & item, const dict_t & dict);
  void printDictName(const std::pair< std::string, dict_t > & namedDict, std::ostream & out);
}

#endif

