#include "commandsSolving.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <StreamGuard.hpp>
#include "polygon.hpp"

void novokhatskiy::commands::commandArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  std::function< double(double, const novokhatskiy::Polygon&) > area;
  using namespace std::placeholders;
  novokhatskiy::StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  if (arg == "EVEN")
  {
    area = std::bind(novokhatskiy::commands::doAccumulateEvenArea, _1, _2);
  }
  else if (arg == "ODD")
  {
    area = std::bind(novokhatskiy::commands::doAccumulateOddArea, _1, _2);
  }
  else if (arg == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    area = std::bind(novokhatskiy::commands::doAccumulateMeanArea, _1, _2, polygons);
  }
  else
  {
    size_t numOfVertexes = {};
    numOfVertexes = std::stoull(arg);
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    area = std::bind(doAccumulateNumOfVertexesArea, _1, numOfVertexes, _2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
}

double novokhatskiy::commands::doAccumulateNumOfVertexesArea(double res, size_t vertexes, const Polygon& polygons)
{
  if (vertexes == polygons.points.size())
  {
    res += getArea(polygons.points);
  }
  return res;
}

double novokhatskiy::commands::doAccumulateEvenArea(double res, const Polygon& p)
{
  if (isEven(p))
  {
    res += getArea(p.points);
  }
  return res;
}

double novokhatskiy::commands::doAccumulateOddArea(double res, const Polygon& p)
{
  if (isOdd(p))
  {
    res += getArea(p.points);
  }
  return res;
}

double novokhatskiy::commands::doAccumulateMeanArea(
  double res, const Polygon& p, const std::vector< Polygon >& polygons
)
{
  if (p.points.size() < 1)
  {
    throw std::logic_error("");
  }
  return res + (getArea(p.points) / polygons.size());
}

void novokhatskiy::commands::commandMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string argument;
  in >> argument;
  std::function< double(double, const Polygon&) > area;
  std::function< size_t(size_t, const Polygon&) > vertexes;
  size_t maxSize = std::numeric_limits< size_t >::max();
  novokhatskiy::StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  using namespace std::placeholders;
  if (argument == "AREA")
  {
    area = std::bind(AccumulateMinArea, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
  }
  else if (argument == "VERTEXES")
  {
    vertexes = std::bind(AccumulateMinVertexes, maxSize, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void novokhatskiy::commands::commandMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string argument;
  in >> argument;
  std::function< double(double, const Polygon&) > area;
  std::function< size_t(size_t, const Polygon&) > vertexes;
  novokhatskiy::StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  using namespace std::placeholders;
  if (argument == "AREA")
  {
    area = std::bind(AccumulateMaxArea, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
  }
  else if (argument == "VERTEXES")
  {
    vertexes = std::bind(AccumulateMaxVertexes, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

double novokhatskiy::commands::AccumulateMaxArea(double res, const Polygon& p)
{
  return std::max(res, getArea(p.points));
}

double novokhatskiy::commands::AccumulateMinArea(double res, const Polygon& p)
{
  return std::min(res, getArea(p.points));
}

size_t novokhatskiy::commands::AccumulateMinVertexes(size_t size, const Polygon& p)
{
  return std::min(size, p.points.size());
}

size_t novokhatskiy::commands::AccumulateMaxVertexes(size_t size, const Polygon& p)
{
  return std::max(size, p.points.size());
}

void novokhatskiy::commands::commandCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::function< bool(const Polygon&) > result;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else
  {
    size_t vertexes = {};
    vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    result = std::bind(areVertexes, _1, vertexes);
    out << std::count_if(polygons.cbegin(), polygons.cend(), result);
  }
}

bool novokhatskiy::commands::isEven(const Polygon& p)
{
  return (p.points.size() % 2 == 0);
}

bool novokhatskiy::commands::isOdd(const Polygon& p)
{
  return !(p.points.size() % 2 == 0);
}

bool novokhatskiy::commands::areVertexes(const Polygon& p, size_t vertexes)
{
  return (p.points.size() == vertexes);
}

bool novokhatskiy::commands::checkPerms(Polygon& p1, Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::is_permutation(p1.points.begin(), p1.points.end(), p2.points.begin());
}

void novokhatskiy::commands::commandPerms(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon inputPolygon;
  in >> inputPolygon;
  if (inputPolygon.points.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  if (inputPolygon.points.size() < 3)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << std::count_if(polygons.begin(), polygons.end(), std::bind(checkPerms, std::placeholders::_1, inputPolygon));
}

bool novokhatskiy::commands::checkRectangle(const Polygon& p)
{
  if (p.points.size() != 4)
  {
    return false;
  }
  RectangleVector firstSide(p.points[0], p.points[1]);
  RectangleVector secondSide(p.points[1], p.points[2]);
  RectangleVector thirdSide(p.points[2], p.points[3]);
  RectangleVector fourthSide(p.points[0], p.points[3]);
  return (firstSide.cos(secondSide) == 0) && (secondSide.cos(thirdSide) == 0) && (thirdSide.cos(fourthSide) == 0);
}

void novokhatskiy::commands::commandRectangle(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(), checkRectangle);
}
