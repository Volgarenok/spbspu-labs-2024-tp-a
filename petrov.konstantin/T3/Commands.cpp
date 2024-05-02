#include "Commands.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include "Geometry.hpp"
#include "Utils.hpp"
//RMECHO SAME
double petrov::getAreaEO(const std::vector< Polygon >& polygons, bool isEven)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonAreaEO, _1, _2, isEven);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getAreaAverage(const std::vector< Polygon >& polygons);
double petrov::getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes);
double petrov::getAreaMax(const std::vector< Polygon >& polygons, bool forArea);
double petrov::getAreaMin(const std::vector< Polygon >& polygons, bool forArea);
double petrov::countEON(const std::vector< Polygon >& polygons, EON setting);
double petrov::rmEcho(std::vector< Polygon >& polygons, const Polygon& mask);
double petrov::countSame(const std::vector< Polygon >& polygons, const Polygon& mask);