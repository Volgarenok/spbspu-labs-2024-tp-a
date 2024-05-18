#ifndef POLYGONMANAGER_HPP
#define POLYGONMANAGER_HPP

#include <vector>
#include <map>
#include <functional>
#include <iterator>
#include "Polygon.hpp"

namespace kozakova
{
  struct PolygonArea
  {
    Point first;
    double operator()(const Point& second);
  };

  struct PolygonMaxSeq
  {
    int cur;
    int maxseq;
    bool operator()(const Polygon& polygon, const Polygon& data);
  };
}

#endif
