#include "point.hpp"
#include "delimeter.hpp"

std::istream& zaparin::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using del = Delimeter;

  int x = 0, y = 0;
  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };

  if (in)
  {
    point = Point{ x, y };
  }

  return in;
}

std::ostream& zaparin::operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

bool zaparin::operator==(const Point& p1, const Point& p2)
{
  if ((p1.x == p2.x) && (p1.y == p2.y))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

double zaparin::getLength(const Point& p1, const Point& p2)
{
  return (std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

