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
    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [](double area, const Polygon &p) -> double {
      return addAreaIf(area, p, checkParity(p, Parity::EVEN));
    });
  }
  else if (subcommand == "ODD")
  {
    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [](double area, const Polygon &p) -> double {
      return addAreaIf(area, p, checkParity(p, Parity::ODD));
    });
  }
  else if (subcommand == "MEAN")
  {
    if (polygons.empty())
    {
      in.setstate(std::ios::failbit);
      throw std::logic_error("warn: at least one polygon is expected");
    }

    double overallArea =
      std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [](double area, const Polygon &p) -> double {
        return area + p.getArea();
      });
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
      throw;
    }

    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [&](float area, const Polygon &p) {
      return addAreaIf(area, p, p.points.size() == nVertexes);
    });
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

  double res = 0.0;
  std::pair< std::vector< Polygon >::const_iterator, std::vector< Polygon >::const_iterator > minmax;
  std::string subcommand;
  std::cin >> subcommand;

  if (subcommand == "AREA")
  {
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(), [](const Polygon &p1, const Polygon &p2) {
      return p1.getArea() < p2.getArea();
    });
    res = min ? (*minmax.first).getArea() : (*minmax.second).getArea();
  }
  else if (subcommand == "VERTEXES")
  {
    minmax = std::minmax_element(polygons.cbegin(), polygons.cend(), [](const Polygon &p1, const Polygon &p2) {
      return p1.points.size() < p2.points.size();
    });
    res = min ? (*minmax.first).points.size() : (*minmax.second).points.size();
  }
  else
  {
    in.setstate(std::ios::failbit);
    throw;
  }

  out << res << '\n';
}
