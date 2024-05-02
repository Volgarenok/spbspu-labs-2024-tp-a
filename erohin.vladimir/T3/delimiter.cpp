#include "delimiter.hpp"
#include <iostream>

std::istream & erohin::operator>>(std::istream & input, Delimiter && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char c = 0;
  input >> c;
  if (input && c != dest.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
