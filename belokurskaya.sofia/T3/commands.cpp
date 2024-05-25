#include "commands.hpp"

#include <string>
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>

#include <streamGuard.hpp>

void belokurskaya::cmd::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  StreamGuard streamGuard(out);
  out << std::setprecision(1) << std::fixed;

  std::string option = "";
  in >> option;
  std::function< double(const Polygon&) > resultFuncForArea;

  if (option == "EVEN")
  {
    resultFuncForArea = calculateAreaBasedOnSizeEven;
  }
  else if (option == "ODD")
  {
    resultFuncForArea = calculateAreaBasedOnSizeOdd;
  }
  else if (option == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("At least one shape is required");
    }
    resultFuncForArea = std::bind(calculateMeanArea, polygons, std::placeholders::_1);
  }
  else
  {
    size_t numVertexes = 0;
    try
    {
      numVertexes = std::stoull(option);
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("There are too many vertices");
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("Command is not found");
    }

    if (numVertexes < 3)
    {
      throw std::invalid_argument("Need more three vertexes");
    }

    resultFuncForArea = std::bind(calculateAreaBasedOnVertexCount, std::placeholders::_1, numVertexes);
  }
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(sumPolygonAreas,
    std::placeholders::_1, std::placeholders::_2, resultFuncForArea));
}

void belokurskaya::cmd::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option = "";
  in >> option;
  if (option == "AREA")
  {
    StreamGuard streamGuard(out);
    out << std::setprecision(1) << std::fixed;

    out << cmd::subcmd::getMinPolygonArea(polygons);
  }
  else if (option == "VERTEXES")
  {
    out << cmd::subcmd::getMinPolygonVertexes(polygons);
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void belokurskaya::cmd::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option = "";
  in >> option;
  std::function< double(const Polygon&) > resultFuncForMax;
  if (option == "AREA")
  {
    StreamGuard streamGuard(out);
    out << std::setprecision(1) << std::fixed;

    out << cmd::subcmd::getMaxPolygonArea(polygons);
  }
  else if (option == "VERTEXES")
  {
    out << cmd::subcmd::getMaxPolygonVertexes(polygons);
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void belokurskaya::cmd::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option = "";
  in >> option;
  std::function< size_t(const Polygon&) > resultFuncForCount;
  if (option == "EVEN")
  {
    resultFuncForCount = countEvenSizePolygons;
  }
  else if (option == "ODD")
  {
    resultFuncForCount = countOddSizePolygons;
  }
  else
  {
    size_t numVertexes = 0;
    try
    {
      numVertexes = std::stoull(option);
    }
    catch (const std::out_of_range&)
    {
      throw std::invalid_argument("There are too many vertices");
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("Invalid command");
    }
    if (numVertexes < 3)
    {
      throw std::invalid_argument("Need more three vertexes");
    }
    resultFuncForCount = std::bind(compareNumVertexes, std::placeholders::_1, numVertexes);
  }
  out << std::accumulate(polygons.begin(), polygons.end(), 0, calcPolyCount);
}

void belokurskaya::cmd::rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (in.fail() || in.peek() != '\n')
  {
    throw std::invalid_argument("Could not read the figure");
  }
  auto last = std::unique(polygons.begin(), polygons.end(),
    std::bind(isIndentical, std::placeholders::_1, std::placeholders::_2, polygon));
  size_t erased = std::distance(last, polygons.end());
  polygons.erase(last, polygons.end());
  out << erased;
}

void belokurskaya::cmd::rects(const std::vector< Polygon >& polygons, std::ostream& out)
{
  size_t rectanglesCount = std::count_if(polygons.begin(), polygons.end(), isRectangle);
  out << rectanglesCount;
}

double belokurskaya::cmd::subcmd::getTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  return 0.5 * std::abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
}

double belokurskaya::cmd::subcmd::getPolygonArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }
  std::vector< double > triangleAreas(polygon.points.size() - 2);
  using namespace std::placeholders;
  std::transform(polygon.points.begin() + 2, polygon.points.end(), std::next(polygon.points.begin(), 1),
    triangleAreas.begin(), std::bind(&cmd::subcmd::getTriangleArea, polygon.points[0], _1, _2));
  return std::accumulate(triangleAreas.begin(), triangleAreas.end(), 0.0);
}

double belokurskaya::cmd::subcmd::getMaxPolygonArea(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("At least one shape is required");
  }
  auto maxIt = std::max_element(polygons.begin(), polygons.end(), comparePolygonAreas);
  return cmd::subcmd::getPolygonArea(*maxIt);
}

