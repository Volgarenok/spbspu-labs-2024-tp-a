#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <fstream>
#include <string>
#include <iterator>
#include <numeric>
#include "polygon.hpp"
#include "helpCommands.hpp"


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
      using namespace std::placeholders;
      cmd["EVEN"] = std::bind(getOddEvenMean, polygons, "EVEM");
      cmd["ODD"] = std::bind(getOddEvenMean, polygons, "ODD");
      cmd["MEAN"] = std::bind(getOddEvenMean, polygons, "MEAN");
    }
    try
    {
      if (!std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
      {
        throw std::invalid_argument("error argument");
      }
      size_t num = std::stoi(argument);
      if (num < 3)
      {
        throw std::invalid_argument("error number vertexes");
      }
      std::vector< Polygon > sortShape;
      auto operation = std::bind(isNumEqSize, std::placeholders::_1, num);
      std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(sortShape), operation);
      std::vector< double > areasShape;
      std::transform(sortShape.cbegin(), sortShape.cend(), std::back_inserter(areasShape), countAreaShape);
      area = std::accumulate(areasShape.cbegin(), areasShape.cend(), 0.0);
    }
    catch (const std::invalid_argument&)
    {
      area = cmd[argument]();
    }
    out << std::fixed << std::setprecision(1) << area << '\n';
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
      catch(const std::invalid_argument&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      catch (const std::out_of_range&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      auto hasVertexCountBind = std::bind(hasVertexCount, std::placeholders::_1, ver);
      count = std::count_if(polygons.cbegin(), polygons.cend(), hasVertexCountBind);
    }
    out << count << "\n";
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
      out << "No polygons provided" << std::endl;
      return;
    }

    if (arg == "AREA")
    {
      auto minIt = std::min_element(polygons.begin(), polygons.end(), MinArea());
      if (minIt != polygons.end())
      {
        double minArea = countAreaShape(*minIt);
        out << std::fixed << std::setprecision(1) << minArea << '\n';
      }
      else
      {
        out << "No valid polygon found" << std::endl;
      }
    }
    else if (arg == "VERTEXES")
    {
      auto minIt = std::min_element(polygons.begin(), polygons.end(), MinVertices());
      if (minIt != polygons.end())
      {
        size_t minVertices = minIt->points.size();
        out << minVertices << '\n';
      }
      else
      {
        out << "No valid polygon found" << std::endl;
      }
    }
    else
    {
      out << "<INVALID COMMAND>\n";
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
      out << "No polygons provided" << std::endl;
      return;
    }

    if (arg == "AREA")
    {
      auto maxIt = std::max_element(polygons.begin(), polygons.end(), MaxArea());
      if (maxIt != polygons.end())
      {
        double maxArea = countAreaShape(*maxIt);
        out << std::fixed << std::setprecision(1) << maxArea << '\n';
      }
      else
      {
        out << "No valid polygon found" << std::endl;
      }
    }
    else if (arg == "VERTEXES")
    {
      auto maxIt = std::max_element(polygons.begin(), polygons.end(), MaxVertices());
      if (maxIt != polygons.end())
      {
        size_t maxVertices = maxIt->points.size();
        out << maxVertices << '\n';
      }
      else
      {
        out << "No valid polygon found" << std::endl;
      }
    }
    else
    {
      out << "<INVALID COMMAND>\n";
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
      out << "<INVALID POLYGON FORMAT>\n";
      return;
    }
    using namespace std::placeholders;
    size_t count = std::count_if(polygons.begin(), polygons.end(), std::bind(arePointsPermutations, _1, targetPolygon));

    out << count << '\n';
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
      out << "<INVALID POLYGON FORMAT>\n";
      return;
    }

    if (polygons.empty())
    {
      out << "<FALSE>\n";
      return;
    }

    BoundingBox bbox = calculateBoundingBox(polygons);

    if (isPolygonInsideBoundingBox(targetPolygon, bbox))
    {
      out << "<TRUE>\n";
    }
    else
    {
      out << "<FALSE>\n";
    }
  }
}


int main(int argc, char* argv[])
{
  using namespace sivkov;
  if (argc != 2)
  {
    std::cerr << "error cmd\n";
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "error file\n";
    return 1;
  }

  std::vector< Polygon > polygons;

  using input_iter = std::istream_iterator< Polygon >;

  while (!in.eof())
  {
    std::copy(input_iter{ in }, input_iter{}, std::back_inserter(polygons));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::string arg = "";
  while (std::cin >> arg)
  {
    try
    {
      if (arg == "COUNT")
      {
        count(std::cin, std::cout, polygons);
      }
      else if (arg == "AREA")
      {
        area(std::cin, std::cout, polygons);
      }
      else if (arg == "MIN")
      {
        min(std::cin, std::cout, polygons);
      }
      else if (arg == "MAX")
      {
        max(std::cin, std::cout, polygons);
      }
      else if (arg == "INFRAME")
      {
        inframe(std::cin, std::cout, polygons);
      }
      else if (arg == "PERMS")
      {
        perms(std::cin, std::cout, polygons);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;

}
