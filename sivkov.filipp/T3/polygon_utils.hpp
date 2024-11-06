#ifndef POLYGON_UTILS_HPP
#define POLYGON_UTILS_HPP

#include "polygon.hpp"

namespace sivkov
{
  bool isPointCountEqual(const Polygon& shape, size_t num);
  bool isPerms(const Polygon& first, const Polygon& second);
}

#endif
