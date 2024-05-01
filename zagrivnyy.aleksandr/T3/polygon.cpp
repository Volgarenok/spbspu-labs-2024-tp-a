#include "polygon.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

#include <delimiter.hpp>

std::istream &zagrivnyy::operator>>(std::istream &in, Point &src)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = zagrivnyy::DelimiterI;
  int x = 0;
  int y = 0;
  in >> del{"("} >> x >> del{";"} >> y >> del{")"};

  if (in)
  {
    src.x = x;
    src.y = y;
  }

  return in;
}

std::istream &zagrivnyy::operator>>(std::istream &in, Polygon &src)
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

  using input_it_t = std::istream_iterator< Point >;
  std::vector< Point > points;
  points.reserve(count);
  std::copy_n(input_it_t{in}, count, std::back_inserter(points));

  if (in && points.size() == count && in.peek() == '\n')
  {
    src.points = std::move(points);
  }

  return in;
}

double zagrivnyy::Polygon::getArea() const
{
  double area = 0.0;

  auto shoelaceFormula = [&](const Point &p1) {
    const Point &p2 = *(std::next(&p1));
    area += p1.x * p2.y - p2.x * p1.y;
  };

  std::for_each(points.cbegin(), points.cend() - 1, shoelaceFormula);

  area += points.back().x * points.front().y - points.front().x * points.back().y;

  return 0.5 * std::abs(area);
}

bool zagrivnyy::Polygon::operator==(const Polygon &src) const
{
  return std::mismatch(points.cbegin(), points.cend(), src.points.cbegin()).first == points.cend();
}

bool zagrivnyy::Point::operator==(const Point &src) const
{
  return x == src.x && y == src.y;
}

bool zagrivnyy::Point::operator<(const Point &src) const
{
  return x < src.x && y < src.y;
}

bool zagrivnyy::Point::operator<=(const Point &src) const
{
  return !(src < *this);
}

bool zagrivnyy::Point::operator>=(const Point &src) const
{
  return !(*this < src);
}
