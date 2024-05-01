#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>
#include "area.hpp"
#include "geometry.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
  double sumArea(const std::vector< Polygon >& polygons);
  std::size_t polygonSize(const Polygon& polygon);
  template < class Comp >
  void extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp&& comp);
}
void demidenko::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  std::vector< Polygon > temp;
  int numOfVertices = 0;
  in >> numOfVertices;
  if (in)
  {
    std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(temp),
      std::bind(std::equal_to<>(), numOfVertices, polygonSize)
    );
    out << sumArea(temp);
  }
  else
  {
    in.clear();
    std::string cmd;
    in >> cmd;
    auto odd = std::bind(std::modulus<>(), polygonSize, 2);
    if (cmd == "ODD")
    {
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), odd);
      out << sumArea(temp);
    }
    else if (cmd == "EVEN")
    {
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), std::bind(std::logical_not<>(), odd));
      out << sumArea(temp);
    }
    else if (cmd == "MEAN")
    {
      if (polygons.size() == 0)
      {
        throw std::runtime_error(ERROR_MESSAGE);
      }
      double sum = sumArea(polygons);
      out << sum / polygons.size();
    }
    else
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
  }
}
double demidenko::sumArea(const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(std::plus<>(), _1, polygonArea));
}
std::size_t demidenko::polygonSize(const Polygon& polygon)
{
  return polygon.points.size();
}
void demidenko::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  extremum(in, out, polygons, std::less<>());
}
void demidenko::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  extremum(in, out, polygons, std::greater<>());
}
template < class Comp >
void demidenko::extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp&& comparator)
{
  std::string cmd;
  in >> cmd;
  using namespace std::placeholders;
  if (cmd == "AREA")
  {
    out << polygonArea(
      *std::max_element(polygons.begin(), polygons.end(), std::bind(comparator, polygonArea, polygonArea))
    );
  }
  else if (cmd == "VERTEXES")
  {
    out << polygonSize(
      *std::max_element(polygons.begin(), polygons.end(), std::bind(comparator, polygonSize, polygonSize))
    );
  }
  else
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::echo(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons);
void demidenko::rightShapes(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
