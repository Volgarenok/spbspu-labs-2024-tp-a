#include "cmds.hpp"
#include <streamGuard.hpp>
#include "polygon.hpp"
#include <numeric>
#include <functional>
#include <iterator>
#include <iomanip>

namespace feofanova
{
  struct AreaFunctor
  {
    double operator()(const Point& a, const Point& b) const
    {
      return (a.x * b.y) - (b.x * a.y);
    }
  };
}

bool odd(const feofanova::Polygon& p)
{
  return p.points.size() % 2;
}

bool even(const feofanova::Polygon& p)
{
  return !odd(p);
}

bool checkVertexes(size_t count, const feofanova::Polygon& p)
{
  return p.points.size() == count;
}

void feofanova::Count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  int res = 0.0;
  std::string subcommand = "";
  std::cin >> subcommand;

  if (subcommand == "EVEN")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), even);
  }
  else if (subcommand == "ODD")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), odd);
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument&)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    using namespace std::placeholders;
    auto counter = std::bind(checkVertexes, nVertexes, _1);
    res = std::count_if(polygons.cbegin(), polygons.cend(), counter);
    }

  out << res << '\n';
}

double feofanova::getArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
   return 0.0;
  }
  std::vector<double> areas(polygon.points.size());
  std::transform(polygon.points.begin(), polygon.points.end() - 1, polygon.points.begin() + 1, areas.begin(), AreaFunctor());
  AreaFunctor func;
  areas.push_back(func(polygon.points.back(), polygon.points.front()));
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return std::abs(area) / 2.0;
}

bool feofanova::isAreaLess(const Polygon& p1, const Polygon& p2)
{
  return getArea(p1) < getArea(p2);
}

bool compareVertexes(const feofanova::Polygon& p1, const feofanova::Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}

bool feofanova::countPerms(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return std::is_permutation(p1.points.cbegin(), p1.points.cend(), p2.points.cbegin());
}

void feofanova::Lessarea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (polygon.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  out << std::count_if(data.cbegin(), data.cend(), std::bind(isAreaLess, _1, polygon)) << '\n';
};

void feofanova::Perms(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (polygon.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  out << std::count_if(data.cbegin(), data.cend(), std::bind(countPerms, _1, polygon)) << '\n';
};

void feofanova::countArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string subcommand = "";
  std::cin >> subcommand;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon&) > countArea = getArea;

  if (subcommand == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), even);
  }
  else if (subcommand == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), odd);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("<INVALID COMMAD>");
    }

    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons));
    }
    else
    {
      size_t nVertexes = 0;
      try
      {
        nVertexes = std::stoull(subcommand);
      }
      catch (const std::invalid_argument&)
      {
        in.setstate(std::ios::failbit);
        throw std::invalid_argument("<INVALID COMMAD>");
      }

      if (nVertexes < 3)
      {
        in.setstate(std::ios::failbit);
        throw std::invalid_argument("<INVALID COMMAD>");
      }

      using namespace std::placeholders;
      auto vertexesFilter = std::bind(checkVertexes, nVertexes, _1);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), vertexesFilter);
    }

    std::vector< double > areas;
    std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), countArea);
    double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    if (subcommand == "MEAN")
    {
      result /= polygons.size();
    }
    out << std::fixed << std::setprecision(1) << result << '\n';
}

void feofanova::countMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("<INVALID COMMAD>");
    }

    std::vector< Polygon >::const_iterator min;
    std::string subcommand;
    std::cin >> subcommand;

    if (subcommand == "AREA")
    {
      min = std::min_element(polygons.cbegin(), polygons.cend(), isAreaLess);
      out << std::fixed << std::setprecision(1) << getArea(*min) << '\n';
    }
    else if (subcommand == "VERTEXES")
    {
      min = std::min_element(polygons.cbegin(), polygons.cend(), compareVertexes);
      out << (*min).points.size() << '\n';
    }
    else
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("INVALID COMMAD>");
    }
}

void feofanova::countMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("<INVALID COMMAD>");
    }

    std::vector< Polygon >::const_iterator max;
    std::string subcommand;
    std::cin >> subcommand;

    if (subcommand == "AREA")
    {
      max = std::max_element(polygons.cbegin(), polygons.cend(), feofanova::isAreaLess);
      out << std::fixed << std::setprecision(1) << getArea(*max) << '\n';
    }
    else if (subcommand == "VERTEXES")
    {
      max = std::max_element(polygons.cbegin(), polygons.cend(), compareVertexes);
      out << std::fixed << std::setprecision(1) << (*max).points.size() << '\n';
    }
    else
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("<INVALID COMMAD>>");
    }
}
