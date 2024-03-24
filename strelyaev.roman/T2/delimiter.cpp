#include "delimiter.hpp"
#include <istream>

std::istream& strelyaev::operator>>(std::istream&& in, const delimiter&& delimiter)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c!= delimiter.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
