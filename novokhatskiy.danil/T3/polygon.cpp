#include "polygon.hpp"
#include <iterator>
#include <functional>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <delimiter.hpp>
#include "commandsSolving.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp = {};
  in >> strictDel{ '(' } >> tmp.x >> strictDel{ ';' } >> tmp.y >> strictDel{ ')' };
  if (in)
  {
    p = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& novokhatskiy::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t countPoints = {};
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  for (size_t i = 0; i < countPoints; i++)
  {
    Point tmpP = {};
    if (in >> tmpP)
    {
      tmp.push_back(tmpP);
    }
  }
  if (in)
  {
    p.points = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using outIt = std::ostream_iterator< Point >;
  out << p.points.size() << ' ';
  std::copy(p.points.cbegin(), p.points.cend(), outIt{ out, " " });
  return out;
}

bool novokhatskiy::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool novokhatskiy::operator<(const Point& lhs, const Point& rhs)
{
  if (lhs.x == rhs.x)
  {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

bool novokhatskiy::operator<(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

double novokhatskiy::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto res = std::bind(AccumulateArea{points[1]}, _1, _2, points[0]);
  return std::accumulate(points.begin(), points.end(), 0.0, res);
}

novokhatskiy::RectangleVector::RectangleVector(const Point& p1, const Point& p2) :
  vertexes(novokhatskiy::Point{ p2.x - p1.x, p2.y - p1.y })
{}

double novokhatskiy::RectangleVector::operator*(const RectangleVector& p1)
{
  return (vertexes.x * p1.vertexes.x) + (vertexes.y * p1.vertexes.y);
}

double novokhatskiy::RectangleVector::getLength() const
{
  return std::sqrt(std::pow(vertexes.x,2) + std::pow(vertexes.y, 2));
}

double novokhatskiy::RectangleVector::cos(const RectangleVector& p1)
{
  return (*this *p1) / (getLength() * p1.getLength());
}
