#include "commands.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <scopeGuard.hpp>

void baranov::area(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  if (shapes.empty())
  {
      throw std::logic_error("There are no shapes");
  }
  ScopeGuard guard(out);
  std::map< std::string, std::function< double(const Polygon &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(sumArea, 0.0, _1, isEven);
    cmds["ODD"] = std::bind(sumArea, 0.0, _1, isOdd);
    cmds["MEAN"] = std::bind(countMeanArea, 0.0, _1, shapes.size());
  }

  std::string cmd;
  in >> cmd;
  std::function< double(const Polygon &) > areaFunctor;
  if (cmds.find(cmd) != cmds.end())
  {
    areaFunctor = cmds.at(cmd);
  }
  else
  {
    using namespace std::placeholders;
    size_t numOfVertexes = std::stoull(cmd);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("Invalid vertexes count");
    }
    std::function< bool(const Polygon &) > predicate = std::bind(isNumOfVertexes, _1, numOfVertexes);
    areaFunctor = std::bind(sumArea, 0.0, _1, predicate);
  }

    std::vector< double > areas;
    std::transform(shapes.cbegin(), shapes.cend(), std::back_inserter(areas), areaFunctor);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void baranov::max(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  if (shapes.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  ScopeGuard guard(out);
  std::map< std::string, std::function< void() > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(maxArea, std::ref(shapes), std::ref(out));
    cmds["VERTEXES"] = std::bind(maxVertexes, std::ref(shapes), std::ref(out));
  }
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1);
  cmds.at(cmd)();
}

void baranov::min(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  if (shapes.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  ScopeGuard guard(out);
  std::map< std::string, std::function< void() > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(minArea, std::ref(shapes), std::ref(out));
    cmds["VERTEXES"] = std::bind(minVertexes, std::ref(shapes), std::ref(out));
  }
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1);
  cmds.at(cmd)();
}

void baranov::count(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{
  std::map< std::string, std::function< bool(const Polygon &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(isEvenVertexesCount, _1);
    cmds["ODD"] = std::bind(isOddVertexesCount, _1);
  }
  std::function< double(const Polygon &) > countFunctor;
  std::string cmd;
  in >> cmd;
  if (cmds.find(cmd) != cmds.end())
  {
    countFunctor = cmds.at(cmd);
  }
  else
  {
    size_t numOfVertexes = std::stoull(cmd);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("Invalid vertexes count");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(isNumOfVertexes, _1, numOfVertexes);
  }
    out << std::count_if(shapes.cbegin(), shapes.cend(), countFunctor);
}

void baranov::rect(std::vector< Polygon > & shapes, std::istream &, std::ostream & out)
{
  out << std::count_if(shapes.cbegin(), shapes.cend(), isRectangle);
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

double baranov::countMeanArea(double currArea, const Polygon & polygon, size_t count)
{
  return currArea + getArea(polygon) / count;
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

bool baranov::isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes)
{
  return numOfVertexes == polygon.points.size();
}

bool baranov::areaComparator(const Polygon & lhs, const Polygon & rhs)
{
  return getArea(lhs) < getArea(rhs);
}

void baranov::maxArea(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

void baranov::minArea(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

bool baranov::vertexesComparator(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void baranov::maxVertexes(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

void baranov::minVertexes(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

bool baranov::isEvenVertexesCount(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool baranov::isOddVertexesCount(const Polygon & polygon)
{
  return !isEvenVertexesCount(polygon);
}

bool baranov::isSquareTriangle(const Point & a, const Point & b, const Point & c)
{
  double ab = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  double ac = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
  double bc = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
  return ab + ac == bc;
}

bool baranov::isRectangle(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() != 4)
  {
    return false;
  }
  const Point & a = points.at(0);
  const Point & b = points.at(1);
  const Point & c = points.at(2);
  const Point & d = points.at(3);
  return isSquareTriangle(a, b, c) && isSquareTriangle(d, b, c);
}

