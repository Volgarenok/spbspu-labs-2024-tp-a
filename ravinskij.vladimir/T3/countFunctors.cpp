#include "countFunctors.hpp"
#include <algorithm>

namespace rav = ravinskij;

bool rav::EvenOddCountFunctor::operator()(const Polygon& polygon, bool isOdd)
{
  return (polygonSize(polygon) % 2) == isOdd;
}

bool rav::VertexNumCountFunctor::operator()(const Polygon& polygon, size_t vertexCount)
{
  return polygonSize(polygon) == vertexCount;
}

rav::GetCount::GetCount(const std::vector< Polygon >& vector):
  polygons(vector)
{
  using namespace std::placeholders;
  subCommands["ODD"] = std::bind(EvenOddCountFunctor{}, _1, true);
  subCommands["EVEN"] = std::bind(EvenOddCountFunctor{}, _1, false);
}

size_t rav::GetCount::operator()(const std::string& subCommand)
{
  SubCommand unariPredFunctor;
  try
  {
    unariPredFunctor = subCommands.at(subCommand);
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(subCommand);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    unariPredFunctor = std::bind(rav::VertexNumCountFunctor{}, _1, number);
  }
  return std::count_if(polygons.cbegin(), polygons.cend(), unariPredFunctor);
}
