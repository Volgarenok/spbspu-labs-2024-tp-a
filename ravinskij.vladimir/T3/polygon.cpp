#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <limits>
#include <functional>
#include <numeric>
#include "partAreaFunctor.hpp"
std::istream& ravinskij::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = ravinskij::CharDelimeter;
  Point temp{ 0, 0 };
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    point = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool ravinskij::Point::operator==(const Point& rhs) const
{
  return (x == rhs.x) && (y == rhs.y);
}

bool ravinskij::Point::operator<(const Point& rhs) const
{
  return (x < rhs.x) && (y < rhs.y);
}

bool ravinskij::Point::operator<=(const Point& rhs) const
{
  return (*this == rhs) || (*this < rhs);
}

bool ravinskij::Point::operator>=(const Point& rhs) const
{
  return !(*this < rhs);
}

std::istream& ravinskij::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::size_t vertexCount = 0;
  in >> vertexCount;
  if (vertexCount < 3)
  {
   in.setstate(std::ios::failbit);
   return in;
  }
  std::vector< ravinskij::Point > temp;
  using input_it_t = std::istream_iterator< ravinskij::Point >;
  std::copy_n(input_it_t{ in }, vertexCount, std::back_inserter(temp));
  if(in && temp.size() == vertexCount)
  {
    polygon.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream& ravinskij::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using output_it_t = std::ostream_iterator< ravinskij::Point >;
  const auto& points = polygon.points;
  std::copy(points.cbegin(), points.cend(), output_it_t{ out, " "});
  return out;
}

bool ravinskij::Polygon::empty() const
{
  return points.empty();
}

bool ravinskij::Polygon::operator==(const Polygon& rhs) const
{
  if (points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(points.cbegin(), points.cend(), rhs.points.cbegin());
}

double ravinskij::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(PartAreaFunctor{ points.at(1) }, _1, _2, points.at(0));
  return std::accumulate(points.cbegin(), points.cend(), 0.0, accumulateArea) / 2;
}

std::size_t ravinskij::Polygon::size() const
{
  return points.size();
}
