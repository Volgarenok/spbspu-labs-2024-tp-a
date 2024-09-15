#include "polygons.hpp"
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>
#include <vector>

#include <delimiter.hpp>


std::istream &arakelyan::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterIO;
  Point temp{0, 0};

  in >> del{'('} >> temp.x_ >> del{';'} >> temp.y_ >> del{')'};

  if (in)
  {
    point = temp;
  }
  return in;
}

std::istream &arakelyan::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t pCounter = 0;
  in >> pCounter;

  if (pCounter < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > temp;

  using it = std::istream_iterator< Point >;
  std::copy_n(it(in), pCounter, std::back_inserter(temp));

  if (in && temp.size() == pCounter)
  {
    polygon.points = temp;
  }

  return in;
}

size_t arakelyan::get_size(const Polygon &polygon)
{
  return polygon.points.size();
}

int arakelyan::get_x(const Point &point)
{
  return point.x_;
}

int arakelyan::get_y(const Point &point)
{
  return point.y_;
}

double arakelyan::get_area(const Polygon &polygon)
{
  std::vector< Point > temp = polygon.points;

  {
    using namespace std::placeholders;
    std::function< int(const Point&, const Point&) > multiply = std::bind(
      std::multiplies< int >{},
      std::bind(get_x, _1),
      std::bind(get_y, _2)
    );
    std::function< int(const Point&, const Point&) >gFunc = std::bind(
      std::minus< int >{},
      std::bind(multiply, _1, _2),
      std::bind(multiply, _2, _1)
    );
    std::vector< int > det;
    std::transform(++temp.begin(), temp.end(), temp.begin(), std::back_inserter(det), gFunc);
    return std::abs(std::accumulate(det.cbegin(), det.cend(), 0.0)) / 2.0;
  }

}

bool arakelyan::operator==(const Polygon &p1, const Polygon &p2)
{
  return p1.points == p2.points;
}

bool arakelyan::operator==(const Point &p1, const Point &p2)
{
  return (p1.x_ == p2.x_) && (p1.y_ == p2.y_);
}
