#include "polygonCommands.hpp"
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