#include "predicates.hpp"

bool novikov::even_vertexes(const Polygon& rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool novikov::odd_vertexes(const Polygon& rhs)
{
  return !even_vertexes(rhs);
}

bool novikov::vertexes_count(const Polygon& rhs, std::size_t num)
{
  return rhs.points.size() == num;
}

bool novikov::compare_areas(const Polygon& lhs, const Polygon& rhs)
{
  return get_area(lhs) < get_area(rhs);
}

bool novikov::compare_vertexes(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}
