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

double skuratov::calculateSumOfAreas(double total, const Polygon& poly, std::function< bool(const Polygon& poly) > condition)
{
  if (condition(poly))
  {
    total += poly.getArea();
  }
  return total;
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

int skuratov::findMinX(const Polygon& poly)
{
  return std::min_element(poly.points.cbegin(), poly.points.cend(), compareByX)->x;
}

int skuratov::findMinY(const Polygon& poly)
{
  return std::min_element(poly.points.cbegin(), poly.points.cend(), compareByY)->y;
}

int skuratov::findMaxX(const Polygon& poly)
{
  return std::max_element(poly.points.cbegin(), poly.points.cend(), compareByX)->x;
}

int skuratov::findMaxY(const Polygon& poly)
{
  return std::max_element(poly.points.cbegin(), poly.points.cend(), compareByY)->y;
}

bool skuratov::compareMinX(const Polygon& p1, const Polygon& p2)
{
  return findMinX(p1) < findMinX(p2);
}

bool skuratov::compareMinY(const Polygon& p1, const Polygon& p2)
{
  return findMinY(p1) < findMinY(p2);
}

bool skuratov::compareMaxX(const Polygon& p1, const Polygon& p2)
{
  return findMaxX(p1) < findMaxX(p2);
}

bool skuratov::compareMaxY(const Polygon& p1, const Polygon& p2)
{
  return findMaxY(p1) < findMaxY(p2);
}

skuratov::Polygon skuratov::createBoundingBox(const std::vector< Polygon >& poly)
{
  int minX = findMinX(*std::min_element(poly.cbegin(), poly.cend(), compareMinX));
  int minY = findMinY(*std::min_element(poly.cbegin(), poly.cend(), compareMinY));
  int maxX = findMaxX(*std::max_element(poly.cbegin(), poly.cend(), compareMaxX));
  int maxY = findMaxY(*std::max_element(poly.cbegin(), poly.cend(), compareMaxY));

  std::vector< Point > boundingBox = { {minX, minY}, {minX, maxY}, {maxX, maxY}, {maxX, minY} };
  return Polygon{ boundingBox };
}

bool skuratov::rightCorner(const Polygon& poly)
{
  return poly.getCorners();
}
