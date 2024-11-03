#include "polygon.hpp"

#include <iostream>


std::istream & kovtun::operator>>(std::istream & in, kovtun::Polygon & polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using dl = kovtun::DelimiterI;

  polygon.points.clear();
  size_t size = 0;
  in >> size;
  for (size_t i = 0; i < size; ++i)
  {
    kovtun::Point point = {};
    in >> dl{'('} >> point.x >> dl{';'} >> point.y >> dl{')'};
    polygon.points.push_back(point);
  }

  return in;
}
