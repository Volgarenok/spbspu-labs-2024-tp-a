#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include "point.hpp"

std::istream& zaparin::operator>>(std::istream& in, Polygon& plg)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  Point pointTemp{ 0, 0 };
  Polygon plgTemp;
  int pointsCount = 0;
  in >> pointsCount;


  for (int i = 0; (i < pointsCount) && in; i++)
  {
    in >> pointTemp;
    plgTemp.points.push_back(pointTemp);
  }

  if (in)
  {
    plg = plgTemp;
  }

  return in;
}

std::ostream& zaparin::operator<<(std::ostream& out, const Polygon& plg)
{
  using out_it = std::ostream_iterator< Point >;

  std::copy(plg.points.begin(), plg.points.end(), out_it{ out, " " });

  return out;
}

bool zaparin::operator==(const Polygon& plg1, const Polygon& plg2)
{
  return (plg1.points == plg2.points);
}
