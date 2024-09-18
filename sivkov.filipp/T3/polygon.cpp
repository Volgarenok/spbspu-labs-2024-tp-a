#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <cmath>
#include <numeric>
#include <Delimiter.hpp>

namespace sivkov
{
  bool operator<(const Point& point1, const Point& point2)
  {
    if (point1.x != point2.x)
    {
      return point1.x < point2.x;
    }
    return point1.y < point2.y;
  }

  bool operator==(const Point& point1, const Point& point2)
  {
    return (point1.x == point2.x) && (point1.y == point2.y);
  }

  std::istream& operator>>(std::istream& in, Point& value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using del = DelimiterI;
    Point newPoint{ 0, 0 };
    in >> del{ '(' } >> newPoint.x >> del{ ';' } >> newPoint.y >> del{ ')' };
    if (in)
    {
      value = newPoint;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }


  bool operator==(const Polygon& polygon1, const Polygon& polygon2)
  {
    return polygon1.points == polygon2.points;
  }

  std::istream& operator>>(std::istream& in, Polygon& value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    size_t count = 0;
    in >> count;
    if (count < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::vector< Point > data;
    data.reserve(count);
    std::copy_n(std::istream_iterator< Point >{ in }, count, std::back_inserter(data));
    if (in && data.size() == count)
    {
      value = Polygon{ data };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
