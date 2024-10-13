#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

using namespace kornienko;

bool kornienko::Point::operator==(const Point & other) const
{
  return (x == other.x && y == other.y);
}

double triangleArea(const Triangle & triangle)
{
  return 0.5 * std::abs((triangle.second.x - triangle.first.x) * (triangle.third.y - triangle.first.y)
 - (triangle.second.y - triangle.first.y) * (triangle.third.x - triangle.first.x));
}

double kornienko::getArea(const Polygon & polygon)
{
  using namespace std::placeholders;
  std::vector< Triangle > triangles(polygon.points.size() - 2);
  TriangleParser base;
  std::generate_n(triangles.begin(), triangles.size(), std::bind(base, polygon));
  std::vector< double > areas(triangles.size());
  std::transform(triangles.cbegin(), triangles.cend(), areas.begin(), triangleArea);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

Triangle kornienko::TriangleParser::operator()(const Polygon & polygon)
{
  return Triangle(polygon, ++count);
}

std::istream & kornienko::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeter;
  Point temp;
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }
  return in;
}

std::ostream & kornienko::operator<<(std::ostream & out, const Point & point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::istream & kornienko::operator>>(std::istream & in, Polygon & polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  Polygon temp;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{in}, n, std::back_inserter(temp.points));
  if (in)
  {
    polygon = temp;
  }
  return in;
}

std::ostream & kornienko::operator<<(std::ostream & out, const Polygon & polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  std::cout << polygon.points.size() << " ";
  using output_it_t = std::ostream_iterator< Point >;
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{out, " "});
  return out;
}