double belokurskaya::cmd::subcmd::getMinPolygonArea(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("At least one shape is required");
  }
  auto minIt = std::min_element(polygons.begin(), polygons.end(), comparePolygonAreas);
  return cmd::subcmd::getPolygonArea(*minIt);
}

size_t belokurskaya::cmd::subcmd::getMaxPolygonVertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("At least one shape is required");
  }
  auto maxIt = std::max_element(polygons.begin(), polygons.end(), comparePolygons);
  return maxIt->points.size();
}

size_t belokurskaya::cmd::subcmd::getMinPolygonVertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("At least one shape is required");
  }
  auto minIt = std::min_element(polygons.begin(), polygons.end(), comparePolygons);
  return minIt->points.size();
}

double belokurskaya::calculateAreaBasedOnSizeEven(const Polygon& polygon)
{
  if (polygon.points.size() % 2 == 0)
  {
    return cmd::subcmd::getPolygonArea(polygon);
  }
  else
  {
    return 0.0;
  }
}

double belokurskaya::calculateAreaBasedOnSizeOdd(const Polygon& polygon)
{
  if (polygon.points.size() % 2 != 0)
  {
    return cmd::subcmd::getPolygonArea(polygon);
  }
  else
  {
    return 0.0;
  }
}

double belokurskaya::calculateAreaBasedOnVertexCount(const Polygon& polygon, size_t numVertexes)
{
  return (polygon.points.size() == numVertexes) ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
}

double belokurskaya::sumPolygonAreas(const double sum, const Polygon& polygon,
  std::function< double(const Polygon&) > resultFunc)
{
  return sum + resultFunc(polygon);
}

size_t belokurskaya::compareNumVertexes(const Polygon& polygon, size_t numVertexes)
{
  size_t result = 0;
  if (polygon.points.size() == numVertexes)
  {
    result = 1;
  }
  return result;
}

double belokurskaya::calcPolyCount(double sum, const Polygon& polygon, size_t(*resultFuncForCount)(const Polygon&))
{
  return sum + resultFuncForCount(polygon);
}

bool belokurskaya::isIndentical(const Polygon& p1, const Polygon& p2, const Polygon& polyToCompare)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin()) &&
    std::equal(p1.points.begin(), p1.points.end(), polyToCompare.points.begin());
}

double belokurskaya::calculateMeanArea(const std::vector< Polygon >& polygons, const Polygon& polygon)
{
  return cmd::subcmd::getPolygonArea(polygon) / polygons.size();
}

size_t belokurskaya::countEvenSizePolygons(const Polygon& polygon)
{
  size_t result = 0;
  if (polygon.points.size() % 2 == 0)
  {
    result = 1;
  }
  return result;
}


size_t belokurskaya::countOddSizePolygons(const Polygon& polygon)
{
  size_t result = 0;
  if (polygon.points.size() % 2 != 0)
  {
    result = 1;
  }
  return result;
}

bool belokurskaya::isRectangle(const Polygon& polygon)
{
  if (polygon.points.size() != 4)
  {
    return false;
  }
  RectVector a(polygon.points[0], polygon.points[1]);
  RectVector b(polygon.points[1], polygon.points[2]);
  RectVector c(polygon.points[2], polygon.points[3]);
  RectVector d(polygon.points[0], polygon.points[3]);
  return (a.cos(b) == 0) && (b.cos(c) == 0) && (c.cos(d) == 0);
}

bool belokurskaya::comparePolygonAreas(const Polygon& a, const Polygon& b)
{
  return cmd::subcmd::getPolygonArea(a) < cmd::subcmd::getPolygonArea(b);
}

bool belokurskaya::comparePolygons(const Polygon& a, const Polygon& b)
{
  return a.points.size() < b.points.size();
}

belokurskaya::RectVector::RectVector(const Point& p1, const Point& p2):
  vertexes(Point{ p2.x - p1.x, p2.y - p1.y })
{}

double belokurskaya::RectVector::operator*(const RectVector& p1)
{
  return vertexes.x * p1.vertexes.x + vertexes.y * p1.vertexes.y;
}

double belokurskaya::RectVector::getLength() const
{
  return std::hypot(vertexes.x, vertexes.y);
}

double belokurskaya::RectVector::cos(const RectVector& p1)
{
  return (*this * p1) / (getLength() * p1.getLength());
}

