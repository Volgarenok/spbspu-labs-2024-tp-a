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
double petrov::AccPolygonMax(double max, const Polygon& polygon, bool forArea)
{
  double counter = forArea ? getArea(polygon) : polygon.points.size();
  if (max < counter)
  {
    max = counter;
  }
  return max;
}
double petrov::AccPolygonMin(double min, const Polygon& polygon, bool forArea)
{
  double counter = forArea ? getArea(polygon) : polygon.points.size();
  if (min > counter)
  {
    min = counter;
  }
  return min;
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