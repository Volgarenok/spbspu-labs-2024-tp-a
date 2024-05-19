#include <cmath>

#include "commands.hpp"

void kornienko::area(std::istream &, std::ostream & out, const std::vector< Polygon > polygons)
{
  for (size_t i = 0; i < polygons.size(); ++i)
  {
    out << polygons[i].getArea() << "\n";
  }
}
