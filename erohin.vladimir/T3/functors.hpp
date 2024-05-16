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

  struct isRightAngle
  {
    Point prev;
    Point center;
    bool operator()(const Point & point);
  };

  struct getFrameRectLeftLower
  {
    Point operator()(const Polygon & polygon);
  };

  struct getFrameRectRightUpper
  {
    Point operator()(const Polygon & polygon);
  };
}

#endif
