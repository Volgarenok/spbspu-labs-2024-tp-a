#include <iostream>
#include <iterator>
#include <algorithm>

#include "polygon.hpp"

using namespace kornienko;

std::istream & kornienko::operator>>(std::istream & in, Point & point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimeter;
  in >> del{ '(' } >> point.x >> del{ ';' } >> point.y >> del{ ')' };
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
  std::cin >> n;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{std::cin}, n, std::back_inserter(polygon.points));
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
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{std::cout, " "});
  return out;
}
