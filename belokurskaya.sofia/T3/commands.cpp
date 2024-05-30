#include "commands.hpp"

#include <string>
#include <map>
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>

#include <streamGuard.hpp>

void belokurskaya::cmd::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  StreamGuard streamGuard(out);

  std::map< std::string, std::function< bool(const Polygon&) > > predicate;
  predicate["EVEN"] = isEven;
  predicate["ODD"] = isOdd;

  std::string option = "";
  in >> option;

  std::function< bool(const Polygon&) > pred;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon&) > functor = cmd::subcmd::getPolygonArea;
  try
  {
    pred = predicate.at(option);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), pred);
  }
  catch (const std::out_of_range&)
  {
    if (option == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("There are no shapes");
      }
      using namespace std::placeholders;
      functor = std::bind(calculateMeanArea, 0.0, _1, polygons.size());
      filteredPolygons = polygons;
    }
    else
    {
      size_t numVertexes = std::stoull(option);

      if (numVertexes < 3)
      {
        throw std::invalid_argument("Need more three vertexes");
      }
      using namespace std::placeholders;
      pred = std::bind(isNumVertexes, _1, numVertexes);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), pred);
    }
  }
  std::vector< double > areas(polygons.size());
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), functor);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(areas.begin(), areas.end(), 0.0);
}

void belokurskaya::cmd::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  StreamGuard streamGuard(out);
  std::map< std::string, std::function< void() > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(cmd::subcmd::getMinPolygonArea, std::ref(polygons), std::ref(out));
    subcommand["VERTEXES"] = std::bind(cmd::subcmd::getMinPolygonVertexes, std::ref(polygons), std::ref(out));
  }
  std::string option = "";
  in >> option;
  out << std::setprecision(1) << std::fixed;
  subcommand.at(option)();
}

void belokurskaya::cmd::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("There are no shapes");
  }
  StreamGuard streamGuard(out);
  std::map< std::string, std::function< void() > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(cmd::subcmd::getMaxPolygonArea, std::ref(polygons), std::ref(out));
    subcommand["VERTEXES"] = std::bind(cmd::subcmd::getMaxPolygonVertexes, std::ref(polygons), std::ref(out));
  }
  std::string option = "";
  in >> option;
  out << std::setprecision(1) << std::fixed;
  subcommand.at(option)();
}

void belokurskaya::cmd::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  StreamGuard streamGuard(out);
  std::map< std::string, std::function< bool(const Polygon&) > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["EVEN"] = std::bind(isEvenVertexes, _1);
    subcommand["ODD"] = std::bind(isOddVertexes, _1);
  }
  std::function< double(const Polygon&) > resultFuncForCount;
  std::string option = "";
  in >> option;
  if (subcommand.find(option) != subcommand.end())
  {
    resultFuncForCount = subcommand.at(option);
  }
  else
  {
    size_t numVertexes = std::stoull(option);
    if (numVertexes < 3)
    {
      throw std::invalid_argument("Need more three vertexes");
    }
    resultFuncForCount = std::bind(compareNumVertexes, std::placeholders::_1, numVertexes);
  }
  out << std::count_if(polygons.begin(), polygons.end(), resultFuncForCount);
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

void belokurskaya::cmd::subcmd::getMaxPolygonArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto maxIt = std::max_element(polygons.begin(), polygons.end(), comparePolygonAreas);
  out << getPolygonArea(*maxIt);
}

void belokurskaya::cmd::subcmd::getMinPolygonArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto minIt = std::min_element(polygons.begin(), polygons.end(), comparePolygonAreas);
  out << getPolygonArea(*minIt);
}

void belokurskaya::cmd::subcmd::getMaxPolygonVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto maxIt = std::max_element(polygons.begin(), polygons.end(), comparePolygons);
  out << maxIt->points.size();
}

void belokurskaya::cmd::subcmd::getMinPolygonVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto minIt = std::min_element(polygons.begin(), polygons.end(), comparePolygons);
  out << minIt->points.size();
}

bool belokurskaya::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool belokurskaya::isOdd(const Polygon& polygon)
{
  return !isEven(polygon);
}

double belokurskaya::isNumVertexes(const Polygon& polygon, size_t numVertexes)
{
  return numVertexes == polygon.points.size();
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

bool belokurskaya::isIndentical(const Polygon& p1, const Polygon& p2, const Polygon& polyToCompare)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::equal(p1.points.begin(), p1.points.end(), p2.points.begin()) &&
    std::equal(p1.points.begin(), p1.points.end(), polyToCompare.points.begin());
}

double belokurskaya::calculateMeanArea(double currArea, const Polygon& polygon, size_t count)
{
  return currArea + cmd::subcmd::getPolygonArea(polygon) / count;
}

bool belokurskaya::isEvenVertexes(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool belokurskaya::isOddVertexes(const Polygon& polygon)
{
  return !isEvenVertexes(polygon);
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

