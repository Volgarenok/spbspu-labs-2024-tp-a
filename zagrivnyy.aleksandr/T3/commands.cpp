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

  using namespace std::placeholders;
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
      throw std::logic_error("At least one point is expected");
    }

    double overallArea =
      std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [](double area, const Polygon &polygon) -> double {
        return area + polygon.getArea();
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

    res = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, [&](float area, const Polygon &polygon) {
      return polygon.points.size() == nVertexes ? area + polygon.getArea() : area;
    });
  }

  out << res << '\n';
}
