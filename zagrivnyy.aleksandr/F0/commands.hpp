#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

#include "dictionary.hpp"

namespace zagrivnyy
{
  void help();
  void check(const char *file);

  using dict = std::map< std::string, zagrivnyy::Dictionary >;
  void read(dict &dictionaries, std::istream &in);
}
#endif
