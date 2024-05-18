#include "additionalCommands.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include "functor.hpp"

double kuznetsov::countAreaShape(const Polygon& shape)
{
  CountAreaTriangle operation{ shape.points[0], shape.points[1] };
  std::vector< double > areas;
  std::transform(shape.points.begin() + 2, shape.points.end(), std::back_inserter(areas), operation);
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return area;
}

bool kuznetsov::isEvenVertexes(const Polygon& shape)
{
  return shape.points.size() % 2 == 0;
}

bool kuznetsov::isOddVertexes(const Polygon& shape)
{
  return shape.points.size() % 2 == 1;
}

bool kuznetsov::isNumEqualSize(const Polygon& shape, size_t num)
{
  return num == shape.points.size();
}

double kuznetsov::getOddEvenMean(std::vector< Polygon >& polygon, OddOrEvenOrMean current)
{
  std::vector< Polygon > sortedPolygon;
  if (current == Odd)
  {
    std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isOddVertexes);
  }
  else if (current == Even)
  {
    std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), isEvenVertexes);
  }
  else
  {
    sortedPolygon = { polygon };
  }
  std::vector< double > areasShapes;
  std::transform(sortedPolygon.begin(), sortedPolygon.end(), std::back_inserter(areasShapes), countAreaShape);
  double area = std::accumulate(areasShapes.begin(), areasShapes.end(), 0.0);
  if (current == Mean)
  {
    return area / polygon.size();
  }
  return area;
}

size_t kuznetsov::getVertexes(Polygon& shape)
{
  return shape.points.size();
}

void kuznetsov::getMinOrMaxArea(std::ostream& out, std::vector< Polygon >& polygon, MinOrMax current)
{
  std::vector< double > areasShapes;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areasShapes), countAreaShape);
  double minOrMax = 0.0;
  if (current == Min)
  {
    minOrMax = *std::min_element(areasShapes.begin(), areasShapes.end());
  }
  else if (current == Max)
  {
    minOrMax = *std::max_element(areasShapes.begin(), areasShapes.end());
  }
  out << std::fixed << std::setprecision(1) << minOrMax << '\n';
}

void kuznetsov::getMinOrMaxVertexes(std::ostream& out, std::vector< Polygon >& polygon, MinOrMax current)
{
  std::vector< size_t > vertexesShapes;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexesShapes), getVertexes);
  size_t minOrMax = 0;
  if (current == Min)
  {
    minOrMax = *std::min_element(vertexesShapes.begin(), vertexesShapes.end());
  }
  else if (current == Max)
  {
    minOrMax = *std::max_element(vertexesShapes.begin(), vertexesShapes.end());
  }
  out << minOrMax << '\n';
}

size_t kuznetsov::countShapesWithEvenOrOddVertexes(std::vector< Polygon >& polygon, OddOrEvenOrMean current)
{
  size_t count = 0;
  if (current == Odd)
  {
    count = std::count_if(polygon.begin(), polygon.end(), isOddVertexes);
  }
  else if (current == Even)
  {
    count = std::count_if(polygon.begin(), polygon.end(), isEvenVertexes);
  }
  return count;
}

bool kuznetsov::isSamePoint(const Point& delta, const Point& newPoint, int& current, const Polygon& polygon)
{
  Point newPointPlusDelta = { newPoint.x + delta.x, newPoint.y + delta.y };
  if (newPointPlusDelta.x == polygon.points[current].x &&
      newPointPlusDelta.y == polygon.points[current].y)
  {
    ++current;
    return true;
  }
  return false;
}

bool kuznetsov::areSame(const Polygon& firstShape, const Polygon& secondShape)
{
  if (firstShape.points.size() != secondShape.points.size())
  {
    return false;
  }

  int deltaX = secondShape.points[0].x - firstShape.points[0].x;
  int deltaY = secondShape.points[0].y - firstShape.points[0].y;
  Point delta{ deltaX, deltaY };
  using namespace std::placeholders;
  auto operation = std::bind(isSamePoint, delta, _1, 0, secondShape);
  return std::count_if(firstShape.points.cbegin(), firstShape.points.cend(), operation) == static_cast<int>(firstShape.points.size());
}

bool kuznetsov::comparisonPointsByX(const Point& first, const Point& second)
{
  return second.x > first.x;
}

bool kuznetsov::comparisonPointsByY(const Point& first, const Point& second)
{
  return second.y > first.y;
}

int kuznetsov::getPointsFrameX(const Polygon& shape, MinOrMax current)
{
  int result = 0;

  auto maxOrMinX = std::minmax_element(shape.points.begin(), shape.points.end(), comparisonPointsByX);
  if (current == Max)
  {
    result = maxOrMinX.second->x;
  }
  else if (current == Min)
  {
    result = maxOrMinX.first->x;
  }
  return result;
}

int kuznetsov::getPointsFrameY(const Polygon& shape, MinOrMax current)
{
  int result = 0;
  auto maxOrMinY = std::minmax_element(shape.points.begin(), shape.points.end(), comparisonPointsByY);
  if (current == Max)
  {
    result = maxOrMinY.second->y;
  }
  else if (current == Min)
  {
    result = maxOrMinY.first->y;
  }
  return result;
}

std::pair< kuznetsov::Point, kuznetsov::Point > kuznetsov::getFrameRectangle(std::vector< Polygon >& shapes)
{
  std::vector< int > vectorMaxX;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(vectorMaxX), std::bind(getPointsFrameX, std::placeholders::_1, Max));
  std::vector< int > vectorMinX;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(vectorMinX), std::bind(getPointsFrameX, std::placeholders::_1, Min));
  std::vector< int > vectorMaxY;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(vectorMaxY), std::bind(getPointsFrameX, std::placeholders::_1, Max));
  std::vector< int > vectorMinY;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(vectorMinY), std::bind(getPointsFrameX, std::placeholders::_1, Min));

  auto maxX = std::max_element(vectorMaxX.begin(), vectorMaxX.end());
  auto minX = std::min_element(vectorMinX.begin(), vectorMinX.end());
  auto maxY = std::max_element(vectorMaxY.begin(), vectorMaxY.end());
  auto minY = std::min_element(vectorMinY.begin(), vectorMinY.end());

  return std::make_pair(Point{ *minX, *minY }, Point{ *maxX, *maxY });
}

bool kuznetsov::isPointBetwen(const Point& min, const Point& point, const Point& max)
{
  return (min.x <= point.x && min.y <= point.y && max.x >= point.x && max.y >= point.y);
}

bool kuznetsov::ifInFrameRectangle(const Polygon& shape, std::pair< Point, Point > frameRectangle)
{
  auto operation = std::bind(isPointBetwen, frameRectangle.first, std::placeholders::_1, frameRectangle.second);
  int count = std::count_if(shape.points.begin(), shape.points.end(), operation);
  return count == static_cast<int>(shape.points.size());
}
