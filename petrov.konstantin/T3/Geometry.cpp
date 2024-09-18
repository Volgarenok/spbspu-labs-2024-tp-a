#include "Geometry.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>
#include <numeric>
#include <functional>
#include <stdexcept>
#include "Delimiter.hpp"
#include "Functors.hpp"

std::istream& petrov::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point input{ 0,0 };
  using del = petrov::DelimiterI;
  in >> del{ '(' } >> input.x >> del{ ';' } >> input.y >> del{ ')' };
  if (in)
  {
    dest = input;
  }
  return in;
}
std::ostream& petrov::operator<<(std::ostream& out, const Point& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << src.x << ';' << src.y << ')';
  return out;
}
bool petrov::operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}
petrov::Point petrov::getDelta(const Point& p1, const Point& p2)
{
  return { p2.x - p1.x, p2.y - p1.y };
}

std::istream& petrov::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  dest.points.clear();
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  std::istream_iterator< Point > inIt(in);
  std::copy_n(inIt, size, std::back_inserter(tmp));
  if (in && size == tmp.size())
  {
    dest = { tmp };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::ostream& petrov::operator<<(std::ostream& out, const Polygon& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << src.points.size();
  for (size_t i = 0; i < src.points.size(); ++i)
  {
    out << ' ' << src.points[i];
  }
  return out;
}
bool petrov::operator==(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin());
}
double petrov::accPolygonAreaEO(double area, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    area += getArea(polygon);
  }
  return area;
}
double petrov::accPolygonArea(double area, const Polygon& polygon)
{
  return area + getArea(polygon);
}
double petrov::accPolygonAreaNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes)
{
  if (polygon.points.size() == numOfVertexes)
  {
    area += getArea(polygon);
  }
  return area;
}
bool petrov::isSmallerPolygonArea(const Polygon& p1, const Polygon& p2)
{
  return getArea(p1) < getArea(p2);
}
bool petrov::isSmallerNumOfVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}
size_t petrov::accPolygonEON(size_t counter, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    ++counter;
  }
  return counter;
}
size_t petrov::accPolygonEON(size_t counter, const Polygon& polygon, size_t numOfVertexes)
{
  if (numOfVertexes == polygon.points.size())
  {
    ++counter;
  }
  return counter;
}
bool petrov::isEqualNOV(const Polygon& p, size_t numOfVertexes)
{
  return p.points.size() == numOfVertexes;
}
bool petrov::isSamePointsWithDelta(const Point& p1, const Point& p2, const Point& delta)
{
  return (p2.x - p1.x == delta.x) && (p2.y - p1.y == delta.y);
}
bool petrov::doesExistRespectivePoint(const Point& point, const Polygon& polygon, const Point& delta)
{
  using namespace std::placeholders;
  auto comp = std::bind(&isSamePointsWithDelta, point, _1, delta);
  return std::find_if(polygon.points.cbegin(), polygon.points.cend(), comp) != polygon.points.cend();
}
bool petrov::isSameWithTwoPoints(const Point& p1, const Point& p2, const Polygon& pol1, const Polygon& pol2)
{
  Point delta = getDelta(p1, p2);
  using namespace std::placeholders;
  auto compWithDelta = std::bind(&doesExistRespectivePoint, _1, pol2, delta);
  using diff_t = std::vector< Polygon >::difference_type;
  auto pol1CBegin = pol1.points.cbegin();
  auto pol1CEnd = pol1.points.cend();
  return std::count_if(pol1CBegin, pol1CEnd, compWithDelta) == static_cast< diff_t >(pol1.points.size());
}
bool petrov::isSame(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  using namespace std::placeholders;
  auto comp = std::bind(&isSameWithTwoPoints, p1.points[0], _1, p1, p2);
  return std::find_if(p2.points.cbegin(), p2.points.cend(), comp) != p2.points.cend();
}
bool petrov::isEven(const Polygon& p)
{
  return p.points.size() % 2 == 0;
}
bool petrov::isOdd(const Polygon& p)
{
  return p.points.size() % 2 != 0;
}
double petrov::getArea(const Polygon& src)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(AccPolygonAreaPart{ src.points[1] }, _1, _2, src.points[0]);
  return 0.5 * std::accumulate(src.points.cbegin(), src.points.cend(), 0.0, areaAcc);
}
