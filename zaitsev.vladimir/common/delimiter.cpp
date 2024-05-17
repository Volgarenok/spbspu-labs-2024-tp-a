#include "delimiter.hpp"
#include <istream>

std::istream& zaitsev::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; exp.expected[i] && in; ++i)
  {
    char c = '0';
    in >> c;
    c = std::tolower(c);
    if (c != exp.expected[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
