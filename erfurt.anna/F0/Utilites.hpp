#ifndef UTILITES_HPP
#define UTILITES_HPP

#include <iosfwd>
#include <set>
#include <vector>
#include "Dictionary.hpp"

namespace erfurt
{
  std::vector<Dictionary> createDictionaryFromFile(std::istream & fin);
  std::string oneWord(std::string & str);
  bool isEng(const std::string & word);
  bool isRus(const std::string & translate);
  Dictionary createCommonDictionary(const Dictionary & dict1, const Dictionary & dict2, const std::string & name);
  Dictionary createUniqueDictionary(const Dictionary & dict1, const Dictionary & dict2, const std::string & name);
}

#endif
