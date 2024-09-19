#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

#include "CrossRefs.hpp"

namespace stepanchenko
{
  void create_tableCmd(std::vector< CrossRefs > cross_refs, std::istream & in);
  void add_to_tableCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
  void get_intersectionCmd(std::vector< CrossRefs > cross_refs, std::istream& in);
}

#endif
