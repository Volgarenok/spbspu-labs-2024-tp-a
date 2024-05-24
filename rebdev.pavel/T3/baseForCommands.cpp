#include "baseForCommands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>

#include "triangle.hpp"

double rebdev::rebdev_private::getArea(double oldArea, const Polygon & p)
{
  size_t triangleNum = (p.points.size() - 2);
  std::vector< Triangle > tria(triangleNum);
  std::generate_n(tria.begin(), triangleNum, TriangleGenerator(p));

  return std::accumulate(tria.begin(), tria.end(), oldArea, plusArea);
}

double rebdev::rebdev_private::areaEvenOddBase(const polyVec & p, lambda pred)
{
  polyVec poly(p);
  auto it = std::remove_if(poly.begin(), poly.end(), pred);
  double area = 0;
  return std::accumulate(poly.begin(), it, area, getArea);
}
