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

  using dict_t = std::map< std::string, zagrivnyy::Dictionary >;
  void read(dict_t &dictionaries, std::istream &in);
  void list(const dict_t &dictionaries, std::istream &in, std::ostream &out);
  void deleteDict(dict_t &dictionaries, std::istream &in);
  void merge(dict_t &dictionaries, std::istream &in);
  void deleteWord(dict_t &dictionaries, std::istream &in, std::ostream &out);
  void find(const dict_t &dictionaries, std::istream &in, std::ostream &out);
  void add(dict_t &dictionaries, std::istream &in);
  void replace(dict_t &dictionaries, std::istream &in);
  void addline(dict_t &dictionaries, std::istream &in);
  void removeline(dict_t &dictionaries, std::istream &in);
  void save(const dict_t &dictionaries, std::istream &in);
}
#endif
