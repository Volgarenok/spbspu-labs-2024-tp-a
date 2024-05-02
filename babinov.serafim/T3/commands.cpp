#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

#include "shapes.hpp"

enum Parity
{
  ODD,
  EVEN
};

enum Extremity
{
  MIN,
  MAX
};

Parity getParity(int num)
{
  return Parity(num % 2 == 0);
}

bool isExpectedParity(const babinov::Polygon& polygon, Parity expected)
{
  return getParity(polygon.points.size()) == expected;
}

bool isExpectedVertexes(const babinov::Polygon& polygon, size_t expected)
{
  return polygon.points.size() == expected;
}

void minOrMax(const std::vector< babinov::Polygon >& polygons, std::istream& in, std::ostream& out, Extremity ex)
{
  if (!polygons.size())
  {
    throw std::logic_error("There must be at least one polygon");
  }
  using namespace std::placeholders;
  std::function< bool(const babinov::Polygon&, const babinov::Polygon&) > pred;
  std::string parameter;
  in >> parameter;
  if (parameter == "AREA")
  {
    if (ex == MIN)
    {
      pred = std::bind(std::greater<>(), std::bind(babinov::getArea, _1), std::bind(babinov::getArea, _2));
    }
    else
    {
      pred = std::bind(std::less<>(), std::bind(babinov::getArea, _1), std::bind(babinov::getArea, _2));
    }
    out << getArea(*std::max_element(polygons.cbegin(), polygons.cend(), pred)) << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    if (ex == MIN)
    {
      pred = std::bind(std::greater<>(), std::bind(babinov::getVertexes, _1), std::bind(babinov::getVertexes, _2));
    }
    else
    {
      pred = std::bind(std::less<>(), std::bind(babinov::getVertexes, _1), std::bind(babinov::getVertexes, _2));
    }
    out << (*std::max_element(polygons.cbegin(), polygons.cend(), pred)).points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid argument");
  }
}

namespace babinov
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    double result;
    std::string parameter;
    in >> parameter;
    if (parameter == "EVEN")
    {
      std::function< bool(const Polygon&) > pred = std::bind(isExpectedParity, _1, EVEN);
      std::function< double(double, const Polygon&) > operation = std::bind(addAreaIf, _1, _2, pred);
      result = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, operation);
    }
    else if (parameter == "ODD")
    {
      std::function< bool(const Polygon&) > pred = std::bind(isExpectedParity, _1, ODD);
      std::function< double(double, const Polygon&) > operation = std::bind(addAreaIf, _1, _2, pred);
      result = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, operation);
    }
    else if (parameter == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("There must be at least one polygon");
      }
      result = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, addArea) / polygons.size();
    }
    else
    {
      int nVertexes = 0;
      nVertexes = std::stoi(parameter);
      if (nVertexes < 3)
      {
        throw std::logic_error("Invalid argument");
      }
      std::function< bool(const Polygon&) > pred = std::bind(isExpectedVertexes, _1, nVertexes);
      std::function< double(double, const Polygon&) > operation = std::bind(addAreaIf, _1, _2, pred);
      result = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, operation);
    }
    out << result << '\n';
  }

  void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minOrMax(polygons, in, out, MAX);
  }

  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minOrMax(polygons, in, out, MIN);
  }

  void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    int result;
    std::function< bool(const Polygon&) > pred;
    std::string parameter;
    in >> parameter;
    if (parameter == "EVEN")
    {
      pred = std::bind(isExpectedParity, _1, EVEN);
    }
    else if (parameter == "ODD")
    {
      pred = std::bind(isExpectedParity, _1, ODD);
    }
    else
    {
      int nVertexes = 0;
      nVertexes = std::stoi(parameter);
      if (nVertexes < 3)
      {
        throw std::logic_error("Invalid argument");
      }
      pred = std::bind(isExpectedVertexes, _1, nVertexes);
    }
    result = std::count_if(polygons.cbegin(), polygons.cend(), pred);
    out << result << '\n';
  }

  void rects(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isRectangle) << '\n';
  }

  void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    Polygon given;
    in >> given;
    if (given.points.empty())
    {
      throw std::invalid_argument("Invalid argument");
    }
    auto pred = std::bind(isIntersect, std::cref(given), _1);
    out << std::count_if(polygons.cbegin(), polygons.cend(), pred) << '\n';
  }
}
