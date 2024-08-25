#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <set>
#include <iosfwd>
#include <list>
#include <string>
#include <utility>
#include "inputDictionary.hpp"

using dict = std::map< std::string, std::map< std::string, std::set< std::string > > >;
using dictionaryOne = std::map< std::string, std::set< std::string > >;

namespace zakozhurnikova
{
  void print(const std::list< std::string >& args, std::ostream& out, const dict& dictionary);
  void complement(std::list< std::string >& args, dict& dictionary);
  void intersect(std::list< std::string >& args, dict& dictionary);
  void doUnion(std::list< std::string >& args, dict& dictionary);
  void specificLetter(std::list< std::string >& args, dict& dictionary);
  void elimination(std::list< std::string >& args, dict& dictionary);
  void destruction(std::list< std::string >& args, dict& dictionary);
  void addition(std::list< std::string >& args, dict& dictionary);
  void palindrome(std::list< std::string >& args, dict& dictionary);
  void rider(std::list< std::string >& args, dict& dictionary);
  void interpreter(std::list< std::string >& args, dict& dictionary);
  void save(std::list< std::string >& args, dict& dictionary);
  void doAddDictionary(std::list< std::string >&, std::istream& in, dict& dictionary);
}

#endif
