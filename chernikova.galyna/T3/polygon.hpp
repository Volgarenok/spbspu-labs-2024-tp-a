#ifndef POLYGON_HPP
#define POLYGON_HPP

namespace chernikova
{
  struct Point
  {
    Point() : x(0), y(0)
    {}
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
}

#endif
