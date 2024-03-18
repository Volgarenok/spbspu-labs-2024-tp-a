#include "delimeter.hpp"

std::istream& zakozhurnikova::operator>>(std::istream& in, const CharDelimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.val)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
