kk#ifndef ADDITIONAL_COMMANDS_HPP
#define ADDITIONAL_COMMANDS_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  double countAreaShape(const Polygon& shape);
  bool isEvenVertexes(const Polygon& shape);
  bool isOddVertexes(const Polygon& shape);
  bool isNumEqualSize(const Polygon& shape, size_t num);
  double getOddEvenMean(std::vector< Polygon >& polygon, OddOrEvenOrMean current);
  size_t getVertexes(Polygon& shape);
  void getMinOrMaxArea(std::ostream& out, std::vector< Polygon >& polygon, MinOrMax current);
  void getMinOrMaxVertexes(std::ostream& out, std::vector< Polygon >& polygon, MinOrMax current);
  size_t countShapesWithEvenOrOddVertexes(std::vector< Polygon >& polygon, OddOrEvenOrMean current);
  bool isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon);
  bool areSame(const Polygon& firstShape, const Polygon& secondShape);
  bool comparisonPointsByX(const Point& first, const Point& second);
  bool comparisonPointsByY(const Point& first, const Point& second);
  int getPointsFrameX(const Polygon& shape, MinOrMax current);
  int getPointsFrameY(const Polygon& shape, MinOrMax current);
  std::pair< Point, Point > getFrameRectangle(std::vector< Polygon >& shapes);
  bool isPointBetwen(const Point& min, const Point& point, const Point& max);
  bool ifInFrameRectangle(const Polygon& shape, std::pair< Point, Point > frameRectangle);
}

#endif
