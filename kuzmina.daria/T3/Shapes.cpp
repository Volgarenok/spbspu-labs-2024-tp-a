#include "Shapes.hpp"
#include <iostream>
#include "DelimiterI.hpp"

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

  int numberOfPoints = 0;
  in >> numberOfPoints;

  if (numberOfPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  using input_it_t = std::istream_iterator< Point >;

  std::vector< Point > tempPoints;

  for (int i = 0; i < numberOfPoints; ++i)
  {
    Point p = {};
    in >> p;

    if (in)
    {
      tempPoints.push_back(p);
    }
  }

  if (in)
  {
    polygon.points = tempPoints;
  }

  return in;
}
