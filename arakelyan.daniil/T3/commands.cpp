#include "commands.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>
#include <numeric>
#include <vector>
#include <iomanip>

#include "polygon.hpp"

double getSumOfAreas(const std::vector< arakelyan::Polygon > &polygons);
bool expectedVertexes(const arakelyan::Polygon &polygon, size_t expectedSize);

void arakelyan::doArea(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  std::vector< Polygon > tempP;

  std::string cmdArg = "";
  in >> cmdArg;

  if (cmdArg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isEven);
    out << std::fixed << std::setprecision(1);
    out << getSumOfAreas(tempP);
  }
  else if (cmdArg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isOdd);
    out << std::fixed << std::setprecision(1);
    out << getSumOfAreas(tempP);
  }
  else if (cmdArg == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("zero polygons");
    }
    out << std::fixed << std::setprecision(1);
    out << (getSumOfAreas(polygons) / polygons.size());
  }
  else //num-of-vertexes
  {
    size_t numOfVertexes = 0;
    numOfVertexes = std::stoull(cmdArg);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("vertexes < 3");
    }

    using namespace std::placeholders;
    auto pr = std::bind(expectedVertexes, _1, numOfVertexes);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), pr);
    out << std::fixed << std::setprecision(1);
    out << getSumOfAreas(tempP);
  }
}

void arakelyan::findMax(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("zero polygons");
  }
  std::string cmdArg = "";
  in >> cmdArg;
  if (cmdArg == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
    out << std::fixed << std::setprecision(1);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else if (cmdArg == "VERTEXES")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getVertexes);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else
  {
    throw std::invalid_argument("invalid argument");
  }
}

void arakelyan::findMin(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("zero polygons");
  }

  std::string cmdArg = "";
  in >> cmdArg;
  if (cmdArg == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
    out << std::fixed << std::setprecision(1);
    out << *(std::min_element(areas.cbegin(), areas.cend()));
  }
  else if (cmdArg == "VERTEXES")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getVertexes);
    out << *(std::min_element(areas.cbegin(), areas.cend()));
  }
  else
  {
    throw std::invalid_argument("invalid argument");
  }
}

void arakelyan::count(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  std::string cmdArg = "";
  in >> cmdArg;

  if (cmdArg == "EVEN")
  {
    out << std::fixed << std::setprecision(1);
    out << std::count_if(polygons.cbegin(), polygons.cend(), isEven);
  }
  else if (cmdArg == "ODD")
  {
    out << std::fixed << std::setprecision(1);
    out << std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
  }
  else
  {
    int numOfVertexes = 0;
    numOfVertexes = std::stoull(cmdArg);
    if (numOfVertexes < 3)
    {
      throw std::logic_error("vertexes < 3");
    }

    auto pr = std::bind(expectedVertexes, std::placeholders::_1, numOfVertexes);
    out << std::count_if(polygons.cbegin(), polygons.cend(), pr);
  }

}

struct Counter
{
  const std::vector< arakelyan::Point > &target;
  size_t counter;
  size_t maxCount;

  Counter(const std::vector< arakelyan::Point > &pol);

  size_t operator()(const arakelyan::Polygon &polygon);
  size_t operator()() const;
};

Counter::Counter(const std::vector< arakelyan::Point > &pol):
  target(pol),
  counter(0),
  maxCount(0)
{}

size_t Counter::operator()(const arakelyan::Polygon &polygon)
{
  if (polygon.points == target)
  {
    ++counter;
  }
  else
  {
    if (counter > maxCount)
    {
      maxCount = counter;
    }
    counter = 0;
  }
  return maxCount;
}

size_t Counter::operator()() const
{
  return maxCount;
}

void arakelyan::maxSeq(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("zero polygons");
  }

  int num = 0;
  in >> num;
  if (num < 3)
  {
    throw std::logic_error("");
  }

  std::vector< Point > inPolygon;
  using inIt = std::istream_iterator< Point >;
  std::copy_n(inIt(in), num, std::back_inserter(inPolygon));

  std::vector< size_t > seq(inPolygon.size());
  if (inPolygon.empty() || in.peek() != '\n')
  {
    throw std::logic_error("invalid count of vertexes");
  }

  Counter counter(inPolygon);
  out << std::for_each(polygons.begin(), polygons.end(), std::ref(counter))();
}

// void arakelyan::rightShapes(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
// {
//
// }

double getSumOfAreas(const std::vector< arakelyan::Polygon > &polygons)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getArea);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

bool expectedVertexes(const arakelyan::Polygon &polygon, size_t expectedSize)
{
  return polygon.points.size() == expectedSize;
}
