#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <set>

namespace kovtun
{
  using line_t = std::map< size_t, std::vector< size_t > >;
  using map_t = std::map< std::string, line_t >;
  using cross_t = std::map< std::string, map_t >;

  void create(cross_t &, std::istream &, std::ostream &);
  void remove(cross_t &, std::istream &, std::ostream &);
  void recover(cross_t &, std::istream &, std::ostream &);
  void search(cross_t &, std::istream &, std::ostream &);
  void replace(cross_t &, std::istream &, std::ostream &);

  void readFile(map_t &, std::string);
  void showMap(map_t &);
}

#endif
