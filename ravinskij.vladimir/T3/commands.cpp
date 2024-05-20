#include "commands.hpp"
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <scopeGuard.hpp>

namespace rav = ravinskij;

void rav::area(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::fixed << std::setprecision(1) << rav::AccumulateArea{polygons}(cmd);
}

void rav::max(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetValue{polygons}(cmd);
}

void rav::min(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetValue{polygons}(cmd);
}

void rav::count(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetCount{polygons}(cmd);
}

bool hasIntersection(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  auto lhsPair = std::minmax_element(lhs.points.cbegin(), lhs.points.cend());
  auto rhsPair = std::minmax_element(rhs.points.cbegin(), rhs.points.cend());
  return !(*lhsPair.second < *rhsPair.first || *rhsPair.second < *lhsPair.first);
}

void rav::intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
  auto intersectPredicate = std::bind(hasIntersection, _1, std::cref(polygon));
  out << std::count_if(polygons.cbegin(), polygons.cend(), intersectPredicate);
}

void rav::inframe(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty vector");
  }
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("invalid read");
  }

  out << (polygon <= getFrameRect(polygons) ? "<TRUE>" : "<FALSE>");
}
