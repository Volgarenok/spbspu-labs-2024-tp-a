#include "point.hpp"
#include <cmath>
#include <delimeter.hpp>

std::istream& zaparin::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  Point temp{ 0, 0 };
  in >> del{ "(" } >> temp.x >> del{ ";" } >> temp.y >> del{ ")" };

  if (in)
  {
    point = temp;
  }

  return in;
}

bool zaparin::operator==(const Point& p1, const Point& p2)
{
  return ((p1.x == p2.x) && (p1.y == p2.y));
}

bool zaparin::operator<(const Point& p1, const Point& p2)
{
  return ((p1.x <= p2.x) && (p1.y <= p2.y));
}

bool zaparin::operator<=(const Point& p1, const Point& p2)
{
  return ((p1.x <= p2.x) && (p1.y <= p2.y));
}

bool zaparin::operator>=(const Point& p1, const Point& p2)
{
  return ((p1.x >= p2.x) && (p1.y >= p2.y));
}

double zaparin::getLength(const Point& p1, const Point& p2)
{
  return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

