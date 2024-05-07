#include "commands.hpp"

#include <functional>
#include <iostream>
#include <numeric>

#include "geometry.hpp"

namespace zhalilov
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
    MAX,
    MIN
  };

  double calcArea(AreaCmdType, size_t vertexes, double, const Polygon &);
  double findMaxMinArea(MaxMinCmdType, double, const Polygon &);
  size_t findMaxMinVertexes(MaxMinCmdType, size_t, const Polygon &);

  void maxMinCmd(MaxMinCmdType, const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out);
}

void zhalilov::commands::area(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < double(double, const Polygon &) > areaFunc;
  if (argument == "EVEN")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Even, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "ODD")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Odd, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::Mean, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::CurrVertex, vertexes, std::placeholders::_1, std::placeholders::_2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaFunc);
}

void zhalilov::commands::max(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  maxMinCmd(MaxMinCmdType::MAX, polygons, in, out);
}

void zhalilov::commands::min(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  maxMinCmd(MaxMinCmdType::MIN, polygons, in, out);
}

void zhalilov::maxMinCmd(MaxMinCmdType type, const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < double(double, const Polygon &) > maxMinFunc;
  if (argument == "AREA")
  {
    maxMinFunc = std::bind(findMaxMinArea, type, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "VERTEXES")
  {
    maxMinFunc = std::bind(findMaxMinVertexes, type, std::placeholders::_1, std::placeholders::_2);
  }
  else
  {
    throw std::invalid_argument("Finding max/min: invalid arg");
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, maxMinFunc);
}
