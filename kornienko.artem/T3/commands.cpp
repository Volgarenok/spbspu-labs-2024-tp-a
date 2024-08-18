#include "commands.hpp"
#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

kornienko::Point pointsDifference(const kornienko::Point & first, const kornienko::Point & second)
{
  return kornienko::Point{second.x - first.x, second.y - first.y};
}

bool isSame(kornienko::Polygon first, kornienko::Polygon second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  std::vector< kornienko::Point > firstDiffs(first.points.size() - 1);
  std::vector< kornienko::Point > secondDiffs(first.points.size() - 1);
  using namespace std::placeholders;
  std::transform(first.points.cbegin() + 1, first.points.cend(), firstDiffs.begin(), std::bind(pointsDifference, _1, first.points[0]));
  std::transform(second.points.cbegin() + 1, second.points.cend(), secondDiffs.begin(), std::bind(pointsDifference, _1, second.points[0]));
  return (firstDiffs == secondDiffs);
}

void kornienko::same(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  kornienko::Polygon context;
  in >> context;
  if (!in || in.peek() != '\n')
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isSame, _1, context)) << "\n";
}

bool isAreaLess(kornienko::Polygon polygon, double area)
{
  return (getArea(polygon) < area);
}

void kornienko::lessArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  kornienko::Polygon context;
  in >> context;
  if (!in || in.peek() != '\n')
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isAreaLess, _1, getArea(context))) << "\n";
}

bool numOfVertexes(const kornienko::Polygon & polygon, size_t num)
{
  return (polygon.points.size() == num);
}

bool evenOrOdd(const kornienko::Polygon & polygon, bool isOdd)
{
  return (polygon.points.size() % 2 == isOdd);
}

void kornienko::count(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  std::function< size_t(const kornienko::Polygon &) > func;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    func = std::bind(evenOrOdd, _1, false);
  }
  else if (context == "ODD")
  {
    func = std::bind(evenOrOdd, _1, true);
  }
  else if (std::all_of(context.cbegin(), context.cend(), ::isdigit) && std::stoi(context) > 2)
  {
    func = std::bind(numOfVertexes, _1, std::stoi(context));
  }
  else
  {
    throw std::exception();
  }
  out << std::count_if(polygons.cbegin(), polygons.cend(), func) << "\n";
}

size_t getVertex(const kornienko::Polygon & polygon)
{
  return polygon.points.size();
}

size_t maxVertexes(const std::vector< kornienko::Polygon > polygons)
{
  std::vector < size_t > vertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), getVertex);
  return *max_element(vertexes.cbegin(), vertexes.cend());
}

size_t minVertexes(const std::vector< kornienko::Polygon > polygons)
{
  std::vector < size_t > vertexes(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), getVertex);
  return *min_element(vertexes.cbegin(), vertexes.cend());
}

double minArea(const std::vector< kornienko::Polygon > polygons)
{
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), kornienko::getArea);
  return *min_element(areas.cbegin(), areas.cend());
}

double maxArea(const std::vector< kornienko::Polygon > polygons)
{
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), kornienko::getArea);
  return *max_element(areas.cbegin(), areas.cend());
}

void kornienko::minVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  if (polygons.size() < 1)
  {
    throw std::exception();
  }
  else if (context == "AREA")
  {
    out << std::setprecision(1) << std::fixed << minArea(polygons);
  }
  else if (context == "VERTEXES")
  {
    out << minVertexes(polygons);
  }
  else
  {
    throw std::exception();
  }
  out << "\n";
}

void kornienko::maxVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  if (polygons.size() < 1)
  {
    throw std::exception();
  }
  else if (context == "AREA")
  {
    out << std::setprecision(1) << std::fixed << maxArea(polygons) ;
  }
  else if (context == "VERTEXES")
  {
    out << maxVertexes(polygons);
  }
  else
  {
    throw std::exception();
  }
  out << "\n";
}

double evenOrOddArea(const kornienko::Polygon & polygon, bool isOdd)
{
  if (evenOrOdd(polygon, isOdd))
  {
    return getArea(polygon);
  }
  else
  {
    return 0;
  }
}

double numOfVertexesArea(const kornienko::Polygon & polygon, size_t num)
{
  if (numOfVertexes(polygon, num))
  {
    return getArea(polygon);
  }
  else
  {
    return 0;
  }
}

void kornienko::area(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  std::vector < Polygon > correctPolygons;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(correctPolygons), std::bind(evenOrOdd, _1, false));
  }
  else if (context == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(correctPolygons), std::bind(evenOrOdd, _1, true));
  }
  else if (context == "MEAN" && polygons.size() > 0)
  {
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(correctPolygons));
  }
  else if (std::stoi(context) > 2)
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(correctPolygons), std::bind(numOfVertexes, _1, std::stoi(context)));
  }
  else
  {
    throw std::exception();
  }
  std::vector < double > areas(correctPolygons.size());
  std::transform(correctPolygons.cbegin(), correctPolygons.cend(), areas.begin(), getArea);
  double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (context == "MEAN")
  {
    sum /= polygons.size();
  }
  out << std::setprecision(1) << std::fixed << sum << "\n";
}
