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

    bool operator==(const Point &other) const {
      return x_ == other.x_ && y_ == other.y_;
    }
  };

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &is, Polygon &polygon);
  bool operator==(const Polygon &a, const Polygon &b);
}

#endif
