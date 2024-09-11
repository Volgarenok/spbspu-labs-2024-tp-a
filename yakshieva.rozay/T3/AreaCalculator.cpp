#include "AreaCalculator.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <stdexcept>

namespace yakshieva
{
  struct computePartialArea
  {
    Point first;
    double operator()(double area, const Point& second);
  };
}

double yakshieva::computePartialArea::operator()(double area, const Point& second)
{
  area += (second.x + first.x) * (first.y - second.y);
  first = second;
  return area;
}

double yakshieva::accamulateAllParts(const Polygon& p)
{
  if (p.points.size() < 3)
  {
    return 0.0;
  }
  double area = std::accumulate(p.points.begin() + 1, p.points.end(), 0.0, computePartialArea{ p.points[0] });
  area += (p.points.back().x + p.points.front().x) * (p.points.back().y - p.points.front().y);
  return std::abs(area) / 2;
}

template < class UnaryPredicate >
double yakshieva::calcAreaByCondition(const std::vector< Polygon >& polygon, UnaryPredicate P)
{
  std::vector< Polygon > selected;
  std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(selected), P);
  std::vector< double > area;
  std::transform(selected.cbegin(), selected.cend(), std::back_inserter(area), accamulateAllParts);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

double yakshieva::calculateAreaEven(const std::vector< Polygon >& context)
{
  return calcAreaByCondition(context, isVertexEven);
}

double yakshieva::calculateAreaOdd(const std::vector< Polygon >& context)
{
  return calcAreaByCondition(context, isVertexOdd);
}

double yakshieva::calculateAreaMean(const std::vector< Polygon >& context)
{
  if (context.empty())
  {
    throw std::logic_error("INVALID ARGUMENT");
  }
  std::vector< double > area;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(area), accamulateAllParts);
  return std::accumulate(area.cbegin(), area.cend(), 0.0) / context.size();
}

double yakshieva::sumAreaWithNumOfVertices(const std::vector< Polygon >& context, size_t numOfVertices)
{
  return calcAreaByCondition(context, std::bind(hasNumOfVertices, std::placeholders::_1, numOfVertices));
}

bool yakshieva::minArea(const Polygon& p1, const Polygon& p2)
{
  return accamulateAllParts(p1) < accamulateAllParts(p2);
}

bool yakshieva::minVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

double yakshieva::getMaxArea(const std::vector< Polygon >& polygons)
{
  auto maxAreaPolygon = std::max_element(polygons.begin(), polygons.end(), minArea);
  if (maxAreaPolygon == polygons.cend())
  {
    throw std::logic_error("To calculate the max, you need at least one figure");
  }
  return accamulateAllParts(*maxAreaPolygon);
}

size_t yakshieva::getMaxVertexes(const std::vector< Polygon >& polygons)
{
  auto maxVertexesPolygon = std::max_element(polygons.begin(), polygons.end(), minVertexes);
  if (maxVertexesPolygon == polygons.cend())
  {
    throw std::logic_error("To calculate the max, you need at least one figure");
  }
  return maxVertexesPolygon->points.size();
}

double yakshieva::getMinArea(const std::vector< Polygon >& polygons)
{
  auto minAreaPolygon = std::min_element(polygons.begin(), polygons.end(), minArea);
  if (minAreaPolygon == polygons.cend())
  {
    throw std::logic_error("To calculate the max, you need at least one figure");
  }
  return accamulateAllParts(*minAreaPolygon);
}

size_t yakshieva::getMinVertexes(const std::vector< Polygon >& polygons)
{
  auto minVertexesPolygon = std::min_element(polygons.begin(), polygons.end(), minVertexes);
  if (minVertexesPolygon == polygons.cend())
  {
    throw std::logic_error("To calculate the max, you need at least one figure");
  }
  return minVertexesPolygon->points.size();
}
