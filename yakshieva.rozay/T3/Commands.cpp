#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include "AreaCalculator.hpp"
#include <StreamGuard.hpp>

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
}

namespace yakshieva
{
  struct LessArea
  {
    double referenceArea;
    bool operator()(const Polygon& polygon) const;
  };
}

bool yakshieva::LessArea::operator()(const Polygon& polygon) const
{
  return accamulateAllParts(polygon) < referenceArea;
}

void yakshieva::doLessAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon refPolygon;
  in >> refPolygon;
  if (!(in && in.peek() == '\n'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto lessAreaCount = std::count_if(polygons.begin(), polygons.end(), LessArea{ accamulateAllParts(refPolygon) });
  out << lessAreaCount << "\n";
}

namespace yakshieva
{
  struct PolygonComparator
  {
    const Polygon& target;
    bool operator()(const Polygon& p1, const Polygon& p2) const;
  };
  size_t removeConsecutiveDuplicates(std::vector< Polygon >& polygons, const Polygon& target);
}

bool yakshieva::PolygonComparator::operator()(const Polygon& p1, const Polygon& p2) const
{
  return p1 == p2 && p2 == target;
}

size_t yakshieva::removeConsecutiveDuplicates(std::vector< Polygon >& polygons, const Polygon& target)
{
  PolygonComparator comparator{ target };
  size_t removedCount = 0;
  auto it = std::adjacent_find(polygons.begin(), polygons.end(), std::bind(comparator, std::placeholders::_1, std::placeholders::_2));
  while (it != polygons.end())
  {
    it = polygons.erase(it);
    ++removedCount;
    it = std::adjacent_find(it, polygons.end(), std::bind(comparator, std::placeholders::_1, std::placeholders::_2));
  }
  return removedCount;
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
  size_t removedCount = removeConsecutiveDuplicates(polygons, polygon);
  out << removedCount << "\n";
}

void yakshieva::duplicateEntries(std::vector< Polygon >& p, const Polygon& targetP)
{
  std::vector< Polygon > temp;
  for (const auto & poly : p)
  {
    temp.push_back(poly);
    if (poly == targetP)
    {
      temp.push_back(targetP);
    }
  }
  p = std::move(temp);
}

void yakshieva::doEchoCommand(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon arg;
  in >> arg;
  if (!in)
  {
    throw std::logic_error("Wrong argument");
  }
  std::string restOfLine;
  std::getline(in, restOfLine);
  size_t count = std::count(polygons.cbegin(), polygons.cend(), arg);
  if (count == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << count << "\n";
  duplicateEntries(polygons, arg);
}

