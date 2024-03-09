#include "delimiters.hpp"
#include <ios>

std::istream& babinov::operator>>(std::istream& in, CharDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    char c = 0;
    in >> c;
    if (c != del.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& babinov::operator>>(std::istream& in, StringDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    const char* expected = del.expected;
    while ((*expected != '\0') && in)
    {
      in >> CharDelimiterI{*expected};
      ++expected;
    }
  }
  return in;
}
