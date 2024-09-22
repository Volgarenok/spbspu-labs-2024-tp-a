#include "Delimiter.hpp"


std::istream & kovtun::operator>>(std::istream & in, kovtun::DelimiterI && delimiter)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  char c = 0;
  in >> c;
  if (c != delimiter.expected)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}
