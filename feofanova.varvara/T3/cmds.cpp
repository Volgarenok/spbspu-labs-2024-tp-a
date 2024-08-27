#include "cmds.hpp"
#include <istream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include "StreamGuard.hpp"

double feofanova::getArea(const std::vector< Polygon >& data) const
{
  double area = 0.0;
  int j = n - 1;
  for (int i = 0; i < data.points.size(); i++)
  {
    area += (data.points[j].x + data.points[i].x) * (data.points[j].y - data.points[i].y);
    j = i;
  }
  return abs(area / 2.0);
  }
}

bool feofanova::isAreaLess(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const
{
  return getArea(input) > getArea(data);
}

bool feofanova::Perms(const std::vector< Polygon >& input, const std::vector< Polygon >& data) const
{
  for (int i = 0; i != input.points.size(); i++)
  {
  CurP = input.points[i];
  if !(std::find(data.points.cbegin(), data.points.cend(), curP)) { return false; }
  }
  return true;
}

