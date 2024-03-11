#include "delimiters.hpp"
#include <ios>
#include <cctype>

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

std::istream& babinov::operator>>(std::istream& in, CharCaseDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    char c = 0;
    in >> c;
    if (std::isalpha(c))
    {
      c = std::tolower(c);
    }
    if (c != del.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::istream& babinov::operator>>(std::istream& in, StringCaseDelimiterI&& del)
{
  std::istream::sentry sentry(in);
  if (sentry)
  {
    const char* expected = del.expected;
    while ((*expected != '\0') && in)
    {
      in >> CharCaseDelimiterI{*expected};
      ++expected;
    }
  }
  return in;
}
