#include "polygon.hpp"
#include "geometryFunc.hpp"
#include <delimiter.hpp>

std::istream& skuratov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point pos = {};

  in >> del{ '(' } >> pos.x >> del{ ';' } >> pos.y >> del{ ')' };
  if (in)
  {
    point = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t verticesNumb = {};
  in >> verticesNumb;

  if (verticesNumb < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > pos;
  using inputItT = std::istream_iterator< Point >;
  std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(pos));

  if (pos.size() == verticesNumb)
  {
    poly.points = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

double skuratov::CalculateArea::operator()(double res, const Point& point3)
{
  res += 0.5 * (std::abs((point1.x - point3.x) * (point2.y - point3.y) - (point2.x - point3.x) * (point1.y - point3.y)));
  point2 = point3;
  return res;
}

double skuratov::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto calcArea = std::bind(CalculateArea{ points[0], points[1] }, _1, _2);
  return std::accumulate(std::next(points.begin()), points.end(), 0.0, calcArea);
}

bool skuratov::CalcRightCorner::operator()(const Point& point3)
{
  Point side1 = { point2.x - point1.x, point2.y - point1.y };
  Point side2 = { point3.x - point1.x, point3.y - point1.y };

  point1 = point2;
  point2 = point3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}

size_t skuratov::Polygon::getCorners() const
{
  if (points.size() < 3)
  {
    return 0;
  }
  auto calcCorner = CalcRightCorner{ points[points.size() - 1], points[points.size() - 2] };
  return std::find_if(points.cbegin(), points.cend(), calcCorner) != points.cend();
}

bool skuratov::operator<=(const Polygon& lhs, const Polygon& rhs)
{
  int lhsMinX = findMinX(lhs);
  int lhsMinY = findMinY(lhs);
  int lhsMaxX = findMaxX(lhs);
  int lhsMaxY = findMaxY(lhs);

  int rhsMinX = findMinX(rhs);
  int rhsMinY = findMinY(rhs);
  int rhsMaxX = findMaxX(rhs);
  int rhsMaxY = findMaxY(rhs);

  return (lhsMinX >= rhsMinX) && (lhsMaxX <= rhsMaxX) && (lhsMinY >= rhsMinY) && (lhsMaxY <= rhsMaxY);
}
