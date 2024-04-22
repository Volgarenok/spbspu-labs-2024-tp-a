#include "polygonCommands.hpp"
#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <string>
#include <streamGuard.hpp>
#include "polygonHandler.hpp"

void kravchenko::Area::operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::function< double(double, const Polygon&) > accArea;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    accArea = std::bind(AccumulateAreaParity{}, _1, _2, true);
  }
  else if (argument == "ODD")
  {
    accArea = std::bind(AccumulateAreaParity{}, _1, _2, false);
  }
  else if (argument == "MEAN")
  {
    accArea = std::bind(AccumulateAreaMean{ data.size() }, _1, _2);
  }
  else
  {
    try
    {
      accArea = std::bind(AccumulateAreaNumOfVertex{}, _1, _2, std::stoull(argument));
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidCommand();
    }
  }
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(data.cbegin(), data.cend(), 0.0, accArea);
}

double kravchenko::AccumulateAreaParity::operator()(double acc, const Polygon& p, bool isEven)
{
  if (isEven == (p.points.size() % 2 == 0))
  {
    acc += p.getArea();
  }
  return acc;
}

double kravchenko::AccumulateAreaMean::operator()(double acc, const Polygon& p)
{
  return acc + (p.getArea() / numOfPolygons);
}

double kravchenko::AccumulateAreaNumOfVertex::operator()(double acc, const Polygon& p, std::size_t numOfVertexes)
{
  if (numOfVertexes == p.points.size())
  {
    acc += p.getArea();
  }
  return acc;
}

void kravchenko::MinMax::operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out, bool isMin)
{
  std::string argument;
  in >> argument;
  using namespace std::placeholders;
  if (argument == "AREA")
  {
    auto accMinMaxArea = std::bind(AccumulateMinMaxArea{}, _1, _2, isMin);
    double accInit = (isMin) ? std::numeric_limits< double >::max() : 0.0;
    StreamGuard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << std::accumulate(data.cbegin(), data.cend(), accInit, accMinMaxArea);
  }
  else if (argument == "VERTEXES")
  {
    auto accMinMaxVertexes = std::bind(AccumulateMinMaxVertexes{}, _1, _2, isMin);
    std::size_t accVertexesInit = (isMin) ? std::numeric_limits< std::size_t >::max() : 0;
    out << std::accumulate(data.cbegin(), data.cend(), accVertexesInit, accMinMaxVertexes);
  }
  else
  {
    throw InvalidCommand();
  }
}

double kravchenko::AccumulateMinMaxArea::operator()(double acc, const Polygon& p, bool isMin)
{
  return (isMin) ? std::min(acc, p.getArea()) : std::max(acc, p.getArea());
}

std::size_t kravchenko::AccumulateMinMaxVertexes::operator()(std::size_t acc, const Polygon& p, bool isMin)
{
  return (isMin) ? std::min(acc, p.points.size()) : std::max(acc, p.points.size());
}

void kravchenko::Count::operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;
  std::function< bool(const Polygon&) > countPred;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    countPred = std::bind(CountParity{}, _1, true);
  }
  else if (argument == "ODD")
  {
    countPred = std::bind(CountParity{}, _1, false);
  }
  else
  {
    try
    {
      countPred = std::bind(CountNumOfVertex{}, _1, std::stoull(argument));
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidCommand();
    }
  }
  out << std::count_if(data.cbegin(), data.cend(), countPred);
}

bool kravchenko::CountParity::operator()(const Polygon& p, bool isEven)
{
  return (isEven == (p.points.size() % 2 == 0));
}

bool kravchenko::CountNumOfVertex::operator()(const Polygon& p, std::size_t numOfVertexes)
{
  return (p.points.size() == numOfVertexes);
}

void kravchenko::RmEcho::operator()(std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon argument;
  in >> argument;
  if (in)
  {
    using namespace std::placeholders;
    auto identicalPred = std::bind(ConsecutiveIdenticalPolygon{}, _1, _2, argument);
    auto last = std::unique(data.begin(), data.end(), identicalPred);
    std::size_t erasedCount = std::distance(last, data.end());
    data.erase(last, data.end());
    out << erasedCount;
  }
  else
  {
    throw InvalidCommand();
  }
}

bool kravchenko::ConsecutiveIdenticalPolygon::operator()(const Polygon& p1, const Polygon& p2, const Polygon& compared)
{
  return (compared.isIdentical(p1) && compared.isIdentical(p2));
}