#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <list>
#include "shape.hpp"

namespace zaitsev
{
  std::ostream& processAreaCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& processMaxCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& processMinCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& processCountCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& processLessareaCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& processInframeCmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
}
#endif
