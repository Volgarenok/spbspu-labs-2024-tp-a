#include "Delimiter.hpp"
#include <cctype>

std::istream& chernikova::operator>>(std::istream& in, DelimiterI&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  bool isLowerCase = (!exp.upperСase) && (c != exp.expected);
  bool isRightCondition = isLowerCase || (std::tolower(c) != std::tolower(exp.expected));
  if (isRightCondition)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& chernikova::operator>>(std::istream& in, StringDelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (const char* i = dest.exp; (*i != '\0') && in; ++i)
  {
    in >> DelimiterI{*i};
  }
  return in;
}
