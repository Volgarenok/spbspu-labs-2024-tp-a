#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include <algorithm>

#include "CrossRefs.hpp"

namespace stepanchenko
{
  void create_tableCmd(std::vector< CrossRefs > cross_refs, std::istream & in);
  void add_to_tableCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void get_intersectionCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void print_linesCmd(std::vector< CrossRefs > cross_refs, std::istream& in, std::ostream& out);
  void print(std::vector< CrossRefs > cross_refs, std::istream& in, std::ostream& out);
  void delete_lines(std::vector< CrossRefs > cross_refs, std::istream& in);
  void move_lines_downCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void rearrangeCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void get_selectionCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void print_tablesCmd(std::vector< CrossRefs > cross_refs, std::ostream& out);
}

#endif
