#include "delimiter.hpp"

std::istream & lebedev::operator>>(std::istream & input, Delimiter && delimiter)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  char temp_symb = 0;
  input >> temp_symb;
  if (std::tolower(temp_symb) != delimiter.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
