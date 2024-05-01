#include "Shapes.hpp"
#include <iostream>
#include "DelimiterI.hpp"

double kuzmina::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto countArea = std::bind(CountArea{ points[1] }, _1, _2, points[0]);

  return std::accumulate(points.begin(), points.end(), 0.0, countArea);
}

double kuzmina::CountArea::operator()(double area, const Point& point2, const Point& point3)
{
  area += 0.5 * std::abs((point3.x - point1.x) * (point2.y - point1.y) - (point2.x - point1.x) * (point3.y - point1.y));
  point1 = point2;

  return area;
}

std::istream& kuzmina::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int tempX = 0, tempY = 0;

  in >> DelimiterI{ '(' } >> tempX >> DelimiterI{ ';' } >> tempY >> DelimiterI{ ')' };

  if (in)
  {
    point.x = tempX;
    point.y = tempY;
  }

  return in;
}

std::ostream& kuzmina::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << '(' << point.x << ';' << point.y << ')';

  return out;
}

std::istream& kuzmina::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int numberOfPoints = 0;
  in >> numberOfPoints;

  if (numberOfPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  using input_it_t = std::istream_iterator< Point >;

  std::vector< Point > tempPoints;
  std::copy_n(input_it_t{ in }, numberOfPoints, std::back_inserter(tempPoints));

  if (in)
  {
    polygon.points = tempPoints;
  }

  return in;
}

std::ostream& kuzmina::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  using output_it_t = std::ostream_iterator< Point >;

  out << polygon.points.size() << ' ';
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_it_t{ out, " " });

  return out;
}
