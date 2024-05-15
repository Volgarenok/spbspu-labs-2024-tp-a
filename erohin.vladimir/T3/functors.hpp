#ifndef FUNCTORS_HPP
#define FUNCTORS_HPP

#include "polygon.hpp"

namespace erohin
{
  struct evaluateArea
  {
    Point start;
    Point prev;
    double operator()(const Point & point);
  };
}

#endif
