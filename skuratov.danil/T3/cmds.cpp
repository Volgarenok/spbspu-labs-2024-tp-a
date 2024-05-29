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

    if (numOfPoints < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
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

  if (polygon.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

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

void skuratov::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;

  if (polygon.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (type == "AREA")
  {
    isMinArea(out, polygon);
  }
  else if (type == "VERTEXES")
  {
    isMinVertexes(out, polygon);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void skuratov::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;

  std::function< bool(const Polygon& polygon) > countNumOfPolygons;

  if (type == "EVEN")
  {
    countNumOfPolygons = isEven;
  }
  else if (type == "ODD")
  {
    countNumOfPolygons = isOdd;
  }
  else if (std::all_of(type.cbegin(), type.cend(), ::isdigit) && std::stoi(type) > 2)
  {
    using namespace std::placeholders;
    countNumOfPolygons = std::bind(isnumOfVertexesForCount, _1, std::stoi(type));
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << std::count_if(polygon.cbegin(), polygon.cend(), countNumOfPolygons) << "\n";
}

void skuratov::lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygon)
{
  Polygon type = {};
  in >> type;
  if (!(in && in.peek() == '\n'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  out << std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isAreaForLess, _1, type.getArea())) << "\n";
}

void skuratov::inFrame(std::istream&, std::ostream&, const std::vector< Polygon >&)
{}

void skuratov::rightShapes(std::ostream& out, const std::vector< Polygon >& polygon)
{
  out << std::count_if(polygon.cbegin(), polygon.cend(), straightCorner) << '\n';
}
