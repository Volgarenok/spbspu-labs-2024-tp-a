#ifndef UTILS_HPP
#define UTILS_HPP
#include <utility>
#include "figures.hpp"

namespace kozlov
{
  struct MakePair
  {
    std::pair< Point, Point > operator()(const Point& p1, const Point& p2) const;
  };
  struct ShoelaceFormula
  {
    double operator()(double acc, const std::pair< Point, Point >& points) const;
  };
  struct SumArea
  {
    double operator()(double acc, const Polygon& poly) const;
  };
  struct HasNumOfVertexes
  {
    size_t vertexNum;
    explicit HasNumOfVertexes(size_t num);
    bool operator()(const Polygon& poly) const;
  };
  struct CompareArea
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const;
  };
  struct CompareVertexes
  {
    bool operator()(const Polygon& p1, const Polygon& p2) const;
  };

  double calcArea(const Polygon& poly);
  bool isEven(const Polygon& poly);
  bool isOdd(const Polygon& poly);
  double calcEvenArea(const std::vector< Polygon >& poly);
  double calcOddArea(const std::vector< Polygon >& poly);
  double calcMeanArea(const std::vector< Polygon >& poly);
  double calcNumVertexArea(const std::vector< Polygon >& poly, size_t vertexNum);
  double getMaxArea(const std::vector< Polygon >& poly);
  size_t getMaxVertexes(const std::vector< Polygon >& poly);
  double getMinArea(const std::vector< Polygon >& poly);
  size_t getMinVertexes(const std::vector< Polygon >& poly);
}
#endif
