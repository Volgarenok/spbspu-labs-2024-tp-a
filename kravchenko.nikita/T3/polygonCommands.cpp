#include "polygonCommands.hpp"
#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <string>
#include <streamGuard.hpp>

void kravchenko::Area::operator()(CommandArguments args)
{
  std::string argument;
  args.in >> argument;
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
    if (args.data.size() == 0)
    {
      throw InvalidCommand();
    }
    accArea = std::bind(AccumulateAreaMean{ args.data.size() }, _1, _2);
  }
  else
  {
    try
    {
      std::size_t numOfVertexes = std::stoull(argument);
      if (numOfVertexes < 3)
      {
        throw std::invalid_argument();
      }
      accArea = std::bind(AccumulateAreaNumOfVertex{}, _1, _2, numOfVertexes);
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidCommand();
    }
  }
  StreamGuard guard(args.out);
  args.out << std::setprecision(1) << std::fixed;
  args.out << std::accumulate(args.data.cbegin(), args.data.cend(), 0.0, accArea);
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

void kravchenko::MinMax::operator()(CommandArguments args, bool isMin)
{
  if (args.data.size() == 0)
  {
    throw InvalidCommand();
  }
  std::string argument;
  args.in >> argument;
  using namespace std::placeholders;
  if (argument == "AREA")
  {
    auto accMinMaxArea = std::bind(AccumulateMinMaxArea{}, _1, _2, isMin);
    double accInit = (isMin) ? std::numeric_limits< double >::max() : 0.0;
    StreamGuard guard(args.out);
    args.out << std::setprecision(1) << std::fixed;
    args.out << std::accumulate(args.data.cbegin(), args.data.cend(), accInit, accMinMaxArea);
  }
  else if (argument == "VERTEXES")
  {
    auto accMinMaxVertexes = std::bind(AccumulateMinMaxVertexes{}, _1, _2, isMin);
    std::size_t accVertexesInit = (isMin) ? std::numeric_limits< std::size_t >::max() : 0;
    args.out << std::accumulate(args.data.cbegin(), args.data.cend(), accVertexesInit, accMinMaxVertexes);
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

void kravchenko::Count::operator()(CommandArguments args)
{
  std::string argument;
  args.in >> argument;
  std::function< bool(const Polygon&) > countPred;
  using namespace std::placeholders;
  if (argument == "EVEN")
  {
    countPred = std::bind(ParityPred{}, _1, true);
  }
  else if (argument == "ODD")
  {
    countPred = std::bind(ParityPred{}, _1, false);
  }
  else
  {
    try
    {
      std::size_t numOfVertexes = std::stoull(argument);
      if (numOfVertexes < 3)
      {
        throw std::invalid_argument();
      }
      countPred = std::bind(NumOfVertexPred{}, _1, );
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidCommand();
    }
  }
  args.out << std::count_if(args.data.cbegin(), args.data.cend(), countPred);
}

bool kravchenko::ParityPred::operator()(const Polygon& p, bool isEven)
{
  return (isEven == (p.points.size() % 2 == 0));
}

bool kravchenko::NumOfVertexPred::operator()(const Polygon& p, std::size_t numOfVertexes)
{
  return (p.points.size() == numOfVertexes);
}

void kravchenko::RmEcho::operator()(CommandArguments args)
{
  Polygon argument;
  args.in >> argument;
  if (args.in)
  {
    using namespace std::placeholders;
    auto identicalPred = std::bind(ConsecutiveIdenticalPolygonPred{}, _1, _2, argument);
    auto last = std::unique(args.data.begin(), args.data.end(), identicalPred);
    std::size_t erasedCount = std::distance(last, args.data.end());
    args.data.erase(last, args.data.end());
    args.out << erasedCount;
  }
  else
  {
    throw InvalidCommand();
  }
}

bool kravchenko::ConsecutiveIdenticalPolygonPred::operator()(const Polygon& p1, const Polygon& p2, const Polygon& compared)
{
  return (compared.isIdentical(p1) && compared.isIdentical(p2));
}

void kravchenko::RightShapes::operator()(CommandArguments args)
{
  args.out << std::count_if(args.data.cbegin(), args.data.cend(), RightPolygonsPred{});
}

bool kravchenko::RightPolygonsPred::operator()(const Polygon& p)
{
  return p.hasRightAngle();
}
