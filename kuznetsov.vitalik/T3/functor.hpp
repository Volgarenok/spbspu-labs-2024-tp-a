#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  struct CountAreaTriangle
  {
    Point first;
    Point second;

    double operator()(const Point& third);
  };
}

#endif
