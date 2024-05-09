#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include <iomanip>
#include <stream_guard.hpp>
#include "detail.hpp"

namespace zaitsev
{
  std::ostream& area_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& max_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& min_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  std::ostream& count_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  void lessarea_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
  void inframe_cmd(std::istream& in, std::ostream& out, std::list< Polygon >& shapes);
}
#endif
