#include "delimiter.hpp"
#include <string>
#include <istream>
#include "streamGuard.hpp"


std::istream& altun::operator>>(std::istream& in, Delimiter&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard s_guard(in);
  char c = 0;
  in >> c;
  if (c != del.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
