#include "cmds.hpp"

namespace feofanova
{
  struct AreaFunctor
  {
    double operator()(const Point& a, const Point& b) const
    {
      return (a.x * b.y) - (b.x * a.y);
    }
  };
}

double feofanova::getArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
   return 0.0;
  }
  std::vector<double> areas(polygon.points.size());
  std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin() + 1, areas.begin(), AreaFunctor());
  AreaFunctor func;
  areas.push_back(func(polygon.points.back(), polygon.points.front()));
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return std::abs(area) / 2.0;
}

bool feofanova::isAreaLess(const std::vector< Polygon >& input, const std::vector< Polygon >& data)
{
  return getArea(input) > getArea(data);
}

bool feofanova::Perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data)
{
  for (int i = 0; i != input.points.size(); i++)
  {
  CurP = input.points[i];
  if !(std::find(data.points.cbegin(), data.points.cend(), curP)) { return false; }
  }
  return true;
}

