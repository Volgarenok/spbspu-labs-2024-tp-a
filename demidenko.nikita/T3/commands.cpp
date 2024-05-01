#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>
#include "geometry.hpp"

namespace demidenko
{
  const char* ERROR_MESSAGE = "Error accured\n";
  template < class F >
  std::string basicAction(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, F&& action);
  double sumArea(const std::vector< Polygon >& polygons);
  std::size_t polygonSize(const Polygon& polygon);
  template < class Comp >
  void extremum(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, Comp&& comp);
  struct EchoChamber
  {
    std::vector< Polygon >& polygons;
    const Polygon& target;
    std::size_t counter;
    Polygon operator()(Polygon&& polygon);
  };
}
void demidenko::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
{
  std::string unhandledCommand = basicAction(in, out, polygons, sumArea);
  if (unhandledCommand == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::runtime_error(ERROR_MESSAGE);
    }
    double sum = sumArea(polygons);
    out << sum / polygons.size();
  }
  else if (!unhandledCommand.empty())
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
}
void demidenko::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
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
  std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons, F&& action
)
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
      std::bind(std::equal_to< int >(), numOfVertices, std::bind(polygonSize, _1))
    );
    out << action(temp);
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
      out << action(temp);
    }
    else if (cmd == "EVEN")
    {
      std::copy_if(
        polygons.begin(),
        polygons.end(),
        std::back_inserter(temp),
        std::bind(std::logical_not<>(), std::bind(odd, _1))
      );
      out << action(temp);
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
    std::bind(std::plus<>(), _1, std::bind(polygonArea, _2))
  );
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
void demidenko::echo(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
{
  Polygon target;
  in >> target;
  if (!in)
  {
    throw std::runtime_error(ERROR_MESSAGE);
  }
  std::vector< Polygon > updatedPolygons;
  EchoChamber chamber{ updatedPolygons, target, 0 };
  std::transform(
    std::make_move_iterator(polygons.begin()),
    std::make_move_iterator(polygons.end()),
    std::back_inserter(updatedPolygons),
    chamber
  );
  polygons = updatedPolygons;
  out << chamber.counter;
}
demidenko::Polygon demidenko::EchoChamber::operator()(Polygon&& polygon)
{
  if (polygon.points == target.points)
  {
    polygons.push_back(Polygon{ target.points });
    ++counter;
  }
  return polygon;
}
void demidenko::rightShapes(std::ostream& out, const std::vector< Polygon >& polygons)
{
  out << std::count_if(polygons.begin(), polygons.end(), isRightPolygon);
}
