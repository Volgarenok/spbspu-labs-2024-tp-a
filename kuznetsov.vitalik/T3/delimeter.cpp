#include "delimeter.hpp"

std::istream& kuznetsov::operator>>(std::istream& in, DelimeterChar&& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char symbol = 0;
  in >> symbol;
  if (isalpha(symbol))
  {
    symbol = tolower(symbol);
  }
  if (symbol != data.symbol)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

