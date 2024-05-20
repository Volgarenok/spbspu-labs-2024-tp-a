#include "areaFunctors.hpp"
#include <numeric>
#include <algorithm>

namespace rav = ravinskij;
rav::AccumulateArea::AccumulateArea(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  subCommands["EVEN"] = std::bind(AreaSummator{}, 0.0, _1, OddPredicate{});
  subCommands["ODD"] = std::bind(AreaSummator{}, 0.0, _1, EvenPredicate{});
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
    Predicate vertexPredicate = std::bind(VertexNumPredicate{}, _1, number);
    accumulateFunctor = std::bind(AreaSummator{}, 0.0, _1, vertexPredicate);
  }
  std::vector< double > areas;
  std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), accumulateFunctor);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

double rav::MeanArea::operator()(double area, const Polygon& polygon, size_t size)
{
  if (size == 0)
  {
    throw std::logic_error("empty vector");
  }
  return area + (getArea(polygon) / size);
}

bool rav::EvenPredicate::operator()(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool rav::OddPredicate::operator()(const Polygon& polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool rav::VertexNumPredicate::operator()(const Polygon& polygon, size_t vertexCount)
{
  return polygon.points.size() == vertexCount;
}

double rav::AreaSummator::operator()(double area, const Polygon& polygon, Predicate pred)
{
  if (pred(polygon))
  {
    area += getArea(polygon);
  }
  return area;
}
