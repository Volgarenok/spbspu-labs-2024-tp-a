#include "baseForCommands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>

#include "triangle.hpp"

double rebdev::rebdev_private::getArea(double oldArea, const Polygon & p)
{
  size_t triangleNum = (p.points.size() - 2);
  std::vector< Triangle > tria(triangleNum);
  std::generate_n(tria.begin(), triangleNum, TriangleGenerator(p));

  return std::accumulate(tria.begin(), tria.end(), oldArea, plusArea);
}

double rebdev::rebdev_private::areaIf(const polyVec & p, lambda pred)
{
  polyVec poly(p);
  auto it = std::remove_if(poly.begin(), poly.end(), pred);
  double area = 0;
  return std::accumulate(poly.begin(), it, area, getArea);
}

void rebdev::rebdev_private::fillAreaVec(const polyVec & p, std::vector< double > & vec)
{
  auto it = p.begin();
  std::generate_n(vec.begin(), p.size(),
    [&]()
    {
      double area = 0;
      return rebdev_private::getArea(area, *(it++));
    });
}

void rebdev::rebdev_private::fillVertVec(const polyVec & p, std::vector< size_t > & vec)
{
  auto it = p.begin();
  std::generate_n(vec.begin(), p.size(),
    [&]()
    {
      return (*(it++)).points.size();
    });
}

double rebdev::rebdev_private::distanceBetweenPoints(const Point & f, const Point & s)
{
  return std::sqrt(std::pow((f.x - s.x), 2) + std::pow((f.y - s.y), 2));
}
