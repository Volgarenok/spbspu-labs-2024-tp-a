#include "commands.hpp"
#include <istream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
#include <scope_guard.hpp>
#include "figures_struct.hpp"

bool isOdd(const nikitov::Polygon& figure)
{
  return figure.points.size() % 2;
}

bool isEven(const nikitov::Polygon& figure)
{
  return !(figure.points.size() % 2);
}

bool isSize(const nikitov::Polygon& figure, size_t pointsNum)
{
  return figure.points.size() == pointsNum;
}

void nikitov::areaCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  ScopeGuard scopeGuard(output);
  output << std::setprecision(1) << std::fixed;
  std::string parameter = {};
  input >> parameter;

  std::vector< Polygon > polygons;
  polygons.reserve(data.size());
  if (parameter == "ODD")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (parameter == "EVEN")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), isEven);
  }
  else if (parameter == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("Error: No polygons");
    }
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (std::all_of(parameter.cbegin(), parameter.cend(), ::isdigit))
  {
    size_t vertexesNum = stoull(parameter);
    if (vertexesNum < 3)
    {
      throw std::logic_error("Error: Wrong number of vertexes");
    }
    std::function< bool(const Polygon&) > pred = std::bind(isSize, std::placeholders::_1, vertexesNum);
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), pred);
  }
  else
  {
    throw std::logic_error("Error: Wrong parameter");
  }
  polygons.shrink_to_fit();

  std::vector< double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), getPolygonArea);
  double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (parameter == "MEAN")
  {
    result /= data.size();
  }
  output << result;
}

bool vertexesComparator(const nikitov::Polygon& rhs, const nikitov::Polygon& lhs)
{
  return rhs.points.size() < lhs.points.size();
}

bool areaComparator(const nikitov::Polygon& rhs, const nikitov::Polygon& lhs)
{
  return getPolygonArea(rhs) < getPolygonArea(lhs);
}

void minMax(const std::vector< nikitov::Polygon >& data, std::istream& input, std::ostream& output, const std::string& line)
{
  std::string parameter = {};
  input >> parameter;

  if (data.empty())
  {
    throw std::logic_error("Error: No polygons");
  }

  if (parameter == "AREA")
  {
    nikitov::ScopeGuard scopeGuard(output);
    output << std::setprecision(1) << std::fixed;
    if (line == "MIN")
    {
      output << getPolygonArea(*std::min_element(data.cbegin(), data.cend(), areaComparator));
    }
    else
    {
      output << getPolygonArea(*std::max_element(data.cbegin(), data.cend(), areaComparator));
    }
  }
  else if (parameter == "VERTEXES")
  {
    if (line == "MIN")
    {
      output << (*std::min_element(data.cbegin(), data.cend(), vertexesComparator)).points.size();
    }
    else
    {
      output << (*std::max_element(data.cbegin(), data.cend(), vertexesComparator)).points.size();
    }
  }
  else
  {
    throw std::logic_error("Error: Wrong parameter");
  }
}

void nikitov::minCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  minMax(data, input, output, "MIN");
}

void nikitov::maxCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  minMax(data, input, output, "MAX");
}

void nikitov::countCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;

  if (parameter == "ODD")
  {
    output << std::count_if(data.cbegin(), data.cend(), isOdd);
  }
  else if (parameter == "EVEN")
  {
    output << std::count_if(data.cbegin(), data.cend(), isEven);
  }
  else if (std::all_of(parameter.cbegin(), parameter.cend(), ::isdigit))
  {
    size_t vertexesNum = stoull(parameter);
    if (vertexesNum < 3)
    {
      throw std::logic_error("Error: Wrong number of vertexes");
    }
    std::function< bool(const Polygon&) > pred = std::bind(isSize, std::placeholders::_1, vertexesNum);
    output << std::count_if(data.cbegin(), data.cend(), pred);
  }
  else
  {
    throw std::logic_error("Error: Wrong parameter");
  }
}


bool isPointEqual(const nikitov::Point& point, int x, int y, const nikitov::Polygon& figure)
{
  nikitov::Point toFind = { point.x - x, point.y - y };
  return std::find(figure.points.cbegin(), figure.points.cend(), toFind) != figure.points.cend();
}

bool isSame(const nikitov::Polygon& rhs, const nikitov::Polygon& lhs)
{
  if (rhs.points.size() != lhs.points.size())
  {
    return false;
  }
  int x = rhs.points.front().x - lhs.points.front().x;
  int y = rhs.points.front().y - lhs.points.front().y;

  std::function< bool(const nikitov::Point&) > pred = std::bind(isPointEqual, std::placeholders::_1, x, y, lhs);
  return std::distance(lhs.points.cbegin(), lhs.points.cend()) == std::count_if(rhs.points.cbegin(), rhs.points.cend(), pred);
}

void nikitov::sameCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  Polygon figure;
  input >> figure;
  if (!input || figure.points.empty() || input.peek() != '\n')
  {
    throw std::invalid_argument("Error: Wrong polygon");
  }

  std::function< bool(const Polygon&) > pred = std::bind(isSame, std::placeholders::_1, figure);
  output << count_if(data.cbegin(), data.cend(), pred);
}

bool isPointIn(const nikitov::Point& point, const nikitov::Polygon& figure)
{
  bool isIn = std::find(figure.points.cbegin(), figure.points.cend(), point) != figure.points.cend();
  nikitov::Point rotatedPoint({ point.y, point.x });
  return isIn || std::find(figure.points.cbegin(), figure.points.cend(), rotatedPoint) != figure.points.cend();
}

bool isPerms(const nikitov::Polygon& rhs, const nikitov::Polygon& lhs)
{
  if (rhs.points.size() != lhs.points.size())
  {
    return false;
  }
  std::function< bool(const nikitov::Point&) > pred = std::bind(isPointIn, std::placeholders::_1, lhs);
  return std::distance(lhs.points.cbegin(), lhs.points.cend()) == std::count_if(rhs.points.cbegin(), rhs.points.cend(), pred);
}

void nikitov::permsCmd(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  Polygon figure;
  input >> figure;
  if (!input || figure.points.empty() || input.peek() != '\n')
  {
    throw std::invalid_argument("Error: Wrong polygon");
  }

  std::function< bool(const Polygon&) > pred = std::bind(isPerms, std::placeholders::_1, figure);
  output << std::count_if(data.cbegin(), data.cend(), pred);
}
