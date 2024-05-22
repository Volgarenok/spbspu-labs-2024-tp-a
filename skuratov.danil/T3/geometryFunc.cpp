#include "geometryFunc.hpp"

bool skuratov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool skuratov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

double skuratov::isMean(const Polygon& polygon, size_t numOfPolygons, double averageArea)
{
  averageArea += polygon.getArea() / numOfPolygons;
  return averageArea;
}

double skuratov::isNumOfVertexes(const Polygon& polygon, size_t numOfVertexes, double sumOfAreas)
{
  if (polygon.points.size() == numOfVertexes)
  {
    sumOfAreas += polygon.getArea();
  }
  return sumOfAreas;
}
