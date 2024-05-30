#include "minMaxFunctors.hpp"
#include <algorithm>
#include <iomanip>
#include <scopeGuard.hpp>

namespace rav = ravinskij;
rav::GetValue::GetValue(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  maxSubCommands["AREA"] = std::bind(rav::GetMaxValue{}, _1, rav::AreaComparator{});
  maxSubCommands["VERTEXES"] = std::bind(rav::GetMaxValue{}, _1, rav::VertexComparator{});
  minSubCommands["AREA"] = std::bind(rav::GetMinValue{}, _1, rav::AreaComparator{});
  minSubCommands["VERTEXES"] = std::bind(rav::GetMinValue{}, _1, rav::VertexComparator{});
}

using options = std::pair< double, size_t >;
options rav::GetValue::operator()(const std::string& command)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty vector");
  }
  options result;
  try
  {
    result = maxSubCommands.at(command)(polygons);
  }
  catch (const std::out_of_range&)
  {
    result = minSubCommands.at(command)(polygons);
  }
  return result;
}

options rav::GetMinValue::operator()(const std::vector< Polygon >& polygons, AreaComparator comp)
{
  options result;
  result.second = 0;
  result.first = getArea(*std::min_element(polygons.cbegin(), polygons.cend(), comp));
  return result;
}

options rav::GetMinValue::operator()(const std::vector< Polygon >& polygons, VertexComparator comp)
{
  options result;
  result.first = 0;
  result.second = polygonSize(*std::min_element(polygons.cbegin(), polygons.cend(), comp));
  return result;
}

options rav::GetMaxValue::operator()(const std::vector< Polygon >& polygons, AreaComparator comp)
{
  options result;
  result.second = 0;
  result.first = getArea(*std::max_element(polygons.cbegin(), polygons.cend(), comp));
  return result;
}

options rav::GetMaxValue::operator()(const std::vector< Polygon >& polygons, VertexComparator comp)
{
  options result;
  result.first = 0;
  result.second = polygonSize(*std::max_element(polygons.cbegin(), polygons.cend(), comp));
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
