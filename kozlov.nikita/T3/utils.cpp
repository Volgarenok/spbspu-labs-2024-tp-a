#include "utils.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>

double kozlov::ShoelaceFormula::operator()(double acc, const std::pair< Point, Point >& points) const
{
  double area = points.first.x * points.second.y - points.second.x * points.first.y;
  return acc + area;
}

double kozlov::calculateArea(const Polygon& poly)
{
  std::vector< std::pair< Point, Point > > pointPairs;
  std::transform(poly.points.begin(), poly.points.end() - 1, poly.points.begin() + 1,
    std::back_inserter(pointPairs), std::make_pair< Point, Point >);
  pointPairs.emplace_back(poly.points.back(), poly.points.front());
  double areaSum = std::accumulate(pointPairs.begin(), pointPairs.end(), 0.0, ShoelaceFormula());
  return 0.5 * std::abs(areaSum);
}
