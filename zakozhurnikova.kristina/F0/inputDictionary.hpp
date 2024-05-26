#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <iosfwd>
#include <scopeGuard.hpp>
#include <map>
#include <set>
#include <list>

namespace zakozhurnikova
{
  using subDict = std::map< std::string, std::set< std::string > >;
  using dict = std::map< std::string, subDict >;
  void inputDictionary(std::istream& in, std::map< std::string, subDict >& maps);
  void inputArgs(std::istream& in, std::list< std::string >& args);
  std::istream& operator>>(std::istream& in, subDict& dict);
  std::ostream& operator<<(std::ostream& out, const subDict& dict);
}

#endif
