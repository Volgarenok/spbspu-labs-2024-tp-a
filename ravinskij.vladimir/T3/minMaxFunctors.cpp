#include "minMaxFunctors.hpp"
#include <algorithm>
#include <iomanip>
#include <scopeGuard.hpp>

namespace rav = ravinskij;
rav::GetValue::GetValue(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  maxSubCommands["AREA"] = std::bind(rav::GetMinMaxValue{}, _1, false, rav::AreaComparator{});
  maxSubCommands["VERTEXES"] = std::bind(rav::GetMinMaxValue{}, _1, false, rav::VertexComparator{});
  minSubCommands["AREA"] = std::bind(rav::GetMinMaxValue{}, _1, true, rav::AreaComparator{});
  minSubCommands["VERTEXES"] = std::bind(rav::GetMinMaxValue{}, _1, true, rav::VertexComparator{});

  subCommands["MAX"] = maxSubCommands;
  subCommands["MIN"] = minSubCommands;
}

using options = std::pair< double, size_t >;
options rav::GetValue::operator()(const std::string& command, const std::string& subCommand)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty vector");
  }
  return subCommands.at(command).at(subCommand)(polygons);
}

options rav::GetMinMaxValue::operator()(const std::vector< Polygon >& polygons, bool isMin, AreaComparator comp)
{
  options result;
  result.second = 0;
  if (isMin)
  {
    result.first = getArea(*std::min_element(polygons.cbegin(), polygons.cend(), comp));
  }
  else
  {
  result.first = getArea(*std::max_element(polygons.cbegin(), polygons.cend(), comp));
  }
  return result;
}

options rav::GetMinMaxValue::operator()(const std::vector< Polygon >& polygons, bool isMin, VertexComparator comp)
{
  options result;
  result.first = 0;
  if (isMin)
  {
    result.second = polygonSize(*std::min_element(polygons.cbegin(), polygons.cend(), comp));
  }
  else
  {
    result.second = polygonSize(*std::max_element(polygons.cbegin(), polygons.cend(), comp));
  }
  return result;
}

std::ostream& rav::operator<<(std::ostream& out, const options& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  rav::ScopeGuard scopeGuard(out);

  if (value.first)
  {
    out << std::fixed << value.first;
  }
  else
  {
    out << value.second;
  }
  return out;
}

bool rav::AreaComparator::operator()(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool rav::VertexComparator::operator()(const Polygon& lhs, const Polygon& rhs)
{
  return polygonSize(lhs) < polygonSize(rhs);
}
