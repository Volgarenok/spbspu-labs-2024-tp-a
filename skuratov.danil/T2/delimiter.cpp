#include "delimiter.hpp"

std::istream& skuratov::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& skuratov::operator>>(std::istream& in, const LineDelimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    in >> Delimiter{ exp.expected[i] };
    ++i;
  }
  return in;
}
