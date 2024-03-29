#include "delimiter.hpp"
#include <istream>

std::istream & sakovskaia::operator>>(std::istream & input, delimiter_t && exp)
{
  std::istream::sentry guard(input);
  char c = 0;
  input >> c;
  if (c != exp.expected)
  {
    input.setstate(std::ios::failbit);
  }
  else
  {
    return input;
  }
}
