#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

#include "commands.hpp"

void kornienko::minOrMax(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons, bool isMax)
{
  if (polygons.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  std::string context;
  in >> context;
  return;
}

double kornienko::evenOrOddArea(const kornienko::Polygon & polygon, bool isEven)
{
  if (polygon.points.size() % 2 == isEven)
  {
    return 0;
  }
  else
  {
    return polygon.getArea();
  }
}

double kornienko::numOfVertexesArea(const kornienko::Polygon & polygon, size_t num)
{
  if (polygon.points.size() == num)
  {
    return polygon.getArea();
  }
  else
  {
    return 0;
  }
}

double kornienko::meanArea(const kornienko::Polygon & polygon)
{
  return polygon.getArea();
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
  else if (context == "MEAN" && polygons.size() > 0)
  {
    func = meanArea;
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
  out << std::setprecision(1) << std::fixed << sum << "\n";
}
