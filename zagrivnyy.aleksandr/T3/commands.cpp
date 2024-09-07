#include "commands.hpp"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "filters.hpp"
#include "polygon.hpp"

void zagrivnyy::area(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcommand = "";
  std::cin >> subcommand;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon &) > countArea = getPolygonArea;

  if (subcommand == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), isEven);
  }
  else if (subcommand == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), isOdd);
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("warn: at least one polygon is expected");
    }

    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons));
    using namespace std::placeholders;
    countArea = std::bind(calcMeanArea, _1, polygons.size());
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("usage: AREA <EVEN|ODD|MEAN|num-of-vertexes>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("warn: At least 3 points are possible");
    }

    using namespace std::placeholders;
    auto vertexesFilter = std::bind(isVertexesCount, nVertexes, _1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), vertexesFilter);
  }

  std::vector< double > areas;
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), countArea);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
}

void zagrivnyy::minMax(const std::vector< Polygon > &polygons, bool min, std::istream &in, std::ostream &out)
{
  if (polygons.empty())
  {
    in.setstate(std::ios::failbit);
    throw std::logic_error("warn: at least one polygon is expected");
  }

  std::pair< std::vector< Polygon >::const_iterator, std::vector< Polygon >::const_iterator > minmax;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(), compareAreas);
    out << (min ? getPolygonArea(*minmax.first) : getPolygonArea(*minmax.second)) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(), compareVertexes);
    out << (min ? (*minmax.first).points.size() : (*minmax.second).points.size()) << '\n';
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("usage: MIN|MAX <AREA|VERTEXES>");
  }
}

void zagrivnyy::count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  int res = 0.0;
  std::string subcommand = "";
  std::cin >> subcommand;

  if (subcommand == "EVEN")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }
  else if (subcommand == "ODD")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else
  {
    size_t nVertexes = 0;
    try
    {
      nVertexes = std::stoull(subcommand);
    }
    catch (const std::invalid_argument &)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("usage: COUNT <EVEN|ODD|num-of-vertexes>");
    }

    if (nVertexes < 3)
    {
      in.setstate(std::ios::failbit);
      throw std::invalid_argument("warn: at least 3 points are possible");
    }

    using namespace std::placeholders;
    auto vertexesFilter = std::bind(isVertexesCount, nVertexes, _1);
    res = std::count_if(polygons.cbegin(), polygons.cend(), vertexesFilter);
  }

  out << res << '\n';
}

void zagrivnyy::rmecho(std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon src;
  in >> src;

  if (src.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("warn: expected polygon with 3 or more points");
  }

  using namespace std::placeholders;
  auto isEqual = std::bind(std::equal_to< Polygon >(), src, _1);
  auto last = std::unique(polygons.begin(), polygons.end(),
    std::bind(std::logical_and< bool >{}, std::bind(isEqual, _1), std::bind(isEqual, _2)));

  ptrdiff_t res = std::distance(last, polygons.end());
  polygons.erase(last, polygons.end());

  out << res << '\n';
}

void zagrivnyy::intersections(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  Polygon src;
  in >> src;

  if (src.points.empty() || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    throw std::invalid_argument("warn: expected polygon with 3 or more points");
  }

  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isIntersects, src, std::placeholders::_1)) << '\n';
}
