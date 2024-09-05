#include "figures_operations.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <cmath>

std::pair< kozlov::Point, kozlov::Point > kozlov::MakePair::operator()(const Point& p1, const Point& p2) const
{
  return std::make_pair(p1, p2);
}

double kozlov::ShoelaceFormula::operator()(double acc, const std::pair< Point, Point >& points) const
{
  double area = points.first.x * points.second.y - points.second.x * points.first.y;
  return acc + area;
}

double kozlov::SumArea::operator()(double acc, const Polygon& poly) const
{
  return acc + calcArea(poly);
}

bool kozlov::HasNumOfVertexes::operator()(const Polygon& poly) const
{
  return poly.points.size() == vertexNum;
}

kozlov::HasNumOfVertexes::HasNumOfVertexes(size_t num):
  vertexNum(num)
{}

bool kozlov::CompareVertexes::operator()(const Polygon& p1, const Polygon& p2) const
{
  return p1.points.size() < p2.points.size();
}

double kozlov::calcArea(const Polygon& poly)
{
  std::vector< std::pair< Point, Point > > pointPairs;
  std::transform(poly.points.begin(), poly.points.end() - 1, poly.points.begin() + 1,
    std::back_inserter(pointPairs), MakePair());
  pointPairs.emplace_back(poly.points.back(), poly.points.front());
  double areaSum = std::accumulate(pointPairs.begin(), pointPairs.end(), 0.0, ShoelaceFormula());
  return 0.5 * std::abs(areaSum);
}

bool kozlov::isEven(const Polygon& poly)
{
  return (poly.points.size() % 2 == 0);
}

bool kozlov::isOdd(const Polygon& poly)
{
  return (poly.points.size() % 2 != 0);
}

double kozlov::calcEvenArea(const std::vector< Polygon >& poly)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if(poly.begin(), poly.end(), std::back_inserter(evenPolygons), isEven);
  return std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, SumArea());
}

double kozlov::calcOddArea(const std::vector< Polygon >& poly)
{
  std::vector< Polygon > oddPolygons;
  std::copy_if(poly.begin(), poly.end(), std::back_inserter(oddPolygons), isOdd);
  return std::accumulate(oddPolygons.begin(), oddPolygons.end(), 0.0, SumArea());
}

double kozlov::calcMeanArea(const std::vector< Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::accumulate(poly.begin(), poly.end(), 0.0, SumArea()) / poly.size();
}

double kozlov::calcNumVertexArea(const std::vector< Polygon >& poly, size_t vertexNum)
{
  std::vector< Polygon > filteredPolygons;
  std::copy_if(poly.begin(), poly.end(),
    std::back_inserter(filteredPolygons), HasNumOfVertexes(vertexNum));
  return std::accumulate(filteredPolygons.begin(), filteredPolygons.end(), 0.0, SumArea());
}

double kozlov::getMaxArea(const std::vector< Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return calcArea(*std::max_element(poly.begin(), poly.end(),
    std::bind(std::less<double>(),
      std::bind(&calcArea, std::placeholders::_1),
      std::bind(&calcArea, std::placeholders::_2))));
}

size_t kozlov::getMaxVertexes(const std::vector< Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::max_element(poly.begin(), poly.end(), CompareVertexes())->points.size();
}

double kozlov::getMinArea(const std::vector< Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return calcArea(*std::max_element(poly.begin(), poly.end(),
    std::bind(std::less<double>(),
      std::bind(&calcArea, std::placeholders::_1),
      std::bind(&calcArea, std::placeholders::_2))));
}

size_t kozlov::getMinVertexes(const std::vector< Polygon >& poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<EMPTY POLYGONS>");
  }
  return std::min_element(poly.begin(), poly.end(), CompareVertexes())->points.size();
}

size_t kozlov::countEvenPoly(const std::vector< Polygon >& poly)
{
  return std::count_if(poly.begin(), poly.end(), isEven);
}

size_t kozlov::countOddPoly(const std::vector< Polygon >& poly)
{
  return std::count_if(poly.begin(), poly.end(), isOdd);
}

size_t kozlov::countNumPoly(const std::vector< Polygon >& poly, size_t vertexNum)
{
  return std::count_if(poly.begin(), poly.end(), HasNumOfVertexes(vertexNum));
}

void kozlov::echoPolygons(std::vector< Polygon >& poly, const Polygon& target)
{
  for (auto it = poly.begin(); it != poly.end(); ++it)
  {
    if (*it == target)
    {
      it = poly.insert(it + 1, target);
    }
  }
}

std::pair< kozlov::Point, kozlov::Point > kozlov::calcFrame(std::pair< Point, Point > frames, const Polygon& poly)
{
  auto minMaxX = std::minmax_element(poly.points.begin(), poly.points.end(), compareX);
  auto minMaxY = std::minmax_element(poly.points.begin(), poly.points.end(), compareY);
  frames.first.x = std::min(frames.first.x, minMaxX.first->x);
  frames.first.y = std::min(frames.first.y, minMaxY.first->y);
  frames.second.x = std::max(frames.second.x, minMaxX.second->x);
  frames.second.y = std::max(frames.second.y, minMaxY.second->y);
  return frames;
}

bool kozlov::compareX(const Point& p1, const Point& p2)
{
  return p1.x < p2.x;
}

bool kozlov::compareY(const Point& p1, const Point& p2)
{
  return p1.y < p2.y;
}

bool kozlov::checkPointInFrame(std::pair< Point, Point > frames, const Point& point)
{
  return (frames.first.x <= point.x && point.x <= frames.second.x) &&
    (frames.first.y <= point.y && point.y <= frames.second.y);
}
