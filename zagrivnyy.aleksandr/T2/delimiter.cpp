#include "delimiter.hpp"

#include <iostream>

std::istream &zagrivnyy::operator>>(std::istream &in, DelimiterI &&exp)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;

  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
