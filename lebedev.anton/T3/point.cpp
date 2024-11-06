#include "point.hpp"
#include <delimiter.hpp>

std::istream & lebedev::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Point temp_point = { 0, 0 };
  input >> Delimiter{ '(' } >> temp_point.x >> Delimiter{ ';' } >> temp_point.y >> Delimiter{ ')' };
  if (input)
  {
    point = temp_point;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

bool lebedev::operator<(const Point & p1, const Point & p2)
{
  return (p1.x < p2.x) && (p1.y < p2.y);
}

double lebedev::getX(const Point & point)
{
  return point.x;
}
double lebedev::getY(const Point & point)
{
  return point.y;
}
