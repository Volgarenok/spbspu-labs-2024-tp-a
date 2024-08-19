#include "polygon.hpp"
#include <iostream>
#include <limits>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>
#include <delimiter.hpp>

std::istream &altun::operator>>(std::istream& in, Point& point)
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

std::istream &altun::operator>>(std::istream& in, Polygon& poly)
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

bool altun::operator==(const Polygon &lhs, const Polygon &rhs)
{
  return lhs.points == rhs.points;
}

bool altun::operator==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

size_t altun::getSize(const Polygon& poly)
{
  return poly.points.size();
}

int altun::getX(const Point& p)
{
  return p.x;
}

int altun::getY(const Point& p)
{
  return p.y;
}

double altun::getPolyArea(const Polygon& poly)
{
  std::vector< Point > tmp = poly.points;
  tmp.push_back(tmp[0]);

  {
    using namespace std::placeholders;
    std::function< int(const Point&, const Point&) > multiplyXY = std::bind(
        std::multiplies< int >{},
        std::bind(getX, _1),
        std::bind(getY, _2));

    std::function< int(const Point&, const Point&) > gaussFunc = std::bind(
        std::minus< int >{},
        std::bind(multiplyXY, _1, _2),
        std::bind(multiplyXY, _2, _1));

    std::vector< int > determ;
    std::transform(++tmp.begin(), tmp.end(), tmp.begin(), std::back_inserter(determ), gaussFunc);

    return std::abs(std::accumulate(determ.cbegin(), determ.cend(), 0.0)) / 2.0;
  }
}
