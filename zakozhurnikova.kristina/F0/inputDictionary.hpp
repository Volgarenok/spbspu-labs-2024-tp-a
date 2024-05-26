#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <iosfwd>
#include <scopeGuard.hpp>
#include <map>
#include <list>

namespace zakozhurnikova
{
  void inputDictionary(std::istream& in, std::map< std::string, std::map< std::string, std::list< std::string > > >& maps);
//  void inputArgs(std::istream& in, std::list< std::string >& args);
}

#endif
