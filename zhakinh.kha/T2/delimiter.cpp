#include "delimiter.hpp"
#include "streamGuard.hpp"
#include <iostream>

std::istream& zhakha::operator>>(std::istream& in, const Delimiter& d)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  char c = 0;
  in >> c;
  if (std::isalpha(c))
  {
    c = std::tolower(c);
  }
  else if (c != d.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
