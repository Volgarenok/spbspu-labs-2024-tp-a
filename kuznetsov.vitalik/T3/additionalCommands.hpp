#ifndef ADDITIONAL_COMMANDS_HPP
#define ADDITIONAL_COMMANDS_HPP

#include "datastruct.hpp"

namespace kuznetsov
{
  double getMaxOrMinArea(bool cur, double& maxOrMinArea, const Polygon& polygon);
  size_t getMaxOrMinVertexes(bool cur, size_t& maxOrMinVertexes, const Polygon& polygon);
  int getCountOfOddOrEvenVertexes(bool cur, int sum, const Polygon& polygon);
  int getCountWithNumVertexes(size_t num, int sum, const Polygon& polygon);
  Point& comparisonPoints(bool cur, Point& point, const Point& newPoint);
  Point& getMinOrMaxPoint(bool cur, Point& framePoint, const Polygon& polygon);
  bool isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon);
  bool areSame(const Polygon& firstShape, const Polygon& secondShape);
  Point getFramePoint(bool cur, Point& framePoint, std::vector< Polygon >& polygon);
  bool comparisonWithTwoPoints(bool& cur, Point& min, Point& max, const Point& newPoint);
  bool isInFrame(Point& min, Point& max, Polygon& polygon);
}

#endif
