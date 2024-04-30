#include "point.hpp"
#include <cmath>
#include <ostream>
#include <delimiterI.hpp>

std::istream& novikov::operator>>(std::istream& in, Point& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point temp{ 0, 0 };
  using del = StrictCaseCharDelimiterI;
  in >> del{ '(' } >> temp.x >> del{ ';' } >> temp.y >> del{ ')' };
  if (in)
  {
    rhs = temp;
  }

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Point& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << rhs.x << ';' << rhs.y << ')';
  return out;
}

bool novikov::operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

double novikov::AreaAccumulator::operator()(double val, const Point& p2, const Point& p3)
{
  val += 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
  p1 = p2;
  return val;
}
