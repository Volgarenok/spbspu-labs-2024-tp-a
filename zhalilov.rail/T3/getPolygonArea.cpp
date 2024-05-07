#include "getPolygonArea.hpp"

#include <cstddef>

#include "geometry.hpp"

double zhalilov::getPolygonArea(const Polygon &polygon)
{
  double area = 0.0;
  size_t size = polygon.points.size();
  for (size_t i = 0; i < size - 1; i++)
  {
    area -= polygon.points[i].x * polygon.points[i + 1].y;
  }
  area -= polygon.points[size - 1].x * polygon.points[0].y;
  for (size_t i = 0; i < size - 1; i++)
  {
    area += polygon.points[i].y * polygon.points[i + 1].x;
  }
  area += polygon.points[size - 1].y * polygon.points[0].x;
  area *= 0.5;
  return area;
}
