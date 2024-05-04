#include "Utils.hpp"
#include <math.h>
#include "Geometry.hpp"

double petrov::AccPolygonAreaPart::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
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