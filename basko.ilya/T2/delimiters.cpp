#include "delimiters.h"

std::istream& basko::operator>>(std::istream& in, DelimiterChar&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  c = std::tolower(c);
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
