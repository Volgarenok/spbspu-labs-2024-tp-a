#include "PolygonManager.hpp"

double kozakova::PolygonsArea::operator()(double area, const Polygon& polygon)
{
  area += getArea(polygon);
  return area;
}

double kozakova::PolygonsArea::operator()(double area, const Polygon& polygon, size_t n)
{
  if (polygon.points.size() == n)
  {
    area += getArea(polygon);
  }
  return area;
}

double kozakova::PolygonsAreaOdd::operator()(double area, const Polygon& polygon)
{
  if (polygon.points.size() % 2)
  {
    area += getArea(polygon);
  }
  return area;
}

double kozakova::PolygonsAreaEven::operator()(double area, const Polygon& polygon)
{
  if (polygon.points.size() % 2 == 0)
  {
    area += getArea(polygon);
  }
  return area;
}

int kozakova::PolygonMaxSeq::operator()(int max, const Polygon& polygon, const Polygon& data)
{
  if (polygon == data)
  {
    cur++;
    max = std::max(max, cur);
  }
  else
  {
    cur = 0;
  }
  return max;
}
