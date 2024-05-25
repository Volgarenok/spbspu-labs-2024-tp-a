#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>

namespace kuznetsov
{
  using frequency_dictionary = std::map< std::string, size_t >;
  void command_create_dictionary(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
  void command_add_word(std::map< std::string, frequency_dictionary >& data, std::istream& in, std::ostream& out);
}

#endif
