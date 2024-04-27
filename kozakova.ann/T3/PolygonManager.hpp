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
    double operator()(double area, const Polygon& polygon, bool isOdd);
    double operator()(double area, const Polygon& polygon, size_t n);
  };

  struct PolygonMaxArea
  {
    double operator()(double max, const Polygon& polygon);
  };

  struct PolygonMaxVertexes
  {
    size_t operator()(size_t max, const Polygon& polygon);
  };

  struct PolygonMinArea
  {
    double operator()(double min, const Polygon& polygon);
  };

  struct PolygonMinVertexes
  {
    size_t operator()(size_t min, const Polygon& polygon);
  };

  struct PolygonCount
  {
    int operator()(int count, const Polygon& polygon, bool isOdd);
    int operator()(int count, const Polygon& polygon, size_t n);
  };

  struct PolygonRect
  {
    int operator()(int count, Polygon& polygon);
  };

  struct PolygonMaxSeq
  {
    int cur;
    int operator()(int max, const Polygon& polygon, const Polygon& data);
  };
}

#endif
