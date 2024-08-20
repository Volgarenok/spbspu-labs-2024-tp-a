#include "cmds.hpp"

void skuratov::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string type;
  in >> type;

  std::function< double(double, const Polygon& poly) > calcArea;
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
    if (poly.size() < 1)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    calcArea = std::bind(isMean, _1, _2, poly.size());
  }
  else
  {
    try
    {
      if (!std::all_of(type.cbegin(), type.cend(), isdigit))
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }

      size_t numOfP = std::stoul(type);
      if (numOfP < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }

      std::vector< Polygon > filteredPolygons;
      std::copy_if(poly.cbegin(), poly.cend(), std::back_inserter(filteredPolygons), std::bind(isNumOfVertexes, _1, numOfP));

      std::vector< double > areas;
      std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), countArea);

      double totalArea = std::accumulate(areas.cbegin(), areas.cend(), 0.0);

      out << std::fixed << std::setprecision(1) << totalArea << '\n';
      return;
    }
    catch (const std::exception&)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  double totalArea = std::accumulate(poly.cbegin(), poly.cend(), 0.0, calcArea);
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
  else if (std::all_of(type.cbegin(), type.cend(), isdigit) && std::stol(type) > 2)
  {
    using namespace std::placeholders;
    countNumOfPolygons = std::bind(isNumOfVertexes, _1, std::stol(type));
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
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
