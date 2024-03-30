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
  if (dest.isCaseSensetive)
  {
    if (input && (c != dest.expected))
    {
      input.setstate(std::ios::failbit);
    }
  }
  else
  {
    if (input && (tolower(c) != tolower(dest.expected)))
    {
      input.setstate(std::ios::failbit);
    }
  }
  return input;
}
