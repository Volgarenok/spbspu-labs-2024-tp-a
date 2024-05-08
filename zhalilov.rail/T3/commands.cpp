#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>

#include "geometry.hpp"
#include "getPolygonArea.hpp"

namespace zhalilov
{
  namespace commands
  {
    enum class AreaCmdType
    {
      Even,
      Odd,
      Mean,
      CurrVertex
    };

    enum class MaxMinCmdType
    {
      Area,
      Vertexes
    };

    enum class CountCmdType
    {
      Even,
      Odd,
      CurrVertex
    };

    double calcArea(AreaCmdType, size_t vertexes, size_t polygons, double, const Polygon &);
    bool compareMaxMim(MaxMinCmdType, const Polygon &, const Polygon &);
  }
}

void zhalilov::commands::area(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < double(double, const Polygon &) > areaFunc;
  if (argument == "EVEN")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Even, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "ODD")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Odd, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::Mean, 0, polygons.size(), std::placeholders::_1, std::placeholders::_2);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::CurrVertex, vertexes, 0, std::placeholders::_1, std::placeholders::_2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaFunc);
}

void zhalilov::commands::max(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }

  std::string argument;
  in >> argument;
  if (argument == "AREA")
  {
    double area = getPolygonArea(*std::max_element(polygons.cbegin(), polygons.cend(), compareArea));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    size_t vertexes = std::max_element(polygons.cbegin(), polygons.cend(), compareArea)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding max: invalid arg");
  }
}

void zhalilov::commands::min(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding min: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &, const Polygon &) > predicate;
  if (argument == "AREA")
  {
    predicate = std::bind(compareMaxMim, MaxMinCmdType::Area, std::placeholders::_1, std::placeholders::_2);
    double area = getPolygonArea(*std::min_element(polygons.cbegin(), polygons.cend(), predicate));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    predicate = std::bind(compareMaxMim, MaxMinCmdType::Vertexes, std::placeholders::_1, std::placeholders::_2);
    size_t vertexes = std::min_element(polygons.cbegin(), polygons.cend(), predicate)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding min: invalid arg");
  }
}

void zhalilov::commands::count(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;

  if (argument == "EVEN")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Even, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "ODD")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Odd, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::Mean, 0, polygons.size(), std::placeholders::_1, std::placeholders::_2);
  }
}

double zhalilov::commands::calcArea(AreaCmdType type, size_t vertexes, size_t polygons, double res, const Polygon &polygon)
{
  double area = 0.0;
  if (type == AreaCmdType::Even)
  {
    if (polygon.points.size() % 2 != 0)
    {
      area = getPolygonArea(polygon);
    }
  }
  else if (type == AreaCmdType::Odd)
  {
    if (polygon.points.size() % 2 == 0)
    {
      area = getPolygonArea(polygon);
    }
  }
  else if (type == AreaCmdType::Mean)
  {
    area = getPolygonArea(polygon) / polygons;
  }
  else
  {
    if (polygon.points.size() == vertexes)
    {
      area = getPolygonArea(polygon);
    }
  }
  return res + area;
}

bool zhalilov::commands::compareMaxMim(MaxMinCmdType type, const Polygon &first, const Polygon &second)
{
  if (type == MaxMinCmdType::Area)
  {
    return getPolygonArea(first) < getPolygonArea(second);
  }
  return first.points.size() < second.points.size();
}
