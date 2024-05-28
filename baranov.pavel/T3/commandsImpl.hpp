#ifndef COMMANDS_IMPL_HPP
#define COMMANDS_IMPL_HPP
#include <vector>
#include <functional>
#include "polygon.hpp"

namespace baranov
{
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

  bool xComparator(const Point & lhs, const Point & rhs);
  bool yComparator(const Point & lhs, const Point & rhs);
  using rect_t = std::pair< Point, Point >;
  rect_t extendFrameRect(rect_t frameRect, const Polygon & polygon);
  bool isPointInRect(const Point & point, const rect_t & rect);
}

#endif

