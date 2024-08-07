#include "auxiliaryCommands.hpp"

#include <vector>
#include <algorithm>
#include <numeric>

double ayupov::GetTriangleArea::operator()(const Point& three)
{
  double area = 0.5 * std::abs(one.x * (two.y - three.y) + two.x * (three.y - one.y) + three.x * (one.y - two.y));
  two = three;
  return area;
}
double ayupov::calculatePolygonArea(const Polygon& polygon)
{
  GetTriangleArea countTR{polygon.points[0], polygon.points[1]};
  std::vector<double> areas;
  std::transform(polygon.points.begin() + 2, polygon.points.end(), std::back_inserter(areas), countTR);
  double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
  return sum;
}
bool ayupov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}
bool ayupov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}
bool ayupov::isRightSize(const Polygon& polygon, size_t size)
{
  return polygon.points.size() == size;
}
size_t ayupov::vertexesNumber(const Polygon& polygon)
{
  return polygon.points.size();
}
double ayupov::maxArea(const std::vector<Polygon> polygons)
{
  std::vector<double> areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), ayupov::calculatePolygonArea);
  return *max_element(areas.cbegin(), areas.cend());
}
double ayupov::minArea(const std::vector<Polygon> polygons)
{
  std::vector<double> areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), ayupov::calculatePolygonArea);
  return *min_element(areas.cbegin(), areas.cend());
}
size_t ayupov::maxVertexes(const std::vector<Polygon> polygons)
{
  std::vector<size_t> nOfVert(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), nOfVert.begin(), ayupov::vertexesNumber);
  return *max_element(nOfVert.cbegin(), nOfVert.cend());
}
size_t ayupov::minVertexes(const std::vector<Polygon> polygons)
{
  std::vector<size_t> nOfVert(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), nOfVert.begin(), ayupov::vertexesNumber);
  return *min_element(nOfVert.cbegin(), nOfVert.cend());
}
