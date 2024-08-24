#include "delimiter.hpp"
#include <cstring>
#include <string>

std::istream & kozlova::operator>>(std::istream & in, DelimiterCharIO && del) {
  std::istream::sentry guard(in);
  if (!guard)
  {
      return in;
  }
  char c = '0';
  in >> c;
  c = std::tolower(c);
  if (in && (c != del.delimiter))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & kozlova::operator>>(std::istream & in, DelimiterStringIO && del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
      return in;
  }
  for (size_t i = 0; del.delimiter[i] && in; ++i)
  {
    char c = '0';
    in >> c;
    if (c != del.delimiter[i])
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
