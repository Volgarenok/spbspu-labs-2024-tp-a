#include "command.hpp"
#include <functional>
#include <numeric>
#include <string>
#include <iomanip>
#include <algorithm>
#include "polygon.hpp"

double accumulateAreaIf(double result, const marishin::Polygon& polygon, bool predicate)
{
  if (predicate == (polygon.points.size() % 2))
  {
    result += polygon.getArea();
  }
  return result;
}

double accumulateArea(double result, const marishin::Polygon& polygon)
{
  result += polygon.getArea();
  return result;
}

double accumulateAreaIfCount(double result, const marishin::Polygon& polygon, size_t count)
{
  if (polygon.points.size() == count)
  {
    result += polygon.getArea();
  }
  return result;
}

bool isEven(const marishin::Polygon& polygon)
{
  if (polygon.points.size() > 2)
  {
    return (polygon.points.size() % 2 == 0);
  }
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
  return (first.getArea() < second.getArea());
}

void marishin::getArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  using namespace std::placeholders;
  std::function< double(double, const Polygon&) > area;
  if (name == "EVEN")
  {
    area = std::bind(accumulateAreaIf, _1, _2, false);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
  else if (name == "ODD")
  {
    area = std::bind(accumulateAreaIf, _1, _2, true);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
  else if (name == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    area = std::bind(accumulateArea, _1, _2);
    out << std::accumulate(data.begin(), data.end(), 0.0, area) / data.size();
  }
  else
  {
    size_t count = 0;
    try
    {
      count = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (count < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    area = std::bind(accumulateAreaIfCount, _1, _2, count);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
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
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (countVertex < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isRightCount = std::bind(isProperSize, _1, countVertex);
    out << std::count_if(data.begin(), data.end(), isRightCount);
  }
}

void marishin::getMin(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
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

void marishin::getMax(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
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

bool hasIntersection(const marishin::Polygon& first, const marishin::Polygon& second)
{
  marishin::Point minLhs = *std::min_element(first.points.cbegin(), first.points.cend());
  marishin::Point maxLhs = *std::max_element(first.points.cbegin(), first.points.cend());
  marishin::Point minRhs = *std::min_element(second.points.cbegin(), second.points.cend());
  marishin::Point maxRhs = *std::max_element(second.points.cbegin(), second.points.cend());

  bool firstCheck = (minLhs <= maxRhs) && (maxLhs >= minRhs);
  bool secondCheck = (minRhs <= maxLhs) && (maxRhs >= minLhs);
  return firstCheck || secondCheck;
}

bool checkRectangle(const marishin::Polygon& p)
{
  if (p.points.size() != 4)
  {
    return false;
  }
  marishin::RectangleVector firstSide(p.points[0], p.points[1]);
  marishin::RectangleVector secondSide(p.points[1], p.points[2]);
  marishin::RectangleVector thirdSide(p.points[2], p.points[3]);
  marishin::RectangleVector fourthSide(p.points[0], p.points[3]);
  return (firstSide.cos(secondSide) == 0) && (secondSide.cos(thirdSide) == 0) && (thirdSide.cos(fourthSide) == 0);
}

void marishin::getRects(const std::vector< marishin::Polygon >& data, std::istream&, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), checkRectangle);
}

void marishin::getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  marishin::Polygon polygon;
  in >> polygon;
  if ((polygon.points.empty()) || (!in) || (in.peek() != '\n'))
  {
    throw std::logic_error("Wrong argument");
  }
  using namespace std::placeholders;
  auto isIntersected = std::bind(hasIntersection, std::cref(polygon), _1);
  out << std::count_if(data.begin(), data.end(), isIntersected);
}
