#ifndef POINT_HPP
#define POINT_HPP

#include <fstream>

namespace vyzhanov
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);
  bool operator==(const Point&, const Point&);
}

#endif
