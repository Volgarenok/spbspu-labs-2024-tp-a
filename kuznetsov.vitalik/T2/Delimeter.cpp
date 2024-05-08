#include "Delimeter.hpp"

std::istream& kuznetsov::operator>>(std::istream& in, DelimeterChar&& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char symbol = 0;
  in >> symbol;
  if (std::isalpha(symbol))
  {
    symbol = std::tolower(symbol);
  }
  if (symbol != data.symbol)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& kuznetsov::operator>>(std::istream& in, DelimeterString&& data)
{
  size_t i = 0;
  while (data.line[i] != '\0')
  {
    in >> DelimeterChar{ data.line[i] };
    ++i;
  }
  return in;
}
