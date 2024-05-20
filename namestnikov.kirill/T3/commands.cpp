#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <functional>
#include <numeric>
#include <stream_guard.hpp>
#include "polygon.hpp"

bool isPolygon(const namestnikov::Polygon & polygon)
{
  return (polygon.points.size() > 2);
}

bool isEven(const namestnikov::Polygon & polygon)
{
  return (isPolygon(polygon)) && (polygon.points.size() % 2 == 0);
}

bool isOdd(const namestnikov::Polygon & polygon)
{
  return !isEven(polygon);
}

bool isProperSize(const namestnikov::Polygon & polygon, size_t number)
{
  return (polygon.points.size() == number);
}

void namestnikov::getCount(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
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
    size_t pointsCount = std::stoull(argument);
    if (pointsCount < 3)
    {
      throw std::logic_error("Wrong number of points");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon &) > isRightCount = std::bind(isProperSize, _1, pointsCount);
    out << std::count_if(data.begin(), data.end(), isRightCount);
  }
}

double accumulatePolygonAreaIf(double result, const namestnikov::Polygon & polygon, bool predicate)
{
  if (predicate == (polygon.points.size() % 2))
  {
    result += polygon.getArea();
  }
  return result;
}

double accumulatePolygonAreaIfCount(double result, const namestnikov::Polygon & polygon, size_t count)
{
  if (polygon.points.size() == count)
  {
    result += polygon.getArea();
  }
  return result;
}

double accumulatePolygonArea(double result, const namestnikov::Polygon & polygon)
{
  result += polygon.getArea();
  return result;
}

void namestnikov::getArea(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::function< double(double, const Polygon &) > isRightShape = std::bind(accumulatePolygonAreaIf, _1, _2, false);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
  }
  else if (argument == "ODD")
  {
    std::function< double(double, const Polygon &) > isRightShape = std::bind(accumulatePolygonAreaIf, _1, _2, true);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
  }
  else if (argument ==  "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("No shapes to accumulate area");
    }
    std::function< double(double, const Polygon &) > isRightShape = std::bind(accumulatePolygonArea, _1, _2);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape) / data.size();
  }
  else
  {
    size_t pointsCount = std::stoull(argument);
    if (pointsCount < 3)
    {
      throw std::logic_error("Wrong number of points");
    }
    std::function< double(double, const Polygon &) > isRightShape = std::bind(accumulatePolygonAreaIfCount, _1, _2, pointsCount);
    out << std::accumulate(data.begin(), data.end(), 0.0, isRightShape);
  }
}

bool comparePoints(const namestnikov::Polygon & first, const namestnikov::Polygon & second)
{
  return (first.points.size() < second.points.size());
}

bool compareArea(const namestnikov::Polygon & first, const namestnikov::Polygon & second)
{
  return (first.getArea() < second.getArea());
}

void namestnikov::getMax(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
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
      throw std::logic_error("Wrong argument");
    }
  }
}

void namestnikov::getMin(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
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
      throw std::logic_error("Wrong argument");
    }
  }
}

bool hasIntersection(const namestnikov::Polygon & first, const namestnikov::Polygon & second)
{
  namestnikov::Point minFirstPoint = *std::min_element(first.points.begin(), first.points.end());
  namestnikov::Point maxFirstPoint = *std::max_element(first.points.begin(), first.points.end());
  namestnikov::Point minSecondPoint = *std::min_element(second.points.begin(), second.points.end());
  namestnikov::Point maxSecondPoint = *std::max_element(second.points.begin(), second.points.end());
  bool check = (maxFirstPoint >= minSecondPoint) && (minFirstPoint <= maxSecondPoint);
  check = check || ((maxSecondPoint >= minFirstPoint) && (minSecondPoint <= maxFirstPoint));
  return check;
}

void namestnikov::getIntersections(const std::vector< Polygon > & data, std::istream & in, std::ostream & out)
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

bool isSamePolygon(const namestnikov::Polygon & first, const namestnikov::Polygon & second)
{
  bool check = true;
  check = check && (first.points.size() == second.points.size());
  check = check && (std::equal(first.points.cbegin(), first.points.cend(), second.points.cbegin()));
  return check;
}

namestnikov::Polygon namestnikov::EchoMaker::operator()(const Polygon & other)
{
  if (other == target)
  {
    data.push_back(target);
  }
  return other;
}

void namestnikov::getEcho(std::vector< Polygon > & data, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if ((polygon.points.empty()) || (!in) || (in.peek() != '\n'))
  {
    throw std::logic_error("Wrong argument");
  }
  using namespace std::placeholders;
  auto isSame = std::bind(isSamePolygon, std::cref(polygon), _1);
  out << std::count_if(data.begin(), data.end(), isSame);
  std::vector< Polygon > temp;
  EchoMaker maker{temp, polygon};
  std::transform(std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()), std::back_inserter(temp), std::ref(maker));
  data = temp;
}
