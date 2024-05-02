#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
//RMECHO SAME
namespace petrov
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };


}

#endif