#include "delimiters.hpp"
#include <ios>
#include <cctype>

std::istream& babinov::operator>>(std::istream& in, CharDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if ((!del.caseSensitive) && (std::isalpha(c)))
  {
    c = std::tolower(c);
  }
  if (c != del.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& babinov::operator>>(std::istream& in, StringDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  const char* expected = del.expected;
  while ((*expected != '\0') && in)
  {
    in >> CharDelimiterI(*expected, del.caseSensitive);
    ++expected;
  }
  return in;
}
