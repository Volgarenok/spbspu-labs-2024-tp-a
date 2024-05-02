#include <numeric>
#include "commandImpl.hpp"

namespace zak = zakozhurnikova;

double zak::PolygonAreaComputer::operator()(double area, const Point& p2, const Point& p3)
{
  area += std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return area;
}

double zak::accumulateArea(const std::string& command, const std::vector< Polygon >& polygons)
{
  using namespace std::placeholders;
  using Command = std::function< double(double, const Polygon&) >;
  std::map< std::string, Command > commands;
  {
    commands["EVEN"] = std::bind(getEvenOddArea, _1, _2, false);
    commands["ODD"] = std::bind(getEvenOddArea, _1, _2, true);
    commands["MEAN"] = std::bind(getMeanArea, _1, _2, polygons.size());
  }
  if (command == "MEAN" && polygons.empty())
  {
    throw std::logic_error("INVALID ARGUMENT");
  }
  Command accumulateFunctor;
  try
  {
    accumulateFunctor = commands.at(command);
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(command);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(getVertexesArea, _1, _2, number);
  }
  return std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, accumulateFunctor);
}

double zak::getVertexesArea(double area, const Polygon& polygon, std::size_t size)
{
  if (polygon.points.size() == size)
  {
    area += polygon.getArea();
  }
  return area;
}

double zak::getEvenOddArea(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += polygon.getArea();
  }
  return area;
}

double zak::getMeanArea(double area, const Polygon& polygon, std::size_t size)
{
  return area + (polygon.getArea()) / size;
}
