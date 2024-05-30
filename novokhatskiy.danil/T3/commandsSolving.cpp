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

bool isEven(const novokhatskiy::Polygon& p)
{
  return (p.points.size() % 2 == 0);
}

bool isOdd(const novokhatskiy::Polygon& p)
{
  return !(p.points.size() % 2 == 0);
}

bool checkSize(const novokhatskiy::Polygon& p, size_t size)
{
  return p.points.size() == size;
}

double accumulateMaxArea(double res, const novokhatskiy::Polygon& p)
{
  return std::max(res, getArea(p));
}

double accumulateMinArea(double res, const novokhatskiy::Polygon& p)
{
  return std::min(res, getArea(p));
}

size_t accumulateMinVertexes(size_t size, const novokhatskiy::Polygon& p)
{
  return std::min(size, p.points.size());
}

size_t accumulateMaxVertexes(size_t size, const novokhatskiy::Polygon& p)
{
  return std::max(size, p.points.size());
}

struct RectangleVector
{
  novokhatskiy::Point vertexes;
  RectangleVector(const novokhatskiy::Point& p1, const novokhatskiy::Point& p2);
  double operator*(const RectangleVector& p1);
  double getLength() const;
  double cos(const RectangleVector& p1);
};

double doAccumulateNumOfVertexesArea(double res, size_t vertexes, const novokhatskiy::Polygon& polygons)
{
  if (vertexes == polygons.points.size())
  {
    res += getArea(polygons);
  }
  return res;
}

double doAccumulateEvenArea(double res, const novokhatskiy::Polygon& p)
{
  if (isEven(p))
  {
    res += getArea(p);
  }
  return res;
}

double doAccumulateOddArea(double res, const novokhatskiy::Polygon& p)
{
  if (isOdd(p))
  {
    res += getArea(p);
  }
  return res;
}

double doAccumulateMeanArea(
  double res, const novokhatskiy::Polygon& p, const std::vector< novokhatskiy::Polygon >& polygons
)
{
  if (p.points.size() < 1)
  {
    throw std::logic_error("");
  }
  return res + (getArea(p) / polygons.size());
}

RectangleVector::RectangleVector(const novokhatskiy::Point& p1, const novokhatskiy::Point& p2):
  vertexes(novokhatskiy::Point{ p2.x - p1.x, p2.y - p1.y })
{}

double RectangleVector::operator*(const RectangleVector& p1)
{
  return (vertexes.x * p1.vertexes.x) + (vertexes.y * p1.vertexes.y);
}

double RectangleVector::getLength() const
{
  return std::sqrt(std::pow(vertexes.x, 2) + std::pow(vertexes.y, 2));
}

double RectangleVector::cos(const RectangleVector& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}

bool areVertexes(const novokhatskiy::Polygon& p, size_t vertexes)
{
  return (p.points.size() == vertexes);
}

bool checkRectangle(const novokhatskiy::Polygon& p)
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

void novokhatskiy::commands::getAreaCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  std::vector< Polygon > tmp;
  tmp.reserve(polygons.size());
  using namespace std::placeholders;
  if (arg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), isEven);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), isOdd);
  }
  else if (arg == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp));
  }
  else
  {
    size_t numOfVertexes = {};
    numOfVertexes = std::stoull(arg);
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::function< bool(const Polygon&) > func = std::bind(checkSize, std::placeholders::_1, numOfVertexes);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tmp), func);
  }
  tmp.shrink_to_fit();
  std::vector< double > areas;
  std::transform(tmp.cbegin(), tmp.cend(), std::back_inserter(areas), getArea);
  double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (arg == "MEAN")
  {
    res /= polygons.size();
  }
  novokhatskiy::StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << res;
}

void novokhatskiy::commands::getMinCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
    area = std::bind(accumulateMinArea, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
  }
  else if (argument == "VERTEXES")
  {
    vertexes = std::bind(accumulateMinVertexes, maxSize, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void novokhatskiy::commands::getMaxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
    area = std::bind(accumulateMaxArea, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
  }
  else if (argument == "VERTEXES")
  {
    vertexes = std::bind(accumulateMaxVertexes, _1, _2);
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0, vertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void novokhatskiy::commands::getCountCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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

bool checkPerms(const novokhatskiy::Polygon& p1, const novokhatskiy::Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::is_permutation(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin());
}

void novokhatskiy::commands::getPermsCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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

void novokhatskiy::commands::getRectangleCmd(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(), checkRectangle);
}
