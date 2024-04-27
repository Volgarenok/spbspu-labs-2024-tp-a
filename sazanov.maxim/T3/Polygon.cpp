#include "Polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
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
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(
    input_it_t{std::cin},
    vertices,
    std::back_inserter(temp)
  );
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
    output_it_t{std::cout, " "}
  );
  return out;
}

double sazanov::Polygon::getArea() const
{
  double area = std::accumulate(points.begin(), points.end(), 0.0, AccumulatePolygonAreaPart{points[0]});
  area += (points[points.size() - 1].x - points[0].x) * (points[points.size() - 1].y + points[0].y);
  return std::abs(area) / 2;
}
