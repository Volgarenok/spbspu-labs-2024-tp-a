#ifndef BASEFORCOMMANDS_HPP
#define BASEFORCOMMANDS_HPP

#include <functional>
#include <vector>

#include "polygon.hpp"

namespace rebdev
{
  namespace rebdev_private
  {
    double getArea(double oldArea, const Polygon & p);
    using polyVec = std::vector< Polygon >;
    using lambda = const std::function< bool(const Polygon &) >;
    double areaIf(const polyVec & p, lambda pred);
  }
}

#endif
