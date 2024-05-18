#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>

#include "geometry.hpp"
#include "getPolygonArea.hpp"
#include "inputShapes.hpp"
#include "pointCompare.hpp"

namespace zhalilov
{
  enum class CountCmdType
  {
    Even,
    Odd,
    CurrVertex
  };

  enum class CoordType
  {
    Abcyss,
    Ordinate
  };

  struct SeqInfoFinder
  {
    SeqInfoFinder();

    size_t operator()(const Polygon &, const Polygon &);

  private:
    size_t currSeq_;
  };

  double calcAreaEven(const Polygon &);
  double calcAreaOdd(const Polygon &);
  double calcAreaMean(size_t, const Polygon &);
  double calcAreaVertexes(size_t, const Polygon &);

  std::pair < Point, Point > findFrame(std::pair < Point, Point >, const Polygon &);
  bool areaCompare(const Polygon &, const Polygon &);
  bool vertexesCompare(const Polygon &, const Polygon &);
  bool countPredicate(CountCmdType, size_t, const Polygon &);
  bool comparePointCoord(CoordType, const Point &, const Point &);
  bool isInFrame(std::pair < Point, Point >, const Point &);
}

void zhalilov::area(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < double(const Polygon &) > areaFunc;
  if (argument == "EVEN")
  {
    areaFunc = calcAreaEven;
  }
  else if (argument == "ODD")
  {
    areaFunc = calcAreaOdd;
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    areaFunc = std::bind(calcAreaMean, polygons.size(), std::placeholders::_1);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    areaFunc = std::bind(calcAreaVertexes, vertexes, std::placeholders::_1);
  }
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), areaFunc);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void zhalilov::max(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &, const Polygon &) > comparer;
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

void zhalilov::min(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding min: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &, const Polygon &) > comparer;
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

void zhalilov::count(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &) > predicate;
  if (argument == "EVEN")
  {
    predicate = std::bind(countPredicate, CountCmdType::Even, 0, std::placeholders::_1);
  }
  else if (argument == "ODD")
  {
    predicate = std::bind(countPredicate, CountCmdType::Odd, 0, std::placeholders::_1);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    predicate = std::bind(countPredicate, CountCmdType::CurrVertex, vertexes, std::placeholders::_1);
  }
  out << std::count_if(polygons.cbegin(), polygons.cend(), predicate);
}

void zhalilov::maxSeq(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polyToFind;
  in >> polyToFind;
  if (in)
  {
    std::string temp;
    in >> temp;
    if (!temp.empty())
    {
      throw std::invalid_argument("Finding max seq: invalid polygon");
    }
  }
  else
  {
    throw std::invalid_argument("Finding max seq: invalid polygon");
  }

  if (polygons.size() == 1)
  {
    out << 0;
    return;
  }

  std::vector < size_t > seqInfo(polygons.size());
  SeqInfoFinder seq;
  auto seqInfoFind = std::bind(&SeqInfoFinder::operator(), &seq, polyToFind, std::placeholders::_1);
  std::transform(polygons.cbegin(), polygons.cend(), seqInfo.begin(), seqInfoFind);
  out << *std::max_element(seqInfo.cbegin(), seqInfo.cend());
}

void zhalilov::inFrame(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polyToCompare;
  in >> polyToCompare;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Is in frame: invalid polygon");
  }

  std::pair < Point, Point > initFrame = { { 0, 0 }, { 0, 0 } };
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

zhalilov::SeqInfoFinder::SeqInfoFinder():
  currSeq_(0)
{}

size_t zhalilov::SeqInfoFinder::operator()(const Polygon &classic, const Polygon &toCompare)
{
  if (classic.points == toCompare.points)
  {
    currSeq_++;
  }
  else
  {
    currSeq_ = 0;
  }
  return currSeq_;
}

double zhalilov::calcAreaEven(const Polygon &polygon)
{
  double area = 0.0;
  if (polygon.points.size() % 2 == 0)
  {
    area = getPolygonArea(polygon);
  }
  return area;
}

double zhalilov::calcAreaOdd(const Polygon &polygon)
{
  double area = 0.0;
  if (polygon.points.size() % 2 != 0)
  {
    area = getPolygonArea(polygon);
  }
  return area;
}

double zhalilov::calcAreaMean(size_t polygons, const Polygon &polygon)
{
  return getPolygonArea(polygon) / polygons;
}

double zhalilov::calcAreaVertexes(size_t vertexes, const Polygon &polygon)
{
  double area = 0.0;
  if (polygon.points.size() == vertexes)
  {
    area = getPolygonArea(polygon);
  }
  return area;
}

std::pair < zhalilov::Point, zhalilov::Point > zhalilov::findFrame(std::pair < Point, Point > res, const Polygon &polygon)
{
  auto findX = std::bind(comparePointCoord, CoordType::Abcyss, std::placeholders::_1, std::placeholders::_2);
  auto findY = std::bind(comparePointCoord, CoordType::Ordinate, std::placeholders::_1, std::placeholders::_2);
  auto xPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), findX);
  auto yPair = std::minmax_element(polygon.points.cbegin(), polygon.points.cend(), findY);
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

bool zhalilov::countPredicate(CountCmdType type, size_t vertexes, const Polygon &polygon)
{
  bool toReturn = false;
  if (type == CountCmdType::Even)
  {
    toReturn = polygon.points.size() % 2 == 0;
  }
  else if (type == CountCmdType::Odd)
  {
    toReturn = polygon.points.size() % 2 != 0;
  }
  else
  {
    toReturn = polygon.points.size() == vertexes;
  }
  return toReturn;
}

bool zhalilov::comparePointCoord(CoordType type, const Point &first, const Point &second)
{
  if (type == CoordType::Abcyss)
  {
    return first.x < second.x;
  }
  return first.y < second.y;
}

bool zhalilov::isInFrame(std::pair < Point, Point > frame, const Point &point)
{
  bool condition = frame.first.x <= point.x && frame.second.x >= point.x;
  condition = condition && frame.first.y <= point.y && frame.second.y >= point.y;
  return condition;
}
