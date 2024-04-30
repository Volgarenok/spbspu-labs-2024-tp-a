#ifndef PART_AREA_FUNCTOR_HPP
#define PART_AREA_FUNCTOR_HPP

#include "polygon.hpp"

namespace ravinskij
{
  struct PartAreaFunctor
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };
}
#endif
