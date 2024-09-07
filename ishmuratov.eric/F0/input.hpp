#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <map>
#include <list>

namespace ishmuratov
{
  using value_t = std::list< std::string >;
  using unit_t = std::map< std::string, value_t >;
  using dict_t = std::map< std::string, unit_t >;

  void input_dictionary(dict_t & dictionaries, std::istream & input);
  void print_help(std::ostream & output);
}

#endif
