#include "commandsSolving.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <limits>
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
    area = std::bind(novokhatskiy::AccumulateMeanArea, _1, _2);
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

double novokhatskiy::AccumulateMeanArea(double res, const Polygon& p)
{
  if (p.points.size() < 1)
  {
    throw std::logic_error("To accumulate mean area, we need to have more than 1 shape"); // заменить на invalid_argument
  }
  return res + (p.getArea() / p.points.size());
}

void novokhatskiy::commandMaxOrMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out, bool isMax)
{
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
  else
  {
    vertexes = std::bind(AccumulateMinOrMaxVertexes, _1, _2, isMax);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
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
