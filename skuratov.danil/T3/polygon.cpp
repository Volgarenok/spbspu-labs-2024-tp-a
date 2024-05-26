#include "polygon.hpp"
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

std::istream& skuratov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t verticesNumb = {};
  in >> verticesNumb;

  std::vector< Point > pos;
  using inputItT = std::istream_iterator< Point >;
  std::copy_n(inputItT{ in }, verticesNumb, std::back_inserter(pos));

  if (pos.size() == verticesNumb)
  {
    polygon.points = pos;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

double skuratov::CalculateArea::operator()(double res, const Point& point3)
{
  res = 0.5 * (std::abs((point1.x - point3.x) * (point2.y - point3.y) - (point2.x - point3.x) * (point1.y - point3.y)));
  point2 = point3;
  return res;
}

double skuratov::Polygon::getArea() const
{
  CalculateArea calcArea{ points[0], points[1] };
  return std::accumulate(points.begin(), points.end(), 0.0, calcArea);
}

bool skuratov::CalculateCorners::operator()(const Point& point3)
{
  Point side1 = { point2.x - point1.x, point2.y - point1.y };
  Point side2 = { point3.x - point1.x, point3.y - point1.y };

  point1 = point2;
  point2 = point3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}

int skuratov::Polygon::getCorners() const
{
  CalculateCorners calcCorners{ points[points.size() - 2], points[points.size() - 1] };
  return std::count_if(points.begin(), points.end(), calcCorners);
}
