#include "commands.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include "polygon.hpp"
#include "auxiliaryCommands.hpp"

void ayupov::area(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  out << std::setprecision(1) << std::fixed;
  std::string mod = "";
  in >> mod;
  std::vector<Polygon> polygonsTC; //TC = toCount
  if (mod == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsTC), isEven);
  }
  else if (mod == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsTC), isOdd);
  }
  else if (mod == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("AREA <MEAN> error. No polygons.");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsTC));
  }
  else if (std::all_of(mod.cbegin(), mod.cend(), ::isdigit))
  {
    double vertexesNum = std::stoul(mod);
    if (vertexesNum < 3)
    {
      throw std::logic_error("AREA <num-of-vertexes> error. Wrong number of vertexes.");
    }
    std::function<bool(const Polygon&)> expression = std::bind(isRightSize, std::placeholders::_1, vertexesNum);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsTC), expression);
  }
  else
  {
    throw std::logic_error("AREA error. Wrong modifier.");
  }
  std::vector<double> areas;
  std::transform(polygonsTC.cbegin(), polygonsTC.cend(), std::back_inserter(areas), calculatePolygonArea);
  double result = std::accumulate(polygonsTC.cbegin(), polygonsTC.cend(), 0.0);
  if (mod == "MEAN")
  {
    result /= polygons.size();
  }
  out << result;
}
