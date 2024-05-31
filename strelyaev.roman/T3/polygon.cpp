#include "polygon.hpp"
#include <iostream>
#include <limits>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>
#include <delimiter.hpp>

std::istream &strelyaev::operator>>(std::istream& in, Point& point)
{
  {
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point tmp{ 0, 0 };
  in >> del{ '(' } >> tmp.x >> del{ ';' } >> tmp.y >> del{ ')' };
  if (in)
  {
    point = tmp;
  }
  return in;
}
}

std::istream &strelyaev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t pointsCount = 0;
  in >> pointsCount;

  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  std::copy_n(in_it{ in }, pointsCount, std::back_inserter(temp));

  if (in && temp.size() == pointsCount)
  {
    poly.points = temp;
  }

  return in;
}

size_t strelyaev::get_size(const Polygon& poly)
{
  return poly.points.size();
}

int strelyaev::get_x(const Point& p)
{
  return p.x;
}

int strelyaev::get_y(const Point& p)
{
  return p.y;
}

double strelyaev::get_area(const Polygon& poly)
{
  std::vector< Point > tmp = poly.points;
  tmp.push_back(tmp[0]);
  {
    using namespace std::placeholders;
    std::function< int(const Point&, const Point&) > multiply_x_y = std::bind(
        std::multiplies< int >{},
        std::bind(get_x, _1),
        std::bind(get_y, _2));
    std::function< int(const Point&, const Point&) > gauss_func = std::bind(
        std::minus< int >{},
        std::bind(multiply_x_y, _1, _2),
        std::bind(multiply_x_y, _2, _1));
    std::vector< int > determ;
    std::transform(++tmp.begin(), tmp.end(), tmp.begin(), std::back_inserter(determ), gauss_func);
    return std::abs(std::accumulate(determ.cbegin(), determ.cend(), 0.0)) / 2.0;
  }
}

bool strelyaev::operator==(const Polygon &lhs, const Polygon &rhs)
{
  return lhs.points == rhs.points;
}
bool strelyaev::operator==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
