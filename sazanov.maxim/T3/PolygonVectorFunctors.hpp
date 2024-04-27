#ifndef POLYGON_VECTOR_FUNCTORS_HPP
#define POLYGON_VECTOR_FUNCTORS_HPP

#include <vector>
#include <string>
#include "Polygon.hpp"

namespace sazanov
{
  struct GetTotalPolygonsArea
  {
    double operator()(const std::vector< Polygon >& vector, const std::string& version = "BASE");
  };

  struct AccumulatePolygonArea
  {
    double operator()(double area, const Polygon& polygon);
    double operator()(double area, const Polygon& polygon, bool isOdd);
  };

  struct GetMeanPolygonsArea
  {
    double operator()(const std::vector< Polygon >& vector);
  };
}

#endif
