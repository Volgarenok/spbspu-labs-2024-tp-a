#include "Delimeter.hpp"

#include <cstring>

std::istream &erfurt::operator>>(std::istream &in, Delimeter &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  for (size_t i = 0; exp.expected[i] && in; ++i)
  {
    in >> c;
    c = tolower(c);
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
