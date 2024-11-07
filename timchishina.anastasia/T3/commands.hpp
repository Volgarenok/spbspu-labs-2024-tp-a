#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "figures.hpp"

namespace timchishina
{
  void doArea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doMax(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doMin(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCount(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doRmecho(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doSame(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doMaxSeq(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
}
#endif
