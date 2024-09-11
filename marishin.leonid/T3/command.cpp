#include "command.hpp"
#include <functional>
#include <numeric>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <map>
#include "polygon.hpp"

bool isEven(const marishin::Polygon& polygon)
{
  return (polygon.points.size() > 2) && (polygon.points.size() % 2 == 0);
}

bool isOdd(const marishin::Polygon& polygon)
{
  return !isEven(polygon);
}

bool isProperSize(const marishin::Polygon& polygon, size_t number)
{
  return (polygon.points.size() == number);
}

bool comparePoints(const marishin::Polygon& first, const marishin::Polygon& second)
{
  return (first.points.size() < second.points.size());
}

bool compareArea(const marishin::Polygon& first, const marishin::Polygon& second)
{
  return (getPolygonArea(first) < getPolygonArea(second));
}

template < class UnaryPredicate >
double getSumArea(const std::vector< marishin::Polygon >& polygon, UnaryPredicate P)
{
  std::vector< marishin::Polygon > selected;
  std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(selected), P);
  std::vector< double > area;
  std::transform(selected.cbegin(), selected.cend(), std::back_inserter(area), marishin::getPolygonArea);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

double doAreaNum(const std::vector< marishin::Polygon >& polygon, size_t numOfVertices)
{
  return getSumArea(polygon, std::bind(isProperSize, std::placeholders::_1, numOfVertices));
}

double doAreaEven(const std::vector< marishin::Polygon >& polygons)
{
  return getSumArea(polygons, isEven);
}

double doAreaOdd(const std::vector< marishin::Polygon >& polygons)
{
  return getSumArea(polygons, isOdd);
}

double doAreaMean(const std::vector< marishin::Polygon >& polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  std::vector< double > area;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), marishin::getPolygonArea);
  return std::accumulate(area.cbegin(), area.cend(), 0.0) / polygons.size();
}

void marishin::getArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string name = "";
  in >> name;
  using namespace std::placeholders;
  std::map< std::string, std::function< double() > > cmds;
  {
    cmds["EVEN"] = std::bind(doAreaEven, data);
    cmds["ODD"] = std::bind(doAreaOdd, data);
    cmds["MEAN"] = std::bind(doAreaMean, data);
  }
  try
  {
    size_t count = std::stoull(name);
    if (count < 3)
    {
      throw std::logic_error("Area calcing: vertexes < 3");
    }
    result = doAreaNum(data, count);
  }
  catch (const std::invalid_argument&)
  {
    result = cmds[name]();
  }
  out << result;
}

void marishin::getCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name == "EVEN")
  {
    out << std::count_if(data.begin(), data.end(), isEven);
  }
  else if (name == "ODD")
  {
    out << std::count_if(data.begin(), data.end(), isOdd);
  }
  else
  {
    size_t countVertex = 0;
    try
    {
      countVertex = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("Area calcing: ivalid argument");
    }
    if (countVertex < 3)
    {
      throw std::logic_error("Area calcing: vertexes < 3");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isRightCount = std::bind(isProperSize, _1, countVertex);
    out << std::count_if(data.begin(), data.end(), isRightCount);
  }
}

void marishin::getMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::min_element(data.begin(), data.end(), compareArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      throw std::logic_error("Finding min: invalid arg");
    }
  }
}

void marishin::getMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << getPolygonArea(*std::max_element(data.begin(), data.end(), compareArea));
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      throw std::logic_error("Finding min: invalid arg");
    }
  }
}
/*
bool hasIntersection(const marishin::Polygon& lhs, const marishin::Polygon& rhs)
{
  auto lhsPoints = std::minmax_element(lhs.points.begin(), lhs.points.end());
  auto rhsPoints = std::minmax_element(rhs.points.begin(), rhs.points.end());

  return !(*lhsPoints.second < *rhsPoints.first || *rhsPoints.second < *lhsPoints.first);
}
*/

bool comPoints(const marishin::Point& a, const marishin::Point& b)
{
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

std::pair<marishin::Point, marishin::Point> findMinMaxX(const marishin::Polygon& polygon)
{
  marishin::Point minPoint = polygon.points[0];
  marishin::Point maxPoint = polygon.points[0];
  for (const auto& point : polygon.points)
  {
    if (comPoints(point, minPoint))
    {
      minPoint = point;
    }
    if (comPoints(maxPoint, point))
    {
      maxPoint = point;
    }
  }
  return {minPoint, maxPoint};
}

bool hasIntersection(const marishin::Polygon& lhs, const marishin::Polygon& rhs)
{
  auto lhsMinMax = findMinMaxX(lhs);
  auto rhsMinMax = findMinMaxX(rhs);
  return !(comPoints(lhsMinMax.second, rhsMinMax.first) || comPoints(rhsMinMax.second, lhsMinMax.first));
}

struct RectangleVector
{
  marishin::Point vertexes;
  RectangleVector(const marishin::Point& p1, const marishin::Point& p2);
  double operator*(const RectangleVector& p1);
  double getLength() const;
  double cos(const RectangleVector& p1);
};

RectangleVector::RectangleVector(const marishin::Point& p1, const marishin::Point& p2):
  vertexes(marishin::Point{ p2.x - p1.x, p2.y - p1.y })
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

bool checkRectangle(const marishin::Polygon& ptr)
{
  if (ptr.points.size() != 4)
  {
    return false;
  }
  RectangleVector firstSide(ptr.points[0], ptr.points[1]);
  RectangleVector secondSide(ptr.points[1], ptr.points[2]);
  RectangleVector thirdSide(ptr.points[2], ptr.points[3]);
  RectangleVector fourthSide(ptr.points[0], ptr.points[3]);
  return (firstSide.cos(secondSide) == 0) && (secondSide.cos(thirdSide) == 0) && (thirdSide.cos(fourthSide) == 0);
}

void marishin::getRects(const std::vector< Polygon >& data, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), checkRectangle);
}

void marishin::getIntersections(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if ((polygon.points.empty()) || (!in) || (in.peek() != '\n'))
  {
    throw std::logic_error("Wrong argument");
  }
  using namespace std::placeholders;
  auto isIntersected = std::bind(hasIntersection, std::cref(polygon), _1);
  out << std::count_if(data.begin(), data.end(), isIntersected);
}
