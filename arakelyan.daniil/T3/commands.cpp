#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>
#include <numeric>
#include <vector>

#include "polygon.hpp"

double getSumOfAreas(const std::vector< arakelyan::Polygon > &polygons);
bool expectedSize(const arakelyan::Polygon &polygon, size_t expectedSize);

void arakelyan::doArea(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
{
  std::vector< Polygon > tempP;

  std::string cmdArg = "";
  in >> cmdArg;

  if (cmdArg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isEven);
  }
  else if (cmdArg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), isOdd);
  }
  else if (cmdArg == "MEAN")
  {
    out << (getSumOfAreas(polygons) / polygons.size());
  }
  else //num-of-vertexes
  {
    size_t num = std::stoull(cmdArg);

    using namespace std::placeholders;
    auto pr = std::bind(expectedSize, _1, num);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(tempP), pr);
  }
  if (cmdArg != "MEAN")
  {
    out << getSumOfAreas(polygons);
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
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
  else if (cmdArg == "VERTEXES")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), arakelyan::getVertexes);
    out << *(std::max_element(areas.cbegin(), areas.cend()));
  }
}
//
// void arakelyan::findMin(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
// {
//
// }
//
// void arakelyan::count(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
// {
//
// }
//
// void arakelyan::maxSeq(std::istream &in, std::ostream &out, const std::vector< Polygon > &polygons)
// {
//
// }
//
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

bool expectedSize(const arakelyan::Polygon &polygon, size_t expectedSize)
{
  return polygon.points.size() == expectedSize;
}
