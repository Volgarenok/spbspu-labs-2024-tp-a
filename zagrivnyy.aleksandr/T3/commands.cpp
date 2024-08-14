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
  double res = 0.0;
  std::string subcommand = "";
  std::cin >> subcommand;

  if (subcommand == "EVEN")
  {
    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,
      [](double area, const Polygon &p) -> double { return addAreaIf(area, p, isEven(p)); });
  }
  else if (subcommand == "ODD")
  {
    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,
      [](double area, const Polygon &p) -> double { return addAreaIf(area, p, isOdd(p)); });
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("warn: at least one polygon is expected");
    }

    double overallArea = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,
      [](double area, const Polygon &p) -> double { return area + p.getArea(); });
    res = overallArea / polygons.size();
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

    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [nVertexes](float area, const Polygon &p) {
      return addAreaIf(area, p, p.points.size() == nVertexes);
    }) << '\n';
    return;
  }

  out << res << '\n';
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
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(),
      [](const Polygon &p1, const Polygon &p2) { return p1.getArea() < p2.getArea(); });
    out << (min ? (*minmax.first).getArea() : (*minmax.second).getArea()) << '\n';
  }
  else if (subcommand == "VERTEXES")
  {
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(),
      [](const Polygon &p1, const Polygon &p2) { return p1.points.size() < p2.points.size(); });
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
    res = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon &p) { return isEven(p); });
  }
  else if (subcommand == "ODD")
  {
    res = std::count_if(polygons.cbegin(), polygons.cend(), [](const Polygon &p) { return isOdd(p); });
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

    res = std::count_if(polygons.cbegin(), polygons.cend(),
      [nVertexes](const Polygon &p) { return p.points.size() == nVertexes; });
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
