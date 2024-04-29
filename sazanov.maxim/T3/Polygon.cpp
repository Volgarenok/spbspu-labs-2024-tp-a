#include "Polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "Point.hpp"
#include "PolygonFunctors.hpp"

std::istream& sazanov::operator>>(std::istream& in, sazanov::Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::size_t vertices = 0;
  in >> vertices;
  if (vertices < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;
  temp.reserve(vertices);
  for (std::size_t i = 0; in && i < vertices && in.peek() != '\n'; ++i)
  {
    Point p{ 0, 0 };
    if (in >> p)
    {
      temp.push_back(p);
    }
  }
  if (temp.size() == vertices)
  {
    polygon.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const sazanov::Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using output_it_t = std::ostream_iterator< Point >;
  std::copy(
    polygon.points.begin(),
    polygon.points.end(),
    output_it_t{out, " "}
  );
  return out;
}

double sazanov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateAreaPart = std::bind(AccumulatePolygonAreaPart{points[1]}, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, accumulateAreaPart) / 2;
}

bool sazanov::isValidPolygon(const sazanov::Polygon& polygon)
{
  return !polygon.points.empty();
}

bool sazanov::Polygon::operator==(const sazanov::Polygon& rhs) const
{
  if (points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(this->points.begin(), this->points.end(), rhs.points.begin());
}
