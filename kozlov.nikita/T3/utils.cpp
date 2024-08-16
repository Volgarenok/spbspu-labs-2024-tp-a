#include "utils.hpp"
#include <algorithm>
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
