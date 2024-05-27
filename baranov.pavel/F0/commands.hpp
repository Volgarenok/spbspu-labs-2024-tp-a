#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void create(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
}

#endif

