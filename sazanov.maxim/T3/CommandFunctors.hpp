#ifndef POLYGON_VECTOR_FUNCTORS_HPP
#define POLYGON_VECTOR_FUNCTORS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include "functional"
#include "Polygon.hpp"

namespace sazanov
{
  struct GetTotalPolygonsArea
  {
    using AccumulateFunctor = std::function< double(double, const Polygon&) >;
    std::unordered_map<std::string, AccumulateFunctor> subCommands;

    void operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out);
  };

  struct AccumulateArea
  {
    double operator()(double area, const Polygon& polygon);
    double operator()(double area, const Polygon& polygon, bool isOdd);
  };

  struct AccumulateAreaWithNumOfVertexes
  {
    std::size_t numOfVertexes;
    double operator()(double area, const Polygon& polygon);
  };

  struct AccumulateMeanArea
  {
    std::size_t numOfPolygons;
    double operator()(double area, const Polygon& polygon);
  };

  struct GetMaxValue
  {
    using GetMaxValueFunctor = std::function< double(double, const Polygon&) >;
    void operator()(const std::vector< Polygon >& vector, GetMaxValueFunctor*, std::ostream& out);
  };

  struct AccumulateMaxMinArea
  {
    double operator()(double area, const Polygon& polygon);
  };
}

#endif
