#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <vector>

namespace kuznetsov
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);

  enum OddOrEvenOrMean
  {
    Odd,
    Even,
    Mean
  };

  enum MinOrMax
  {
    Max,
    Min
  };

}

#endif
