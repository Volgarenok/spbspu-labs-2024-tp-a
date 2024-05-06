#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include <streamGuard.hpp>
#include "polygonCommands.hpp"

void kravchenko::cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< double(double, const Polygon&) > accArea;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    accArea = std::bind(area::AccumulateAreaParity{}, _1, _2, true);
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    accArea = std::bind(area::AccumulateAreaParity{}, _1, _2, false);
  }
  else if (argument == "MEAN")
  {
    if (data.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    accArea = std::bind(area::AccumulateAreaMean{ data.size() }, _1, _2);
  }
  else
  {
    std::size_t numOfVertexes = 0;
    try
    {
      numOfVertexes = std::stoull(argument);
    }
    catch(const std::invalid_argument&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    accArea = std::bind(area::AccumulateAreaNumOfVertex{ numOfVertexes }, _1, _2);
  }

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(data.cbegin(), data.cend(), 0.0, accArea);
}

double kravchenko::area::AccumulateAreaParity::operator()(double acc, const Polygon& p, bool isEven)
{
  if (isEven == (p.points.size() % 2 == 0))
  {
    acc += p.getArea();
  }
  return acc;
}

double kravchenko::area::AccumulateAreaMean::operator()(double acc, const Polygon& p)
{
  return acc + (p.getArea() / numOfPolygons);
}

double kravchenko::area::AccumulateAreaNumOfVertex::operator()(double acc, const Polygon& p)
{
  if (numOfVertexes == p.points.size())
  {
    acc += p.getArea();
  }
  return acc;
}

void kravchenko::cmdMinMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, bool isMin)
{
  if (data.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string argument;
  in >> argument;

  if (argument == "AREA")
  {
    using namespace std::placeholders;
    auto accMinMaxArea = std::bind(minMax::AccumulateMinMaxArea{}, _1, _2, isMin);
    double accInit = (isMin) ? std::numeric_limits< double >::max() : 0.0;
    StreamGuard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << std::accumulate(data.cbegin(), data.cend(), accInit, accMinMaxArea);
  }
  else if (argument == "VERTEXES")
  {
    using namespace std::placeholders;
    auto accMinMaxVertexes = std::bind(minMax::AccumulateMinMaxVertexes{}, _1, _2, isMin);
    std::size_t accVertexesInit = (isMin) ? std::numeric_limits< std::size_t >::max() : 0;
    out << std::accumulate(data.cbegin(), data.cend(), accVertexesInit, accMinMaxVertexes);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

double kravchenko::minMax::AccumulateMinMaxArea::operator()(double acc, const Polygon& p, bool isMin)
{
  return (isMin) ? std::min(acc, p.getArea()) : std::max(acc, p.getArea());
}

std::size_t kravchenko::minMax::AccumulateMinMaxVertexes::operator()(std::size_t acc, const Polygon& p, bool isMin)
{
  return (isMin) ? std::min(acc, p.points.size()) : std::max(acc, p.points.size());
}

void kravchenko::cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< bool(const Polygon&) > countPred;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    countPred = std::bind(count::ParityPred{}, _1, true);
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    countPred = std::bind(count::ParityPred{}, _1, false);
  }
  else
  {
    std::size_t numOfVertexes = 0;
    try
    {
      numOfVertexes = std::stoull(argument);
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    if (numOfVertexes < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    countPred = std::bind(count::NumOfVertexPred{ numOfVertexes }, _1);
  }
  out << std::count_if(data.cbegin(), data.cend(), countPred);
}

bool kravchenko::count::ParityPred::operator()(const Polygon& p, bool isEven)
{
  return (isEven == (p.points.size() % 2 == 0));
}

bool kravchenko::count::NumOfVertexPred::operator()(const Polygon& p)
{
  return (p.points.size() == numOfVertexes);
}

void kravchenko::cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon argument;
  if (in >> argument)
  {
    using namespace std::placeholders;
    auto identical = std::bind(&Polygon::isIdentical, argument, _1);
    auto identicalPred = std::bind(std::logical_and< bool >{}, std::bind(identical, _1), std::bind(identical, _2));
    auto last = std::unique(data.begin(), data.end(), identicalPred);
    std::size_t erasedCount = std::distance(last, data.end());
    data.erase(last, data.end());
    out << erasedCount;
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kravchenko::cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out)
{
  using namespace std::placeholders;
  out << std::count_if(data.cbegin(), data.cend(), std::bind(&Polygon::hasRightAngle, _1));
}
