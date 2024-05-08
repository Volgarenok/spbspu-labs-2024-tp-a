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
  namespace commands
  {
    enum class AreaCmdType
    {
      Even,
      Odd,
      Mean,
      CurrVertex
    };

    enum class MaxMinCmdType
    {
      Area,
      Vertexes
    };

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

    double calcArea(AreaCmdType, size_t vertexes, size_t polygons, double, const Polygon &);
    std::pair < size_t, size_t > findMax(const Polygon &, std::pair < size_t, size_t >, const Polygon &);
    std::pair < Point, Point > findFrame(std::pair < Point, Point >, const Polygon &);
    bool maxMinPredicate(MaxMinCmdType, const Polygon &, const Polygon &);
    bool countPredicate(CountCmdType, size_t, const Polygon &);
    bool comparePointCoord(CoordType, const Point &, const Point &);
    bool isInFrame(std::pair < Point, Point >, const Point &);
  }

  bool operator==(const Point &, const Point &);
}

void zhalilov::commands::area(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string argument;
  in >> argument;
  std::function < double(double, const Polygon &) > areaFunc;
  if (argument == "EVEN")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Even, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "ODD")
  {
    areaFunc = std::bind(calcArea, AreaCmdType::Odd, 0, 0, std::placeholders::_1, std::placeholders::_2);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Area calcing: no polygons");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::Mean, 0, polygons.size(), std::placeholders::_1, std::placeholders::_2);
  }
  else
  {
    size_t vertexes = std::stoull(argument);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Area calcing: vertexes < 3");
    }
    areaFunc = std::bind(calcArea, AreaCmdType::CurrVertex, vertexes, 0, std::placeholders::_1, std::placeholders::_2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaFunc);
}

void zhalilov::commands::max(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding max: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &, const Polygon &) > predicate;
  if (argument == "AREA")
  {
    predicate = std::bind(maxMinPredicate, MaxMinCmdType::Area, std::placeholders::_1, std::placeholders::_2);
    double area = getPolygonArea(*std::max_element(polygons.cbegin(), polygons.cend(), predicate));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    predicate = std::bind(maxMinPredicate, MaxMinCmdType::Vertexes, std::placeholders::_1, std::placeholders::_2);
    size_t vertexes = std::max_element(polygons.cbegin(), polygons.cend(), predicate)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding max: invalid arg");
  }
}

void zhalilov::commands::min(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Finding min: no polygons");
  }

  std::string argument;
  in >> argument;
  std::function < bool(const Polygon &, const Polygon &) > predicate;
  if (argument == "AREA")
  {
    predicate = std::bind(maxMinPredicate, MaxMinCmdType::Area, std::placeholders::_1, std::placeholders::_2);
    double area = getPolygonArea(*std::min_element(polygons.cbegin(), polygons.cend(), predicate));
    out << area;
  }
  else if (argument == "VERTEXES")
  {
    predicate = std::bind(maxMinPredicate, MaxMinCmdType::Vertexes, std::placeholders::_1, std::placeholders::_2);
    size_t vertexes = std::min_element(polygons.cbegin(), polygons.cend(), predicate)->points.size();
    out << vertexes;
  }
  else
  {
    throw std::invalid_argument("Finding min: invalid arg");
  }
}

void zhalilov::commands::count(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
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

void zhalilov::commands::maxSeq(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon polyToFind;
  in >> polyToFind;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Finding max seq: invalid polygon");
  }

  std::function < std::pair < size_t, size_t >(std::pair < size_t, size_t >, const Polygon &) > seqFunc;
  seqFunc = std::bind(findMax, std::cref(polyToFind), std::placeholders::_1, std::placeholders::_2);
  out << std::accumulate(polygons.cbegin(), polygons.cend(), std::make_pair(0, 0), seqFunc).first;
}

void zhalilov::commands::inFrame(const std::vector < Polygon > &polygons, std::istream &in, std::ostream &out)
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

double zhalilov::commands::calcArea(AreaCmdType type, size_t vertexes, size_t polygons, double res, const Polygon &polygon)
{
  double area = 0.0;
  if (type == AreaCmdType::Even)
  {
    if (polygon.points.size() % 2 == 0)
    {
      area = getPolygonArea(polygon);
    }
  }
  else if (type == AreaCmdType::Odd)
  {
    if (polygon.points.size() % 2 != 0)
    {
      area = getPolygonArea(polygon);
    }
  }
  else if (type == AreaCmdType::Mean)
  {
    area = getPolygonArea(polygon) / polygons;
  }
  else
  {
    if (polygon.points.size() == vertexes)
    {
      area = getPolygonArea(polygon);
    }
  }
  return res + std::abs(area);
}

std::pair < size_t, size_t > zhalilov::commands::findMax(const Polygon &toFind, std::pair < size_t, size_t > res, const Polygon &polygon)
{
  if (toFind.points == polygon.points)
  {
    res.second++;
    if (res.first < res.second)
    {
      res.first = res.second;
    }
  }
  res.second = 0;
  return res;
}

std::pair < zhalilov::Point, zhalilov::Point > zhalilov::commands::findFrame(std::pair < Point, Point > res, const Polygon &polygon)
{
  auto findX = std::bind(comparePointCoord, CoordType::Abcyss, std::placeholders::_1, std::placeholders::_2);
  auto findY = std::bind(comparePointCoord, CoordType::Ordinate, std::placeholders::_1, std::placeholders::_2);
  int maxX = std::max_element(polygon.points.cbegin(), polygon.points.cend(), findX)->x;
  int minX = std::min_element(polygon.points.cbegin(), polygon.points.cend(), findX)->x;
  int maxY = std::max_element(polygon.points.cbegin(), polygon.points.cend(), findY)->y;
  int minY = std::min_element(polygon.points.cbegin(), polygon.points.cend(), findX)->y;
  res.second.x = maxX > res.second.x ? maxX : res.second.x;
  res.second.y = maxY > res.second.y ? maxY : res.second.y;
  res.first.x = minX < res.first.x ? minX : res.first.x;
  res.first.y = minY < res.first.y ? minY : res.first.y;
  return res;
}

bool zhalilov::commands::maxMinPredicate(MaxMinCmdType type, const Polygon &first, const Polygon &second)
{
  if (type == MaxMinCmdType::Area)
  {
    return getPolygonArea(first) < getPolygonArea(second);
  }
  return first.points.size() < second.points.size();
}

bool zhalilov::commands::countPredicate(CountCmdType type, size_t vertexes, const Polygon &polygon)
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

bool zhalilov::commands::comparePointCoord(CoordType type, const Point &first, const Point &second)
{
  if (type == CoordType::Abcyss)
  {
    return first.x < second.x;
  }
  return first.y < second.y;
}

bool zhalilov::commands::isInFrame(std::pair < Point, Point > frame, const Point &point)
{
  bool condition = frame.first.x <= point.x && frame.second.x >= point.x;
  condition = condition && frame.first.y <= point.y && frame.second.y >= point.y;
  return condition;
}

bool zhalilov::operator==(const Point &first, const Point &second)
{
  return first.x == second.x && first.y == second.y;
}
