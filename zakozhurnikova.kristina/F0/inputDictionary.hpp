#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <iosfwd>
#include <map>
#include <set>
#include <list>
#include <scopeGuard.hpp>

namespace zakozhurnikova
{
  using subDict = std::map< std::string, std::set< std::string > >;
  using dict = std::map< std::string, subDict >;
  bool isDictionary(const std::string& nameDictionary, const dict& dictionary);
  void inputDictionary(std::istream& in, std::map< std::string, subDict >& maps);
  void inputArgs(std::istream& in, std::list< std::string >& args);
  std::istream& operator>>(std::istream& in, subDict& dict);
}

#endif
