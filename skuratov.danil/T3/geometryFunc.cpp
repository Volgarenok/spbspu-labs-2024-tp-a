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
