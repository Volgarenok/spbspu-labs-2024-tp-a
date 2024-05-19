#include "areaFunctors.hpp"
#include <numeric>
#include <algorithm>

namespace rav = ravinskij;
rav::AccumulateArea::AccumulateArea(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  subCommands["EVEN"] = std::bind(EvenOddAreaFunctor{}, 0.0, _1, false);
  subCommands["ODD"] = std::bind(EvenOddAreaFunctor{}, 0.0, _1, true);
  subCommands["MEAN"] = std::bind(MeanArea{}, 0.0, _1, polygons.size());
  emptyVectorSupport["EVEN"] = true;
  emptyVectorSupport["ODD"] = true;
  emptyVectorSupport["MEAN"] = false;
}
double rav::AccumulateArea::operator()(const std::string& subCommand)
{
  SubCommand accumulateFunctor;
  try
  {
    accumulateFunctor = subCommands.at(subCommand);
    if (!emptyVectorSupport[subCommand] && polygons.empty())
    {
      throw std::logic_error("empty vector");
    }
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(subCommand);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(rav::VertexNumArea{}, 0.0, _1, number);
  }
  std::vector< double > areas;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), accumulateFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

double rav::EvenOddAreaFunctor::operator()(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += getArea(polygon);
  }
  return area;
}

double rav::MeanArea::operator()(double area, const Polygon& polygon, size_t size)
{
  if (size == 0)
  {
    throw std::logic_error("empty vector");
  }
  return area + (getArea(polygon) / size);
}

double rav::VertexNumArea::operator()(double area, const Polygon& polygon, size_t vertexCount)
{
  if (polygon.points.size() == vertexCount)
  {
    area += getArea(polygon);
  }
  return area;
}
