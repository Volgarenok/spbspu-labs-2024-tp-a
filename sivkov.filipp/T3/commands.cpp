#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include "utility.hpp"

namespace sivkov
{
  void area(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }
    double area = 0.0;
    std::string argument;
    in >> argument;
    std::map< std::string, std::function< double() > > cmd;
    {
      cmd["EVEN"] = std::bind(getOddEvenMean, polygons, "EVEN");
      cmd["ODD"] = std::bind(getOddEvenMean, polygons, "ODD");
      cmd["MEAN"] = std::bind(getOddEvenMean, polygons, "MEAN");
    }
    try
    {
      if (!std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
      {
        throw std::logic_error("error argument");
      }
      size_t num = std::stoi(argument);
      if (num < 3)
      {
        throw std::invalid_argument("error number vertexes");
      }
      std::vector< Polygon > sortShape;
      using namespace std::placeholders;
      auto operation = std::bind(isNumEqSize, _1, num);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(sortShape), operation);
      std::vector< double > areasShape;
      std::transform(sortShape.cbegin(), sortShape.cend(), std::back_inserter(areasShape), countAreaShape);
      area = std::accumulate(areasShape.cbegin(), areasShape.cend(), 0.0);
    }
    catch (const std::invalid_argument&)
    {
      area = cmd[argument]();
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
  void min(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    std::string arg;
    in >> arg;

    if (polygons.empty())
    {
      throw std::invalid_argument("Error format");
    }

    if (arg == "AREA")
    {
      auto minIt = std::min_element(polygons.begin(), polygons.end(), MinArea());
      if (minIt != polygons.end())
      {
        double minArea = countAreaShape(*minIt);
        out << std::fixed << std::setprecision(1) << minArea;
      }
      else
      {
        throw std::invalid_argument("Error format");
      }
    }
    else if (arg == "VERTEXES")
    {
      auto minIt = std::min_element(polygons.begin(), polygons.end(), MinVertices());
      if (minIt != polygons.end())
      {
        size_t minVertices = minIt->points.size();
        out << minVertices;
      }
      else
      {
        throw std::invalid_argument("Error format");
      }
    }
    else
    {
      throw std::invalid_argument("Error format");
    }
  }
  void max(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return;
    }

    std::string arg;
    in >> arg;

    if (polygons.empty())
    {
      throw std::invalid_argument("Error format");
      return;
    }

    if (arg == "AREA")
    {
      auto maxIt = std::max_element(polygons.begin(), polygons.end(), MaxArea());
      if (maxIt != polygons.end())
      {
        double maxArea = countAreaShape(*maxIt);
        out << std::fixed << std::setprecision(1) << maxArea;
      }
      else
      {
        throw std::invalid_argument("Error format");
      }
    }
    else if (arg == "VERTEXES")
    {
      auto maxIt = std::max_element(polygons.begin(), polygons.end(), MaxVertices());
      if (maxIt != polygons.end())
      {
        size_t maxVertices = maxIt->points.size();
        out << maxVertices;
      }
      else
      {
        throw std::invalid_argument("Error format");
      }
    }
    else
    {
      throw std::invalid_argument("Error format");
    }
  }

  void perms(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
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

  void inframe(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
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
