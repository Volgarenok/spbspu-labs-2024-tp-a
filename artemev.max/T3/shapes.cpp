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
  cur.p1 = cur.p2;
  cur.p2 = cur.p3;
  cur.p3 = nextPoints.back();
  nextPoints.pop_back();
  return cur;
};

double calculateAngle(const Triangle& triangle)
{
  double a = std::pow(triangle.p2.x - triangle.p1.x, 2) + std::pow(triangle.p2.y - triangle.p1.y, 2);
  double b = std::pow(triangle.p3.x - triangle.p2.x, 2) + std::pow(triangle.p3.y - triangle.p2.y, 2);
  double c = std::pow(triangle.p1.x - triangle.p3.x, 2) + std::pow(triangle.p1.y - triangle.p3.y, 2);
  return a + b - c;
}

bool isRightAngles(double angle)
{
  return angle == 0;
}

size_t artemev::countRightAngle(const Polygon& polygon)
{
  std::vector< Triangle > triangles;
  triangles.reserve(polygon.points.size());
  TriangleGen triangle{};
  triangle.cur = Triangle{polygon.points[0], polygon.points[1], polygon.points[2]};
  triangle.nextPoints = std::vector< Point >(polygon.points.begin() + 3, polygon.points.end());
  std::reverse(triangle.nextPoints.begin(), triangle.nextPoints.end());
  triangles.push_back(Triangle({ polygon.points[0], polygon.points[1], polygon.points[2] }));
  std::generate_n(std::back_inserter(triangles), polygon.points.size() - 3, triangle);
  triangles.push_back(Triangle({ *(----polygon.points.end()), polygon.points.back(), polygon.points[0] }));
  triangles.push_back(Triangle({ polygon.points.back(), polygon.points[0], polygon.points[1] }));

  std::vector< double > angles(triangles.size());
  std::transform(triangles.cbegin(), triangles.cend(), angles.begin(), calculateAngle);
  return std::count_if(angles.begin(), angles.end(), isRightAngles);
}
