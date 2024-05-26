#include "cmds.hpp"
#include <iomanip>
#include <string>
#include "geometryFunc.hpp"

void skuratov::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  std::string cmd = {};
  in >> cmd;
  std::function< double(double, const Polygon& polygon) > calcArea;

  using namespace std::placeholders;
  if (cmd == "ODD")
  {
    calcArea = std::bind(calculateSumOfAreas, _1, _2, isOdd);
  }
  else if (cmd == "EVEN")
  {
    calcArea = std::bind(calculateSumOfAreas, _1, _2, isEven);
  }
  else if (cmd == "MEAN")
  {
    calcArea = std::bind(isMean, _1, _2, polygon.size());
  }
  else
  {
    size_t numOfPoints = {};
    try
    {
      numOfPoints = std::stoul(cmd);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    calcArea = std::bind(isNumOfVertexes, _1, _2, numOfPoints);
  }
  out << std::fixed << std::setprecision(1) << std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, calcArea) << '\n';
}

void skuratov::max(std::istream&, std::ostream&, const std::vector< Polygon >& polygon)
{}

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
