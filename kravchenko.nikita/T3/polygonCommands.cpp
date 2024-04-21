#include "polygonCommands.hpp"
#include <exception>
#include <functional>
#include <iomanip>
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