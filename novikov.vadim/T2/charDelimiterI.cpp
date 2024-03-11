#include "charDelimiterI.hpp"
#include <cctype>

std::istream& novikov::operator>>(std::istream& in, const CharDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char ch = '\0';
  in >> ch;
  if (ch != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& novikov::operator>>(std::istream& in, const IgnoreCaseCharDelimiterI& exp)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char ch = '\0';
  in >> ch;
  if (std::isalpha(ch) && std::isalpha(exp.expected))
  {
    if (std::tolower(ch) != std::tolower(exp.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else if (ch != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
