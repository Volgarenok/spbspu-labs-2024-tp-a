#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <functional>
#include <numeric>
#include <stream_guard.hpp>
#include "polygon.hpp"

bool isPolygon(namestnikov::Polygon)
{
  return (polygon.points.size() > 2);
}

bool isEven(namestnikov::Polygon polygon)
{
  return (isPolygon(polygon)) && (polygon.points.size() % 2);
}

bool isOdd(namestnikov::Polygon polygon)
{
  return !isEven(polygon);
}

bool isProperSize(namestnikov::Polygon polygon, size_t number)
{
  return (polygon.points.size() == number);
}

void namestnikov::getCount(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(data.begin(), data.end(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(data.begin(), data.end(), isOdd);
  }
  else
  {
    try
    {
      size_t pointsCount = std::stoull(argument);
      if (pointsCount < 3)
      {
         throw std::logic_error("Wrong number of points");
      }
      using namespace std::placeholders;
      std::function< bool(namestnikov::Polygon) > isRightCount = std::bind(isProperSize, _1, pointsCount);
      out << std::count_if(data.begin(), data.end(), isRightCount);
    }
    catch (const std::invalid_argument &)
    {
      out << "<INVALID COMMAND>";
    }   
  }
}

template< class Predicate >
double accumulatePolygonArea(double result, namestnikov::Polygon polygon, Predicate predicate)
{
  if predicate(polygon)
  {
    result += polygon.getArea();
  }
  return result;
}

void namestnikov::getArea(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::function< double(double, namestnikov::Polygon) > isRightShape = std::bind(accumulatePolygonArea, _1, _2, isEven);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
  }
  else if (argument == "ODD")
  {
    std::function< double(double, namestnikov::Polygon) > isRightShape = std::bind(accumulatePolygonArea, _1, _2, isOdd);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
  }
  else if (argument ==  "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("No shapes to accumulate area");
    }
    std::function< double(double, namestnikov::Polygon) > isRightShape = std::bind(accumulatePolygonArea, _1, _2, isPolygon);
    out << std::accumulate(data,begin(), data.end(), 0.0, isRightShape);
  }
  else
  {
    try
    {
      size_t pointsCount = std::stoull(argument);
      if (pointsCount < 3)
      {
         throw std::logic_error("Wrong number of points");
      }
      std::function< bool(namestnikov::Polygon) > isRightCount = std::bind(isProperSize, _1, pointsCount);
      std::function< double(double, namestnikov::Polygon) > isRightShape = std::bind(accumulatePolygonArea, _1, _2, isRightCount);
      out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
    }
    catch (const std::invalid_argument &)
    {
      out << "<INVALID COMMAND>";
    }
  }
}

bool comparePoints(namestnikov::Polygon first, namestnikov::Polygon second)
{
  return (first.points.size() < second.points.size());
}

bool compareArea(namestnikov::Polygon first, namestnikov::Polygon second)
{
  return (first.getArea() < second.getArea());
}

void namestnikov::getMax(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
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
      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << std::max_element(data.begin(), data.end(), compareArea)->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

void namestnikov::getMin(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
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
      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << std::min_element(data.begin(), data.end(), compareArea)->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

bool hasIntersection(namestnikov::Polygon first, namestnikov::Polygon second)
{
  namestnikov::Point minFirstPoint = *std::min_element(first.points.begin(), first.points.end());
  namestnikov::Point maxFirstPoint = *std::max_element(first.points.begin(), first.points.end());
  namestnikov::Point minSecondPoint = *std::min_element(second.points.begin(), second.points.end());
  namestnikov::Point maxSecondPoint = *std::max_element(second.points.begin(), second.points.end());
  bool check = (maxFirstPoint >= minSecondPoint) && (minFirstPoint <= maxSecondPoint);
  check = check || ((maxSecondPoint >= minFirstPoint) && (minSecondPoint <= maxFirstPoint));
  return check;

}

void namestnikov::getIntersections(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
{
  namestnikov::Polygon polygon;
  in >> polygon;
  if (polygon.points.empty())
  {
    throw std::logic_error("Wrong argument");
  }
  using namespace std::placeholders;
  bool isIntersected = std::bind(hasIntersection, &polygon, _1);
  out << std::count_if(data.begin(), data.end(), isIntersected);
}