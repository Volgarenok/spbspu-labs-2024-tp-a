#include "areaFunctors.hpp"
#include <numeric>
#include <algorithm>

namespace rav = ravinskij;
rav::AccumulateArea::AccumulateArea(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  subCommands["EVEN"] = std::bind(AreaSummator{}, 0.0, _1);
  subCommands["ODD"] = std::bind(AreaSummator{}, 0.0, _1);
  subCommands["MEAN"] = std::bind(MeanArea{}, 0.0, _1, polygons.size());
  emptyVectorSupport["EVEN"] = true;
  emptyVectorSupport["ODD"] = true;
  emptyVectorSupport["MEAN"] = false;
  Filter oddPredicate = std::bind(std::logical_not< bool >{}, std::bind(EvenPredicate{}, _1));
  filters["EVEN"] = EvenPredicate{};
  filters["ODD"] = oddPredicate;
  filters["MEAN"] = nullptr;
}
double rav::AccumulateArea::operator()(const std::string& subCommand)
{
  SubCommand accumulateFunctor;
  Filter filter;
  try
  {
    accumulateFunctor = subCommands.at(subCommand);
    filter = filters.at(subCommand);
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
    accumulateFunctor = std::bind(AreaSummator{}, 0.0, _1);
    filter = std::bind(VertexNumPredicate{}, _1, number);
  }
  const std::vector< Polygon >* filtered = &polygons;
  std::vector< Polygon > temp;
  if (filter != nullptr)
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(temp), filter);
    filtered = &temp;
  }

  std::vector< double > areas(filtered->size());
  std::transform(filtered->cbegin(), filtered->cend(), areas.begin(), accumulateFunctor);
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

bool rav::VertexNumPredicate::operator()(const Polygon& polygon, size_t vertexCount)
{
  return polygon.points.size() == vertexCount;
}

double rav::AreaSummator::operator()(double area, const Polygon& polygon)
{
  area += getArea(polygon);
  return area;
}
