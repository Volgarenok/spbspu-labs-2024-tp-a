#include "polygon.hpp"

#include <algorithm>

std::istream& belokurskaya::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t numPoints;
  in >> numPoints;
  if (numPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  std::generate_n(std::back_inserter(tmp), numPoints, [&in]()
    {
      Point tmpPoint;
      in >> tmpPoint;
      return tmpPoint;
    });
  tmp.shrink_to_fit();
  if (!in.fail())
  {
    polygon.points = tmp;
  }
  return in;
}

std::ostream& belokurskaya::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << polygon.points.size() << " ";
  std::copy
  (
    polygon.points.cbegin(),
    polygon.points.cend(),
    std::ostream_iterator< Point >{ out, " " }
  );
}
