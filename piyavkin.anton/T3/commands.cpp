#include "commands.hpp"
#include <functional>
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