#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

#include "commands.hpp"

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
    out << "<INVALID COMMAND>\n";
    return;
  }
  else if (context == "AREA")
  {
    out << minArea(polygons);
  }
  else if (context == "VERTEXES")
  {
    out << minVertexes(polygons);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  out << "\n";
}

void kornienko::maxVertexOrArea(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  if (polygons.size() < 1)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  else if (context == "AREA")
  {
    out << maxArea(polygons) ;
  }
  else if (context == "VERTEXES")
  {
    out << maxVertexes(polygons);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  out << "\n";
}

double evenOrOddArea(const kornienko::Polygon & polygon, bool isEven)
{
  if (polygon.points.size() % 2 == isEven)
  {
    return 0;
  }
  else
  {
    return getArea(polygon);
  }
}

double numOfVertexesArea(const kornienko::Polygon & polygon, size_t num)
{
  if (polygon.points.size() == num)
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
  std::function< double(const kornienko::Polygon &) > func;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    func = std::bind(evenOrOddArea, _1, true);
  }
  else if (context == "ODD")
  {
    func = std::bind(evenOrOddArea, _1, false);
  }
  else if (context == "MEAN")
  {
    if (polygons.size() > 0)
    {
      func = getArea;
    }
    else
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
  }
  else if (std::all_of(context.cbegin(), context.cend(), ::isdigit))
  {
    if (std::stoi(context) < 3)
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    func = std::bind(numOfVertexesArea, _1, std::stoi(context));
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), func);
  double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (context == "MEAN")
  {
    sum /= polygons.size();
  }
  if (std::all_of(context.cbegin(), context.cend(), ::isdigit) && polygons.size() == 0)
  {
    out << "0.0\n";
    return;
  }
  out << std::setprecision(1) << std::fixed << sum << "\n";
}
