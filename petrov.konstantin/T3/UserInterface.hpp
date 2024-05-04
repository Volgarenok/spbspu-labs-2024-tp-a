#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <iostream>
#include <vector>
#include "Geometry.hpp"

namespace petrov
{
  void run(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons);
  double getAreaNOV(std::vector< Polygon >& polygons, std::istream& in);
  double countNOV(std::vector< Polygon >& polygons, std::istream& in);
}

#endif
