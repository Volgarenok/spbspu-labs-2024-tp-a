#include "CommandPredicates.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "DoubleO.hpp"
#include "Polygon.hpp"

double sazanov::accumulateMeanArea(double sumArea, double area, size_t numOfPolygons)
{
  return sumArea + (area / numOfPolygons);
}

bool sazanov::compareArea(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool sazanov::compareVertex(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void sazanov::outputArea(const Polygon& polygon, std::ostream& out)
{
  out << DoubleO{getArea(polygon)};
}

void sazanov::outputVertex(const Polygon& polygon, std::ostream& out)
{
  out << polygon.points.size();
}

bool sazanov::isEvenNumOfVertexes(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool sazanov::isOddNumOfVertexes(const Polygon& polygon)
{
  return !isEvenNumOfVertexes(polygon);
}

bool sazanov::isEqualNumOfVertexes(const Polygon& polygon, size_t numOfVertexes)
{
  return polygon.points.size() == numOfVertexes;
}

bool sazanov::isSamePolygons(const Polygon& lhs, const Polygon& rhs)
{
  if (rhs.points.size() != lhs.points.size())
  {
    return false;
  }
  std::vector< Point > sortedLhs = lhs.points;
  std::sort(sortedLhs.begin(), sortedLhs.end());

  std::vector< Point > sortedRhs = rhs.points;
  std::sort(sortedRhs.begin(), sortedRhs.end());

  int xDiff = sortedLhs.front().x - sortedRhs.front().x;
  int yDiff = sortedLhs.front().y - sortedRhs.front().y;

  using namespace std::placeholders;
  return std::equal(sortedLhs.cbegin(), sortedLhs.cend(), sortedRhs.cbegin(), std::bind(isEqualPointDiff, _1, _2, xDiff, yDiff));
}

bool sazanov::isEqualPointDiff(const Point& lhs, const Point& rhs, int xDiff, int yDiff)
{
  return lhs.x - rhs.x == xDiff && lhs.y - rhs.y == yDiff;
}

size_t sazanov::getNumberInSequence(const Polygon& polygon, const Polygon& commandPolygon, const std::vector< size_t >& sequenceHistory)
{
  if (polygon != commandPolygon)
  {
    return 0;
  }
  if (sequenceHistory.empty())
  {
    return 1;
  }
  return sequenceHistory.back() + 1;
}
