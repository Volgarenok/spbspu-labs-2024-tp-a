#ifndef PREDICATES_HPP
#define PREDICATES_HPP

#include "polygon.hpp"

namespace novikov
{
  bool even_vertexes(const Polygon& rhs);
  bool odd_vertexes(const Polygon& rhs);
  bool vertexes_count(const Polygon& rhs, std::size_t num);
}

#endif
