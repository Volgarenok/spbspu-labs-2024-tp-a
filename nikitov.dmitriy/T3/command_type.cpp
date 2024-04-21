#include "command_type.hpp"
#include <istream>
#include <string>

std::istream& nikitov::operator>>(std::istream& input, CommandType& value)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  std::getline(input, value.line);

  return input;
}
