#include "commandImpl.hpp"
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <ostream>
#include <scopeGuard.hpp>

namespace zak = zakozhurnikova;

double zak::accumulateArea(const std::string& command, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  using Command = std::function< double(const Polygon&) >;
  std::map< std::string, Command > commands;
  commands["EVEN"] = std::bind(areaSum, 0.0, _1, evenPredicate);
  commands["ODD"] = std::bind(areaSum, 0.0 , _1, oddPredicate);
  commands["MEAN"] = std::bind(getMeanArea, 0.0, _1, polygons.size());

  if (command == "MEAN" && polygons.empty())
  {
    throw std::logic_error("INVALID ARGUMENT");
  }
  Command accumulateFunctor;
  try
  {
    accumulateFunctor = commands.at(command);
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(command);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    Predicate vertexPredicate = std::bind(vertexNumPredicate, _1, number);
    accumulateFunctor = std::bind(areaSum, 0.0, _1, vertexPredicate);
  }
  std::vector< double > areas;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), accumulateFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

bool zak::evenPredicate(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zak::oddPredicate(const Polygon& polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool zak::vertexNumPredicate(const Polygon& polygon, size_t vertexCount)
{
  return polygon.points.size() == vertexCount;
}

double zak::getMeanArea(double area, const Polygon& polygon, size_t size)
{
  return area + (polygon.getArea()) / size;
}

double zak::areaSum(double area, const Polygon& polygon, Predicate pred)
{
  if (pred(polygon))
  {
    area += polygon.getArea();
  }
  return area;
}

size_t zak::countVertexes(const std::string& command, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  using Command = std::function< bool(const Polygon&) >;
  std::map< std::string, Command > commands;
  {
    commands["EVEN"] = std::bind(evenCountFunctor, _1);
    commands["ODD"] = std::bind(oddCountFunctor, _1);
  }
  Command countFunctor;
  try
  {
    countFunctor = commands.at(command);
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(command);
    if (number < 3)
    {
      throw std::logic_error("INVALID COMMAND");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(vertexesCountFunctor, _1, number);
  }
  return std::count_if(polygons.cbegin(), polygons.cend(), countFunctor);
}

bool zak::oddCountFunctor(const Polygon& polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool zak::evenCountFunctor(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zak::vertexesCountFunctor(const Polygon& polygon, size_t size)
{
  return polygon.points.size() == size;
}

bool zak::compareArea(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.getArea() < rhs.getArea();
}

bool zak::compareVertex(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void zak::getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << std::min_element(polygons.cbegin(), polygons.cend(), compareArea)->getArea();
}

void zak::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << std::max_element(polygons.cbegin(), polygons.cend(), compareArea)->getArea();
}

void zak::getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << std::min_element(polygons.cbegin(), polygons.cend(), compareVertex)->points.size();
}

void zak::getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << std::max_element(polygons.cbegin(), polygons.cend(), compareVertex)->points.size();
}
