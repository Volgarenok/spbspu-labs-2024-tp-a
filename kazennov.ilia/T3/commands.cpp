#include "commands.h"

#include <functional>
#include <cmath>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <string>
#include <set>
#include <map>


bool isEven(const kazennov::Polygon p)
{
  return (p.points.size() % 2 == 0);
}

bool isOdd(const kazennov::Polygon p)
{
  return (p.points.size() % 2 == 1);
}

bool sizeCheck(const kazennov::Polygon p, long unsigned int size)
{
  return (p.points.size() == size);
}

bool areaCompare(const kazennov::Polygon& polygon,
  const kazennov::Polygon& other)
{
  return (kazennov::PolygonArea(polygon) < kazennov::PolygonArea(other));
}

bool vertexCompare(const kazennov::Polygon& polygon, const kazennov::Polygon& other)
{
  return (polygon.points.size() < other.points.size());
}

bool isPerm(const kazennov::Polygon& polygon, const kazennov::Polygon& other)
{
  if (polygon.points.size() != other.points.size())
  {
    return false;
  }
  return std::is_permutation(polygon.points.cbegin(), polygon.points.cend(),
    other.points.cbegin(), other.points.cend(), std::equal_to<kazennov::Point>{});
}

bool intersectionCheck(const kazennov::Polygon& polygon, const kazennov::Polygon& other)
{
  auto polygonMinMax = std::minmax_element(polygon.points.cbegin(), polygon.points.cend());
  auto otherMinMax = std::minmax_element(other.points.cbegin(), other.points.cend());
  return !(*polygonMinMax.second < *otherMinMax.first || *polygonMinMax.first > *otherMinMax.second);
}

bool higherPoint(const kazennov::Point& point, const kazennov::Point& other)
{
  return (point.y < other.y);
}

kazennov::Point getHighestPoint(const kazennov::Polygon& polygon)
{
  return *std::max_element(polygon.points.cbegin(), polygon.points.cend(), higherPoint);
}

kazennov::Point getHighestPointFromVector(const std::vector<kazennov::Point>& point)
{
  return *std::max_element(point.cbegin(), point.cend(), higherPoint);
}

kazennov::Point getLowestPoint(const kazennov::Polygon& polygon)
{
  return *std::min_element(polygon.points.cbegin(), polygon.points.cend(), higherPoint);
}

kazennov::Point getLowestPointFromVector(const std::vector<kazennov::Point>& point)
{
  return *std::min_element(point.cbegin(), point.cend(), higherPoint);
}

bool righterPoint(const kazennov::Point& point, const kazennov::Point& other)
{
  return (point.x < other.x);
}

kazennov::Point getRightestPoint(const kazennov::Polygon& polygon)
{
  return *std::max_element(polygon.points.cbegin(), polygon.points.cend(), righterPoint);
}

kazennov::Point getRightestPointFromVector(const std::vector<kazennov::Point>& point)
{
  return *std::max_element(point.cbegin(), point.cend(), righterPoint);
}

kazennov::Point getLeftestPoint(const kazennov::Polygon& polygon)
{
  return *std::min_element(polygon.points.cbegin(), polygon.points.cend(), righterPoint);
}

kazennov::Point getLeftestPointFromVector(const std::vector<kazennov::Point>& point)
{
  return *std::min_element(point.cbegin(), point.cend(), righterPoint);
}

double getAreaByType(const std::vector< kazennov::Polygon > & polygon, std::string arg)
{
  std::vector< kazennov::Polygon > Polygons;
  using namespace std::placeholders;
  if (arg == "EVEN")
  {
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(Polygons), isEven);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(Polygons), isOdd);
  }
  else if (arg == "MEAN")
  {
    std::copy(polygon.cbegin(), polygon.cend(), std::back_inserter(Polygons));
  }
  std::vector < double > areas(Polygons.size());
  std::transform(Polygons.cbegin(), Polygons.cend(), std::back_inserter(areas), kazennov::PolygonArea);
  double area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (arg == "MEAN")
  {
    if (polygon.size() != 0)
    {
      return area/polygon.size();
    }
    else
    {
      throw std::invalid_argument("Wrong argument");
    }
  }
  else
  {
    return area;
  }

}

void kazennov::getArea(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  double area;
  std::string arg;
  in >> arg;
  std::map< std::string, std::function< double() > > cmd;
  {
    using namespace std::placeholders;
    cmd["EVEN"] = std::bind(getAreaByType, polygon, "EVEN");
    cmd["ODD"] = std::bind(getAreaByType, polygon, "ODD");
    cmd["MEAN"] = std::bind(getAreaByType, polygon, "MEAN");
  }
  try
  {
    if (!std::all_of(arg.cbegin(), arg.cend(), isdigit))
    {
      throw std::invalid_argument("Wrong argument");
    }
    if (std::stoi(arg) < 3)
    {
      throw std::invalid_argument("Wrong number vertexes");
    }
    using namespace std::placeholders;
    std::vector< Polygon > Polygons;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(Polygons), std::bind(sizeCheck, _1, std::stoi(arg)));
    std::vector < double > areas(Polygons.size());
    std::transform(Polygons.cbegin(), Polygons.cend(), std::back_inserter(areas), PolygonArea);
    area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  }
  catch (const std::invalid_argument&)
  {
    area = cmd[arg]();
  }
  out << std::fixed << std::setprecision(1) << area;
}

