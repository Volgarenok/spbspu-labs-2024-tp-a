#ifndef POLYGON_VECTOR_FUNCTORS_HPP
#define POLYGON_VECTOR_FUNCTORS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "Polygon.hpp"

namespace sazanov
{
  struct GetTotalPolygonsArea
  {
    using AccumulateFunctor = std::function< double(double, const Polygon&) >;
    std::unordered_map< std::string, AccumulateFunctor > subCommands;
    std::unordered_map< std::string, bool > emptyVectorSupport;
    using NumberCommandFunctor = std::function< double(double, const Polygon&, std::size_t) >;
    NumberCommandFunctor numberCommand;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct AccumulateArea
  {
    double operator()(double area, const Polygon& polygon);
    double operator()(double area, const Polygon& polygon, bool isOdd);
  };

  struct AccumulateAreaWithNumOfVertexes
  {
    double operator()(double area, const Polygon& polygon, std::size_t numOfVertexes);
  };

  struct AccumulateMeanArea
  {
    std::size_t numOfPolygons;
    double operator()(double area, const Polygon& polygon);
  };

  struct GetMaxValue
  {
    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValue = std::function< void(const Polygon&, std::ostream& out) >;
    std::unordered_map< std::string, std::pair< Comparator, OutputValue > > subCommands;

    void operator()(const std::vector<Polygon>& vector, std::istream& in, std::ostream& out);
  };

  struct AreaComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct VertexComparator
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct OutputArea
  {
    void operator()(const Polygon& polygon, std::ostream& out);
  };

  struct OutputVertex
  {
    void operator()(const Polygon& polygon, std::ostream& out);
  };

  struct GetMinValue
  {
    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValue = std::function< void(const Polygon&, std::ostream& out) >;
    std::unordered_map< std::string, std::pair< Comparator, OutputValue > > subCommands;

    void operator()(const std::vector<Polygon>& vector, std::istream& in, std::ostream& out);
  };

  struct CountPolygons
  {
    using CountFunctor = std::function< bool(const Polygon&) >;
    std::unordered_map<std::string, CountFunctor> subCommands;
    using NumberCommandFunctor = std::function< bool(const Polygon&, std::size_t) >;
    NumberCommandFunctor numberCommand;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct CountWithParity
  {
    bool operator()(const Polygon& polygon, bool isOdd);
  };

  struct CountWithNumOfVertexes
  {
    bool operator()(const Polygon& polygon, std::size_t numOfVertexes);
  };

  struct GetMaxSequence
  {
    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct AccumulatePolygonSequence
  {
    std::size_t curSeq = 0;
    std::size_t operator()(std::size_t maxSeq, const Polygon& polygon, const Polygon& commandPolygon);
  };

  struct CountSamePolygons
  {
    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct IsSamePolygons
  {
    bool operator()(const Polygon& lhs, const Polygon& rhs);
  };

  struct IsEqualPointDiff
  {
    bool operator()(const Point& lhs, const Point& rhs, int xDiff, int yDiff);
  };

  struct PointComparator
  {
    bool operator()(const Point& lhs, const Point& rhs);
  };
}

#endif
