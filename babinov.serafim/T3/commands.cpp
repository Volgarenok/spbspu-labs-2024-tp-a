#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
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

double addAreaIfCorrectParity(double currentArea, const Polygon& polygon, Parity parity)
{
  if (getParity(polygon.points.size()) == parity)
  {
    currentArea += getArea(polygon);
  }
  return currentArea;
}

namespace babinov
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    Parity expParity;
    std::string vertexes;
    in >> vertexes;
    if (vertexes == "EVEN")
    {
      expParity = EVEN;
    }
    else if (vertexes == "ODD")
    {
      expParity = ODD;
    }
    else
    {
      throw std::invalid_argument("Incorrect parity of vertexes");
    }
    auto addArea = std::bind(addAreaIfCorrectParity, _1, _2, expParity);
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, addArea);
    out << sum << '\n';
  }
}
