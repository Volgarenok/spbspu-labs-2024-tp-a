#include "CommandPredicates.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "StreamGuard.hpp"
#include "Polygon.hpp"

double sazanov::accumulateAreaWithParity(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double sazanov::accumulateAreaWithNumOfVertexes(double area, const Polygon& polygon, std::size_t numOfVertexes)
{
  if (polygon.points.size()  == numOfVertexes)
  {
    area += polygon.getArea();
  }
  return area;
}

double sazanov::accumulateMeanArea(double area, const Polygon& polygon, std::size_t numOfPolygons)
{
  return area + (polygon.getArea() / numOfPolygons);
}

bool sazanov::compareArea(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  return lhs.getArea() < rhs.getArea();
}

bool sazanov::compareVertex(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void sazanov::outputArea(const sazanov::Polygon& polygon, std::ostream& out)
{
  StreamGuard guard(std::cout);
  std::cout << std::setprecision(1) << std::fixed;
  out << polygon.getArea();
}

void sazanov::outputVertex(const sazanov::Polygon& polygon, std::ostream& out)
{
  out << polygon.points.size();
}

bool sazanov::countWithParity(const sazanov::Polygon& polygon, bool isOdd)
{
  return polygon.points.size() % 2 == isOdd;
}

bool sazanov::countWithNumOfVertexes(const sazanov::Polygon& polygon, std::size_t numOfVertexes)
{
  return polygon.points.size() == numOfVertexes;
}

bool sazanov::IsSamePolygons(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  if (rhs.points.size() != lhs.points.size())
  {
    return false;
  }
  Polygon sortedLhs = lhs;
  std::sort(sortedLhs.points.begin(), sortedLhs.points.end(), PointComparator);

  Polygon sortedRhs = rhs;
  std::sort(sortedRhs.points.begin(), sortedRhs.points.end(), PointComparator);

  int xDiff = sortedLhs.points.front().x - sortedRhs.points.front().x;
  int yDiff = sortedLhs.points.front().y - sortedRhs.points.front().y;

  using namespace std::placeholders;
  return std::equal(sortedLhs.points.cbegin(), sortedLhs.points.cend(), sortedRhs.points.cbegin(),
    std::bind(IsEqualPointDiff, _1, _2, xDiff, yDiff));
}

bool sazanov::IsEqualPointDiff(const sazanov::Point& lhs, const sazanov::Point& rhs, int xDiff, int yDiff)
{
  return lhs.x - rhs.x == xDiff && lhs.y - rhs.y == yDiff;
}

bool sazanov::PointComparator(const sazanov::Point& lhs, const sazanov::Point& rhs)
{
  if (lhs.x != rhs.x)
  {
    return lhs.x < rhs.x;
  }
  return lhs.y < rhs.y;
}

std::size_t sazanov::accumulatePolygonSequence::operator()(std::size_t maxSeq, const sazanov::Polygon& polygon,
  const sazanov::Polygon& commandPolygon)
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
