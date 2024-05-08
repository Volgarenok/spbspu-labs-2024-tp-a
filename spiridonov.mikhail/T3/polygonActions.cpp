#include <algorithm>
#include <functional>
#include <iomanip>
#include <limits>
#include <numeric>
#include <string>
#include "polygonActions.hpp"

const char* spiridonov::InvalidActionException::what() const noexcept
{
  return "<INVALID COMMAND>";
}

void spiridonov::areaAction(const std::vector<Polygon>& polygons, ActionStreams args)
{
  std::string argument;
  args.in >> argument;

  std::function< double(double, const Polygon&) > accArea;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    accArea = std::bind(AccumulateAreaParity{}, _1, _2, true);
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    accArea = std::bind(AccumulateAreaParity{}, _1, _2, false);
  }
  else if (argument == "MEAN")
  {
    if (polygons.empty())
    {
      throw InvalidActionException();
    }
    using namespace std::placeholders;
    accArea = std::bind(AccumulateAreaMean{ polygons.size() }, _1, _2);
  }
  else
  {
    std::size_t numberOfVertices = 0;
    try
    {
      numberOfVertices = std::stoull(argument);
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidActionException();
    }
    if (numberOfVertices < 3)
    {
      throw InvalidActionException();
    }
    using namespace std::placeholders;
    accArea = std::bind(AccumulateAreaNumOfVertex{ numberOfVertices }, _1, _2);
  }

  args.out << std::setprecision(1) << std::fixed;
  args.out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accArea);
}

double spiridonov::AccumulateAreaParity::operator()(double acc, const Polygon& polygon, bool isEven)
{
  if (isEven == (polygon.points.size() % 2 == 0))
  {
    acc += polygon.getArea();
  }
  return acc;
}

double spiridonov::AccumulateAreaMean::operator()(double acc, const Polygon& polygon)
{
  return acc + (polygon.getArea() / numberOfPolygons);
}

double spiridonov::AccumulateAreaNumOfVertex::operator()(double acc, const Polygon& polygon)
{
  if (numberOfVertices == polygon.points.size())
  {
    acc += polygon.getArea();
  }
  return acc;
}

void spiridonov::minMaxAction(const std::vector< Polygon >& polygons, ActionStreams args, bool isMin)
{
  if (polygons.size() == 0)
  {
    throw InvalidActionException();
  }

  std::string argument;
  args.in >> argument;

  if (argument == "AREA")
  {
    using namespace std::placeholders;
    auto accMinMaxArea = std::bind(AccumulateMinMaxArea{}, _1, _2, isMin);
    double accInit = (isMin) ? std::numeric_limits< double >::max() : 0.0;
    args.out << std::setprecision(1) << std::fixed;
    args.out << std::accumulate(polygons.cbegin(), polygons.cend(), accInit, accMinMaxArea);
  }
  else if (argument == "VERTEXES")
  {
    using namespace std::placeholders;
    auto accMinMaxVertexes = std::bind(AccumulateMinMaxVertexes{}, _1, _2, isMin);
    std::size_t accVertexesInit = (isMin) ? std::numeric_limits< std::size_t >::max() : 0;
    args.out << std::accumulate(polygons.cbegin(), polygons.cend(), accVertexesInit, accMinMaxVertexes);
  }
  else
  {
    throw InvalidActionException();
  }
}

double spiridonov::AccumulateMinMaxArea::operator()(double acc, const Polygon& polygon, bool isMin)
{
  return (isMin) ? std::min(acc, polygon.getArea()) : std::max(acc, polygon.getArea());
}

std::size_t spiridonov::AccumulateMinMaxVertexes::operator()(std::size_t acc, const Polygon& polygon, bool isMin)
{
  return (isMin) ? std::min(acc, polygon.points.size()) : std::max(acc, polygon.points.size());
}

void spiridonov::countAction(const std::vector< Polygon >& polygons, ActionStreams args)
{
  std::string argument;
  args.in >> argument;

  std::function< bool(const Polygon&) > countPred;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    countPred = std::bind(ParityPred{}, _1, true);
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    countPred = std::bind(ParityPred{}, _1, false);
  }
  else
  {
    std::size_t numberOfVertices = 0;
    try
    {
      numberOfVertices = std::stoull(argument);
    }
    catch (const std::invalid_argument&)
    {
      throw InvalidActionException();
    }
    if (numberOfVertices < 3)
    {
      throw InvalidActionException();
    }
    using namespace std::placeholders;
    countPred = std::bind(NumOfVertexPred{ numberOfVertices }, _1);
  }
  args.out << std::count_if(polygons.cbegin(), polygons.cend(), countPred);
}

bool spiridonov::ParityPred::operator()(const Polygon& polygon, bool isEven)
{
  return (isEven == (polygon.points.size() % 2 == 0));
}

bool spiridonov::NumOfVertexPred::operator()(const Polygon& polygon)
{
  return (polygon.points.size() == numberOfVertices);
}

void spiridonov::echoAction(std::vector< Polygon >& polygons, ActionStreams args)
{
  Polygon argument;
  if (args.in >> argument)
  {
    std::size_t addedNumber = 0;
    using namespace std::placeholders;
    auto identical = std::bind(&Polygon::isIdentical, argument, _1);
    int i = -1;
    std::vector< std::vector< Polygon > > result;
    std::generate_n(std::back_inserter(result), polygons.size(),
      [&]() {
        i++;
        if (identical(polygons[i]))
        {
          return std::vector<Polygon>{polygons[i], polygons[i]};
        }
        return std::vector<Polygon>{polygons[i]};
      });
    auto flattened_result = std::accumulate(std::begin(result), std::end(result), std::vector<Polygon>(),
      [](std::vector<Polygon>& target, const std::vector<Polygon>& src) {
        target.insert(std::end(target), std::begin(src), std::end(src));
        return target;
      });
    addedNumber = flattened_result.size() - polygons.size();
    polygons = std::move(flattened_result);
    args.out << addedNumber;
  }
  else
  {
    throw InvalidActionException();
  }
}

void spiridonov::lessAreaAction(std::vector< Polygon >& polygons, ActionStreams args)
{
  Polygon argument;
  if (args.in >> argument)
  {
    using namespace std::placeholders;
    args.out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(&Polygon::isLessArea, argument, _1));
  }
  else
  {
    throw InvalidActionException();
  }
}
