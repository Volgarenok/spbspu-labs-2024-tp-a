#include "Shapes.hpp"
#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <DelimiterI.hpp>

bool kuzmina::comparePoints(const Point& point1, const Point& point2)
{
  return (point1.x == point2.x) && (point1.y == point2.y);
}

bool kuzmina::comparePolygonPointsSize(const Polygon& polygon1, const Polygon& polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

double kuzmina::getArea(const Polygon& polygon)
{
  using namespace std::placeholders;
  auto countArea = std::bind(CountArea{ polygon.points[1] }, _1, _2, polygon.points[0]);

  return std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0, countArea);
}

double kuzmina::CountArea::operator()(double area, const Point& point2, const Point& point3)
{
  area += 0.5 * std::abs((point3.x - point1.x) * (point2.y - point1.y) - (point2.x - point1.x) * (point3.y - point1.y));
  point1 = point2;

  return area;
}

bool kuzmina::Polygon::hasRightAngle() const
{
  auto countAngle = CountAngle{ points[points.size() - 1], points[points.size() - 2] };

  return std::find_if(points.cbegin(), points.cend(), countAngle) != points.cend();
}

bool kuzmina::CountAngle::operator()(const Point& point3)
{
  Point side1 = { point2.x - point1.x, point2.y - point1.y };
  Point side2 = { point3.x - point1.x, point3.y - point1.y };

  point1 = point2;
  point2 = point3;

  return side1.x * side2.x + side1.y * side2.y == 0;
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

std::istream& kuzmina::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t numberOfPoints = 0;
  in >> numberOfPoints;

  if (numberOfPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > tempPoints;
  tempPoints.reserve(numberOfPoints);

  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, numberOfPoints, std::back_inserter(tempPoints));

  if (!in || tempPoints.size() != numberOfPoints)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    polygon.points = tempPoints;
  }

  return in;
}
