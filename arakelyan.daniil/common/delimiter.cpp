#include "delimiter.hpp"

#include <iostream>

#include "inFormatters.hpp"

std::istream &arakelyan::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
