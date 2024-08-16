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

void ayupov::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  out << std::setprecision(1) << std::fixed;
  std::string mod = "";
  in >> mod;
  std::vector< Polygon > polygonsTC;
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
    size_t vertexesNum = std::stoul(mod);
    if (vertexesNum < 3)
    {
      throw std::logic_error("AREA <num-of-vertexes> error. Wrong number of vertexes.");
    }
    std::function< bool(const Polygon&) > expression = std::bind(isRightSize, std::placeholders::_1, vertexesNum);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsTC), expression);
  }
  else
  {
    throw std::logic_error("AREA error. Wrong modifier.");
  }
  std::vector< double > areas(polygonsTC.size());
  std::transform(polygonsTC.cbegin(), polygonsTC.cend(), std::back_inserter(areas), calculatePolygonArea);
  double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (mod == "MEAN")
  {
    result /= polygons.size();
  }
  out << result;
}
void ayupov::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string key = "";
  in >> key;
  if (polygons.empty())
  {
    throw std::logic_error("No polygons");
  }
  else if (key == "AREA")
  {
    out << std::setprecision(1) << std::fixed << maxArea(polygons);
  }
  else if (key == "VERTEXES")
  {
    out << maxVertexes(polygons);
  }
  else
  {
    throw std::logic_error("Wrong key");
  }
}
void ayupov::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string key = "";
  in >> key;
  if (polygons.empty())
  {
    throw std::logic_error("No polygons");
  }
  else if (key == "AREA")
  {
    out << std::setprecision(1) << std::fixed << minArea(polygons);
  }
  else if (key == "VERTEXES")
  {
    out << minVertexes(polygons);
  }
  else
  {
    throw std::logic_error("Wrong key");
  }
}
void ayupov::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string key = "";
  in >> key;
  if (key == "EVEN")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }
  else if (key == "ODD")
  {
    out << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else if (std::all_of(key.begin(), key.end(), ::isdigit))
  {
    if (std::stoi(key) < 3)
    {
      throw std::logic_error("Wrong number of vertexes");
    }
    else
    {
      std::function< size_t(const Polygon&) > counter = std::bind(isRightSize, std::placeholders::_1, std::stoi(key));
      out << std::count_if(polygons.cbegin(), polygons.cend(), counter);
    }
  }
  else
  {
    throw std::logic_error("Wrong key");
  }
}
void ayupov::echo(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon newPoly;
  in >> newPoly;
  if (in)
  {
    size_t sameCounter = 0;
    std::vector< Polygon > temp;
    for (auto& polygon : polygons)
    {
      temp.push_back(polygon);
      if (polygon == newPoly)
      {
        temp.push_back(polygon);
        ++sameCounter;
      }
    }
    polygons = temp;
    out << sameCounter;
  }
  else
  {
    throw std::logic_error("Wrong polygon");
  }
}
void ayupov::inFrame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon poly;
  in >> poly;
  if (in)
  {
    std::pair< Point, Point > nullFrame{{0,0},{0,0}};
    auto frame = std::accumulate(polygons.cbegin(), polygons.cend(), nullFrame, getFrameRectangle);
    auto criteria = std::bind(isPointInFrame, frame, std::placeholders::_1);
    size_t pointsInFrame = std::count_if(poly.points.cbegin(), poly.points.cend(), criteria);
    if (pointsInFrame == poly.points.size())
    {
      out << "<TRUE>";
    }
    else
    {
      out << "<FALSE>";
    }
  }
  else
  {
    throw std::logic_error("Wrong polygon");
  }
}
void ayupov::maxSeq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon poly;
  in >> poly;
  if (in)
  {
    std::vector< size_t > lengths(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(lengths),
      std::bind(getSequenceLength, std::placeholders::_1, poly, std::cref(lengths)));
    out << *std::max_element(lengths.cbegin(), lengths.cend());
  }
  else
  {
    throw std::logic_error("Wrong polygon");
  }
}
void ayupov::lessArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon poly;
  in >> poly;
  if (in)
  {
    auto func = std::bind(areaComparer, std::placeholders::_1, poly);
    out << std::count_if(polygons.cbegin(), polygons.cend(), func);
  }
  else
  {
    throw std::logic_error("Wrong polygon");
  }
}
