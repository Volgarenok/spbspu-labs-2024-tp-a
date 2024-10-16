#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

#include "CrossRefs.hpp"

namespace stepanchenko
{
  void create_tableCmd(std::vector< CrossRefs > & cross_refs, std::istream & in);
  void add_to_tableCmd(std::vector< CrossRefs > & cross_refs, std::istream& in);
  void get_intersectionCmd(std::vector< CrossRefs > & cross_refs, std::istream& in);
  void print_linesCmd(std::vector< CrossRefs > & cross_refs, std::istream& in, std::ostream& out);
  void printCmd(std::vector< CrossRefs > & cross_refs, std::istream& in, std::ostream& out);
  void delete_linesCmd(std::vector< CrossRefs > & cross_refs, std::istream& in);
  void move_lines_downCmd(std::vector< CrossRefs > & cross_refs, std::istream& in);
  void viewCmd(std::vector< CrossRefs >& cross_refs, std::ostream& out);
  void get_selectionCmd(std::vector< CrossRefs > & cross_refs, std::istream& in);
  void saveCmd(std::istream& in, std::vector< CrossRefs > & cross_refs);
}

#endif
