#include "polygon.hpp"

#include <algorithm>
#include <cmath>

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
  std::generate_n(std::back_inserter(tmp), numPoints,
    [&in]()
    {
      Point tmpPoint;
      in >> tmpPoint;
      return tmpPoint;
    });
  if (!in.fail())
  {
    polygon.points = tmp;
    polygon.points.shrink_to_fit();
  }
  return in;
}

bool belokurskaya::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points;
}

belokurskaya::RectVector::RectVector(const Point& p1, const Point& p2):
  vertexes(Point{ p2.x - p1.x, p2.y - p1.y })
{}

double belokurskaya::RectVector::operator*(const RectVector& p1)
{
  return vertexes.x * p1.vertexes.x + vertexes.y * p1.vertexes.y;
}

double belokurskaya::RectVector::getLength() const
{
  return std::hypot(vertexes.x, vertexes.y);
}

double belokurskaya::RectVector::cos(const RectVector& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}
