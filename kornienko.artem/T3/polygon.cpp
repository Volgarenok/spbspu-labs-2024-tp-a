#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

#include "polygon.hpp"

using namespace kornienko;

double kornienko::Polygon::getArea() const
{
  using namespace std::placeholders;
  Triangle base = { points[1] };
  auto areaGetter = std::bind(base, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, areaGetter);
}

double kornienko::Triangle::operator()(double res, const Point & second, const Point & third)
{
  res += round(5 * std::abs((second.x - first.x) * (third.y - first.y) - (second.y - first.y) * (third.x - first.x))) / 10;
  first = second;
  return res;
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
