#include "delimiter.hpp"
#include <istream>

std::istream& zaitsev::operator>>(std::istream& in, const CharDelimiter&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
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
