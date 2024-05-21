#include "commands.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <scopeGuard.hpp>

void baranov::area(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  ScopeGuard guard(out);
  std::map< std::string, std::function< double(const Polygon &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(sumArea, 0.0, _1, isEven);
    cmds["ODD"] = std::bind(sumArea, 0.0, _1, isOdd);
  }
  std::string cmd;
  in >> cmd;
  auto areaFunctor = cmds.at(cmd);

  std::vector< double > areas;
  std::transform(shapes.cbegin(), shapes.cend(), std::back_inserter(areas), areaFunctor);

  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

baranov::AreaCounter::AreaCounter(const Point & a):
  a_(a)
{}

double baranov::AreaCounter::operator()(double currArea, const Point & b, const Point & c)
{
  currArea += 0.5 * std::abs((b.x - a_.x) * (c.y - a_.y) - (c.x - a_.x) * (b.y - a_.y));
  a_ = b;
  return currArea;
}

double baranov::getArea(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() < 3)
  {
    return 0.0;
  }
  using namespace std::placeholders;
  auto areaFunctor = std::bind(AreaCounter(points.at(1)), 0.0, _1, points.at(0));
  std::vector< double > areas;
  std::transform(points.cbegin(), points.cend(), std::back_inserter(areas), areaFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

double baranov::sumArea(double currArea, const Polygon & polygon, std::function< bool(const Polygon &) > p)
{
  if (p(polygon))
  {
    currArea += getArea(polygon);
  }
  return currArea;
}

bool baranov::isEven(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool baranov::isOdd(const Polygon & polygon)
{
  return !isEven(polygon);
}

