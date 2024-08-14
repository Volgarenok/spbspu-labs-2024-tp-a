#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& zhakha::operator>>(std::istream& in, const Delimiter& exp)
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
  else if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
