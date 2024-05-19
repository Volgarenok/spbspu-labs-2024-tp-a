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

bool checkIntersect(const rav::Point& lhsMin, const rav::Point& rhsMin, const rav::Point& lhsMax, const rav::Point& rhsMax)
{
  return (lhsMin <= rhsMax) && !(lhsMax < rhsMin);
}
bool hasIntersection(const rav::Polygon& lhs, const rav::Polygon& rhs)
{
  //std::pair< rav::Point, rav::Point > lhsPair, rhsPair;
  //lhsPair.first = *std::min_element(lhs.points.cbegin(), lhs.points.cend());
  //lhsPair.second = *std::max_element(lhs.points.cbegin(), lhs.points.cend());
  //rhsPair.first = *std::min_element(rhs.points.cbegin(), rhs.points.cend());
  // rhsPair.second = *std::max_element(rhs.points.cbegin(), rhs.points.cend());
  auto lhsPair = std::minmax_element(lhs.points.cbegin(), lhs.points.cend());
  auto rhsPair = std::minmax_element(rhs.points.cbegin(), rhs.points.cend());
  return checkIntersect(*(lhsPair.first), *(rhsPair.first), *(lhsPair.second), *(rhsPair.second)) ||
    checkIntersect(*(rhsPair.first), *(lhsPair.first), *(rhsPair.second), *(lhsPair.second));
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

  out << (polygon <= getFrameRect(polygons) ? "<TRUE>" : "<FALSE>");
}
