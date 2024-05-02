#include <iomanip>
#include <scopeGuard.hpp>
#include "commands.hpp"

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
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
}

void zak::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
}
void zak::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << countVertexes(cmd, polygons);
}
void zak::intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
}

void zak::rmecho(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
}
