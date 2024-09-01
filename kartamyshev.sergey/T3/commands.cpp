#include "commands.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>

#include "Polygon.h"


bool isOdd(const kartamyshev::Polygon& polygon)
{
  return polygon.points.size() % 2;
}

bool isEven(const kartamyshev::Polygon& polygon)
{
  return !(polygon.points.size() % 2);
}

bool isCorrectSizeFigure(const kartamyshev::Polygon& polygon, size_t size)
{
  return polygon.points.size() == size;
}

bool comparerVertexes(const kartamyshev::Polygon& polygon1, const kartamyshev::Polygon& polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

bool compareArea(const kartamyshev::Polygon& first, const kartamyshev::Polygon& second)
{
  return getArea(first) < getArea(second);
}

kartamyshev::Point overlay(const kartamyshev::Point& first, const kartamyshev::Point& second)
{
  return kartamyshev::Point{ second.x - first.x, second.y - first.y };
}
