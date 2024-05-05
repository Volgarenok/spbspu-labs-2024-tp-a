#include "delimiter.hpp"

#include <streamGuard.hpp>

std::istream& ibragimov::detail::operator>>(std::istream& in, Delimiter&& rhs)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard sguard(in);
  char c = '0';
  in >> c;
  if ((in) && (c != rhs.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
