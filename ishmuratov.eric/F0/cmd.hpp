#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include "utilities.hpp"

namespace ishmuratov
{
  void create_dict(dict_t & dictionaries, std::istream & input);
  void delete_dict(dict_t & dictionaries, std::istream & input);
  void add_key(dict_t & dictionaries, std::istream & input);
  void add_value(dict_t & dictionaries, std::istream & input);
  void remove_key(dict_t & dictionaries, std::istream & input);
  void print_dict(const dict_t & dictionaries, std::istream & input, std::ostream & output);
  void get_value(const dict_t & dictionaries, std::istream & input, std::ostream & output);
  void save(const dict_t & dictionaries, std::istream & input);
  void read(dict_t & dictionaries, std::istream & input);
  void renamedict(dict_t & dictionaries, std::istream & input);
  void intersect(dict_t & dictionaries, std::istream & input);
  void uniond(dict_t & dictionaries, std::istream & input);
}

#endif
