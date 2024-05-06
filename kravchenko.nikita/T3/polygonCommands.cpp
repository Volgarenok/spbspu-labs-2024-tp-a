#include <limits>
#include <map>
#include <numeric>
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

void kravchenko::cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< bool(const Polygon&) > countPred;
  std::function< std::size_t(const Polygon&) > getPointsCount;
  std::function< std::size_t(std::size_t) > getMod2;
  {
    using namespace std::placeholders;
    getPointsCount = std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1));
    getMod2 = std::bind(std::modulus< std::size_t >{}, _1, 2);
  }
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    std::function< bool(std::size_t) > isEven = std::bind(std::equal_to< std::size_t >{}, std::bind(getMod2, _1), 0);
    countPred = std::bind(isEven, std::bind(getPointsCount, _1));
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    std::function< bool(std::size_t) > isOdd = std::bind(std::equal_to< std::size_t >{}, std::bind(getMod2, _1), 1);
    countPred = std::bind(isOdd, std::bind(getPointsCount, _1));
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
    countPred = std::bind(std::equal_to< std::size_t >{}, std::bind(getPointsCount, _1), numOfVertexes);
  }
  out << std::count_if(data.cbegin(), data.cend(), countPred);
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
