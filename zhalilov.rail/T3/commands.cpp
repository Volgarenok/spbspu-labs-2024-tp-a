#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>

#include "geometry.hpp"
#include "getPolygonArea.hpp"
#include "inputShapes.hpp"

namespace zhalilov
{
  bool isEven(const Polygon &);
  bool isOdd(const Polygon &);
  bool isCurrVertexes(size_t, const Polygon &);
  double calcAreaDefault(const Polygon &);
  double calcAreaMean(size_t, const Polygon &);

  bool countEven(const Polygon &);
  bool countOdd(const Polygon &);
  bool countVertex(size_t, const Polygon &);

  std::pair< Point, Point > findFrame(std::pair< Point, Point >, const Polygon &);
  bool areaCompare(const Polygon &, const Polygon &);
  bool vertexesCompare(const Polygon &, const Polygon &);
  bool compareAbcyss(const Point &, const Point &);
  bool compareOrdinate(const Point &, const Point &);
  bool isInFrame(std::pair< Point, Point >, const Point &);

  bool seqTransformer(const std::vector< Polygon > &polygons, const Polygon &toFind, size_t n);

  bool operator==(const Point &first, const Point &second);
  bool operator==(const Polygon &first, const Polygon &second);
}

void zhalilov::area(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::vector< Polygon > polygonsToCount;
  std::function< double(const Polygon &) > calcAreaFunc = calcAreaDefault;
  if (argument == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount));
    calcAreaFunc = std::bind(calcAreaMean, polygons.size(), std::placeholders::_1);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    auto vertexPred = std::bind(isCurrVertexes, vertexes, std::placeholders::_1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), vertexPred);
  }
  std::vector< double > areas;
  std::transform(polygonsToCount.cbegin(), polygonsToCount.cend(), std::back_inserter(areas), calcAreaFunc);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void zhalilov::max(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function< bool(const Polygon &, const Polygon &) > comparer;
  if (argument == "AREA")
  {
    comparer = areaCompare;
    double area = getPolygonArea(*std::max_element(polygons.cbegin(), polygons.cend(), comparer));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    comparer = vertexesCompare;
    size_t vertexes = std::max_element(polygons.cbegin(), polygons.cend(), comparer)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding max: invalid arg");
  }
}

void zhalilov::min(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding min: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function< bool(const Polygon &, const Polygon &) > comparer;
  if (argument == "AREA")
  {
    comparer = areaCompare;
    double area = getPolygonArea(*std::min_element(polygons.cbegin(), polygons.cend(), comparer));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    comparer = vertexesCompare;
    size_t vertexes = std::min_element(polygons.cbegin(), polygons.cend(), comparer)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding min: invalid arg");
  }
}

void zhalilov::count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function< bool(const Polygon &) > predicate;
  if (argument == "EVEN")
  {
    predicate = countEven;
  }
  else if (argument == "ODD")
  {
    predicate = countOdd;
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    predicate = std::bind(countVertex, vertexes, std::placeholders::_1);
  }
  out << std::count_if(polygons.cbegin(), polygons.cend(), predicate);
}

void zhalilov::maxSeq(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polyToFind;
  in >> polyToFind;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Finding max seq: invalid polygon");
  }

  if (polygons.size() == 1)
  {
    out << 0;
    return;
  }

  std::vector< size_t > naturals(polygons.size());
  std::iota(naturals.begin(), naturals.end(), 1);
  auto transformFunc = std::bind(seqTransformer, std::cref(polygons), std::cref(polyToFind), std::placeholders::_1);
  std::vector< bool > seqInfo;
  std::transform(naturals.cbegin(), naturals.cend(), std::back_inserter(seqInfo), transformFunc);
  out << std::count(seqInfo.cbegin(), seqInfo.cend(), true);
}

void zhalilov::inFrame(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polyToCompare;
  in >> polyToCompare;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Is in frame: invalid polygon");
  }

  std::pair< Point, Point > initFrame = { { 0, 0 }, { 0, 0 } };
  auto frame = std::accumulate(polygons.cbegin(), polygons.cend(), initFrame, findFrame);
  auto predicate = std::bind(isInFrame, frame, std::placeholders::_1);
  size_t howManyInFrame = std::count_if(polyToCompare.points.cbegin(), polyToCompare.points.cend(), predicate);
  if (howManyInFrame == polyToCompare.points.size())
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

bool zhalilov::isEven(const Polygon &polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zhalilov::isOdd(const Polygon &polygon)
{
  return polygon.points.size() % 2 != 0;
}

double zhalilov::calcAreaMean(size_t polygons, const Polygon &polygon)
{
  return getPolygonArea(polygon) / polygons;
}

bool zhalilov::isCurrVertexes(size_t vertexes, const Polygon &polygon)
{
  return polygon.points.size() == vertexes;
}

double zhalilov::calcAreaDefault(const Polygon &polygon)
{
  return getPolygonArea(polygon);
}

bool zhalilov::countEven(const Polygon &polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zhalilov::countOdd(const Polygon &polygon)
{
  return polygon.points.size() % 2 != 0;;
}

bool zhalilov::countVertex(size_t vertexes, const Polygon &polygon)
{
  return polygon.points.size() == vertexes;
}

std::pair< zhalilov::Point, zhalilov::Point > zhalilov::findFrame(std::pair< Point, Point > res, const Polygon &polygon)
{
  auto xPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compareAbcyss);
  auto yPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), compareOrdinate);
  res.second.x = xPair.second->x > res.second.x ? xPair.second->x : res.second.x;
  res.second.y = yPair.second->y > res.second.y ? yPair.second->y : res.second.y;
  res.first.x = xPair.first->x < res.first.x ? xPair.first->x : res.first.x;
  res.first.y = yPair.first->y < res.first.y ? yPair.first->y : res.first.y;
  return res;
}

bool zhalilov::areaCompare(const Polygon &first, const Polygon &second)
{
  return getPolygonArea(first) < getPolygonArea(second);
}

bool zhalilov::vertexesCompare(const Polygon &first, const Polygon &second)
{
  return first.points.size() < second.points.size();
}

bool zhalilov::compareAbcyss(const Point &first, const Point &second)
{
  return first.x < second.x;
}

bool zhalilov::compareOrdinate(const Point &first, const Point &second)
{
  return first.y < second.y;
}

bool zhalilov::isInFrame(std::pair< Point, Point > frame, const Point &point)
{
  bool condition = frame.first.x <= point.x && frame.second.x >= point.x;
  condition = condition && frame.first.y <= point.y && frame.second.y >= point.y;
  return condition;
}

bool zhalilov::seqTransformer(const std::vector< Polygon > &polygons, const Polygon &toFind, size_t n)
{
  return std::search_n(polygons.cbegin(), polygons.cend(), n, toFind) != polygons.cend();
}

bool zhalilov::operator==(const Point &first, const Point &second)
{
  return first.x == second.x && first.y == second.y;
}

bool zhalilov::operator==(const Polygon &first, const Polygon &second)
{
  return first.points == second.points;
}
