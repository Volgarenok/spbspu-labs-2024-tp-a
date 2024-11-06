#include "Delimeter.hpp"
#include <cstring>

std::istream & erfurt::operator>>(std::istream & in, Delimeter && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
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
