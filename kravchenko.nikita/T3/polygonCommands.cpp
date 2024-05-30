#include "polygonCommands.hpp"
#include <limits>
#include <numeric>

bool kravchenko::predicates::isEven(size_t n)
{
  return (n % 2 == 0);
}

bool kravchenko::predicates::emptyFilter(const Polygon&)
{
  return true;
}

size_t kravchenko::predicates::parseNumOfVertexes(const std::string& argument)
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

void kravchenko::cmdArea(const std::vector< Polygon >& data, const cmd::AreaArgs& args, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  if (argument == "MEAN" && data.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  cmd::Filter filter;
  cmd::Calculator calc;
  try
  {
    auto argPair = args.at(argument);
    filter = argPair.first;
    calc = argPair.second;
  }
  catch (const std::out_of_range&)
  {
    using namespace std::placeholders;
    filter = std::bind(
      std::equal_to< size_t >{},
      std::bind(getNumberOfVertexes, _1),
      predicates::parseNumOfVertexes(argument)
    );
    calc = getArea;
  }
  std::vector< Polygon > filteredPolygons(data.size());
  auto it = std::copy_if(data.cbegin(), data.cend(), filteredPolygons.begin(), filter);
  filteredPolygons.erase(it, filteredPolygons.cend());

  std::vector< double > areas(filteredPolygons.size());
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), areas.begin(), calc);

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

void kravchenko::cmdMinMax(const std::vector< Polygon >& data, const cmd::MinMaxArgs& args, std::istream& in, std::ostream& out)
{
  if (data.size() == 0)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string arg;
  in >> arg;
  try
  {
    args.at(arg)(data, out);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void kravchenko::cmdCount(const std::vector< Polygon >& data, const cmd::CountArgs& args, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  cmd::Filter pred;
  try
  {
    pred = args.at(argument);
  }
  catch (const std::out_of_range&)
  {
    using namespace std::placeholders;
    pred = std::bind(
      std::equal_to< size_t >{},
      std::bind(getNumberOfVertexes, _1),
      predicates::parseNumOfVertexes(argument)
    );
  }
  out << std::count_if(data.cbegin(), data.cend(), pred);
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
  out << std::count_if(data.cbegin(), data.cend(), hasRightAngle);
}
