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

    void fillAreaVec(const polyVec & p, std::vector< double > & vec);
    void fillVertVec(const polyVec & p, std::vector< size_t > & vec);

    double distanceBetweenPoints(const Point & f, const Point & s);
  }
}

#endif
