#include "geometryFunc.hpp"

bool skuratov::isEven(const Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}

bool skuratov::isOdd(const Polygon& poly)
{
  return poly.points.size() % 2 == 1;
}

double skuratov::countArea(const Polygon& poly)
{
  return poly.getArea();
}

double skuratov::isMean(double averageArea, const Polygon& poly, size_t numOfPolygons)
{
  averageArea += poly.getArea() / numOfPolygons;
  return averageArea;
}

bool skuratov::isNumOfVertexes(const Polygon& poly, size_t num)
{
  return (poly.points.size() == num);
}

bool skuratov::maxAndMinArea(const Polygon& p1, const Polygon& p2)
{
  return p1.getArea() < p2.getArea();
}

bool skuratov::maxAndMinVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

void skuratov::isMaxArea(std::ostream& out, const std::vector< Polygon >& poly)
{
  if (!poly.empty())
  {
    double maxArea = std::max_element(poly.begin(), poly.end(), maxAndMinArea)->getArea();
    out << std::fixed << std::setprecision(1) << maxArea << '\n';
  }
}

void skuratov::isMaxVertexes(std::ostream& out, const std::vector< Polygon >& poly)
{
  if (!poly.empty())
  {
    size_t maxVertices = std::max_element(poly.begin(), poly.end(), maxAndMinVertexes)->points.size();
    out << maxVertices << '\n';
  }
}

void skuratov::isMinArea(std::ostream& out, const std::vector< Polygon >& poly)
{
  if (!poly.empty())
  {
    double minArea = std::min_element(poly.begin(), poly.end(), maxAndMinArea)->getArea();
    out << std::fixed << std::setprecision(1) << minArea << '\n';
  }
}

void skuratov::isMinVertexes(std::ostream& out, const std::vector< Polygon >& poly)
{
  if (!poly.empty())
  {
    size_t minVertices = std::min_element(poly.begin(), poly.end(), maxAndMinVertexes)->points.size();
    out << minVertices << '\n';
  }
}

bool skuratov::isAreaForLess(const Polygon& poly, double area)
{
  return (poly.getArea() < area);
}

bool skuratov::compareByX(const Point& p1, const Point& p2)
{
  return p1.x < p2.x;
}

bool skuratov::compareByY(const Point& p1, const Point& p2)
{
  return p1.y < p2.y;
}

int skuratov::getMinX(const Polygon& p)
{
  return std::min_element(p.points.cbegin(), p.points.cend(), compareByX)->x;
}

int skuratov::getMinY(const Polygon& p)
{
  return std::min_element(p.points.cbegin(), p.points.cend(), compareByY)->y;
}

int skuratov::getMaxX(const Polygon& p)
{
  return std::max_element(p.points.cbegin(), p.points.cend(), compareByX)->x;
}

int skuratov::getMaxY(const Polygon& p)
{
  return std::max_element(p.points.cbegin(), p.points.cend(), compareByY)->y;
}

skuratov::Polygon skuratov::createBoundingBox(const std::vector< Polygon >& poly)
{
  int minX = std::numeric_limits< int >::max();
  int minY = std::numeric_limits< int >::max();
  int maxX = std::numeric_limits< int >::min();
  int maxY = std::numeric_limits< int >::min();

  std::vector< int > xCoords;
  std::vector< int > yCoords;

  std::transform(poly.cbegin(), poly.cend(), std::back_inserter(xCoords), getMinX);
  std::transform(poly.cbegin(), poly.cend(), std::back_inserter(yCoords), getMinY);
  std::transform(poly.cbegin(), poly.cend(), std::back_inserter(xCoords), getMaxX);
  std::transform(poly.cbegin(), poly.cend(), std::back_inserter(yCoords), getMaxY);

  minX = *std::min_element(xCoords.begin(), xCoords.end());
  maxX = *std::max_element(xCoords.begin(), xCoords.end());
  minY = *std::min_element(yCoords.begin(), yCoords.end());
  maxY = *std::max_element(yCoords.begin(), yCoords.end());

  std::vector< Point > boundingBox = { {minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY} };
  return Polygon{ boundingBox };
}

bool skuratov::rightCorner(const Polygon& poly)
{
  return poly.getCorners();
}
