#include "geometryFunc.hpp"

bool skuratov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool skuratov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

double skuratov::calculateSumOfAreas(double sum, const Polygon& polygon, std::function< bool(const Polygon& polygon) > state)
{
  if (state(polygon))
  {
    sum += polygon.getArea();
  }
  return sum;
}

double skuratov::isMean(double averageArea, const Polygon& polygon, size_t numOfPolygons)
{
  averageArea += polygon.getArea() / numOfPolygons;
  return averageArea;
}

double skuratov::isNumOfVertexes(double sumOfAreas, const Polygon& polygon, size_t numOfVertexes)
{
  if (polygon.points.size() == numOfVertexes)
  {
    sumOfAreas += polygon.getArea();
  }
  return sumOfAreas;
}

bool skuratov::maxAndMinArea(const Polygon& p1, const Polygon& p2)
{
  return p1.getArea() < p2.getArea();
}

bool skuratov::maxAndMinVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

void skuratov::isMaxArea(std::ostream& out, const std::vector< Polygon >& polygon)
{
  if (!polygon.empty())
  {
    auto maxAreas = std::max_element(polygon.begin(), polygon.end(), maxAndMinArea)->getArea();
    out << std::fixed << std::setprecision(1) << maxAreas << '\n';
  }
}

void skuratov::isMaxVertexes(std::ostream& out, const std::vector< Polygon >& polygon)
{
  if (!polygon.empty())
  {
    size_t maxVertices = std::max_element(polygon.begin(), polygon.end(), maxAndMinVertexes)->points.size();
    out << maxVertices << '\n';
  }
}

void skuratov::isMinArea(std::ostream& out, const std::vector< Polygon >& polygon)
{
  if (!polygon.empty())
  {
    auto minAreas = std::min_element(polygon.begin(), polygon.end(), maxAndMinArea)->getArea();
    out << std::fixed << std::setprecision(1) << minAreas << '\n';
  }
}

void skuratov::isMinVertexes(std::ostream& out, const std::vector< Polygon >& polygon)
{
  if (!polygon.empty())
  {
    size_t minVertices = std::min_element(polygon.begin(), polygon.end(), maxAndMinVertexes)->points.size();
    out << minVertices << '\n';
  }
}

bool skuratov::isnumOfVertexesForCount(const Polygon& polygon, size_t num)
{
  return (polygon.points.size() == num);
}

bool skuratov::isAreaForLess(const Polygon& polygon, double area)
{
  return (polygon.getArea() < area);
}
