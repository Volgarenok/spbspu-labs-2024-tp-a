#include "delimiters.hpp"
#include <ios>
#include <cctype>

babinov::CharDelimiterI babinov::CharDelimiterI::sensitive(char exp)
{
  return babinov::CharDelimiterI(exp, true);
}

babinov::CharDelimiterI babinov::CharDelimiterI::insensitive(char exp)
{
  return babinov::CharDelimiterI(exp, false);
}

babinov::StringDelimiterI babinov::StringDelimiterI::sensitive(const char* exp)
{
  return babinov::StringDelimiterI(exp, true);
}

babinov::StringDelimiterI babinov::StringDelimiterI::insensitive(const char* exp)
{
  return babinov::StringDelimiterI(exp, false);
}

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
    if (del.caseSensitive)
    {
      in >> CharDelimiterI::sensitive(*expected);
    }
    else
    {
      in >> CharDelimiterI::insensitive(*expected);
    }
    ++expected;
  }
  return in;
}
