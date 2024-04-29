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