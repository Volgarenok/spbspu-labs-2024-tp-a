#include "commands.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <numeric>
#include <map>
#include <iomanip>

void vyzhanov::area(const std::vector< Polygon >& polygons,
  std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  std::vector< Polygon > temp;
  std::function< double(const Polygon&) > functor = getPolygonArea;
  std::map< std::string, std::function< bool(const Polygon&) > > predicate;
  std::function< bool(const Polygon&) > pred;

  if (arg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(),
      std::back_inserter(temp), isEven);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(),
      std::back_inserter(temp), isOdd);
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    using namespace std::placeholders;
    functor = std::bind(getMeanArea, 0.0, _1, polygons.size());
    temp = polygons;
  }
  else
  {
    size_t numVertexes = std::stoull(arg);
    if (numVertexes < 3)
    {
      throw std::invalid_argument("Need more three vertexes");
    }
    using namespace std::placeholders;
    pred = predicate.at(arg);
    pred = std::bind(isNumVertexes, _1, numVertexes);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(temp), pred);
    std::vector< double > areas(polygons.size());
    std::transform(temp.cbegin(), temp.cend(), std::back_inserter(areas), functor);
    output << std::setprecision(1) << std::fixed;
    output << std::accumulate(areas.begin(), areas.end(), 0.0);
  }
}

void vyzhanov::max(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }
  std::string arg;
  input >> arg;
  if (arg == "AREA")
  {
    auto result = std::max_element(polygons.cbegin(), polygons.cend(), compareArea);
    output << getPolygonArea(*result) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    auto result = std::max_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    output << (*result).points.size() << "\n";
  }
}

void vyzhanov::min(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }
  std::string arg;
  input >> arg;
  if (arg == "AREA")
  {
    auto result = std::min_element(polygons.cbegin(), polygons.cend(), compareArea);
    output << getPolygonArea(*result) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    auto result = std::min_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    output << (*result).points.size() << "\n";
  }
}

void vyzhanov::count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg = "";
  input >> arg;
  std::vector< Polygon > result;
  if (arg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(result), isEven);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(result), isOdd);
  }
  else
  {
    size_t num = std::stoll(arg);
    if (num < 3)
    {
      throw std::out_of_range("Area calcing: vertexes < 3");
    }
    auto pred = std::bind(isNumVertexes, std::placeholders::_1, num);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(result), pred);
  }
  output << result.size() << "\n";
}

void vyzhanov::lessarea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon compare;
  std::vector< Polygon > temp;
  input >> compare;
  if (!input || input.peek() != '\n')
  {
    throw std::out_of_range("bad input");
  }
  auto pred = std::bind(compareArea, std::placeholders::_1, compare);
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(temp), pred);
  output << temp.size() << "\n";
}

void vyzhanov::reacts(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  size_t rectanglesCount = std::count_if(polygons.begin(), polygons.end(), isRectangle);
  output << rectanglesCount;
}

void vyzhanov::rmecho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon polygon;
  input >> polygon;
  if (!input || input.peek() != '\n')
  {
    throw std::invalid_argument("bad input");
  }
  size_t counter = 0;
  std::vector<Polygon> res;
  auto pred = std::bind(areSame, std::placeholders::_1,
    std::cref(polygon), std::ref(counter));
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(res), pred);
  output << polygons.size() - res.size() << '\n';
  polygons = std::move(res);
}

bool vyzhanov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool vyzhanov::isOdd(const Polygon& polygon)
{
  return polygon.points.size() % 2 != 0;
}

double vyzhanov::getMeanArea(double currArea, const Polygon& polygon, size_t count)
{
  return currArea + getPolygonArea(polygon) / count;
}

double vyzhanov::isNumVertexes(const Polygon& polygon, size_t numVertexes)
{
  return numVertexes == polygon.points.size();
}
bool vyzhanov::compareArea(const Polygon& polygon1, const Polygon& polygon2)
{
  return getPolygonArea(polygon1) < getPolygonArea(polygon2);
}

bool vyzhanov::compareVertexes(const Polygon& polygon1, const Polygon& polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

bool vyzhanov::isRectangle(const Polygon& polygon)
{
  if (polygon.points.size() != 4)
  {
    return false;
  }
  RectangleVector a(polygon.points[0], polygon.points[1]);
  RectangleVector b(polygon.points[1], polygon.points[2]);
  RectangleVector c(polygon.points[2], polygon.points[3]);
  RectangleVector d(polygon.points[0], polygon.points[3]);
  return (a.cos(b) == 0) && (b.cos(c) == 0) && (c.cos(d) == 0);
}

vyzhanov::RectangleVector::RectangleVector(const Point& p1, const Point& p2):
  vertexes(Point{ p2.x - p1.x, p2.y - p1.y })
{}

double vyzhanov::RectangleVector::operator*(const RectangleVector& p1)
{
  return (vertexes.x * p1.vertexes.x) + (vertexes.y * p1.vertexes.y);
}

double vyzhanov::RectangleVector::getLength() const
{
  return std::hypot(vertexes.x, vertexes.y);
}

double vyzhanov::RectangleVector::cos(const RectangleVector& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}

bool vyzhanov::areSame(const Polygon& src, const Polygon& p, size_t& counter)
{
  if (src == p)
  {
    ++counter;
    if (counter > 1)
    {
      counter = 0;
      return false;
    }
  }
  return true;
}
