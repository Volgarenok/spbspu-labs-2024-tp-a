#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "figures.hpp"

namespace kozlov
{
  void doCmdArea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCmdMax(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCmdMin(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCmdCount(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCmdEcho(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCmdInframe(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
}
#endif
