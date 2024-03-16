#include <fstream>
#include "data_struct.hpp"

std::istream& nikitov::operator>>(std::istream& input, Delimiter delimiter)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  char c = 0;
  input >> c;
  if (c != delimiter.expected)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}