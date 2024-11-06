#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>
#include <delimeter.hpp>
#include "geometry.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
  double sumArea(const std::vector< Polygon >& polygons);
  size_t polygonSize(const Polygon& polygon);
  template < class Comp >
  void extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp comp);
}
void demidenko::doAreaCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{

  using namespace std::placeholders;
  std::vector< Polygon > temp;
  int numOfVertices = 0;
  in >> numOfVertices;
  if (in)
  {
    if (numOfVertices < 3)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    auto equalToNumOfVertices = std::bind(std::equal_to< int >(), numOfVertices, std::bind(polygonSize, _1));
    temp.reserve(std::count_if(polygons.begin(), polygons.end(), equalToNumOfVertices));
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), equalToNumOfVertices);
    out << sumArea(temp) << '\n';
  }
  else
  {
    in.clear();
    std::string cmd;
    in >> cmd;
    auto odd = std::bind(std::modulus<>(), std::bind(polygonSize, _1), 2);
    if (cmd == "ODD")
    {
      temp.reserve(std::count_if(polygons.begin(), polygons.end(), odd));
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), odd);
      out << sumArea(temp) << '\n';
    }
    else if (cmd == "EVEN")
    {
      auto even = std::bind(std::logical_not<>(), std::bind(odd, _1));
      temp.reserve(std::count_if(polygons.begin(), polygons.end(), even));
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), even);
      out << sumArea(temp) << '\n';
    }
    else if (cmd == "MEAN")
    {
      if (polygons.size() == 0)
      {
        throw std::runtime_error(ERROR_MESSAGE);
      }
      double sum = sumArea(polygons);
      out << sum / polygons.size() << '\n';
    }
    else
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
  }
}
void demidenko::doCountCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  auto countVertices = std::bind(&std::vector< Polygon >::size, _1);
  std::vector< Polygon > temp;
  int numOfVertices = 0;
  in >> numOfVertices;
  if (in)
  {
    if (numOfVertices < 3)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    auto equalToNumOfVertices = std::bind(std::equal_to< int >(), numOfVertices, std::bind(polygonSize, _1));
    temp.reserve(std::count_if(polygons.begin(), polygons.end(), equalToNumOfVertices));
    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), equalToNumOfVertices);
    out << countVertices(temp) << '\n';
  }
  else
  {
    in.clear();
    std::string cmd;
    in >> cmd;
    auto odd = std::bind(std::modulus<>(), std::bind(polygonSize, _1), 2);
    if (cmd == "ODD")
    {
      temp.reserve(std::count_if(polygons.begin(), polygons.end(), odd));
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), odd);
      out << countVertices(temp) << '\n';
    }
    else if (cmd == "EVEN")
    {
      auto even = std::bind(std::logical_not<>(), std::bind(odd, _1));
      temp.reserve(std::count_if(polygons.begin(), polygons.end(), even));
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), even);
      out << countVertices(temp) << '\n';
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
  return std::accumulate(
    polygons.begin(),
    polygons.end(),
    0.0,
    std::bind(std::plus<>(), _1, std::bind(getPolygonArea, _2))
  );
}
size_t demidenko::polygonSize(const Polygon& polygon)
{
  return polygon.points.size();
}
void demidenko::doMaxCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  extremum(in, out, polygons, std::less<>());
}
void demidenko::doMinCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  extremum(in, out, polygons, std::greater<>());
}
template < class Comp >
void demidenko::extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp comparator)
{
  if (polygons.empty())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  std::string cmd;
  in >> cmd;
  using namespace std::placeholders;
  if (cmd == "AREA")
  {
    out << getPolygonArea(*std::max_element(
      polygons.begin(),
      polygons.end(),
      std::bind(comparator, std::bind(getPolygonArea, _1), std::bind(getPolygonArea, _2))
    ));
    out << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    out << polygonSize(*std::max_element(
      polygons.begin(),
      polygons.end(),
      std::bind(comparator, std::bind(polygonSize, _1), std::bind(polygonSize, _2))
    ));
    out << '\n';
  }
  else
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::doEchoCommand(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
{
  Polygon target;
  in >> target;
  if (in.fail() || in.peek() != '\n')
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  using namespace std::placeholders;
  size_t matches = std::count_if(polygons.begin(), polygons.end(), std::bind(isPolygonEqual, _1, std::ref(target)));
  std::vector< Polygon > updatedPolygons;
  updatedPolygons.reserve(polygons.size() + matches);
  for (auto& polygon : polygons)
  {
    if (std::equal(polygon.points.begin(), polygon.points.end(), target.points.begin(), isPointEqual))
    {
      updatedPolygons.push_back(polygon);
    }
    updatedPolygons.push_back(polygon);
  }
  polygons = updatedPolygons;
  out << matches << '\n';
}
void demidenko::doRightShapesCommand(std::ostream& out, const std::vector< Polygon >& polygons)
{
  out << std::count_if(polygons.begin(), polygons.end(), isRightPolygon) << '\n';
}
