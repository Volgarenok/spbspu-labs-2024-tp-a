#include "Commands.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <limits>
#include "Geometry.hpp"
#include "Utils.hpp"

double petrov::getAreaEO(const std::vector< Polygon >& polygons, bool isEven)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonAreaEO, _1, _2, isEven);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getAreaAverage(const std::vector< Polygon >& polygons)
{
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, AccPolygonArea) / polygons.size();
}
double petrov::getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonAreaNumOfVertexes, _1, _2, numOfVertexes);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getMax(const std::vector< Polygon >& polygons, bool forArea)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonMax, _1, _2, forArea);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getMin(const std::vector< Polygon >& polygons, bool forArea)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonMin, _1, _2, forArea);
  using areaLim = std::numeric_limits< double >;
  return std::accumulate(polygons.cbegin(), polygons.cend(), areaLim::max(), areaAcc);
}
size_t petrov::countEON(const std::vector< Polygon >& polygons, bool isEven)
{
  using namespace std::placeholders;
  size_t(*func)(size_t, const Polygon&, bool) = &AccPolygonEON;
  auto areaAcc = std::bind(func, _1, _2, isEven);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0, areaAcc);
}
size_t petrov::countEON(const std::vector< Polygon >& polygons, double numOfVertexes)
{
  using namespace std::placeholders;
  size_t(*func)(size_t, const Polygon&, size_t) = &AccPolygonEON;
  auto areaAcc = std::bind(func, _1, _2, numOfVertexes);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0, areaAcc);
}
double petrov::rmEcho(std::vector< Polygon >& polygons, const Polygon& mask);
double petrov::countSame(const std::vector< Polygon >& polygons, const Polygon& mask);