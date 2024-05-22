#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <functional>
#include "polygon.hpp"

namespace baranov
{
  void area(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void max(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void min(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void count(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void rect(std::vector< Polygon > & shapes, std::istream &, std::ostream & out);

  class AreaCounter
  {
    public:
      explicit AreaCounter(const Point &);
      double operator()(double currArea, const Point & b, const Point & c);
    private:
      Point a_;
  };
  double getArea(const Polygon & polygon);
  double countMeanArea(double currArea, const Polygon & polygon, size_t count);
  double sumArea(double area, const Polygon & polygon, std::function< bool(const Polygon &) > p);
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  bool isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes);

  bool areaComparator(const Polygon & lhs, const Polygon & rhs);
  void maxArea(std::vector< Polygon > & shapes, std::ostream & out);
  void minArea(std::vector< Polygon > & shapes, std::ostream & out);

  bool vertexesComparator(const Polygon & lhs, const Polygon & rhs);
  void maxVertexes(std::vector< Polygon > & shapes, std::ostream & out);
  void minVertexes(std::vector< Polygon > & shapes, std::ostream & out);

  bool isEvenVertexesCount(const Polygon & polygon);
  bool isOddVertexesCount(const Polygon & polygon);

  bool isEqualLines(const Point & a1, const Point & a2, const Point & b1, const Point & b2);
  bool isSquareTriangle(const Point & a, const Point & b, const Point & c);
  bool isRectangle(const Polygon & polygon);
}

#endif

