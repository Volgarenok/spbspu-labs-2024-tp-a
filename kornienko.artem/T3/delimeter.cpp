#include "delimeter.hpp"

std::istream & kornienko::operator>>(std::istream & in, const Delimeter && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (std::tolower(c) != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
