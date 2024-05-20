#include "Commands.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <limits>
#include <stdexcept>
#include "Geometry.hpp"
#include "Utils.hpp"

double petrov::getAreaEO(const std::vector< Polygon >& polygons, bool forEven)
{
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonAreaEO, _1, _2, forEven);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getAreaAverage(const std::vector< Polygon >& polygons)
{
  if (polygons.size() == 0)
  {
    throw std::logic_error("<NO POLYGONS>");
  }
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, AccPolygonArea) / polygons.size();
}
double petrov::getAreaNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes)
{
  if (numOfVertexes < 3)
  {
    throw std::logic_error("<CANT BE LESS THAN 3 VERTEXES>");
  }
  using namespace std::placeholders;
  auto areaAcc = std::bind(&AccPolygonAreaNumOfVertexes, _1, _2, numOfVertexes);
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc);
}
double petrov::getExtremum(const std::vector< Polygon >& polygons, bool forArea, bool forMax)
{
  using iter = std::vector< Polygon >::const_iterator;
  using compType = bool(*)(const Polygon&, const Polygon&);
  using extElemType = iter(*)(iter, iter, compType);
  extElemType extremum_element = nullptr;
  if (forMax)
  {
    extremum_element = std::max_element;
  }
  else
  {
    extremum_element = std::min_element;
  }
  auto comp = forArea ? isSmallerPolygonArea : isSmallerNumOfVertexes;
  auto polIterator = extremum_element(polygons.cbegin(), polygons.cend(), comp);
  if (polIterator == polygons.cend())
  {
    throw std::logic_error("<NO SUCH VERTEXES>");
  }

  return forArea ? getArea(*polIterator) : (*polIterator).points.size();
}
double petrov::countPolygonsEO(const std::vector< Polygon >& polygons, bool forEven)
{
  auto comp = forEven ? &isEven : &isOdd;
  return std::count_if(polygons.cbegin(), polygons.cend(), comp);
}
double petrov::countPolygonsNumOfVertexes(const std::vector< Polygon >& polygons, size_t numOfVertexes)
{
  if (numOfVertexes < 3)
  {
    throw std::logic_error("<CANT BE LESS THAN 3 VERTEXES>");
  }
  using namespace std::placeholders;
  auto comp = std::bind(&isEqualNOV, _1, numOfVertexes);
  return std::count_if(polygons.cbegin(), polygons.cend(), comp);
}
double petrov::rmEcho(std::vector< Polygon >& polygons, const Polygon& mask)
{
  auto tmp = std::unique(polygons.begin(), polygons.end(), EqualPol{ mask });
  size_t count = std::distance(tmp, polygons.end());
  polygons.erase(tmp, polygons.end());
  return count;
}
double petrov::countSame(const std::vector< Polygon >& polygons, const Polygon& mask)
{
  if (mask.points.size() < 3)
  {
    throw std::logic_error("<MASK CANT HAVE LESS THAN 3 VERTEXES>");
  }
  using namespace std::placeholders;
  auto comp = std::bind(&isSame, _1, mask);
  return std::count_if(polygons.cbegin(), polygons.cend(), comp);
}
