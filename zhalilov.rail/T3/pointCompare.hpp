#ifndef POINTCOMPARE_HPP
#define POINTCOMPARE_HPP

namespace zhalilov
{
  struct Point;
  bool operator==(const Point &first, const Point &second);
  bool operator<(const Point &first, const Point &second);
}

#endif
