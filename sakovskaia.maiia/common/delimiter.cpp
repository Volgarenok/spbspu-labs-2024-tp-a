#include "delimiter.hpp"
#include <string>
#include <istream>

std::istream & sakovskaia::operator>>(std::istream & input, Delimiter && exp)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  char c = 0;
  for (size_t i = 0; exp.expected[i] != '\0'; i++)
  {
    input >> c;
    if (c != exp.expected[i])
    {
      input.setstate(std::ios::failbit);
    }
  }
  return input;
}
