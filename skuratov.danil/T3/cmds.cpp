#include "cmds.hpp"
#include <string>
#include "geometryFunc.hpp"

void skuratov::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;
  std::function< double(double, const Polygon& polygon) > calcArea;

  using namespace std::placeholders;
  if (type == "ODD")
  {
    calcArea = std::bind(calculateSumOfAreas, _1, _2, isOdd);
  }
  else if (type == "EVEN")
  {
    calcArea = std::bind(calculateSumOfAreas, _1, _2, isEven);
  }
  else if (type == "MEAN")
  {
    calcArea = std::bind(isMean, _1, _2, polygon.size());
  }
  else
  {
    size_t numOfPoints = {};
    try
    {
      numOfPoints = std::stoul(type);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    calcArea = std::bind(isNumOfVertexes, _1, _2, numOfPoints);
  }
  out << std::fixed << std::setprecision(1) << std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, calcArea) << '\n';
}

void skuratov::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;

  if (type == "AREA")
  {
    isMaxArea(out, polygon);
  }
  else if (type == "VERTEXES")
  {
    isMaxVertexes(out, polygon);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void skuratov::min(std::istream&, std::ostream&, const std::vector< Polygon >& polygon)
{}

void skuratov::count(std::istream&, std::ostream&, const std::vector< Polygon >& polygon)
{}

void skuratov::lessArea(std::istream&, std::ostream&, const std::vector< Polygon >& polygon)
{}

void skuratov::inFrame(std::istream&, std::ostream&, const std::vector< Polygon >& polygon)
{}

void skuratov::rightShapes(std::ostream&, const std::vector< Polygon >& polygon)
{}
