#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include "point.hpp"

namespace zaparin
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& plg);
}

#endif

