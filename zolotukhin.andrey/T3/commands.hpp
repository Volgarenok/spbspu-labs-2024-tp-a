#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygon.hpp"

namespace zolotukhin
{
  void doArea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doMax(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doMin(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void lessarea(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void doCount(std::vector< Polygon >& poly, std::istream& in, std::ostream& out);
  void getMaxSeq(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void doRightShapes(std::vector< Polygon >& polygons, std::ostream& out);
}
#endif
