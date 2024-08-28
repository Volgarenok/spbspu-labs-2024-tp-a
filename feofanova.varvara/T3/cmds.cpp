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

bool feofanova::isAreaLess(const Polygon& p1, const Polygon& p2)
{
  return getArea(p1) > getArea(p2);
}

bool feofanova::Perms(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::is_permutation(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin());
}

