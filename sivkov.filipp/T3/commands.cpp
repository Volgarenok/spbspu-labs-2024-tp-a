#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include "utility.hpp"

namespace sivkov
{
  void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    double area = 0.0;
    std::string arg;
    in >> arg;
    std::map< std::string, std::function< double() > > cmd;
    {
      using namespace std::placeholders;
      cmd["EVEN"] = std::bind(getOddEvenMean, polygons, "EVEN");
      cmd["ODD"] = std::bind(getOddEvenMean, polygons, "ODD");
      cmd["MEAN"] = std::bind(getOddEvenMean, polygons, "MEAN");
    }
    try
    {
      if (!std::all_of(arg.cbegin(), arg.cend(), isdigit))
      {
        throw std::invalid_argument("error argument");
      }
      size_t num = std::stoi(arg);
      if (num < 3)
      {
        throw std::invalid_argument("error number vertexes");
      }
      std::vector< Polygon > sortShape;
      auto operation = std::bind(compare, std::placeholders::_1, num);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(sortShape), operation);
      std::vector< double > areas;
      std::transform(sortShape.cbegin(), sortShape.cend(), std::back_inserter(areas), countAreaShape);
      area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    }
    catch (const std::invalid_argument&)
    {
      area = cmd[arg]();
    }
    out << std::fixed << std::setprecision(1) << area;
  }

  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    std::string arg = "";
    in >> arg;
    size_t count = 0;
    if (arg == "EVEN")
    {
      count = std::count_if(polygons.cbegin(), polygons.cend(), isEvenVertices);
    }
    else if (arg == "ODD")
    {
      count = std::count_if(polygons.cbegin(), polygons.cend(), isOddVertices);
    }
    else
    {
      long long ver = 0;
      try
      {
        ver = std::stoull(arg);
      }
      catch (const std::invalid_argument&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      catch (const std::out_of_range&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      if (ver < 3)
      {
        throw std::invalid_argument("Error vertexes");
      }
      auto hasVertexCountBind = std::bind(hasVertexCount, std::placeholders::_1, ver);
      count = std::count_if(polygons.cbegin(), polygons.cend(), hasVertexCountBind);
    }
    out << count;
  }
  void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Error format");
    }

    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    std::string arg;
    in >> arg;

    if (arg == "AREA")
    {
      minMaxAreas(out, polygons, "MIN");
    }
    else if (arg == "VERTEXES")
    {
      minMaxVertexes(out, polygons, "MIN");
    }
    else
    {
      throw std::invalid_argument("Error arg");
    }
  }

  void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    std::string arg;
    in >> arg;

    if (arg == "AREA")
    {
      minMaxAreas(out, polygons, "MAX");
    }
    else if (arg == "VERTEXES")
    {
      minMaxVertexes(out, polygons, "MAX");
    }
    else
    {
      throw std::invalid_argument("Error arg");
    }
  }

  void perms(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    Polygon targetPolygon;
    if (!(in >> targetPolygon))
    {
      throw std::invalid_argument("Error format");
    }
    using namespace std::placeholders;
    size_t count = std::count_if(polygons.begin(), polygons.end(), std::bind(arePointsPermutations, _1, targetPolygon));

    out << count;
  }

  void inframe(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    Polygon targetPolygon;
    if (!(in >> targetPolygon) || (in.peek() != '\n'))
    {
      throw std::invalid_argument("Error format");
    }

    BoundingBox bbox = calculateBoundingBox(polygons);
    if (isPolygonInsideBoundingBox(targetPolygon, bbox))
    {
      out << "<TRUE>";
    }
    else
    {
      out << "<FALSE>";
    }
  }
}
