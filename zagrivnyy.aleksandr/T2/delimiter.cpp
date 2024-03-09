#include "delimiter.hpp"

#include <cstring>
#include <iostream>

zagrivnyy::DelimiterI::DelimiterI(const char *expected): expected(expected)
{
  this->size = std::strlen(expected);
}

std::istream &zagrivnyy::operator>>(std::istream &in, DelimiterI &&exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  for (size_t i = 0; (i < exp.length()) && in; ++i)
  {
    in >> c;
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }

  return in;
}
