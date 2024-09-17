#include "polygon.hpp"
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <functional>
#include <algorithm>
#include <stdexcept>
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
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

size_t arakelyan::getVertexes(const Polygon &polygon)
{
  return polygon.points.size();
}

int arakelyan::getX(const Point &point)
{
  return point.x_;
}

int arakelyan::getY(const Point &point)
{
  return point.y_;
}

double arakelyan::getArea(const Polygon &polygon)
{
  std::vector< Point > temp = polygon.points;
  temp.push_back(temp[0]);
  {
    using namespace std::placeholders;
    std::function< int(const Point&, const Point&) > multiply = std::bind(
      std::multiplies< int >{},
      std::bind(getX, _1),
      std::bind(getY, _2)
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

bool arakelyan::isEven(const Polygon &polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool arakelyan::isOdd(const Polygon &polygon)
{
  return !isEven(polygon);
}

namespace details
{

  struct IsRightAngle
  {
    arakelyan::Point p1;
    arakelyan::Point p2;

    bool operator()(const arakelyan::Point &point) const;
  };

  double dotProduct(const arakelyan::Point &p1, const arakelyan::Point &p2, const arakelyan::Point &p3)
  {
    double ABx = p2.x_ - p1.x_;
    double ABy = p2.y_ - p1.y_;

    double BCx = p3.x_ - p2.x_;
    double BCy = p3.y_ - p2.y_;

    return ABx * BCx + ABy * BCy;
  }

  bool IsRightAngle::operator()(const arakelyan::Point &p) const
  {
    return std::abs(dotProduct(p1, p2, p)) == 0;
  }

}

bool arakelyan::hasRightShapes(const Polygon &polygon)
{
  if (polygon.points.size() < 3)
  {
    throw std::invalid_argument("cannot find angle!");
  }

  auto pr = details::IsRightAngle{*(polygon.points.cend() - 2), *(polygon.points.cend() - 1)};
  return std::any_of(polygon.points.cbegin(), polygon.points.cend(), pr);
}
