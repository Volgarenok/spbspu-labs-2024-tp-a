#include "polygonCommands.hpp"
#include <limits>
#include <map>
#include <numeric>

bool kravchenko::isEven(size_t n)
{
  return (n % 2 == 0);
}

size_t kravchenko::parseNumberOfVertexes(const std::string& argument)
{
  size_t numOfVertexes = 0;
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
  return numOfVertexes;
}

void kravchenko::cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  if (data.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string argument;
  in >> argument;

  using Filter = std::function< bool(const Polygon&) >;
  using Accumulator = std::function< double(double, const Polygon&) >;

  std::map< std::string, std::pair< Filter, Accumulator > > argumentMap;
  {
    using namespace std::placeholders;
    argumentMap["EVEN"] = {
      std::bind(isEven, std::bind(getNumberOfVertexes, _1)),
      std::bind(std::plus< double >{}, _1, std::bind(getArea, _2))
    };
    argumentMap["ODD"] = {
      std::bind(std::logical_not< bool >{}, std::bind(isEven, std::bind(getNumberOfVertexes, _1))),
      std::bind(std::plus< double >{}, _1, std::bind(getArea, _2))
    };
    argumentMap["MEAN"] = {
      getNumberOfVertexes,
      std::bind(std::plus< double >{}, _1, std::bind(std::divides< double >(), std::bind(getArea, _2), data.size()))
    };
  }
  Filter filter;
  Accumulator accumulator;
  try
  {
    auto argPair = argumentMap.at(argument);
    filter = argPair.first;
    accumulator = argPair.second;
  }
  catch (const std::out_of_range&)
  {
    using namespace std::placeholders;
    filter = std::bind(std::equal_to< size_t >{}, std::bind(getNumberOfVertexes, _1), parseNumberOfVertexes(argument));
    accumulator = std::bind(std::plus< double >{}, _1, std::bind(getArea, _2));
  }
  std::vector< Polygon > filteredPolygons;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(filteredPolygons), filter);

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(filteredPolygons.cbegin(), filteredPolygons.cend(), 0.0, accumulator);
}

void kravchenko::cmdMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  predicateElement(data, in, out, std::less<>());
}

void kravchenko::cmdMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  predicateElement(data, in, out, std::greater<>());
}

void kravchenko::cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< bool(const Polygon&) > countPred;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    countPred = std::bind(isEven, std::bind(getNumberOfVertexes, _1));
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    countPred = std::bind(std::logical_not< bool >{}, std::bind(isEven, std::bind(getNumberOfVertexes, _1)));
  }
  else
  {
    using namespace std::placeholders;
    countPred = std::bind(
      std::equal_to< size_t >{},
      std::bind(getNumberOfVertexes, _1),
      parseNumberOfVertexes(argument)
    );
  }
  out << std::count_if(data.cbegin(), data.cend(), countPred);
}

void kravchenko::cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon argument;
  if (!(in >> argument))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  auto identical = std::bind(isIdentical, argument, _1);
  auto identicalPred = std::bind(std::logical_and< bool >{}, std::bind(identical, _1), std::bind(identical, _2));
  auto last = std::unique(data.begin(), data.end(), identicalPred);
  out << std::distance(last, data.end());
  data.erase(last, data.end());
}

void kravchenko::cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out)
{
  using namespace std::placeholders;
  out << std::count_if(data.cbegin(), data.cend(), std::bind(hasRightAngle, _1));
}
