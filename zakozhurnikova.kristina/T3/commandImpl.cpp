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
  using Command = std::function< double(double, const Polygon&) >;
  std::map< std::string, Command > commands;
  {
    commands["EVEN"] = std::bind(getEvenOddArea, _1, _2, false);
    commands["ODD"] = std::bind(getEvenOddArea, _1, _2, true);
    commands["MEAN"] = std::bind(getMeanArea, _1, _2, polygons.size());
  }
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
    std::size_t number = std::stoull(command);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(getVertexesArea, _1, _2, number);
  }
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateFunctor);
}

double zak::getVertexesArea(double area, const Polygon& polygon, std::size_t size)
{
  if (polygon.points.size() == size)
  {
    area += polygon.getArea();
  }
  return area;
}

double zak::getEvenOddArea(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double zak::getMeanArea(double area, const Polygon& polygon, std::size_t size)
{
  return area + (polygon.getArea()) / size;
}

size_t zak::countVertexes(const std::string& command, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  using Command = std::function< bool(const Polygon&) >;
  std::map< std::string, Command > commands;
  {
    commands["EVEN"] = std::bind(evenOddCountFunctor, _1, false);
    commands["ODD"] = std::bind(evenOddCountFunctor, _1, true);
  }
  Command countFunctor;
  try
  {
    countFunctor = commands.at(command);
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(command);
    if (number < 3)
    {
      throw std::logic_error("INVALID COMMAND");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(vertexesCountFunctor, _1, number);
  }
  return std::count_if(polygons.cbegin(), polygons.cend(), countFunctor);
}

bool zak::evenOddCountFunctor(const Polygon& polygon, bool isOdd)
{
  return polygon.points.size() % 2 == isOdd;
}

bool zak::vertexesCountFunctor(const Polygon& polygon, std::size_t size)
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
