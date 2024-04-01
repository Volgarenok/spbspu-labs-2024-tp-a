#include "delimiter.hpp"
#include <iostream>
#include <cctype>

std::istream & erohin::operator>>(std::istream & input, Delimiter && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char c = 0;
  input >> c;
  bool isExpected = dest.isCaseSensetive && (c == dest.expected);
  bool isIgnoredCaseExpected = !dest.isCaseSensetive && (tolower(c) == tolower(dest.expected));
  if (input && !(isExpected || isIgnoredCaseExpected))
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
