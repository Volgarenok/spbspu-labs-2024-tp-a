#include "cmds.hpp"
#include <map>

void skuratov::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  std::map< std::string, std::function< bool(const Polygon&) > > type;
  type["ODD"] = isOdd;
  type["EVEN"] = isEven;

  std::string anotherType;
  in >> anotherType;

  using namespace std::placeholders;
  std::vector< Polygon > filteredPolygons;
  std::function< double(const Polygon& poly) > calcArea = countArea;

  try
  {
    std::copy_if(poly.cbegin(), poly.cend(), std::back_inserter(filteredPolygons), type.at(anotherType));
  }
  catch (...)
  {
    if (anotherType == "MEAN")
    {
      if (poly.size() < 1)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      filteredPolygons = poly;
      calcArea = std::bind(isMean, 0.0, _1, poly.size());
    }
    else
    {
      size_t numOfP = std::stoul(anotherType);
      if (numOfP < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      std::copy_if(poly.cbegin(), poly.cend(), std::back_inserter(filteredPolygons), std::bind(isNumOfVertexes, _1, numOfP));
    }
  }
  std::vector< double > areas;
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), calcArea);

  double totalArea = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  out << std::fixed << std::setprecision(1) << totalArea << '\n';
}

void skuratov::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;

  if (poly.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (type == "AREA")
  {
    isMaxArea(out, poly);
  }
  else if (type == "VERTEXES")
  {
    isMaxVertexes(out, poly);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void skuratov::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type = {};
  in >> type;

  if (poly.size() < 1)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }

  if (type == "AREA")
  {
    isMinArea(out, poly);
  }
  else if (type == "VERTEXES")
  {
    isMinVertexes(out, poly);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void skuratov::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
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
  else
  {
    try
    {
      long numVertices = std::stol(type);
      if (numVertices <= 2)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }

      using namespace std::placeholders;
      countNumOfPolygons = std::bind(isNumOfVertexes, _1, numVertices);
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  out << std::count_if(poly.cbegin(), poly.cend(), countNumOfPolygons) << "\n";
}

void skuratov::lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  Polygon type = {};
  in >> type;
  if (!in || in.peek() == '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  using namespace std::placeholders;
  out << std::count_if(poly.cbegin(), poly.cend(), std::bind(isAreaForLess, _1, type.getArea())) << "\n";
}

void skuratov::inFrame(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }

  Polygon type = {};
  in >> type;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if (type <= createBoundingBox(poly))
  {
    out << "<TRUE>" << '\n';
  }
  else
  {
    out << "<FALSE>" << '\n';
  }
}

void skuratov::rightShapes(std::ostream& out, const std::vector< Polygon >& poly)
{
  out << std::count_if(poly.cbegin(), poly.cend(), rightCorner) << '\n';
}