void kazennov::getMax(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  std::string arg;
  in >> arg;
  if (polygon.empty())
  {
    throw std::exception();
  }
  else
  {
    if (arg == "AREA")
    {
      out << std::fixed << std::setprecision(1) << PolygonArea(*std::max_element(polygon.begin(), polygon.end(), areaCompare));
    }
    else if (arg == "VERTEXES")
    {
      auto vert = *std::max_element(polygon.begin(), polygon.end(), vertexCompare);
      out << vert.points.size();
    }
    else
    {
      throw std::invalid_argument("Wrong argument");
    }
  }
}

void kazennov::getMin(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{

  std::string arg;
  in >> arg;
  if (polygon.empty())
  {
    throw std::exception();
  }
  else
  {
    if (arg == "AREA")
    {
      out << std::fixed << std::setprecision(1) << PolygonArea(*std::min_element(polygon.begin(), polygon.end(), areaCompare));
    }
    else if (arg == "VERTEXES")
    {
      auto vert = *std::min_element(polygon.begin(), polygon.end(), vertexCompare);
      out << vert.points.size();
    }
    else
    {
      throw std::invalid_argument("Wrong argument");
     }
  }
}

void kazennov::getCount(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  std::string arg;
  in >> arg;
  using namespace std::placeholders;
  if (arg == "EVEN")
  {
    out << std::count_if(polygon.cbegin(), polygon.cend(), isEven);
  }
  else if (arg == "ODD")
  {
    out << std::count_if(polygon.cbegin(), polygon.cend(), isOdd);
  }
  else if (std::stoi(arg) > 2)
  {
    out << std::count_if(polygon.cbegin(), polygon.cend(), std::bind(sizeCheck, _1, std::stoi(arg)));
  }
  else
  {
    throw std::invalid_argument("Wrong argument");
  }
}

void kazennov::getPerms(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  Polygon temp;
  in >> temp;
  if (!in || temp.points.empty())
  {
    throw std::invalid_argument("Wrong argument");
  }
  using namespace std::placeholders;
  out << std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isPerm, temp, _1));
}

void kazennov::getIntersections(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  Polygon temp;
  in >> temp;
  if (!in)
  {
    throw std::invalid_argument("Wrong argument");
  }
  else
  {
    std::set< Point > checkForEqualPoints(temp.points.cbegin(), temp.points.cend());
    if (checkForEqualPoints.size() != temp.points.size())
    {
      throw std::invalid_argument("Have equal points");
    }
    using namespace std::placeholders;
    out << std::count_if(polygon.cbegin(), polygon.cend(), std::bind(intersectionCheck, temp, _1));
  }
}

void kazennov::getInframe(std::istream& in, std::ostream& out, const std::vector< Polygon > & polygon)
{
  Polygon temp;
  in >> temp;
  if (!in)
  {
    throw std::invalid_argument("Wrong argument");
  }
  else
  {
    std::set< Point > checkForEqualPoints(temp.points.cbegin(), temp.points.cend());
    if (checkForEqualPoints.size() != temp.points.size())
    {
      throw std::invalid_argument("Have equal points");
    }
    using namespace std::placeholders;
    std::vector< kazennov::Point > Points;
    std::transform(polygon.cbegin(), polygon.cend(), std::back_inserter(Points), getHighestPoint);
    kazennov::Point highest = getHighestPointFromVector(Points);
    std::transform(polygon.cbegin(), polygon.cend(), std::back_inserter(Points), getLowestPoint);
    kazennov::Point lowest = getLowestPointFromVector(Points);
    std::transform(polygon.cbegin(), polygon.cend(), std::back_inserter(Points), getRightestPoint);
    kazennov::Point righest = getRightestPointFromVector(Points);
    std::transform(polygon.cbegin(), polygon.cend(), std::back_inserter(Points), getLeftestPoint);
    kazennov::Point leftest = getLeftestPointFromVector(Points);
    bool isHigher = getHighestPoint(temp).y < highest.y;
    bool isLower = getLowestPoint(temp).y > lowest.y;
    bool isRighter =  getRightestPoint(temp).x < righest.x;
    bool isLefter = getLeftestPoint(temp).x > leftest.x;
    if (isHigher && isLower && isRighter && isLefter)
    {
      out << "<TRUE>";
    }
    else
    {
      out << "<FALSE>";
    }
  }
}
