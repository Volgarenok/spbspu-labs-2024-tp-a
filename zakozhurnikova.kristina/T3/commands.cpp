#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <scopeGuard.hpp>

namespace zak = zakozhurnikova;

void zak::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1) << zak::accumulateArea(cmd, polygons);
}
void zak::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("INVALID COMMAND");
  }
  std::string cmd;
  in >> cmd;
  using namespace std::placeholders;
  using Command = std::function< void() >;
  std::map< std::string, Command > commands;
  {
    commands["AREA"] = std::bind(getMaxArea, std::cref(polygons), std::ref(out));
    commands["VERTEXES"] = std::bind(getMaxVertex, std::cref(polygons), std::ref(out));
  }
  Command maxFunctor;
  maxFunctor = commands.at(cmd);
  maxFunctor();
}

void zak::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("INVALID COMMAND");
  }
  std::string cmd;
  in >> cmd;
  using namespace std::placeholders;
  using Command = std::function< void() >;
  std::map< std::string, Command > commands;
  {
    commands["AREA"] = std::bind(getMinArea, std::cref(polygons), std::ref(out));
    commands["VERTEXES"] = std::bind(getMinVertex, std::cref(polygons), std::ref(out));
  }
  Command minFunctor;
  minFunctor = commands.at(cmd);
  minFunctor();
}
void zak::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << countVertexes(cmd, polygons);
}

bool hasIntersection(const zak::Polygon& lhs, const zak::Polygon& rhs)
{
  zak::Point minLhs = *std::min_element(lhs.points.cbegin(), lhs.points.cend());
  zak::Point maxLhs = *std::max_element(lhs.points.cbegin(), lhs.points.cend());
  zak::Point minRhs = *std::min_element(rhs.points.cbegin(), rhs.points.cend());
  zak::Point maxRhs = *std::max_element(rhs.points.cbegin(), rhs.points.cend());

  bool firstCheck = (minLhs <= maxRhs) && (maxLhs >= minRhs);
  bool secondCheck = (minRhs <= maxLhs) && (maxRhs >= minLhs);
  return firstCheck || secondCheck;
}

void zak::intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty vector");
  }

  Polygon polygon;
  in >> polygon;

  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("invalid read");
  }
  using namespace std::placeholders;
  auto intersectPredicate = std::bind(hasIntersection, std::cref(polygon), _1);
  out << std::count_if(polygons.cbegin(), polygons.cend(), intersectPredicate);
}

void zak::rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  auto toRemoveIt = std::unique(polygons.begin(), polygons.end(), std::equal_to< Polygon >());
  std::size_t removedCount = std::distance(toRemoveIt, polygons.end());
  polygons.erase(toRemoveIt, polygons.end());
  out << --removedCount;
}
