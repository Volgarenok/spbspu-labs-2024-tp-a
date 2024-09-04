#ifndef COMMANDS_H
#define COMMANDS_H

#include "shapes.h"

namespace kazennov
{
  void getArea(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getMax(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getMin(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getCount(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getPerms(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getIntersections(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
  void getInframe(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon);
}

#endif
