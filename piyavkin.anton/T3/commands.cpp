#include "commands.hpp"
#include <functional>
#include <algorithm>
#include <numeric>

double getAreaEvenOdd(double curr, const piyavkin::Polygon& pol, bool even)
{
  if (even && pol.points.size() % 2 != 0)
  {
    curr += pol.getArea();
  }
  else if (!even && pol.points.size() % 2 == 0)
  {
    curr += pol.getArea();
  }
  return curr;
}

double getAreaMean(double curr, const piyavkin::Polygon& pol)
{
  curr += pol.getArea();
  return curr;
}

double getNVertex(double curr, const piyavkin::Polygon& pol, size_t count)
{
  if (pol.points.size() == count)
  {
    curr += pol.getArea();
  }
  return curr;
}

void piyavkin::getArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol)
{
  std::string name = "";
  in >> name;
  double sum = 0;
  using namespace std::placeholders;
  if (name == "EVEN")
  {
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, true));
  }
  else if (name == "ODD")
  {
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, false));
  }
  else if (name == "MEAN")
  {
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, getAreaMean) / pol.size();
  }
  else
  {
    size_t count = 0;
    const size_t minCount = 3;
    try
    {
      count = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (count < minCount)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, std::bind(getNVertex, _1, _2, count));
  }
  out << sum << '\n';
}

size_t getVertex(const piyavkin::Polygon& pol)
{
  return pol.points.size();
}

void piyavkin::getMinMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol, bool min)
{
  if (pol.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string name = "";
  in >> name;
  if (name == "AREA")
  {
    std::vector< double > areas;
    areas.resize(pol.size());
    std::transform(pol.begin(), pol.end(), areas.begin(), std::bind(getAreaMean, 0.0, std::placeholders::_1));
    if (min)
    {
      out << *std::min_element(areas.begin(), areas.end()) << '\n';
    }
    else
    {
      out << *std::max_element(areas.begin(), areas.end()) << '\n';
    }
  }
  else if (name == "VERTEX")
  {
    std::vector< size_t > areas;
    areas.resize(pol.size());
    std::transform(pol.begin(), pol.end(), areas.begin(), getVertex);
    if (min)
    {
      out << *std::min_element(areas.begin(), areas.end()) << '\n';
    }
    else
    {
      out << *std::max_element(areas.begin(), areas.end()) << '\n';
    }
  }
}

bool isEven(const piyavkin::Polygon& pol, bool even)
{
  return even == (pol.points.size() % 2 != 0);
}

bool isCorrectCountAngle(const piyavkin::Polygon& pol, size_t countVertex)
{
  return countVertex == pol.points.size();
}

void piyavkin::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol)
{
  std::string name = "";
  in >> name;
  std::function< bool(const Polygon&) > countPred;
  if (name == "EVEN")
  {
    using namespace std::placeholders;
    countPred = std::bind(isEven, _1, true);
  }
  else if (name == "ODD")
  {
    using namespace std::placeholders;
    countPred = std::bind(isEven, _1, false);
  }
  else
  {
    size_t countVertex = 0;
    const size_t minVertex = 3;
    try
    {
      countVertex = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (countVertex < minVertex)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    countPred = std::bind(isCorrectCountAngle, _1, countVertex);
  }
  out << std::count_if(pol.cbegin(), pol.cend(), countPred) << '\n';
}