#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace baranov
{
  using dict_t = std::map< std::string, size_t >;
  void createCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void clearCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void deleteCmd(std::map< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
}

#endif

