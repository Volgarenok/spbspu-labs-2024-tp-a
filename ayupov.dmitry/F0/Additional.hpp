#ifndef ADDITIONAL_HPP
#define ADDITIONAL_HPP

#include <string>
#include <map>

#include "Dictionary.hpp"

namespace ayupov
{
  void isDict(const std::map< std::string, ARDictionary >& dicts, const std::string& dict);
  void printDict(std::ostream& out, const std::pair< const std::string, ARDictionary >& dict);
  void printPair(std::ostream& out, const std::pair< std::string, std::set<std::string> >& pair);
  void printWord(std::ostream& out, const std::string& word);
}

#endif
