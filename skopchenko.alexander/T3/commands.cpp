#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include "polygon.hpp"
#include "stream_guard.hpp"

bool isPolygon(const skopchenko::Polygon& polygon)
{
  return (polygon.points.size() > 2);
}

bool isEven(const skopchenko::Polygon& polygon)
{
  return (isPolygon(polygon)) && (polygon.points.size() % 2 == 0);
}

bool isOdd(const skopchenko::Polygon& polygon)
{
  return !isEven(polygon);
}

size_t maxSeq(std::vector< skopchenko::Polygon > polygons, const skopchenko::Polygon& given)
{
  std::vector< size_t > count;
  skopchenko::SeqCounter seqCount;
  using namespace std::placeholders;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(count), std::bind(seqCount, _1, given));
  return *(std::max_element(count.begin(), count.end()));
}

bool isProperSize(const skopchenko::Polygon& polygon, size_t number)
{
  return (polygon.points.size() == number);
}

void skopchenko::getCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
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
    std::function< bool(const Polygon&) > isRightCount = std::bind(isProperSize, _1, pointsCount);
    out << std::count_if(data.begin(), data.end(), isRightCount);
  }
}

void skopchenko::getArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string argument = "";
  in >> argument;
  std::vector< Polygon > shapes;
  shapes.reserve(data.size());
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(shapes), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(shapes), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("No shapes to accumulate area");
    }
    std::copy(data.cbegin(), data.cend(), std::back_inserter(shapes));
  }
  else
  {
    size_t pointsCount = std::stoull(argument);
    if (pointsCount < 3)
    {
      throw std::logic_error("Wrong number of points");
    }
    std::function< bool(const Polygon&) > isRightCount = std::bind(isProperSize, _1, pointsCount);
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(shapes), isRightCount);
  }
  std::vector< double > areas(shapes.size());
  std::transform(shapes.cbegin(), shapes.cend(), std::back_inserter(areas), getPolygonArea);
  double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  (argument == "MEAN") ? (out << result / data.size()) : (out << result);
}

bool comparePoints(const skopchenko::Polygon& first, const skopchenko::Polygon& second)
{
  return (first.points.size() < second.points.size());
}

bool compareArea(const skopchenko::Polygon& first, const skopchenko::Polygon& second)
{
  return (getPolygonArea(first) < getPolygonArea(second));
}

void skopchenko::getMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
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
      out << getPolygonArea(*std::max_element(data.begin(), data.end(), compareArea));
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

void skopchenko::getMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
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
      out << getPolygonArea(*std::min_element(data.begin(), data.end(), compareArea));
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
