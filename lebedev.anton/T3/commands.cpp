#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
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
bool fitSize(const lebedev::Polygon& polygon, size_t points_number)
{
  return polygon.points.size() == points_number;
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
    selected_polygons.resize(selected_polygons.size());
  }
  else if (argument == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons), isOdd);
    selected_polygons.resize(selected_polygons.size());
  }
  else if (argument == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(selected_polygons));
    selected_polygons.resize(selected_polygons.size());
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
    selected_polygons.resize(selected_polygons.size());
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::vector< double > polygons_areas;
  polygons_areas.reserve(selected_polygons.size());
  std::transform(selected_polygons.cbegin(), selected_polygons.cend(), polygons_areas.begin(), getArea);
  double area = std::accumulate(polygons_areas.cbegin(), polygons_areas.cend(), 0.0);
  if (argument == "MEAN")
  {
    area /= polygons.size();
  }
  lebedev::StreamGuard stream_guard(output);
  output << std::fixed << std::setprecision(1);
  output << area;
}
