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
  template < class F >
  std::string basicAction(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, F action);
  double sumArea(const std::vector< Polygon >& polygons);
  size_t polygonSize(const Polygon& polygon);
  template < class Comp >
  void extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp comp);
  Point readPoint(std::istream& in)
  {
    if (in.peek() == '\n')
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    Point point;
    in >> DelimeterI{ " " } >> point;
    if (!in)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    return point;
  }
}
void demidenko::doAreaCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string unhandledCommand = basicAction(in, out, polygons, sumArea);
  if (unhandledCommand == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    double sum = sumArea(polygons);
    out << sum / polygons.size() << '\n';
  }
  else if (!unhandledCommand.empty())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::doCountCommand(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  std::string unhandledCommand = basicAction(in, out, polygons, std::bind(&std::vector< Polygon >::size, _1));
  if (!unhandledCommand.empty())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
template < class F >
std::string demidenko::basicAction(
  std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, F action
)
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
    std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(temp),
      std::bind(std::equal_to< int >(), numOfVertices, std::bind(polygonSize, _1))
    );
    out << action(temp) << '\n';
  }
  else
  {
    in.clear();
    std::string cmd;
    in >> cmd;
    auto odd = std::bind(std::modulus<>(), std::bind(polygonSize, _1), 2);
    if (cmd == "ODD")
    {
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(temp), odd);
      out << action(temp) << '\n';
    }
    else if (cmd == "EVEN")
    {
      std::copy_if(
        polygons.begin(),
        polygons.end(),
        std::back_inserter(temp),
        std::bind(std::logical_not<>(), std::bind(odd, _1))
      );
      out << action(temp) << '\n';
    }
    else
    {
      return cmd;
    }
  }
  return "";
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
  size_t size = 0;
  in >> size;
  if (size < 3)
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  std::generate_n(std::back_inserter(target.points), size, std::bind(readPoint, std::ref(in)));
  if (in.peek() != '\n')
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  std::vector< Polygon > updatedPolygons;
  size_t matches = 0;
  for (auto& polygon : polygons)
  {
    if (std::equal(polygon.points.begin(), polygon.points.end(), target.points.begin(), isPointEqual))
    {
      ++matches;
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
