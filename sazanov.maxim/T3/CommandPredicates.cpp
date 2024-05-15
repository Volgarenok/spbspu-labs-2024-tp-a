#include "CommandPredicates.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <StreamGuard.hpp>
#include "Polygon.hpp"

double sazanov::accumulateAreaWithParity(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double sazanov::accumulateAreaWithNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes)
{
  if (polygon.points.size()  == numOfVertexes)
  {
    area += polygon.getArea();
  }
  return area;
}

double sazanov::accumulateMeanArea(double area, const Polygon& polygon, size_t numOfPolygons)
{
  return area + (polygon.getArea() / numOfPolygons);
}

bool sazanov::compareArea(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.getArea() < rhs.getArea();
}

bool sazanov::compareVertex(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void sazanov::outputArea(const Polygon& polygon, std::ostream& out)
{
  out << PolygonAreaO{polygon};
}

void sazanov::outputVertex(const Polygon& polygon, std::ostream& out)
{
  out << polygon.points.size();
}

bool sazanov::countWithParity(const Polygon& polygon, bool isOdd)
{
  return polygon.points.size() % 2 == isOdd;
}

bool sazanov::countWithNumOfVertexes(const Polygon& polygon, size_t numOfVertexes)
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

size_t sazanov::accumulatePolygonSequence::operator()(size_t maxSeq, const Polygon& polygon,
  const Polygon& commandPolygon)
{
  if (polygon == commandPolygon)
  {
    ++curSeq;
  }
  else
  {
    curSeq = 0;
  }
  maxSeq = std::max(curSeq, maxSeq);
  return maxSeq;
}
