#include "geometryFunc.hpp"

bool skuratov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool skuratov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
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

double skuratov::maxArea(const Polygon& p1, const Polygon& p2)
{
  return p1.getArea() < p2.getArea();
}

size_t skuratov::maxVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

void skuratov::isMaxArea(std::ostream& out, const std::vector<Polygon>& polygons)
{
  if (!polygons.empty())
  {
    double maxAreas = std::max_element(polygons.begin(), polygons.end(), maxArea)->getArea();
    out << std::fixed << std::setprecision(1) << maxArea << '\n';
  }
}

void skuratov::isMaxVertexes(std::ostream& out, const std::vector<Polygon>& polygons)
{
  if (!polygons.empty())
  {
    size_t maxVertices = std::max_element(polygons.begin(), polygons.end(), maxVertexes)->points.size();
    out << maxVertices << '\n';
  }
}
