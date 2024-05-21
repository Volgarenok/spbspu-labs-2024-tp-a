#include "polygon.hpp"
#include <iostream>
#include <limits>
#include <iterator>
#include <numeric>
#include <functional>
#include <delimeter.hpp>


std::istream& strelyaev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using del = Delimiter;
  return in >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
}

std::istream& strelyaev::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >(in), size, std::back_inserter(points));
  if (in.good())
  {
    poly.points = points;
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return in;
}

size_t strelyaev::size_getter(const Polygon& poly)
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
    std::function< int(const Point&, const Point&) > multiply_x_y = std::bind(std::multiplies< int >{}, std::bind(get_x, _1), std::bind(get_y, _2));
    std::function< int(const Point&, const Point&) > gauss_func = std::bind(std::minus< int >{}, std::bind(multiply_x_y, _1, _2), std::bind(multiply_x_y, _2, _1));
    std::vector< int > determ;
    std::transform(++tmp.begin(), tmp.end(), tmp.begin(), std::back_inserter(determ), gauss_func);
    return std::abs(std::accumulate(determ.cbegin(), determ.cend(), 0.0)) / 2.0;
  }
}

bool strelyaev::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points;
}
bool strelyaev::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

