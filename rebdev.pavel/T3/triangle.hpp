#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "polygon.hpp"

namespace rebdev
{
  struct Triangle
  {
    Point pointArr[3];
    double getArea() const noexcept;
  };
  class TriangleGenerator
  {
    public:
      explicit TriangleGenerator(const Polygon & p) noexcept;
      Triangle operator()() noexcept;
    private:
      const Polygon & safedPoly;
      size_t pointNow;
  };

  double plusArea(double areaNow, const Triangle & tria) noexcept;
}

#endif
