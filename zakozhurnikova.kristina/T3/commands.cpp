#include <scopeGuard.hpp>
#include "commands.hpp"
#include "commandsImpl.hpp"

namespace zak = zakozhurnikova;

void zak::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
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
  Polygon p;
  in >> p;
  if (p.points.empty())
  {
    throw std::runtime_error("invalid_read");
  }
  out << p.points[0].x << ' ' << polygons.size() << '\n';
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
