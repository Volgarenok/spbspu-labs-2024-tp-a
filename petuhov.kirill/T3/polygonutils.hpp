#ifndef POLYGONUTILS_HPP
#define POLYGONUTILS_HPP

#include "polygon.hpp"
#include <vector>
#include <string>

namespace petuhov
{
  std::vector< Polygon > read_polygons(const std::string &filename);
}

#endif
