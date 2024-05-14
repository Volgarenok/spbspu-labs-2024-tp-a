#ifndef POLYGONMANAGER_HPP
#define POLYGONMANAGER_HPP

#include <vector>
#include <map>
#include <functional>
#include <iterator>
#include "Polygon.hpp"

namespace kozakova
{
  struct PolygonsArea
  {
    double operator()(double area, const Polygon& polygon);
    double operator()(double area, const Polygon& polygon, size_t n);
  };

  struct PolygonsAreaOdd
  {
    double operator()(double area, const Polygon& polygon);
  };

  struct PolygonsAreaEven
  {
    double operator()(double area, const Polygon& polygon);
  };

  struct PolygonMaxSeq
  {
    int cur;
    int maxseq;
    bool operator()(const Polygon& polygon, const Polygon& data);
  };
}

#endif
