#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include "shapes.hpp"

using babinov::Polygon;

enum Parity
{
  EVEN,
  ODD
};

Parity getParity(int num)
{
  if (num % 2 == 0)
  {
    return EVEN;
  }
  return ODD;
}

double addArea(double currentArea, const Polygon& polygon)
{
  return currentArea += getArea(polygon);
}

double addAreaIfExpectedParity(double currentArea, const Polygon& polygon, Parity expected)
{
  if (getParity(polygon.points.size()) == expected)
  {
    currentArea = addArea(currentArea, polygon);
  }
  return currentArea;
}

double addAreaIfExpectedVertexesNumber(double currentArea, const Polygon& polygon, int expected)
{
  if (polygon.points.size() == expected)
  {
    currentArea = addArea(currentArea, polygon);
  }
  return currentArea;
}

namespace babinov
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    double result;
    std::string vertexes;
    in >> vertexes;
    if (vertexes == "EVEN")
    {
      auto operation = std::bind(addAreaIfExpectedParity, _1, _2, EVEN);
      result = std::accumulate(polygons.begin(), polygons.end(), 0.0, operation);
    }
    else if (vertexes == "ODD")
    {
      auto operation = std::bind(addAreaIfExpectedParity, _1, _2, ODD);
      result = std::accumulate(polygons.begin(), polygons.end(), 0.0, operation);
    }
    else if (vertexes == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("There must be at least one polygon");
      }
      result = std::accumulate(polygons.begin(), polygons.end(), 0.0, addArea) / polygons.size();
    }
    else
    {
      int nVertexes = std::stoi(vertexes);
      auto operation = std::bind(addAreaIfExpectedVertexesNumber, _1, _2, nVertexes);
      result = std::accumulate(polygons.begin(), polygons.end(), 0.0, operation);
    }
    out << result << '\n';
  }
}
