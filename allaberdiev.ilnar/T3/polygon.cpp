#include "polygon.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <delimiter.hpp>

std::istream& allaberdiev::operator>>(std::istream& in, Point& point)
{
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    Point temp{0, 0};
    in >> Delimiter{'('} >> temp.x >> Delimiter{';'} >> temp.y >> Delimiter{')'};
    if (in)
    {
      point = temp;
    }
    return in;
  }
}

std::istream& allaberdiev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t points_count = 0;
  in >> points_count;

  if (points_count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;

  using input_it = std::istream_iterator< Point >;
  std::copy_n(input_it{in}, points_count, std::back_inserter(temp));

  if (in && temp.size() == points_count)
  {
    poly.points = temp;
  }

  return in;
}

size_t allaberdiev::get_size(const Polygon& poly)
{
  return poly.points.size();
}

int allaberdiev::get_x(const Point& p)
{
  return p.x;
}

int allaberdiev::get_y(const Point& p)
{
  return p.y;
}

double allaberdiev::get_area(const Polygon& poly)
{
  std::vector< Point > temp = poly.points;
  temp.push_back(temp[0]);
  {
    std::function< int(const Point&, const Point&) > multiply_x_y = std::bind(
        std::multiplies< int >{},
        std::bind(get_x, std::placeholders::_1),
        std::bind(get_y, std::placeholders::_2));
    std::function< int(const Point&, const Point&) > gauss_func = std::bind(
        std::minus< int >{},
        std::bind(multiply_x_y, std::placeholders::_1, std::placeholders::_2),
        std::bind(multiply_x_y, std::placeholders::_2, std::placeholders::_1));
    std::vector< int > determ;
    std::transform(++temp.begin(), temp.end(), temp.begin(), std::back_inserter(determ), gauss_func);
    return std::abs(std::accumulate(determ.cbegin(), determ.cend(), 0.0)) / 2.0;
  }
}

bool allaberdiev::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points;
}
bool allaberdiev::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
