#include "delimiter.hpp"

#include <cstring>
#include <iostream>

std::istream &zagrivnyy::operator>>(std::istream &in, DelimiterI &&exp)
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
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }

  return in;
}
