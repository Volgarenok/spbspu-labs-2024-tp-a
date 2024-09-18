#include "point.hpp"
#include <iostream>
#include <delimeter.hpp>

std::istream& vyzhanov::operator>>(std::istream& input, Point& point)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using del = Delimeter;
  Point tmp;
  input >> del{ '(' } >> tmp.x >> del{ ';' } >> tmp.y >> del{ ')' };
  if (input)
  {
    point = tmp;
  }
  return input;
}

std::ostream& vyzhanov::operator<<(std::ostream& output, const Point& point)
{
  output << '(' << point.x << ';' << point.y << ')';
  return output;
}

bool vyzhanov::operator==(const Point& first, const Point& second)
{
  return (first.x == second.x) && (first.y == second.y);
}
