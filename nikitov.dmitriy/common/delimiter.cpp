#include "delimiter.hpp"
#include <istream>

std::istream& nikitov::operator>>(std::istream& input, DelimiterString&& delimiter)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  size_t i = 0;
  while (delimiter.expected[i] != '\0')
  {
    input >> DelimiterChar({delimiter.expected[i++]});
  }
  return input;
}

std::istream& nikitov::operator>>(std::istream& input, DelimiterChar&& delimiter)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  char c = {};
  input >> c;
  if (c != delimiter.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
