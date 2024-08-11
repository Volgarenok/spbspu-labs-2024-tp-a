#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace isaychev
{
  using polCollection = std::vector< Polygon >;

  void doAreaCmd(std::istream & in, std::ostream & out, const polCollection & col);
/*  void doCountCmd(std::istream & in, std::ostream & out, const polCollection & col);
  void doMaxCmd(std::istream & in, std::ostream & out, const polCollection & col);
  void doMinCmd(std::istream & in, std::ostream & out, const polCollection & col);
  void doMaxSeqCmd(std::istream & in, std::ostream & out, const polCollection & col);
  void doIntersectionsCmd(std::istream & in, std::ostream & out, const polCollection & col);*/
}

#endif
