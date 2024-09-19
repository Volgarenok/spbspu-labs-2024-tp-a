#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include "polygon_area.hpp"
#include "polygon_utils.hpp"
#include "polygon_vertices.hpp"
#include "polygon_inframe.hpp"

namespace sivkov
{
  void area(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
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
      size_t ver = std::stoi(arg);
      if (ver < 3)
      {
        throw std::invalid_argument("error number vertexes");
      }
      std::vector< Polygon > shape;
      auto operation = std::bind(isPointCountEqual, std::placeholders::_1, ver);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(shape), operation);
      std::vector< double > areas;
      std::transform(shape.cbegin(), shape.cend(), std::back_inserter(areas), calculateArea);
      area = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    }
    catch (const std::invalid_argument&)
    {
      area = cmd[arg]();
    }
    out << std::fixed << std::setprecision(1) << area;
  }

  void min(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
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
      minArea(out, polygons);
    }
    else if (arg == "VERTEXES")
    {
      minVertex(out, polygons);
    }
    else
    {
      throw std::invalid_argument("Error arg");
    }
  }

  void max(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
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
      maxArea(out, polygons);
    }
    else if (arg == "VERTEXES")
    {
      maxVertex(out, polygons);
    }
    else
    {
      throw std::invalid_argument("Error arg");
    }
  }

  void count(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
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

  void perms(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    Polygon polygon;
    in >> polygon;
    if (polygon.points.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (polygon.points.size() < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    out << std::count_if(polygons.begin(), polygons.end(), std::bind(isPerms, std::placeholders::_1, polygon));
  }

  void inFrame(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    Polygon polygon;
    in >> polygon;

    if (!in || in.peek() != '\n' || polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::pair< Point, Point> frameRectangle = findOverallBoundingBox(polygons);

    if (ifInFrame(polygon, frameRectangle))
    {
      out << "<TRUE>";
    }
    else
    {
      out << "<FALSE>";
    }
  }
}
