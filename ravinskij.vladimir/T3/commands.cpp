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
  out << std::setprecision(1) << rav::GetValue{polygons}("MAX", cmd);
}

void rav::min(const std::vector < Polygon >& polygons, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;
  out << std::setprecision(1) << rav::GetValue{polygons}("MIN", cmd);
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
  rav::Point minLhs = *std::min_element(lhs.points.cbegin(), lhs.points.cend());
  rav::Point maxLhs = *std::max_element(lhs.points.cbegin(), lhs.points.cend());
  rav::Point minRhs = *std::min_element(rhs.points.cbegin(), rhs.points.cend());
  rav::Point maxRhs = *std::max_element(rhs.points.cbegin(), rhs.points.cend());

  bool firstCheck = (minLhs <= maxRhs) && (maxLhs >= minRhs);
  bool secondCheck = (minRhs <= maxLhs) && (maxRhs >= minLhs);
  return firstCheck || secondCheck;
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
  auto intersectPredicate = std::bind(hasIntersection, std::cref(polygon), _1);
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

  out << (polygon < getFrameRect(polygons) ? "<TRUE>" : "<FALSE>");
}
