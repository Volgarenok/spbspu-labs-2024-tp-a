#include "polygonCommands.hpp"
#include <limits>
#include <map>
#include <numeric>

bool kravchenko::detail::isEvenNumberOfVertexes(const Polygon& p)
{
  return (p.points.size() % 2) == 0;
}

size_t kravchenko::detail::getNumberOfVertexes(const Polygon& p)
{
  return p.points.size();
}

double kravchenko::detail::accumulateAreaParity(double acc, const Polygon& p, bool isEven)
{
  if (isEven == (p.points.size() % 2 == 0))
  {
    acc += getArea(p);
  }
  return acc;
}

double kravchenko::detail::accumulateAreaNumOfVertex(double acc, const Polygon& p, size_t numOfVertexes)
{
  if (numOfVertexes == p.points.size())
  {
    acc += getArea(p);
  }
  return acc;
}

void kravchenko::cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< double(double, const Polygon&) > accArea;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;

    accArea = std::bind(detail::accumulateAreaParity, _1, _2, true);
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    accArea = std::bind(detail::accumulateAreaParity, _1, _2, false);
  }
  else if (argument == "MEAN")
  {
    if (data.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    std::function< double(const Polygon&) > getMeanArea = std::bind(
      std::divides< double >{},
      std::bind(getArea, _1),
      data.size()
    );
    accArea = std::bind(std::plus< double >{}, _1, std::bind(getMeanArea, _2));
  }
  else
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
    using namespace std::placeholders;
    accArea = std::bind(detail::accumulateAreaNumOfVertex, _1, _2, numOfVertexes);
  }

  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(data.cbegin(), data.cend(), 0.0, accArea);
}

void kravchenko::cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument;
  in >> argument;

  std::function< bool(const Polygon&) > countPred;
  if (argument == "EVEN")
  {
    using namespace std::placeholders;
    countPred = detail::isEvenNumberOfVertexes;
  }
  else if (argument == "ODD")
  {
    using namespace std::placeholders;
    countPred = std::bind(std::logical_not< bool >{}, std::bind(detail::isEvenNumberOfVertexes, _1));
  }
  else
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
    using namespace std::placeholders;
    countPred = std::bind(std::equal_to< size_t >{}, std::bind(detail::getNumberOfVertexes, _1), numOfVertexes);
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
