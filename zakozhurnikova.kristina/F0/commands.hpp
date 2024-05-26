#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <set>
#include <iosfwd>
#include <list>
#include <string>
#include <utility>

using dict = std::map< std::string, std::map< std::string, std::set< std::string > > >;
using dictionaryOne = std::map< std::string, std::set< std::string > >;

namespace zakozhurnikova
{
  void print(const std::list< std::string >& args, const dict& dictionary);
  void complement(std::list< std::string >& args, dict& dictionary);
  void intersect(std::list< std::string >& args, dict& dictionary);
}

#endif
