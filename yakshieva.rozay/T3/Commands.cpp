#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <map>
#include <string>
#include "AreaCalculator.hpp"
#include "CommandList.hpp"
#include "StreamGuard.hpp"

void yakshieva::doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  double result = 0.0;
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< double() > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(calculateAreaEven, polygons);
    cmds["ODD"] = std::bind(calculateAreaOdd, polygons);
    cmds["MEAN"] = std::bind(calculateAreaMean, polygons);
  }
  try
  {
    size_t number = std::stoull(argument);
    if (number < 3)
    {
      throw std::logic_error("Cannot be a polygon with such vertex number");
    }
    result = sumAreaWithNumOfVertices(polygons, number);
  }
  catch (const std::invalid_argument&)
  {
    result = cmds[argument]();
  }
  StreamGuard guard(out);
  out << std::fixed << std::setprecision(1);
  out << result << "\n";
}

void yakshieva::doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< double() > > cmdArea;
  std::map< std::string, std::function< size_t() > > cmdVertexes;
  cmdArea["AREA"] = std::bind(getMaxArea, polygons);
  cmdVertexes["VERTEXES"] = std::bind(getMaxVertexes, polygons);
  if (cmdArea.find(argument) != cmdArea.end())
  {
    out << std::fixed << std::setprecision(1);
    out << cmdArea[argument]() << "\n";
  }
  else if (cmdVertexes.find(argument) != cmdVertexes.end())
  {
    out << cmdVertexes[argument]() << "\n";
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void yakshieva::doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< double() > > cmdArea;
  std::map< std::string, std::function< size_t() > > cmdVertexes;
  cmdArea["AREA"] = std::bind(getMinArea, polygons);
  cmdVertexes["VERTEXES"] = std::bind(getMinVertexes, polygons);
  if (cmdArea.find(argument) != cmdArea.end())
  {
    out << std::fixed << std::setprecision(1);
    out << cmdArea[argument]() << "\n";
  }
  else if (cmdVertexes.find(argument) != cmdVertexes.end())
  {
    out << cmdVertexes[argument]() << "\n";
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void yakshieva::doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string s;
  in >> s;
  if (s == "EVEN")
  {
    out << std::count_if(polygons.begin(), polygons.end(), isVertexEven) << "\n";
  }
  else if (s == "ODD")
  {
    out << std::count_if(polygons.begin(), polygons.end(), isVertexOdd) << "\n";
  }
  else if (s == std::to_string(std::stoi(s)))
  {
    size_t num = static_cast< size_t >(std::stoi(s));
    if (num < 3)
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      using namespace std::placeholders;
      out << std::count_if(polygons.begin(), polygons.end(), std::bind(hasNumOfVertices, _1, num)) << "\n";
    }
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void yakshieva::doLessAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon refPolygon;
  in >> refPolygon;
  if (!in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto lessAreaCount = std::count_if(polygons.begin(), polygons.end(), LessArea{ accamulateAllParts(refPolygon) });
  out << lessAreaCount << "\n";
}

void yakshieva::doRmechoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  std::string restOfLine;
  std::getline(in, restOfLine);
  if (!restOfLine.empty() || !in)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::size_t removedCount = removeConsecutiveDuplicates(polygons, polygon);
  out << removedCount << "\n";
}

void yakshieva::doEchoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  Polygon arg;
  in >> arg;
  std::string restOfLine;
  std::getline(in, restOfLine);
  if (!restOfLine.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::size_t count = std::count(polygons.cbegin(), polygons.cend(), arg);
  out << count << "\n";
  duplicateEntries(polygons, arg);
}
