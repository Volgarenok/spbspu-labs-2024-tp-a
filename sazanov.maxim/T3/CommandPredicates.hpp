#ifndef COMMAND_PREDICATES_HPP
#define COMMAND_PREDICATES_HPP

#include <ostream>
#include "Polygon.hpp"

namespace sazanov
{
  double accumulateMeanArea(double sumArea, double area, size_t numOfPolygons);
  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertex(const Polygon& lhs, const Polygon& rhs);
  void outputArea(const Polygon& polygon, std::ostream& out);
  void outputVertex(const Polygon& polygon, std::ostream& out);
  bool isEvenNumOfVertexes(const Polygon& polygon);
  bool isOddNumOfVertexes(const Polygon& polygon);
  bool isEqualNumOfVertexes(const Polygon& polygon, size_t numOfVertexes);
  bool isSamePolygons(const Polygon& lhs, const Polygon& rhs);
  bool isEqualPointDiff(const Point& lhs, const Point& rhs, int xDiff, int yDiff);
  size_t getNumberInSequence(const Polygon& polygon, const Polygon& commandPolygon, const std::vector< size_t >& sequenceHistory);
}

#endif
