#include "datastruct.hpp"
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <memory>
#include "Delimeter.hpp"

std::istream& kuznetsov::operator>>(std::istream& in, Point& point)
{
  using delchr = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> delchr{ '(' } >> x >> delchr{ ';' } >> y >> delchr{ ')' };
  if (in)
  {
    point = { x, y };
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  using input_it_t = std::istream_iterator< kuznetsov::Point >;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
  if (in && n == points.size())
  {
    polygon = { points };
  }
  return in;
}

struct Triangle
{
  kuznetsov::Point a;
  kuznetsov::Point b;
  kuznetsov::Point c;
};

double countArea(const Triangle& triangle)
{
  double a = (triangle.a.x - triangle.c.x) * (triangle.b.y - triangle.c.y);
  double b = (triangle.b.x - triangle.c.x) * (triangle.a.y - triangle.c.y);
  return 0.5 * std::abs(a - b);
}

struct TriangleProducer
{
  TriangleProducer(const kuznetsov::Polygon& newPolygon) :
    current(1),
    polygon(newPolygon)
  {}

  Triangle operator()();

  size_t current;
  const kuznetsov::Polygon& polygon;
};

Triangle TriangleProducer::operator()()
{
  Triangle triangle{ polygon.points[0], polygon.points[current], polygon.points[current + 1] };
  ++current;
  if (current == polygon.points.size() - 2)
  {
    current = 1;
  }
  return triangle;
}

double kuznetsov::countAreaPolygon(const Polygon& polygon)
{
  TriangleProducer data(polygon);
  std::vector< Triangle > arr(static_cast< int >(polygon.points.size()) - 2);
  std::generate(arr.begin(), arr.end(), data);
  std::vector< double > areas;
  std::transform(arr.begin(), arr.end(), std::back_inserter(areas), countArea);
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return area;
}

double kuznetsov::getAreaOddEven(std::vector< Polygon >& polygon, Pred func)
{
  std::vector< Polygon > sortedPolygon;
  std::copy_if(polygon.begin(), polygon.end(), std::back_inserter(sortedPolygon), func);
  std::vector< double > areasPolygon;
  std::transform(sortedPolygon.begin(), sortedPolygon.end(), std::back_inserter(areasPolygon), countAreaPolygon);
  double area = std::accumulate(areasPolygon.begin(), areasPolygon.end(), 0.0);
  return area;
}

double kuznetsov::getAreaMean(std::vector< Polygon >& polygon)
{
  if (!polygon.size())
  {
    throw std::logic_error("Polygon size < 0");
  }
  std::vector< double > areasPolygon;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areasPolygon), countAreaPolygon);
  double area = std::accumulate(areasPolygon.begin(), areasPolygon.end(), 0.0);
  return area / polygon.size();
}

size_t kuznetsov::getVertexes(const Polygon& polygon)
{
  return polygon.points.size();
}

void kuznetsov::getMinOrMaxArea(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func)
{
  if (polygon.size() == 0)
  {
    throw std::invalid_argument("Size = 0");
  }
  std::vector< double > areasPolygon;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areasPolygon), countAreaPolygon);
  double minOrMax = 0.0;
  if (!func)
  {
    minOrMax = *std::min_element(areasPolygon.begin(), areasPolygon.end());
  }
  else
  {
    minOrMax = *std::max_element(areasPolygon.begin(), areasPolygon.end());
  }
  out << std::fixed << std::setprecision(1) << minOrMax << '\n';
}

void kuznetsov::getMinOrMaxVertexes(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func)
{
  if (polygon.size() == 0)
  {
    throw std::invalid_argument("Size = 0");
  }
  std::vector< size_t > vertexesPolygon;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexesPolygon), getVertexes);
  size_t minOrMax = 0;
  if (!func)
  {
    minOrMax = *std::min_element(vertexesPolygon.begin(), vertexesPolygon.end());
  }
  else
  {
    minOrMax = *std::max_element(vertexesPolygon.begin(), vertexesPolygon.end());
  }
  out << minOrMax << '\n';
}

size_t kuznetsov::countPolygonWithEvenOrOddVertexes(std::vector< Polygon >& polygon, Pred func)
{
  size_t count = std::count_if(polygon.begin(), polygon.end(), func);
  return count;
}
