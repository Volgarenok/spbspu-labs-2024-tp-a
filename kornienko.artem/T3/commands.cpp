#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

#include "commands.hpp"

double getVertex(const kornienko::Polygon & polygon)
{
  return polygon.points.size();
}

void kornienko::minOrMax(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons, bool isMax)
{
  std::string context;
  in >> context;
  using namespace std::placeholders;
  std::function< double(const kornienko::Polygon &) > func;
  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  else if (context == "AREA")
  {
    func = getArea;
  }
  else if (context == "VERTEXES")
  {
    func = getVertex;
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  std::vector < double > data(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), data.begin(), func);
  if (isMax)
  {
    out << *max_element(data.cbegin(), data.cend()) << "\n";
  }
  else
  {
    out << *min_element(data.cbegin(), data.cend()) << "\n";
  }
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
  if (std::all_of(context.cbegin(), context.cend(), ::isdigit) && sum == 0)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  out << std::setprecision(1) << std::fixed << sum << "\n";
}
