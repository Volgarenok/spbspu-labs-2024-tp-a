#include "commands.hpp"
#include <map>
#include <algorithm>
#include <cstddef>
#include <cctype>
#include <string>
#include <functional>
#include <numeric>
#include <iomanip>
#include <scopeGuard.hpp>

namespace grechishnikov
{
  bool isNumber(const std::string& str);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isEqualToNumber(size_t vertices, const Polygon& polygon);

  Polygon makeTriangle(Point a, Point b, Point c);
  std::vector< Polygon > splitToTriangles(Polygon polygon);
  double findAreaOfTriangle(Polygon polygon);
  double findArea(Polygon polygon);

  bool lessArea(const Polygon& first, const Polygon& second);
  bool lessVertexes(const Polygon& first, const Polygon& second);

  void outMaxArea(const std::vector< Polygon > polygons, std::ostream& out);
  void outMinArea(const std::vector< Polygon > polygons, std::ostream& out);
  void outMaxVertexes(const std::vector< Polygon > polygons, std::ostream& out);
  void outMinVertexes(const std::vector< Polygon > polygons, std::ostream& out);
}

void grechishnikov::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;

  ScopeGuard guard(out);
  std::string cmd;
  in >> cmd;

  double divider = 1;
  if (cmd == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::logic_error("Not enough elements foe command");
    }
    divider = polygons.size();
  }

  size_t vertices = 0;
  if (isNumber(cmd))
  {
    vertices = std::stoull(cmd);
    if (vertices < 3)
    {
      throw std::logic_error("Number cannot be lower than three");
    }
    cmd = "NUMBER";
  }
  auto isNumber = std::bind(isEqualToNumber, vertices, _1);

  std::map< std::string, std::function< bool(const Polygon&) > > options;
  options["EVEN"] = isEven;
  options["ODD"] = isOdd;
  options["NUMBER"] = isNumber;
  options["MEAN"] = [](Polygon) { return true; };

  std::vector< Polygon > filteredPolygons;
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(filteredPolygons), options.at(cmd));
  std::vector< double > areas;
  std::transform(filteredPolygons.cbegin(), filteredPolygons.cend(), std::back_inserter(areas), findArea);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0) / divider;
}

void grechishnikov::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;

  std::string cmd;
  in >> cmd;

  size_t vertices = 0;
  if (isNumber(cmd))
  {
    vertices = std::stoull(cmd);
    if (vertices < 3)
    {
      throw std::logic_error("Number cannot be lower than three");
    }
    cmd = "NUMBER";
  }
  auto isNumber = std::bind(isEqualToNumber, vertices, _1);

  std::map< std::string, std::function< bool(const Polygon&) > > options;
  options["EVEN"] = isEven;
  options["ODD"] = isOdd;
  options["NUMBER"] = isNumber;

  out << std::count_if(polygons.cbegin(), polygons.cend(), options.at(cmd));
}

void grechishnikov::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;

  if (polygons.empty())
  {
    throw std::logic_error("Elements were not provided");
  }

  std::string cmd;
  in >> cmd;

  std::map< std::string, std::function< void(const std::vector< Polygon >& polygons, std::ostream& out) > > options;
  options["AREA"] = outMaxArea;
  options["VERTEXES"] = outMaxVertexes;
  options.at(cmd)(polygons, out);
}

void grechishnikov::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;

  if (polygons.empty())
  {
    throw std::logic_error("Elements were not provided");
  }

  std::string cmd;
  in >> cmd;

  std::map< std::string, std::function< void(const std::vector< Polygon >& polygons, std::ostream& out) > > options;
  options["AREA"] = outMinArea;
  options["VERTEXES"] = outMinVertexes;
  options.at(cmd)(polygons, out);
}

bool grechishnikov::isNumber(const std::string& str)
{
  size_t pos = 0;
  try
  {
    std::stoull(str, &pos);
  }
  catch (...)
  {
    return false;
  }
  return pos == str.size();
}

bool grechishnikov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool grechishnikov::isOdd(const Polygon& polygon)
{
  return !isEven(polygon);
}

bool grechishnikov::isEqualToNumber(size_t vertices, const Polygon& polygon)
{
  return polygon.points.size() == vertices;
}

grechishnikov::Polygon grechishnikov::makeTriangle(Point a, Point b, Point c)
{
  return Polygon{ { a, b, c } };
}

std::vector< grechishnikov::Polygon > grechishnikov::splitToTriangles(Polygon polygon)
{
  using namespace std::placeholders;
  auto toTriangle = std::bind(makeTriangle, polygon.points[0], polygon.points[1], _1);
  std::vector< Polygon > res;
  auto startIter = polygon.points.cbegin() + 2;
  std::transform(startIter, polygon.points.cend(), std::back_inserter(res), toTriangle);
  return res;
}

double grechishnikov::findAreaOfTriangle(Polygon polygon)
{
  Point a{ polygon.points[0] };
  Point b{ polygon.points[1] };
  Point c{ polygon.points[2] };
  return 0.5 * std::abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

double grechishnikov::findArea(Polygon polygon)
{
  std::vector< Polygon > triangles = splitToTriangles(polygon);
  std::vector< double > areas;
  std::transform(triangles.cbegin(), triangles.cend(), std::back_inserter(areas), findAreaOfTriangle);
  return std::accumulate(areas.cbegin(), areas.cend(), 0.0);
}

bool grechishnikov::lessArea(const Polygon& first, const Polygon& second)
{
  return findArea(first) < findArea(second);
}

bool grechishnikov::lessVertexes(const Polygon& first, const Polygon& second)
{
  return first.points.size() < second.points.size();
}

void grechishnikov::outMaxArea(const std::vector< Polygon > polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  auto res = std::max_element(polygons.cbegin(), polygons.cend(), lessArea);
  out << findArea(*res);
}

void grechishnikov::outMinArea(const std::vector< Polygon > polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  auto res = std::min_element(polygons.cbegin(), polygons.cend(), lessArea);
  out << findArea(*res);
}

void grechishnikov::outMaxVertexes(const std::vector< Polygon > polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  auto res = std::max_element(polygons.cbegin(), polygons.cend(), lessVertexes);
  out << res->points.size();
}

void grechishnikov::outMinVertexes(const std::vector< Polygon > polygons, std::ostream& out)
{
  ScopeGuard guard(out);
  out << std::fixed << std::setprecision(1);
  auto res = std::min_element(polygons.cbegin(), polygons.cend(), lessVertexes);
  out << res->points.size();
}
