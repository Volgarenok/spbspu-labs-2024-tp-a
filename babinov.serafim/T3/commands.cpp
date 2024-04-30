#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include "shapes.hpp"

using namespace babinov;

double getArea(const Triangle& triangle)
{
  double a = Vector(triangle.a, triangle.b).getLength();
  double b = Vector(triangle.b, triangle.c).getLength();
  double c = Vector(triangle.a, triangle.c).getLength();
  double semiPer = (a + b + c) / 2;
  return std::sqrt(semiPer * (semiPer - a) * (semiPer - b) * (semiPer - c));
}

double addPolygonPartArea(double currentArea, Triangle& prevPart, const Point& newPt)
{
  prevPart.b = prevPart.c;
  prevPart.c = newPt;
  return currentArea += getArea(prevPart);
}

double getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  Triangle areaPart{polygon.points[0], polygon.points[1], polygon.points[2]};
  double area = getArea(areaPart);
  if (polygon.points.size() > 3)
  {
    auto operation = std::bind(addPolygonPartArea, _1, std::ref(areaPart), _2);
    area += std::accumulate(polygon.points.cbegin() + 3, polygon.points.cend(), 0.0, operation);
  }
  return area;
}

enum Parity
{
  ODD,
  EVEN
};

Parity getParity(int num)
{
  return Parity(num % 2 == 0);
}

bool isExpectedParity(const Polygon& polygon, Parity expected)
{
  return getParity(polygon.points.size()) == expected;
}

bool isExpectedVertexes(const Polygon& polygon, size_t expected)
{
  return polygon.points.size() == expected;
}

double addArea(double currentArea, const Polygon& polygon)
{
  return currentArea += getArea(polygon);
}

double addAreaIf(double currentArea, const Polygon& polygon, std::function< bool(const Polygon&) > pred)
{
  if (pred(polygon))
  {
    currentArea += getArea(polygon);
  }
  return currentArea;
}

bool isAreaLess(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool isVertexesLess(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool isRectangle(const Polygon& polygon)
{
  if (polygon.points.size() == 4)
  {
    Vector firstSide(polygon.points[0], polygon.points[1]);
    Vector secondSide(polygon.points[1], polygon.points[2]);
    Vector thirdSide(polygon.points[2], polygon.points[3]);
    Vector fourthSide(polygon.points[0], polygon.points[3]);
    return (firstSide.findCosBetween(secondSide) == 0)
        && (secondSide.findCosBetween(thirdSide) == 0)
        && (thirdSide.findCosBetween(fourthSide) == 0);
  }
  return false;
}

bool isIntersect(const Polygon& first, const Polygon& second)
{
  using namespace std::placeholders;
  Point minPtFirst = *std::min_element(first.points.cbegin(), first.points.cend());
  Point minPtSecond = *std::min_element(second.points.cbegin(), second.points.cend());
  Point maxPtFirst = *std::max_element(first.points.cbegin(), first.points.cend());
  Point maxPtSecond = *std::max_element(second.points.cbegin(), second.points.cend());
  return ((maxPtFirst >= minPtSecond) && (minPtFirst <= maxPtSecond))
      || ((maxPtFirst >= minPtSecond) && (minPtFirst <= maxPtSecond));
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
        in.setstate(std::ios::failbit);
        throw std::logic_error("There must be at least one polygon");
      }
      result = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, addArea) / polygons.size();
    }
    else
    {
      int nVertexes = 0;
      try
      {
        nVertexes = std::stoi(parameter);
      }
      catch (...)
      {
        in.setstate(std::ios::failbit);
        throw;
      }
      if (nVertexes < 3)
      {
        in.setstate(std::ios::failbit);
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
    if (!polygons.size())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("There must be at least one polygon");
    }
    using namespace std::placeholders;
    std::string parameter;
    in >> parameter;
    if (parameter == "AREA")
    {
      out << getArea(*std::max_element(polygons.cbegin(), polygons.cend(), isAreaLess)) << '\n';
    }
    else if (parameter == "VERTEXES")
    {
      out << (*std::max_element(polygons.cbegin(), polygons.cend(), isVertexesLess)).points.size() << '\n';
    }
    else
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("Invalid argument");
    }
  }

  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    if (!polygons.size())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("There must be at least one polygon");
    }
    using namespace std::placeholders;
    std::string parameter;
    in >> parameter;
    if (parameter == "AREA")
    {
      auto isAreaGreater = std::bind(isAreaLess, _2, _1);
      out << getArea(*std::max_element(polygons.cbegin(), polygons.cend(), isAreaGreater)) << '\n';
    }
    else if (parameter == "VERTEXES")
    {
      auto isVertexesGreater = std::bind(isVertexesLess, _2, _1);
      out << (*std::max_element(polygons.cbegin(), polygons.cend(), isVertexesGreater)).points.size() << '\n';
    }
    else
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("Invalid argument");
    }
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
      try
      {
        nVertexes = std::stoi(parameter);
      }
      catch (...)
      {
        in.setstate(std::ios::failbit);
        throw;
      }
      if (nVertexes < 3)
      {
        in.setstate(std::ios::failbit);
        throw std::logic_error("Invalid argument");
      }
      pred = std::bind(isExpectedVertexes, _1, nVertexes);
    }
    result = std::count_if(polygons.cbegin(), polygons.cend(), pred);
    out << result << '\n';
  }

  void rects(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
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
