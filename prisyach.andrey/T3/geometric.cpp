#include "geometric.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "delimiters.hpp"

bool prisyach::operator==(const Point & p1, const Point & p2)
{
  return ((p1.x_ == p2.x_) && (p2.y_ == p1.y_));
}

bool prisyach::operator!=(const Point & p1, const Point & p2)
{
  return ((p1.x_ != p2.x_) || (p2.y_ != p1.y_));
}

bool prisyach::operator<(const Point & p1, const Point & p2)
{
  return ((p1.x_ < p2.x_) || (p1.y_ < p2.y_));
}

bool prisyach::operator>(const Point & p1, const Point & p2)
{
  return ((p1.x_ > p2.x_) || (p1.y_ > p2.y_));
}

bool prisyach::operator<=(const Point & p1, const Point & p2)
{
  return ((p1.x_ <= p2.x_) || (p1.y_ <= p2.y_));
}

bool prisyach::operator>=(const Point & p1, const Point & p2)
{
  return ((p1.x_ >= p2.x_) || (p1.y_ >= p2.y_));
}

std::istream & prisyach::operator>>(std::istream & in, Point & p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  else
  {
    Point temp{};
    in >> DelimiterChar{'('} >> temp.x_ >> DelimiterChar{';'} >> temp.y_ >> DelimiterChar{')'};
    if (in)
    {
      p = temp;
    }
    return in;
  }
}

double prisyach::getArea(const Polygon & p)
{
  auto bind = std::bind(PolygonArea{p.points[1]}, std::placeholders::_1, std::placeholders::_2, p.points[0]);
  return std::accumulate(p.points.cbegin(), p.points.cend(), 0.0, bind);
}

bool prisyach::operator==(const Polygon & p1, const Polygon & p2)
{
  return ((p1.points.size() == p2.points.size()) && (std::equal(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin())));
}

bool prisyach::operator!=(const Polygon & p1, const Polygon & p2)
{
  return !((p1.points.size() == p2.points.size()) && (std::equal(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin())));
}

std::istream & prisyach::operator>>(std::istream & in, Polygon & p)
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
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, (pointsCount - 1), std::inserter(temp, temp.end()));
  if (in.peek() != '\n')
  {
    std::copy_n(input_it_t{ in }, 1, std::inserter(temp, temp.end()));
  }
  if (in && (temp.size() == pointsCount) && ((in.peek() == '\n')))
  {
    p.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
