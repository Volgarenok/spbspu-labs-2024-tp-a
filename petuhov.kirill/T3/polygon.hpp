#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iosfwd>
#include <vector>

namespace petuhov
{
  struct Point
  {
    int x_;
    int y_;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  bool operator==(const Polygon &a, const Polygon &b) {
    return a.points == b.points;
  }
}

#endif
