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
