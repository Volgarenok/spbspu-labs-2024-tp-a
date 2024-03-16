#include <fstream>
#include "delimiter.hpp"

std::istream& nikitov::operator>>(std::istream& input, DelimiterString delimiter)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    size_t i = 0;
    while (delimiter.expected[i] != '\0')
    {
      char c = 0;
      input >> c;
      if (c != delimiter.expected[i++])
      {
        input.setstate(std::ios::failbit);
        break;
      }
    }
  }
  return input;
}

std::istream& nikitov::operator>>(std::istream& input, DelimiterChar delimiter)
{
  std::istream::sentry guard(input);
  if (guard)
  {
    char c = 0;
    input >> c;
    if (c != delimiter.expected)
    {
      input.setstate(std::ios::failbit);
    }
  }
  return input;
}