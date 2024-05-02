#include "polygon.hpp"
#include <iostream>

std::istream & erohin::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char c = 0;
  input >> c >> point.x >> c >> point.y >> c;
  return input;
}
