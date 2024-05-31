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

bool isVertexesLess(const babinov::Polygon& first, const babinov::Polygon& second)
{
  return (first.points.size() < second.points.size());
}

bool isAreaLess(const babinov::Polygon& first, const babinov::Polygon& second)
{
  return (babinov::getArea(first) < babinov::getArea(second));
}

std::function< bool(const babinov::Polygon&, const babinov::Polygon&) > getMinOrMaxAreaPredicate(Extremity ex)
{
  using namespace std::placeholders;
  if (ex == MIN)
  {
    return std::bind(std::greater<>(), std::bind(babinov::getArea, _1), std::bind(babinov::getArea, _2));
  }
  return std::bind(std::less<>(), std::bind(babinov::getArea, _1), std::bind(babinov::getArea, _2));
}

std::function< bool(const babinov::Polygon&, const babinov::Polygon&) > getMinOrMaxVertexesPredicate(Extremity ex)
{
  using namespace std::placeholders;
  if (ex == MIN)
  {
    return std::bind(std::greater<>(), std::bind(babinov::getVertexes, _1), std::bind(babinov::getVertexes, _2));
  }
  return std::bind(std::less<>(), std::bind(babinov::getVertexes, _1), std::bind(babinov::getVertexes, _2));
}

void minOrMax(const std::vector< babinov::Polygon >& polygons, std::istream& in, std::ostream& out, Extremity ex)
{
  if (!polygons.size())
  {
    throw std::logic_error("There must be at least one polygon");
  }
  std::function< bool(const babinov::Polygon&, const babinov::Polygon&) > pred;
  std::string parameter;
  in >> parameter;
  if (parameter == "AREA")
  {
    pred = getMinOrMaxAreaPredicate(ex);
    out << babinov::getArea(*std::max_element(polygons.cbegin(), polygons.cend(), pred)) << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    pred = getMinOrMaxVertexesPredicate(ex);
    out << (*std::max_element(polygons.cbegin(), polygons.cend(), pred)).points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double getArea(const std::vector< babinov::Polygon >& polygons, std::function< bool(const babinov::Polygon&) > pred)
{
  std::vector< babinov::Polygon > matching;
  std::vector< double > areas;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(matching), pred);
  std::transform(matching.begin(), matching.end(), std::back_inserter(areas), babinov::getArea);
  return std::accumulate(areas.begin(), areas.end(), 0.0);
}

namespace babinov
{
  void execCmdArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    double result;
    std::string parameter;
    in >> parameter;
    if (parameter == "EVEN")
    {
      result = ::getArea(polygons, std::bind(isExpectedParity, _1, EVEN));
    }
    else if (parameter == "ODD")
    {
      result = ::getArea(polygons, std::bind(isExpectedParity, _1, ODD));
    }
    else if (parameter == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("There must be at least one polygon");
      }
      std::vector< double > areas;
      std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), getArea);
      result = std::accumulate(areas.begin(), areas.end(), 0.0) / polygons.size();
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
      result = ::getArea(polygons, pred);
    }
    out << result << '\n';
  }

  void execCmdMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minOrMax(polygons, in, out, MAX);
  }

  void execCmdMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minOrMax(polygons, in, out, MIN);
  }

  void execCmdCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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

  void execCmdRects(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isRectangle) << '\n';
  }

  void execCmdIntersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
