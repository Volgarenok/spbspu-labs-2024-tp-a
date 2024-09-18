#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>

void checkEmpty(const std::vector< allaberdiev::Polygon >& v)
{
  if (v.empty())
  {
    throw std::logic_error("EMPTY VECTOR");
  }
}

void allaberdiev::count(std::ostream& out,
    std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  using namespace std::placeholders;
  std::string str_args = "";
  in >> str_args;

  std::function< bool(const Polygon&) > pred;
  try
  {
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  size_t count = std::count_if(polygons_vector.cbegin(), polygons_vector.cend(), pred);
  out << count;
}

void allaberdiev::getArea(std::ostream& out, std::istream& in,
    const std::vector< Polygon >& polygons_vector,
    const std::map< std::string, std::function< bool(const Polygon&) > >& args)
{
  std::function< bool(const Polygon&) > pred;
  std::string str_args = "";
  in >> str_args;
  size_t devide = 1;
  if (str_args == "MEAN")
  {
    checkEmpty(polygons_vector);
    devide = polygons_vector.size();
  }
  try
  {
    using namespace std::placeholders;
    size_t ver = std::stoull(str_args);
    if (ver < 3)
    {
      throw std::logic_error("INVALID COMMANDS");
    }
    pred = std::bind(std::equal_to< size_t >{}, std::bind(get_size, _1), ver);
  }
  catch (...)
  {
    pred = args.at(str_args);
  }
  std::vector< Polygon > area_polygons;
  std::copy_if(polygons_vector.cbegin(), polygons_vector.cend(), std::back_inserter(area_polygons), pred);
  std::vector< double > areas(area_polygons.size());
  std::transform(area_polygons.cbegin(), area_polygons.cend(), std::back_inserter(areas), get_area);
  out << std::setprecision(1);
  out << std::fixed;
  double a = std::accumulate(areas.begin(), areas.end(), 0.0) / devide;
  out << a;
}

void allaberdiev::findMax(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::max_element(areas.begin(), areas.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > areas(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(areas), get_size);
    out << *std::max_element(areas.begin(), areas.end());
  }
}

void allaberdiev::findMin(std::ostream& out, std::istream& in, const std::vector< Polygon >& polygons_vector)
{
  checkEmpty(polygons_vector);
  std::string str_args = "";
  in >> str_args;
  if (str_args == "AREA")
  {
    std::vector< double > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_area);
    out << std::setprecision(1);
    out << std::fixed;
    out << *std::min_element(tmp.begin(), tmp.end());
  }
  if (str_args == "VERTEXES")
  {
    std::vector< size_t > tmp(polygons_vector.size());
    std::transform(polygons_vector.begin(), polygons_vector.end(), std::back_inserter(tmp), get_size);
    out << *std::min_element(tmp.begin(), tmp.end());
  }
}

void allaberdiev::rmEchoCommand(std::ostream& out, std::istream& in, std::vector< Polygon >& polygons)
{
  Polygon polygon;
  in >> polygon;
  if (in.fail() || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  auto it = std::unique(polygons.begin(), polygons.end(),
      [&polygon](const Polygon& p1, const Polygon& p2) {
        return p1 == polygon && p1 == p2;
      });

  int removedCount = std::distance(it, polygons.end());
  polygons.erase(it, polygons.end());

  out << removedCount << "\n";
}

bool allaberdiev::isRectangle(const Polygon& polygon)
{
  if (get_size(polygon) != 4)
  {
    throw std::logic_error("<WRONG POLYGON>");
  }

  const Point& A = polygon.points[0];
  const Point& B = polygon.points[1];
  const Point& C = polygon.points[2];
  const Point& D = polygon.points[3];

  auto dist = [](const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  };

  return dist(A, B) == dist(C, D) && dist(B, C) == dist(D, A) && dist(A, C) == dist(B, D);
}

void allaberdiev::rectsCommand(std::ostream& out, const std::vector< Polygon >& polygons)
{
  int rectCount = std::count_if(polygons.begin(), polygons.end(), isRectangle);
  if (rectCount != 0) out << rectCount << "\n";
  else out << "<INVALID COMMAND>\n";
}

bool allaberdiev::isRightAngle(const Point& A, const Point& B, const Point& C)
{
  int abx = B.x - A.x;
  int aby = B.y - A.y;
  int bcx = C.x - B.x;
  int bcy = C.y - B.y;
  return abx * bcx + aby * bcy == 0;
}

bool allaberdiev::rightAngleAtVertex(const Polygon& polygon, int index) {
    size_t n = get_size(polygon);
    const Point& A = polygon.points[index];
    const Point& B = polygon.points[(index + 1) % n];
    const Point& C = polygon.points[(index + 2) % n];
    return isRightAngle(A, B, C);
}

bool allaberdiev::hasRightAngle(const Polygon& polygon) {
    size_t n = get_size(polygon);
    return std::any_of(polygon.points.begin(), polygon.points.end(),
        [&polygon, n](const Point& A) {
            int index = &A - &polygon.points[0];
            return rightAngleAtVertex(polygon, index);
        });
}

void allaberdiev::rightShapesCommand(std::ostream& out, const std::vector< Polygon >& polygons)
{
  int rightAngleCount = std::count_if(polygons.begin(), polygons.end(), hasRightAngle);

  out << rightAngleCount;
}
