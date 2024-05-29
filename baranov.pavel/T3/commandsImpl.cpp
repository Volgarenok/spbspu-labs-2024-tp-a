#include "commandsImpl.hpp"
#include <map>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "polygon.hpp"

baranov::AreaCounter::AreaCounter(const Point & a):
  a_(a)
{}

double baranov::AreaCounter::operator()(double currArea, const Point & b, const Point & c)
{
  currArea += 0.5 * std::abs((b.x - a_.x) * (c.y - a_.y) - (c.x - a_.x) * (b.y - a_.y));
  a_ = b;
  return currArea;
}

double baranov::getArea(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() < 3)
  {
    return 0.0;
  }
  using namespace std::placeholders;
  auto areaFunctor = std::bind(AreaCounter(points.at(1)), 0.0, _1, points.at(0));
  std::vector< double > areas;
  std::transform(points.cbegin(), points.cend(), std::back_inserter(areas), areaFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

double baranov::countMeanArea(double currArea, const Polygon & polygon, size_t count)
{
  return currArea + getArea(polygon) / count;
}

double baranov::sumArea(double currArea, const Polygon & polygon, std::function< bool(const Polygon &) > p)
{
  if (p(polygon))
  {
    currArea += getArea(polygon);
  }
  return currArea;
}

bool baranov::isEven(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool baranov::isOdd(const Polygon & polygon)
{
  return !isEven(polygon);
}

bool baranov::isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes)
{
  return numOfVertexes == polygon.points.size();
}

bool baranov::areaComparator(const Polygon & lhs, const Polygon & rhs)
{
  return getArea(lhs) < getArea(rhs);
}

void baranov::maxArea(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

void baranov::minArea(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), areaComparator);
  out << getArea(*result);
}

bool baranov::vertexesComparator(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void baranov::maxVertexes(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::max_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

void baranov::minVertexes(std::vector< Polygon > & shapes, std::ostream & out)
{
  auto result = std::min_element(shapes.cbegin(), shapes.cend(), vertexesComparator);
  out << result->points.size();
}

bool baranov::isEvenVertexesCount(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool baranov::isOddVertexesCount(const Polygon & polygon)
{
  return !isEvenVertexesCount(polygon);
}

bool baranov::isSquareTriangle(const Point & a, const Point & b, const Point & c)
{
  double ab = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  double ac = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
  double bc = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
  return ac == ab + bc || ab == ac + bc || bc == ac + ab;
}

bool baranov::isEqualLines(const Point & a1, const Point & a2, const Point & b1, const Point & b2)
{
  return std::abs(a1.x - a2.x) == std::abs(b1.x - b2.x) && std::abs(a1.y - a2.y) == std::abs(b1.y - b2.y);
}

bool baranov::isRectangle(const Polygon & polygon)
{
  const std::vector< Point > & points = polygon.points;
  if (points.size() != 4)
  {
    return false;
  }
  const Point & a = points.at(0);
  const Point & b = points.at(1);
  const Point & c = points.at(2);
  const Point & d = points.at(3);
  return isSquareTriangle(a, b, c) && (isEqualLines(a, b, c, d) || isEqualLines(a, c, b, d) || isEqualLines(a, d, b, c));
}

bool baranov::xComparator(const Point & lhs, const Point & rhs)
{
  return lhs.x < rhs.x;
}

bool baranov::yComparator(const Point & lhs, const Point & rhs)
{
  return lhs.y < rhs.y;
}

baranov::rect_t baranov::extendFrameRect(rect_t frameRect, const Polygon & polygon)
{
  int ax = std::min_element(polygon.points.cbegin(), polygon.points.cend(), xComparator)->x;
  int ay = std::min_element(polygon.points.cbegin(), polygon.points.cend(), yComparator)->y;

  int bx = std::max_element(polygon.points.cbegin(), polygon.points.cend(), xComparator)->x;
  int by = std::max_element(polygon.points.cbegin(), polygon.points.cend(), yComparator)->y;

  frameRect.first.x = std::min(ax, frameRect.first.x);
  frameRect.first.y = std::min(ay, frameRect.first.y);

  frameRect.second.x = std::max(bx, frameRect.second.x);
  frameRect.second.y = std::max(by, frameRect.second.y);

  return frameRect;
}

bool baranov::isPointInRect(const Point & point, const rect_t & rect)
{
  return rect.first.x <= point.x && rect.second.x >= point.x
    && rect.first.y <= point.y && rect.second.y >= point.y;
}

