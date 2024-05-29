#include "shapes.hpp"
#include <istream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>
#include <vector>
#include <Delimiter.hpp>

struct AccumulateArea
{
  artemev::Point p1;
  double operator()(double area, const artemev::Point& second, const artemev::Point& p3);
};

std::istream& artemev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using delChar = artemev::DelimiterCharI;
  int x, y;
  in >> delChar({'('}) >> x >> delChar({';'}) >> y >> delChar({')'});
  if (in)
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

bool artemev::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::istream& artemev::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int countTop;
  in >> countTop;
  if (countTop < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >{ in }, countTop, std::back_inserter(points));

  if (in)
  {
    polygon.points = std::move(points);
  }

  return in;
}

double artemev::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AccumulateArea{ polygon.points.at(1) }, _1, _2, polygon.points.at(0));
  return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, accumulateArea);
}

double countArea(const artemev::Point& p1, const artemev::Point& second, const artemev::Point& p3)
{
  return std::abs((second.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (second.y - p1.y)) / 2;
}

double AccumulateArea::operator()(double area, const artemev::Point& second, const artemev::Point& p3)
{
  area += countArea(p1, second, p3);
  p1 = second;
  return area;
}

struct Triangle
{
  artemev::Point p1;
  artemev::Point p2;
  artemev::Point p3;
};

struct TriangleGen
{
  Triangle cur;
  std::vector< artemev::Point > nextPoints;
  Triangle operator()();
};

Triangle TriangleGen::operator()()
{
  cur.p2 = cur.p3;
  cur.p3 = nextPoints.back();
  nextPoints.pop_back();
  return cur;
};

double calculateAngle(const Triangle& triangle)
{
  double a = std::hypot(triangle.p2.x - triangle.p1.x, triangle.p2.y - triangle.p1.y);
  double b = std::hypot(triangle.p3.x - triangle.p2.x, triangle.p3.y - triangle.p2.y);
  double c = std::hypot(triangle.p1.x - triangle.p3.x, triangle.p1.y - triangle.p3.y);
  return std::acos((a * a + b * b - c * c) / (2 * a * b));
}

bool isRightAngles(double angle)
{
  return std::abs(angle - M_PI / 2) < 0.00001; //dada imenno tak
}

size_t artemev::countRightAngle(const Polygon& polygon)
{
  std::vector< Triangle > triangles;
  triangles.reserve(polygon.points.size() - 2);
  TriangleGen triangle{};
  triangle.nextPoints = polygon.points;
  std::generate_n(std::back_inserter(triangles), polygon.points.size() - 2, triangle);

  std::vector< double > angles;
  angles.reserve(triangles.size());
  std::transform(triangles.begin(), triangles.end(), std::back_inserter(angles), calculateAngle);

  return std::count_if(angles.begin(), angles.end(), isRightAngles);
}
