#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <string>
#include <scope_guard.hpp>
#include "polygon.hpp"

bool isEven(const lebedev::Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}
bool isOdd(const lebedev::Polygon & polygon)
{
  return (polygon.points.size() % 2 == 1);
}
bool isDigit(std::string str)
{
  return std::all_of(str.cbegin(), str.cend(), isdigit);
}
bool fitSize(const lebedev::Polygon & polygon, size_t points_number)
{
  return polygon.points.size() == points_number;
}
double getMaxAreaOfPair(double a, const lebedev::Polygon & polygon)
{
  return std::max(a, lebedev::getArea(polygon));
}
size_t getMaxVertexesOfPair(size_t a, const lebedev::Polygon & polygon)
{
  return std::max(a, polygon.points.size());
}
double getMinAreaOfPair(double a, const lebedev::Polygon & polygon)
{
  return std::min(a, lebedev::getArea(polygon));
}
size_t getMinVertexesOfPair(size_t a, const lebedev::Polygon & polygon)
{
  return std::min(a, polygon.points.size());
}
bool checkIntersection(const lebedev::Polygon & p1, const lebedev::Polygon & p2)
{
  auto p1_minmax = std::minmax_element(p1.points.cbegin(), p1.points.cend());
  auto p2_minmax = std::minmax_element(p2.points.cbegin(), p2.points.cend());
  return !((*p1_minmax.second) < (*p2_minmax.first) || (*p2_minmax.second) < (*p1_minmax.first));
}
int getPointsDiffX(const lebedev::Point & p1, const lebedev::Point & p2)
{
  return p1.x - p2.x;
}
int getPointsDiffY(const lebedev::Point & p1, const lebedev::Point & p2)
{
  return p1.y - p2.y;
}
bool areSame(const lebedev::Polygon & p1, const lebedev::Polygon & p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  std::vector< int > diff_x;
  diff_x.reserve(p1.points.size());
  std::vector< int > diff_y;
  diff_y.reserve(p1.points.size());
  std::transform(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin(), std::back_inserter(diff_x), getPointsDiffX);
  std::transform(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin(), std::back_inserter(diff_y), getPointsDiffY);

  std::vector<int>::iterator it_x = std::unique(diff_x.begin(), diff_x.end());
  std::vector<int>::iterator it_y = std::unique(diff_y.begin(), diff_y.end());

  return it_x == (++diff_x.cbegin()) && it_y == (++diff_y.cbegin());
}

void lebedev::getAreaCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::vector< Polygon > selected_polygons;
  selected_polygons.reserve(polygons.size());
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons));
  }
  else if (isDigit(argument))
  {
    size_t points_num = 0;
    points_num = std::stoull(argument);
    if (points_num < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::function< bool(const Polygon &) > funct = std::bind(fitSize, _1, points_num);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons), funct);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  selected_polygons.resize(selected_polygons.size());

  std::vector< double > polygons_areas;
  polygons_areas.reserve(selected_polygons.size());
  std::transform(selected_polygons.cbegin(), selected_polygons.cend(), std::back_inserter(polygons_areas), getArea);
  double area = std::accumulate(polygons_areas.cbegin(), polygons_areas.cend(), 0.0);
  if (argument == "MEAN")
  {
    area /= polygons.size();
  }
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  output << area;
}

void lebedev::getMaxCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string argument;
  input >> argument;
  using namespace std::placeholders;
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  if (argument == "AREA")
  {
    output << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, getMaxAreaOfPair);
  }
  else if (argument == "VERTEXES")
  {
    output << std::accumulate(polygons.cbegin(), polygons.cend(), 0, getMaxVertexesOfPair);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void lebedev::getMinCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string argument;
  input >> argument;
  using namespace std::placeholders;
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  if (argument == "AREA")
  {
    double max_double = std::numeric_limits< double >::max();
    output << std::accumulate(polygons.cbegin(), polygons.cend(), max_double, getMinAreaOfPair);
  }
  else if (argument == "VERTEXES")
  {
    size_t max_size_t = std::numeric_limits< size_t >::max();
    output << std::accumulate(polygons.cbegin(), polygons.cend(), max_size_t, getMinVertexesOfPair);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void lebedev::getCountCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }
  else if (argument == "ODD")
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else if (isDigit(argument))
  {
    size_t points_num = 0;
    points_num = std::stoull(argument);
    if (points_num < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::function< bool(const Polygon &) > funct = std::bind(fitSize, _1, points_num);
    output << std::count_if(polygons.cbegin(), polygons.cend(), funct);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void lebedev::getIntersectionsCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  Polygon polygon;
  input >> polygon;
  if (polygon.points.size() < 3 || !input)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto funct = std::bind(checkIntersection, _1, std::cref(polygon));
  output << std::count_if(polygons.cbegin(), polygons.cend(), funct);
}

void lebedev::getSameCmd(const std::vector< Polygon > & polygons, std::istream & input, std::ostream & output)
{
  Polygon polygon;
  input >> polygon;
  if (polygon.points.size() < 3 || !input)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto funct = std::bind(areSame, _1, polygon);
  output << std::count_if(polygons.cbegin(), polygons.cend(), funct);
}
