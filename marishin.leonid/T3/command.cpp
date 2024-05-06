#include "command.hpp"
#include <functional>
#include <numeric>
#include <string>
#include <iomanip>
#include <algorithm>

double getAreaEvenOdd(double curr, const marishin::Polygon& pol, bool even)
{
  if (even == (pol.points.size() % 2 == 0))
  {
    curr += pol.getArea();
  }
  return curr;
}

double getAreaMean(double curr, const marishin::Polygon& pol)
{
  curr += pol.getArea();
  return curr;
}

double getNVertex(double curr, const marishin::Polygon& pol, size_t count)
{
  if (pol.points.size() == count)
  {
    curr += pol.getArea();
  }
  return curr;
}

void getArea(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  double sum = 0;
  using namespace std::placeholders;
  if (name == "EVEN")
  {
    sum = std::accumulate(data.begin(), data.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, true));
  }
  else if (name == "ODD")
  {
    sum = std::accumulate(data.begin(), data.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, false));
  }
  else if (name == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    sum = std::accumulate(data.begin(), data.end(), 0.0, getAreaMean) / data.size();
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
    sum = std::accumulate(data.begin(), data.end(), 0.0, std::bind(getNVertex, _1, _2, count));
  }
  out << std::setprecision(1) << std::fixed << sum;
}

void getCount(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
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
    countPred = std::bind(, _1, countVertex);
  }
  out << std::count_if(data.cbegin(), data.cend(), countPred);
}

void getMin(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << std::min_element(data.begin(), data.end(), )->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(data.begin(), data.end(), )->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

void getMax(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << std::max_element(data.begin(), data.end(), )->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(data.begin(), data.end(), )->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

void getRects(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  //...
}

void getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  //...
}
