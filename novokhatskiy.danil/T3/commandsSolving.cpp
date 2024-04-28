#include "commandsSolving.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <numeric>
#include <functional>
#include "StreamGuard.hpp"
#include "polygon.hpp"

void novokhatskiy::commandArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  std::function< double (double, const novokhatskiy::Polygon&) > area;
  novokhatskiy::StreamGuard guard(out);
  using namespace std::placeholders;
  out << std::setprecision(1) << std::fixed;
  if (arg == "EVEN")
  {
    area = std::bind(novokhatskiy::AccumulateEvenOrOddArea, _1, _2, true);
  }
  else if (arg == "ODD")
  {
    area = std::bind(novokhatskiy::AccumulateEvenOrOddArea, _1, _2, false);
    //AccumulateEvenOrOddArea(polygons.front(), out, false);
  }
  else if (arg == "MEAN")
  {
    area = std::bind(novokhatskiy::AccumulateMeanArea, _1, _2);
  }
  else
  {
    size_t numOfVertexes = {};
    try
    {
      numOfVertexes = std::stoull(arg);
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    area = std::bind(AccumulateNumOfVertexesArea, _1, numOfVertexes, _2);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, area);
}

double novokhatskiy::AccumulateNumOfVertexesArea(double res, size_t vertexes, const Polygon& polygons)
{
  if (vertexes == polygons.points.size())
  {
    res += polygons.getArea();
  }
  return res;
}

double novokhatskiy::AccumulateEvenOrOddArea(double res, const Polygon& p, bool isEven)
{
  if (isEven == (p.points.size() % 2 == 0))
  {
    res += p.getArea();
  }
  return res;
}

double novokhatskiy::AccumulateMeanArea(double res, const Polygon& p)
{
  if (p.points.size() < 1)
  {
    throw std::logic_error("To accumulate mean area, we need to have more than 1 shape"); // заменить на invalid_argument
  }
  return res + (p.getArea() / p.points.size());
}
