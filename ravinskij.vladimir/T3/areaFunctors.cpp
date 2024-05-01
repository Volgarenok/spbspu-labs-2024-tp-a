#include "areaFunctors.hpp"
#include <numeric>

namespace rav = ravinskij;
rav::AccumulateArea::AccumulateArea(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  subCommands["EVEN"] = std::bind(EvenOddAreaFunctor{}, _1, _2, false);
  subCommands["ODD"] = std::bind(EvenOddAreaFunctor{}, _1, _2, true);
  subCommands["MEAN"] = std::bind(MeanArea{}, _1, _2, polygons.size());
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
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(subCommand);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(rav::VertexNumArea{}, _1, _2, number);
  }
  if (!emptyVectorSupport[subCommand] && polygons.empty())
  {
    throw std::logic_error("empty vector");
  }
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateFunctor);
}

double rav::EvenOddAreaFunctor::operator()(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double rav::MeanArea::operator()(double area, const Polygon& polygon, std::size_t size)
{
  if (size == 0)
  {
    throw std::logic_error("empty vector");
  }
  return area + (polygon.getArea() / size);
}

double rav::VertexNumArea::operator()(double area, const Polygon& polygon, std::size_t vertexCount)
{
  if (polygon.points.size() == vertexCount)
  {
    area += polygon.getArea();
  }
  return area;
}
