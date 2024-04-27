#include "PolygonManager.hpp"

double kozakova::PolygonsArea::operator()(double area, const Polygon& polygon)
{
  area += polygon.getArea();
  return area;
}

double kozakova::PolygonsArea::operator()(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size()%2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double kozakova::PolygonsArea::operator()(double area, const Polygon& polygon, size_t n)
{
  if (polygon.points.size() == n)
  {
    area += polygon.getArea();
  }
  return area;
}

double kozakova::PolygonMaxArea::operator()(double max, const Polygon& polygon)
{
  return std::max(max, polygon.getArea());
}

size_t kozakova::PolygonMaxVertexes::operator()(size_t max, const Polygon& polygon)
{
  return std::max(max, polygon.points.size());
}

double kozakova::PolygonMinArea::operator()(double min, const Polygon& polygon)
{
  return std::min(min, polygon.getArea());
}

size_t kozakova::PolygonMinVertexes::operator()(size_t min, const Polygon& polygon)
{
  return std::min(min, polygon.points.size());
}

int kozakova::PolygonCount::operator()(int count, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    count++;
  }
  return count;
}

int kozakova::PolygonCount::operator()(int count, const Polygon& polygon, size_t n)
{
  if (polygon.points.size() == n)
  {
    count++;
  }
  return count;
}

int kozakova::PolygonRect::operator()(int count, Polygon& polygon)
{
  if (polygon.points.size() == 4)
  {
    count += polygon.isRect();
  }
  return count;
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
