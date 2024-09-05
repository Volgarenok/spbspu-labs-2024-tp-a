#ifndef FIGURES_OPERATIONS_HPP
#define FIGURES_OPERATIONS_HPP
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
  size_t countEvenPoly(const std::vector< Polygon >& poly);
  size_t countOddPoly(const std::vector< Polygon >& poly);
  size_t countNumPoly(const std::vector< Polygon >& poly, size_t vertexNum);
  void echoPolygons(std::vector< Polygon >& poly, const Polygon& target);
  std::pair< Point, Point > calcFrame(std::pair< Point, Point > frames, const Polygon& poly);
  bool compareX(const Point& p1, const Point& p2);
  bool compareY(const Point& p1, const Point& p2);
  bool checkPointInFrame(std::pair< Point, Point > frames, const Point& point);
}
#endif
