#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <scopeGuard.hpp>
#include "commandImpl.hpp"

namespace zak = zakozhurnikova;

void zak::doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1) << zak::accumulateArea(cmd, polygons);
}
void zak::doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
  commands["AREA"] = std::bind(getMaxArea, std::cref(polygons), std::ref(out));
  commands["VERTEXES"] = std::bind(getMaxVertex, std::cref(polygons), std::ref(out));

  Command maxFunctor;
  maxFunctor = commands.at(cmd);
  maxFunctor();
}

void zak::doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
void zak::doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << countVertexes(cmd, polygons);
}

bool hasIntersection(const zak::Polygon& lhs, const zak::Polygon& rhs)
{
  auto lhsPoints = std::minmax_element(lhs.points.cbegin(), lhs.points.cend());
  auto rhsPoints = std::minmax_element(rhs.points.cbegin(), rhs.points.cend());

  return !(*lhsPoints.second < *rhsPoints.first || *rhsPoints.second < *lhsPoints.first);
}

void zak::doIntersectionsCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty vector");
  }

  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::invalid_argument("invalid read");
  }
  using namespace std::placeholders;
  auto intersectPredicate = std::bind(hasIntersection, std::cref(polygon), _1);
  out << std::count_if(polygons.cbegin(), polygons.cend(), intersectPredicate);
}

bool areSame(const zak::Polygon& src, const zak::Polygon& p, size_t& counter)
{
  if (src == p)
  {
    ++counter;
    if (counter > 1)
    {
      counter = 0;
      return false;
    }
  }
  return true;
}

void zak::doRmechoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  if (!(in >> polygon))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  size_t counter = 0;
  std::vector<Polygon> res;
  using namespace std::placeholders;
  auto pred = std::bind(areSame, _1, std::cref(polygon), std::ref(counter));
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(res), pred);
  out << polygons.size() - res.size() << '\n';
  polygons = std::move(res);
}
