#include "minMaxFunctors.hpp"
#include <algorithm>

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

using options = std::pair< double, std::size_t >;

options rav::GetMinMaxValue::operator()(const std::vector< Polygon >& polygons, bool isMin, AreaComparator comp)
{
  options result;
  result.second = 0;
  if (isMin)
  {
    result.first = std::min_element(polygons.cbegin(), polygons.cend(), comp)->getArea();
  }
  else
  {
  result.first = std::max_element(polygons.cbegin(), polygons.cend(), comp)->getArea();
  }
  return result;
}

options rav::GetMinMaxValue::operator()(const std::vector< Polygon >& polygons, bool isMin, VertexComparator comp)
{
  options result;
  result.first = 0;
  if (isMin)
  {
    result.second = std::min_element(polygons.cbegin(), polygons.cend(), comp)->size();
  }
  else
  {
  result.second = std::max_element(polygons.cbegin(), polygons.cend(), comp)->size();
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

  out << (value.first != 0 ? value.first : value.second);
  return out;
}

bool rav::AreaComparator::operator()(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.getArea() < rhs.getArea();
}

bool rav::VertexComparator::operator()(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.size() < rhs.size();
}
