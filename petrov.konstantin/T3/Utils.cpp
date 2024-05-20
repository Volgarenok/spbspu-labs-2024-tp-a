#include "Utils.hpp"
#include <math.h>
#include <algorithm>
#include <functional>
#include "Geometry.hpp"

double petrov::AccPolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

bool petrov::EqualPol::operator()(const Polygon& p1, const Polygon& p2)
{
  return p1 == mask && p1 == p2;
}

double petrov::AccPolygonAreaEO(double area, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    area += getArea(polygon);
  }
  return area;
}
double petrov::AccPolygonArea(double area, const Polygon& polygon)
{
  return area + getArea(polygon);
}
double petrov::AccPolygonAreaNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes)
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
size_t petrov::AccPolygonEON(size_t counter, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    ++counter;
  }
  return counter;
}
size_t petrov::AccPolygonEON(size_t counter, const Polygon& polygon, size_t numOfVertexes)
{
  if (numOfVertexes == polygon.points.size())
  {
    ++counter;
  }
  return counter;
}
bool petrov::isEven(const Polygon& p)
{
  return p.points.size() % 2 == 0;
}
bool petrov::isOdd(const Polygon& p)
{
  return p.points.size() % 2 != 0;
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

bool petrov::myIsdigit(char symbol)
{
  return std::isdigit(static_cast< unsigned char >(symbol));
}
