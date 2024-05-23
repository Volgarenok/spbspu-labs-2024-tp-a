#include "commands.hpp"
#include <functional>
#include <iomanip>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <string>
#include <scopeGuard.hpp>
#include "polygon.hpp"

bool isOdd(const basko::Polygon& polygon)
{
  return polygon.points.size() % 2;
}

bool isEven(const basko::Polygon& polygon)
{
  return !(polygon.points.size() % 2);
}

bool isSize(const basko::Polygon& polygon, size_t numPoints)
{
  return polygon.points.size() == numPoints;
}

void basko::area(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  std::vector< Polygon > polygons;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (value.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::copy(value.cbegin(), value.cend(), std::back_inserter(polygons));
  }
  else
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    std::copy_if(value.cbegin(), value.cend(), std::back_inserter(polygons), isCorrectCount);
    std::vector< double > areas;
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), getPolygonArea);
    double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    if (argument == "MEAN")
    {
      res /= value.size();
    }
    out << res;
  }
}

bool comparatorPoints(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return rhs.points.size() < lhs.points.size();
}

bool comparatorArea(const basko::Polygon& lhs, const basko::Polygon& rhs)
{
  return getPolygonArea(rhs) < getPolygonArea(lhs);
}

void basko::max(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  else
  {
    if (argument == "AREA")
    {
      ScopeGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::max_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
}

void basko::min(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (value.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  else
  {
    if (argument == "AREA")
    {
      ScopeGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::min_element(value.begin(), value.end(), comparatorArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(value.begin(), value.end(), comparatorPoints)->points.size();
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
}

void basko::count(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(value.begin(), value.end(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(value.begin(), value.end(), isOdd);
  }
  else if (std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
  {
    size_t countPoints = std::stoull(argument);
    if (countPoints < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isCorrectCount = std::bind(isSize, _1, countPoints);
    out << std::count_if(value.begin(), value.end(), isCorrectCount);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void basko::rightshapes(const std::vector<Polygon>& value, std::ostream& out)
{
  out << std::count_if(value.cbegin(), value.cend(), isRightAngle);
}

void basko::inframe(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  Polygon argument;
  in >> argument;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void basko::echo(const std::vector<Polygon>& value, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::vector< Polygon > tempValue;
  size_t polygonCount = 0;
  for (const auto& shape : value)
  {
    tempValue.push_back(shape);
    if (shape == polygon)
    {
      ++polygonCount;
      tempValue.push_back(polygon);
    }
  }
  value = tempValue;
  out << polygonCount;
}
