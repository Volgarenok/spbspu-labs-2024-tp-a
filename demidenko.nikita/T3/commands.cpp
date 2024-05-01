#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <streamGuard.hpp>
#include "area.hpp"
#include "geometry.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
  double sumArea(const std::vector< Polygon >& polygons)
  {
    using namespace std::placeholders;
    return std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(std::plus<>(), _1, polygonArea));
  }
  std::size_t polygonSize(const Polygon& polygon)
  {
    return polygon.points.size();
  }
}
void demidenko::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);

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
void demidenko::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
void demidenko::echo(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons);
void demidenko::rightShapes(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
