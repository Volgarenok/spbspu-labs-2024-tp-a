#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "polygon.hpp"

namespace rebdev
{
  struct Triangle
  {
    Point pointArr[3];
    double getArea() const;
  };
  class TriangleGenerator
  {
    public:
      TriangleGenerator(const Polygon & p);
      Triangle operator()();
    private:
      const Polygon & safedPoly;
      size_t pointNow;
  };

  double plusArea(double areaNow, const Triangle & tria);
}

#endif
