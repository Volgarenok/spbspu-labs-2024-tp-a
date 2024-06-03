#include "delimiter.hpp"
#include <istream>

std::istream & sakovskaia::operator>>(std::istream & input, Delimiter && exp)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  char c = 0;
  input >> c;
  if (c != exp.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
