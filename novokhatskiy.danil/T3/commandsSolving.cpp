#include "commandsSolving.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <limits>
#include <iomanip>
#include <cmath>
#include <string>
#include <numeric>
#include <functional>
#include "StreamGuard.hpp"
#include "polygon.hpp"

void novokhatskiy::commandArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  std::function< double (double, const novokhatskiy::Polygon&) > area;
  std::function< double(double, const novokhatskiy::Polygon&, const std::vector< Polygon >&) > mean;
  using namespace std::placeholders;
  novokhatskiy::StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  if (arg == "EVEN")
  {
    area = std::bind(novokhatskiy::AccumulateEvenOrOddArea, _1, _2, true);
  }
  else if (arg == "ODD")
  {
    area = std::bind(novokhatskiy::AccumulateEvenOrOddArea, _1, _2, false);
    //AccumulateEvenOrOddArea(polygons.front(), out, false);
  }
  else if (arg == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    mean = std::bind(novokhatskiy::AccumulateMeanArea, _1, _2, polygons);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, mean);
  }
  else
  {
    size_t numOfVertexes = {};
    try
    {
      numOfVertexes = std::stoull(arg);
    }
    catch (const std::invalid_argument&)
    {
      throw;
    }
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    area = std::bind(AccumulateNumOfVertexesArea, _1, numOfVertexes, _2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
}

double novokhatskiy::AccumulateNumOfVertexesArea(double res, size_t vertexes, const Polygon& polygons)
{
  if (vertexes == polygons.points.size())
  {
    res += polygons.getArea();
  }
  return res;
}

double novokhatskiy::AccumulateEvenOrOddArea(double res, const Polygon& p, bool isEven)
{
  if (isEven == (p.points.size() % 2 == 0))
  {
    res += p.getArea();
  }
  return res;
}

double novokhatskiy::AccumulateMeanArea(double res, const Polygon& p, const std::vector< Polygon >& polygons)
{
  if (p.points.size() < 1)
  {
    throw std::logic_error("To accumulate mean area, we need to have more than 1 shape"); // заменить на invalid_argument
  }
  return res + (p.getArea() / polygons.size());
}

void novokhatskiy::commandMaxOrMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out, bool isMax)
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
    area = std::bind(AccumulateMinOrMaxArea, _1, _2, isMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
  }
  else if (argument == "VERTEXES")
  {
    vertexes = std::bind(AccumulateMinOrMaxVertexes, _1, _2, isMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

double novokhatskiy::AccumulateMinOrMaxArea(double res, const Polygon& p, bool isMax)
{
  if (isMax)
  {
    return std::max(res, p.getArea());
  }
  else
  {
    return std::min(res, p.getArea());
  }
}

size_t novokhatskiy::AccumulateMinOrMaxVertexes(size_t size, const Polygon& p, bool isMax)
{
  if (isMax)
  {
    return std::max(size, p.points.size());
  }
  else
  {
    return std::min(std::numeric_limits< size_t >::max(), p.points.size());
  }
}

void novokhatskiy::commandCountEvenOddVertexes(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::function< bool(const Polygon&) > result;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    result = std::bind(checkEvenOrOdd, _1, true);
    out << std::count_if(polygons.cbegin(), polygons.cend(), result);
  }
  else if (argument == "ODD")
  {
    result = std::bind(checkEvenOrOdd, _1, false);
    out << std::count_if(polygons.cbegin(), polygons.cend(), result);
  }
  else
  {
    size_t vertexes = {};
    try
    {
      vertexes = std::stoull(argument);
      if (vertexes < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      result = std::bind(checkNumbersOfVertexes, _1, vertexes);
      out << std::count_if(polygons.cbegin(), polygons.cend(), result);
    }
    catch (const std::invalid_argument&)
    {
      throw;
    }
  }
}

bool novokhatskiy::checkEvenOrOdd(const Polygon& p, bool isEven)
{
  return (isEven == (p.points.size() % 2 == 0));
}

bool novokhatskiy::checkNumbersOfVertexes(const Polygon& p, size_t vertexes)
{
  return (p.points.size() == vertexes);
}

bool novokhatskiy::checkPerms(Polygon& p1, Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  std::sort(p1.points.begin(), p1.points.end());
  return (p1.points == p2.points);
}

void novokhatskiy::commandPerms(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  Polygon inputPolygon;
  in >> inputPolygon;
  std::vector< Polygon > data = polygons;
  if (inputPolygon.points.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND");
  }
  if (inputPolygon.points.size() < 3)
  {
    throw std::invalid_argument("<INVALID COMMAND");
  }
  using namespace std::placeholders;
  std::sort(inputPolygon.points.begin(), inputPolygon.points.end());
  out << std::count_if(data.begin(), data.end(), std::bind(checkPerms, _1, inputPolygon));
}

bool novokhatskiy::checkRectangle(const Polygon& p)
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

void novokhatskiy::commandRectangle(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(), checkRectangle);
}
